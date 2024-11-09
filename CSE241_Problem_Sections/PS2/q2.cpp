#include <iostream>
#include <string>

using namespace std;

bool isDigitsInt(string);
bool isInRange(string);

int main()
{
    string num1, num2;
    
    cout << "enter num1: ";  cin >> num1;
    
    if(!isDigitsInt(num1) || !isInRange(num1))
    {
        cout << "invalid number! exiting..." << endl;
        return 0;
    }

    cout << "enter num2: ";  cin >> num2;

    if(!isDigitsInt(num2) || !isInRange(num2))
    {
        cout << "invalid number! exiting..." << endl;
        return 0;
    }

    return 0;
}

bool isDigitsInt(string num)
{
    for(char c: num)
    {
        if((c < 47) || (c > 58)) return false;
    }

    return true;
}

bool isInRange(string num)
{
    if(num.length() > 20) 
        return false;

    return true;
}