#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 20

enum {IN, OUT, AND, OR, NOT, FF}; //the last one is flipflop

typedef struct gate {
    int type; // type of the gate
    char name[MAX_NAME_LEN]; // name of the gate
    struct gate* inp1; // points to input gate1
    struct gate* inp2; // points to input gate2
    int output; // stores the current output. this may be useful if the gate is connected to more than one gate.
    int former_out; // only for flipflop. -1 by default
} gate_t;

void createGate(gate_t**, char*, char*); // allocates memory for gate, initializes and fill all values of it
void setDeafultFF(gate_t**, int); //sets former outputs to -1, unless the former out is 1
void connectGates(gate_t**, char*, char*); //connects two gate
void takeInputsAndEvaluate(gate_t**, int, int); //assigns inputs to output variables of input gates
int evaluate(gate_t*); //evaluates the circuit

int main() 
{
    FILE* reader = NULL;
    gate_t** gates = NULL;
    int nOg = 0, nOi = 0; //number of gates, num of inputs
    char line[2 * MAX_NAME_LEN + 13], lineType[12], name1[MAX_NAME_LEN], name2[MAX_NAME_LEN]; //line, line type, gate1 name, gate2 name

    reader = fopen("circuit.txt", "r");

    if (reader == NULL) 
    {
        printf("dosya nerde?!! bb!");
        return 1;
    }
    
    while (fgets(line, sizeof(line), reader)) 
    {
        if(line[0] == 'G') nOg++; //count number of gates
        if(line[5] == 'I') nOi++; //increment the counter of input gates
    }
    
    gates = (gate_t**)calloc((nOg+1), sizeof(gate_t*)); //create gates array
    
    for (fseek(reader, 0, SEEK_SET); fgets(line, sizeof(line), reader);) //take file pointer to beginning of the file, read to EOF, increment index
    {
        sscanf(line, "%s %s %s", lineType, name1, name2);

        if (lineType[0] == 'G') createGate(gates, name1, name2); //if line defines a gate, create a gate and point it with gate[i], assign type of gate
        else connectGates(gates, name2, name1);
    }

    fclose(reader);
    
    takeInputsAndEvaluate(gates, nOg, nOi); 

    for(int i = 0; i < nOg; i++) free(gates[i]); //free rows
    free(gates); 

    return 0;
}

void createGate(gate_t** gates, char* type, char* name) 
{
    int i = 0;
    while(gates[i] != NULL) i++; //find the end of the array
    
    gates[i] = (gate_t*)malloc(sizeof(gate_t)); //allocate memory for the new gate and assign that memory to current gate pointer

    //---------------take type---------------
        if (type[0] == 'O') // if the first letter is o, type can be OR or OUTPUT
        {
            if (type[1] == 'U') gates[i]->type = OUT;
            else if (type[1] == 'R') gates[i]->type = OR;
        } 
        
        else if (type[0] == 'A') gates[i]->type = AND; 
        else if (type[0] == 'N') gates[i]->type = NOT;
        else if (type[0] == 'F') gates[i]->type = FF; 
        else if (type[0] == 'I') gates[i]->type = IN;
    //------end of taking type---------------

    //---------------take name---------------
        strcpy(gates[i]->name, name);
    //------end of taking name---------------

    //---------------initialize other variables---------------
        gates[i]->output = -1; //set output as -1 to indicate that the gate is not processed before
        gates[i]->former_out = 0;
        gates[i]->inp1 = NULL;
        gates[i]->inp2 = NULL;
    //---------------end of initializing----------------------
}

