#include <iostream>
#include <cstring>
using namespace std;

void initializer(char*);

int main()
{
    char str[15] = "boylebasta";
    initializer(str);
    cout << str << endl;
    cin >> str;
    cout << str;
}

void initializer(char* str)
{
    memset(str, 'x', 15*sizeof(char));
}