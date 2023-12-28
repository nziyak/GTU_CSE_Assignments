#include <stdio.h>
#include <string.h>

#define CARB_CAL_1G 4 /* Number of calories in 1g carbohydrate */
#define PROTEIN_CAL_1G 4 /* Number of calories in 1g protein */
#define FAT_CAL_1G 9 /* Number of calories in 1g fat */
#define WATER_CAL_1G 0 /* Number of calories in 1g water */
#define INGNUM 20 //number of (sub)ingredients
#define INGLEN 30 //length of a (sub)ingredient
#define LINECHARNUM (INGNUM*INGLEN+100) //number of characters at a line

typedef struct{
    double carbP,
           fatP,
           proP;
}percT;

typedef struct{
    double carbC,
           fatC,
           proC,
           totalMass;
}calT;

int isBase(char*); //checks if the ingredient is base case or not
void extractName(char*, int); //extract the name of ingredient (get rid of parenthesis and the number of inside of them)
double getAmount(const char*, int); //takes the amount of ingredient in the parenthesis
void getAndParse(char (*)[INGLEN], int*); //gets ingredients with separated by comma and parses them. then assigns to elements of 2D char array "parts"
int myStrLen(const char*); //calculates and returns string length
void mainJr(char*, calT*, percT*); //recursive function
void removeSpace(char*); //removes spaces in each ingredient string

int main()
{
    char mealName[30];
    calT cals;
    percT percs;

    printf("What is the meal?:\n");
    scanf("%s", mealName);
    fflush(stdin);
    
    cals.totalMass = 0;

    mainJr(mealName, &cals, &percs);

    printf("Total calories is %lf in %lfg %s. %%%lf calories from carbs, %%%lf from proteins, %%%lf from fats.", 
                                                                     (cals.carbC + cals.fatC + cals.proC),
                                                                      cals.totalMass,
                                                                      mealName,
                                                                      percs.carbP,
                                                                      percs.proP,
                                                                      percs.fatP);
    return 0;
}

void mainJr(char* name, calT* calP, percT* percP)
{
    percT percs; //a local struct that will hold the percentages
    char macros[50];
    int nameLen = myStrLen(name);

    if(isBase(name)) //if the element is base(leaf) element
    { 
        extractName(name, nameLen); //extract name. from butter(50g) to butter

        nameLen = myStrLen(name); //calculate the name length again because after the extraction it changed

        double amount = getAmount(name, nameLen); //get amount. from butter(50g) to 50
        calP->totalMass += amount; //add the mass of the ingredient to total mass

        do{
            
            printf("List the amount macro nutrients in %s:\n", name);
            fgets(macros, sizeof(macros), stdin);
            sscanf(macros, "%lf%lf%lf", &percs.carbP, &percs.proP, &percs.fatP);

            if((percs.carbP + percs.proP + percs.fatP) > 100) printf("sum of the percentages is greater than 100. please enter again.\n");
        
        }while((percs.carbP + percs.proP + percs.fatP) > 100);

        //calculate total percentages and assign to struct
        percP->carbP += percs.carbP;
        percP->proP += percs.proP;
        percP->fatP += percs.fatP;

        //calculate total calories and assign to struct
        calP->carbC += (amount * percs.carbP)/100 * CARB_CAL_1G;
        calP->proC += (amount * percs.proP)/100 * PROTEIN_CAL_1G;
        calP->fatC += (amount * percs.fatP)/100 * FAT_CAL_1G;
    }

    else //if the element has sub-components
    {
        int nOP; // num of parts
        char parts[INGNUM][INGLEN];
        
        printf("What is %s?:\n", name);
        getAndParse(parts, &nOP); //get sub-components and parse them

        for(int i = 0; i < nOP; i++) //make recursive calls for every sub-component
        {
            mainJr(parts[i], calP, percP);
        }
    }
}

int isBase(char* name) //name with parenthesis
{ 
    //look for parenthesis
    for(char* findP = name; *findP != '\0'; findP++)
    {
        if( (*findP) == '(' ) return 1; //if there is parenthesis after the word, it is the base case
    }
        
    return 0;
}

void extractName(char* name, int nameLen)
{
    int i;
    
    for(i = 0; i < nameLen; i++) //look for parenthesis
    {
        if( (name[i]) == '(' ) break;
    }
    
    name[i] = '\0';
}

int myStrLen(const char* name)
{
    int i;
    for(i = 0; name[i] != '\0'; i++){}
    return i;
}

double getAmount(const char* name, int nameLen)
{
    double amount;
    int i;
    
    //look for parenthesis
    for(i = 0; i < nameLen; i++)
    {
        if( (name[i]) == '(' ) break; //when arrive to parenthesis, break to hold the index of the parenthesis
    }

    sscanf((name+i+1), "%lf", &amount); //take the amount from the index after the ( character
    return amount; 
}

void getAndParse(char (*ings)[INGLEN], int* nOi) //ingredients array and number of ingredients
{
    char tempLine[LINECHARNUM];
    const char delimiter[] = ","; //ingredients are separated with comma
    
    fgets(tempLine, LINECHARNUM, stdin); //take ingredients separated with comma to tempLine

    tempLine[strcspn(tempLine, "\n")] = '\0'; //replace \n with \0

    //tokenize the string using strtok
    char *currIng = strtok(tempLine, delimiter); //current ingredient
    
    int i;
    *nOi = 0;
    for(i = 0; currIng != NULL && i < INGNUM; i++, (*nOi)++)
    {
        strcpy(ings[i], currIng);
        currIng = strtok(NULL, delimiter); //take the next ingredient
    }

    for (int j = 0; j < i; ++j) removeSpace(ings[j]); //print the separated ingredients
}

void removeSpace(char* name)
{
    char* traverser = name; //traverser is at the beginning of the string firstly
    
    while (*traverser == ' ') traverser++; //go to the beginning of the word

    char *start = traverser; //store the beginning position of the word with start pointer

    while (*traverser && (*traverser != ' ') && (*traverser != ',')) traverser++; //go to the end of the word. there can be a comma or space after the word                 
    //now traverser points to the end of the word

    //copy the word to the beginning of the string
    while (start <= traverser) //while not arrived to end of the word, copy letters
    {
        *(name++) = *(start++); //first assign *start to *name. then increment name, then increment start.
    }

    *name = '\0'; //add null after the word
}