void connectGates(gate_t** gates, char* parent, char* child)
{
    gate_t* childGate = NULL;
    gate_t* parentGate = NULL;
    
    int i;
    for (i = 0; gates[i] != NULL; ++i)  //locate the child node
    {
        if (!strcmp(gates[i]->name, child))
        {
            childGate = gates[i];
            break;
        }
    }

    for (i = 0; gates[i] != NULL; ++i)  //locate the parent node
    {
        if (!strcmp(gates[i]->name, parent))
        {
            parentGate = gates[i];
            break;
        }
    } 
    
    if (childGate != NULL && parentGate != NULL)
    {
        if (parentGate->inp1 != NULL && (parentGate->type == FF || parentGate->type == NOT)) //if type is FLIPFLOP or NOT and trying to connect some node to inp2
        {
            printf("FLIPFLOP or NOT gate can not take more than one input.\n"); //print error message and return
            return;   
        }
        
        else if (parentGate->inp1 == NULL)    parentGate->inp1 = childGate;  //if inp1 is empty, link parent to child
        else if (parentGate->inp2 == NULL)    parentGate->inp2 = childGate;  //if inp2 is empty, link parent to child 
        else printf("Gate %s already have 2 inputs.\n", parentGate->name);
    }
    
    else //if childGate or parentGate are not located print error message
    {
        if(childGate == NULL)
        {
            printf("childGate is NULL. exiting...\n");
            exit(0);
        }

        else if(parentGate == NULL)
        {
            printf("parentGate is NULL. exiting...\n");
            exit(0);
        }
    } 
}

void takeInputsAndEvaluate(gate_t** gates, int nOg, int nOi)
{
    FILE *reader = NULL;
    int i, j, output; //loop counters, result of the circuit

    reader = fopen("input.txt", "r");

    if (reader == NULL) 
    {
        printf("input.txt is could not been opened. exiting...\n");
        exit(0);
    }

//locate the root(which is output gate)
    gate_t *root = NULL;  
    if(gates[nOg-1]->type == OUT) root = gates[nOg-1]; //if it is the last defined gate, assign root as the last gate
    else //else, look for the output gate and locate it
    {
        for (i = 0; i < nOg; ++i) 
        {
            if (gates[i]->type == OUT) //find the output gate
            {
                root = gates[i];
                break;
            }
        }
    }
//the root is located    

    char* inpLine = (char*)malloc((nOi+2) * sizeof(char)); //create an array to hold inputs. created dynamically because num of inputs is not known at first

    if(inpLine == NULL)
    {
        printf("inputs array could not been allocated. exiting...\n");
        exit(0);
    }

    while(fgets(inpLine, sizeof(inpLine), reader)) //take each line to inpLine
    {
        for(i = 0, j = 0; inpLine[i] != '\n' && gates[j] != NULL; j++)
        {
            if (gates[j]->type == IN) //if type of gate is INPUT, then take inputs from input.txt into the gate
            {
                gates[j]->output = inpLine[i] - '0';
                i++;
            }
        }
        output = evaluate(root->inp1);
        printf("%d\n", output);
        setDeafultFF(gates, nOg);
    }
    
    free(inpLine);
    fclose(reader);
}

int evaluate(gate_t* g)
{
    int inp1;

    if(g->type == IN) return g->output; //base case

    else
    {
        if(g->output != -1) //if output is not -1, that means this flip flop is processed before, so return the former output without evaluating the rest of the circuit
        {
            return g->former_out;
        }
        
        else if(g->type == FF)
        {
            inp1 = evaluate(g->inp1); //assign inp1
                
            if(g->former_out) //if former output is 1, update former output and output then return !inp
            {
                g->output = g->former_out = !inp1;
                return !inp1;
            }
                
            else //if former output is 0, update former output then return inp1 as it is
            {
                g->output = g->former_out = inp1;
                return inp1;
            }   
            
        }

        else
        {
            int inp2;

            inp1 = evaluate(g->inp1); //find the value of inp1 by evaluating the rest of the circuit recursively

            if(g->inp2 != NULL) inp2 = evaluate(g->inp2);
            else inp2 = 0; //if inp2 does not point to anything, set it to 0 to it do not cause any problem

            if(g->type == AND)
            {
                g->output = g->former_out = inp1 && inp2; //update output and former output 
                return g->output;
            }
             
            else if(g->type == OR)
            {
                g->output = g->former_out = inp1 || inp2;
                return g->output;
            }

            else if(g->type == NOT)
            {
                g->output = g->former_out = !inp1;
                return g->output;
            }
        }
    }
}

void setDeafultFF(gate_t** gates, int nOg)
{
    for(int i = 0; i < nOg; i++) 
    {
        if(gates[i]->type != IN) gates[i]->output = -1; //set outputs to -1 to indicate all gates are not processed before
    }
}