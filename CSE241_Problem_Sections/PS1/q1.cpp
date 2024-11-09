#include <iostream>
using namespace std;

int isPrime(int num);

int main()
{
    for(int i = 3; i < 100; i++)
    {
        if(isPrime(i)) cout << i << ",";
    }
    
    return 0;
}

int isPrime(int num)
{
    for(int j = 2; j*j <= num; j++)
    {
        if(num % j == 0) return 0;
    }
    
    return 1;
}