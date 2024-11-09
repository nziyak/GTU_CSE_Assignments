#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAXNUMOFDIGITS = 15; //maximum possible digit number
const char digitSet[15] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e'};

int giveHint(char*, char*); //checks if the proposed and secret numbers are same. returns finish situation
int isValid(char*); //checks validity of secret number. returns validity value of secret number
int isValid(char*, char*); //checks validity of prediction. returns validity value of prediction
bool isDigitRepeats(char*); //looks for repeated digits. returns true if repeated digit found
int numLen(char*); //finds and returns length of number. 
bool areDigitsValid(char*); //checks if any of the digits is not in the given digits set

int main(int argc, char* argv[])
{
    srand(time(NULL)); //seed rand with time
    
    char prediction[16], //will be used for predictions of user
        secretNum[16]; 
    
    int validity, //used for validity values of numbers
        isFinished, //to check if the game is finished
        iterations = 0, //to count iterations
        prevGenerated[15] = {0}; //a flag array, to prevent generating same digit

    if((argc != 3) || ((argv[1][1] != 'r') && (argv[1][1] != 'u')) || (atoi(argv[2]) <= 0)) //if not enough arguments are given  
    {                                                                                      //OR undefined flag is given OR digitNum or given secret number is equal or less than zero
        cout << "EO" << endl;                                                             //OR digitNum or given secret number is equal or less than zero, give EO and terminate
        return 0;
    }
    
    if(argv[1][1] == 'u') //if mode is user
    {
        validity = isValid(argv[2]); //take validity value of user input of secret number
        
        if(!validity) //if validity value is O
        {            //give EO and terminate
            cout << "EO" << endl; 
            return 0;
        }
        
        else if(validity == 1) //if validity value is 1
        {                     //give E1 and terminate
            cout << "E1" << endl; 
            return 0;
        }
        
        else if(validity == 2) //if validity value is 2
        {                     //give E2 and terminate
            cout << "E2" << endl;
            return 0;
        }
        
        do{    
            
            cin >> prediction; //take user prediction

            validity = isValid(prediction, argv[2]); //take validity value of prediction

            if(!validity) //if validity value is O
            {            //give E0 and terminate
                cout << "EO" << endl;
                return 0;
            }

            else if(validity == 1) //if validity value is 1
            {                     //give E1 and terminate
                cout << "E1" << endl; 
                return 0;
            }
            
            else if(validity == 2) //if validity value is 2
            {                     //give E2 and terminate
                cout << "E2" << endl;
                return 0;
            }

            isFinished = giveHint(prediction, argv[2]);

            if(isFinished == 1) 
                return 0;
            
            else if(isFinished == 2)
            {
                cout << "FAILED" << endl;
                return 0;
            }

        }while(1);
    }

    else if(argv[1][1] == 'r')
    {
        int index;
        
        if(atoi(argv[2]) > MAXNUMOFDIGITS) //if desired digit number is greater than the defined give E1 and terminate
        {
            cout << "E1" << endl;
            return 0;
        }
        
        index = rand() % (MAXNUMOFDIGITS-1) + 1; //generate a random index
        secretNum[0] = digitSet[index];  //select the char from the randomly selected index to determine the first digit
        //first digit is determined before others because it must be greater than 0 to be valid
        
        prevGenerated[index] = 1;

        int i;
        for(i = 1; i < atoi(argv[2]); i++) //generate secret number randomly
        {
            do{
              
                index = rand() % (MAXNUMOFDIGITS-1); //generate a random index
                
                if(prevGenerated[index] == 0) //if the generated index is not used
                {
                    prevGenerated[index] = 1; //set it as used and break
                    break;
                }
                
            }while(prevGenerated[index] == 1); //try until finding an unused index

            secretNum[i] = digitSet[index]; //select the char at the randomly selected index to determine current digit
        }

        secretNum[i] = '\0'; //assign null after the number

        do{    
            
            cin >> prediction; //take user prediction

            validity = isValid(prediction, secretNum); //take validity value of prediction

            if(!validity) //if validity value is O
            {            //give E0 and terminate
                cout << "EO" << endl;
                return 0;
            }

            else if(validity == 1) //if validity value is 1
            {                     //give E1 and terminate
                cout << "E1" << endl; 
                return 0;
            }
            
            else if(validity == 2) //if validity value is 2
            {                     //give E2 and terminate
                cout << "E2" << endl;
                return 0;
            }

            isFinished = giveHint(prediction, secretNum);

            if(isFinished == 1) 
                return 0;
            
            else if(isFinished == 2)
            {
                cout << "FAILED" << endl;
                return 0;
            }

        }while(1);
    }
    
    return 0;
}

int giveHint(char* prediction, char* secretNum)
{
    int Cexact = 0, 
        Cmisplaced = 0,
        predLen = numLen(prediction), //prediction length
        secretNumLen = numLen(secretNum); //secret number length

    static int iterations = 0; //iterations of game, to be incremented at each iteration

    for(int i = 0; i < predLen; i++) //look for every digit of the prediction
    {
        for(int j = 0; j < secretNumLen; j++) //look for every digit of the secret number
        {
            if(prediction[i] == secretNum[j]) //if digit occurence is found
            {
                if(i == j) //and if their places are same
                    Cexact++; //increment counter of exact placed
                else //else
                    Cmisplaced++; //increment counter of misplaced
            }
        }
    }

    iterations++;

    if(Cexact == predLen) //if every digit of the prediction is at the correct place finish game
    {
        cout << "FOUND " << iterations << endl;
        return 1;
    }

    else if(iterations > 100) //if user tried lots of times but couldnt find the secret number, finished
        return 2;
    
    else
    {
        cout << Cexact << " " << Cmisplaced << endl;
        return 0;
    }
}

int isValid(char* secretNum)
{
    if((secretNum[0] == '0') || isDigitRepeats(secretNum)) //if first digit is 0 or there are repeating digits
        return 0;
    
    else if(!areDigitsValid(secretNum)) //if digit(s) of secret number is not in the given digits set
        return 2;

    else return 3;
}

int isValid(char* prediction, char* secretNum)
{
    if((prediction[0] == '0') || isDigitRepeats(prediction)) //if first digit is 0 or there are repeating digits
        return 0;
    
    else if (numLen(prediction) != numLen(secretNum)) //if lengths are not equal
        return 1;

    else if(!areDigitsValid(prediction)) //if digit(s) of prediction is not in the given digits set
        return 2; 

    else return 3;
}

bool isDigitRepeats(char* num)
{
    int numLength = numLen(num);
    
    for(int i = 0; i < numLength; i++) //look for every digit of number
    {
        for(int j = i + 1; j < numLength; j++) //look at the rest of the number
        {
            if(num[i] == num[j]) return true;
        }
    }

    return false;
}

int numLen(char* num)
{
    int digitCount = 0;

    for(char* digit = num; *digit != '\0'; digit++, digitCount++); //count digits until the NULL

    return digitCount;
}

bool areDigitsValid(char* num)
{
    bool found = false;

    for(int i = 0; i < numLen(num); i++) //look for every digit of number
    {
        for(int j = 0; j < MAXNUMOFDIGITS; j++) //with the every element of given digit set
        {
            if(found) found = false; //if the previous digit is found in the set, set flag to false to be able to check the current digit
            
            if(num[i] == digitSet[j]) //if the current digit is found in the set,  
            {                        
                found = true;       //set flag to true
                break;             //and stop looking for the current digit
            }
        }
    }
    
    return found;
}
