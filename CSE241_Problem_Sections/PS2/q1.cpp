#include <iostream>
#include <random>
#include <time.h>
using namespace std;

int AaronShoots();
int BobShoots();
int CharlieShoots();

int main()
{
    int winNums[3] = {0},
        totalNums = 0;

    bool isCharlieAlive = true, 
         isBobAlive = true, 
         isAaronAlive = true;

    srand(time(NULL));

    for(int i = 0; i < 10000; i++)
    {
        while((isAaronAlive && isCharlieAlive) || (isAaronAlive && isBobAlive) || (isBobAlive && isCharlieAlive))
        {
            if(!AaronShoots()) 
            {
                winNums[0]++;
                totalNums++;

                if(isCharlieAlive)
                {
                    cout << "Aaron shot Charlie" << endl;
                    isCharlieAlive = false;
                }
                    
                else
                {
                    cout << "Aaron shot Bob" << endl;
                    isBobAlive = false;
                }

                cout << "Aaron's score: " << winNums[0] << endl;
            } 
                
            if(!BobShoots())
            {
                winNums[1]++;
                totalNums++;

                if(isCharlieAlive)
                {
                    cout << "Bob shot Charlie" << endl;
                    isCharlieAlive = false;
                }

                else
                {
                    cout << "Bob shot Aaron" << endl;
                    isAaronAlive = false;
                }

                cout << "Bob's score: " << winNums[1] << endl;
            }

            if(!CharlieShoots())
            {
                winNums[2]++;
                totalNums++;
                
                if(isBobAlive)
                {
                    cout << "Charlie shot Bob" << endl;
                    isBobAlive = false;
                }

                else
                {
                    cout << "Charlie shot Aaron" << endl;
                    isAaronAlive = false;
                }

                cout << "Charlie's score: " << winNums[2] << endl;
            }

            cout << endl << "end of the round " << i <<endl;
        }

        isCharlieAlive = true;
        isBobAlive = true;
        isAaronAlive = true;
    }

    cout << "\nGame Over!" << endl;
                
    if(((winNums[0] > winNums[1]) && (winNums[1] > winNums[2])) || ((winNums[0] > winNums[2]) && (winNums[2] > winNums[1])))
    {
        cout << "Aaron wins " << winNums[0] << " of 10000 duels or " << winNums[0] / 100.0 << "%" << endl;
    }

    else if(((winNums[1] > winNums[0]) && (winNums[0] > winNums[2])) || ((winNums[1] > winNums[2]) && (winNums[2] > winNums[0])))
    {
        cout << "Bob wins " << winNums[1] << " of 10000 duels or " << winNums[1] / 100.0 << "%" << endl;
    }

    else if(((winNums[2] > winNums[0]) && (winNums[0] > winNums[1])) || ((winNums[2] > winNums[1]) && (winNums[1] > winNums[0])))
    {
        cout << "Charlie wins " << winNums[2] << " of 10000 duels or " << winNums[2] / 100.0 << "%" << endl;
    }

    return 0;
}

int AaronShoots()
{
    return (rand() % 3);
}

int BobShoots()
{
    return (rand() % 3);
}

int CharlieShoots()
{
    return (rand() % 3);
}