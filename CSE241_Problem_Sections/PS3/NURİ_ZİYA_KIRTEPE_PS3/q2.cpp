#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int i, numSuitors;
    unsigned int current;

    cout << "enter the number of the suitors: ";
    cin >> numSuitors;

    vector<int> suitors(numSuitors);

    for(int i = 0; i < numSuitors; i++)
    {
        suitors[i] = i + 1;
    }

    if(numSuitors <= 0)
    {
        cout << "there are not enough suitors." << endl;
        return 0;
    }

    else if(numSuitors == 1)
    {
        cout << "u should stand first in line" << endl;
        cout << "winner is found! the first!" << endl;
        return 0;
    }

    else
    {
        current = 0;

        while(suitors.size() > 1)
        {
            for(i = 0; i < 2; i++)
            {
                current++;

                if(current == suitors.size())
                    current = 0;
            }

            suitors.erase(suitors.begin() + current);

            if(current == suitors.size())
                    current = 0;
        }
    }
    
    cout << "to win the princess, u should stand in position " <<
            suitors[0] << endl;

    return 0;
}

