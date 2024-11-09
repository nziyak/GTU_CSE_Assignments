#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int humanTurn(int humanTotalScore);
int computerTurn(int* computerTotalScore);
int rollDice();

int main()
{
    int humanTotalScore = 0, computerTotalScore = 0;
    
    srand(time(NULL));

    while((humanTotalScore < 100) && (computerTotalScore < 100))
    {
        humanTotalScore = humanTurn(humanTotalScore);
        cout << "humanTotalScore: " << humanTotalScore << endl;

        if(humanTotalScore >= 100)
        {
            cout << "Human wins!" << endl;
            return 0;
        }

        computerTotalScore = computerTurn(&computerTotalScore);

        if(computerTotalScore >= 100)
        {
            cout << "Computer wins!" << endl;
            return 0;
        }
    }
}

int humanTurn(int humanTotalScore)
{
    int rollVal = 0;
    int totVal = 0;
    char sel;

    do{
        cout << "r or h? " << endl;
        cout << "> ";
        cin >> sel;
        
        if(sel == 'r')
        {
            rollVal = rollDice();

            cout << "rollVal: " << rollVal << endl;

            if(rollVal == 1) break;
            else totVal += rollVal;
        }

        else if(sel == 'h') 
        {
            humanTotalScore += totVal;
            return humanTotalScore;
        }

        else
        {
            cout << "invalid input" << endl;
            exit(0);
        }
        
        //humanTotalScore += rollVal;

    }while(rollVal != 1);

    return humanTotalScore;
}

int computerTurn(int* computerTotalScore)
{}

int rollDice()
{
    return (rand() % 6) + 1;
}