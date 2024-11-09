#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

class myInt
{
    public:

        myInt();
        myInt(int newNum);
        void setInt(int newNum);
        int getInt();
        int operator[](int index);

    private:
        
        int num;
};

myInt::myInt(int newNum)
{
    num = newNum;
}

void myInt::setInt(int newNum)
{
    num = newNum;
}

int myInt::getInt()
{
    return num;
}

int myInt::operator[](int index)
{
    int temp;

    if(index < 0)
    {
        cout << "illegal index val\n";
        return -1;
    }

    else
    {
        temp = (int) (num / (pow(10, index)));
        //rightmost digit is the answer
        return (temp % 10);
    }
}

int main()
{
    myInt num(418);
    cout << num[0] << " " << num[1] << " " << num[2] << endl;
    cout << num[3] << endl;
    cout << num[-1] << endl;
    return 0; 
}