#include <iostream>

using namespace std;

class HotDogStand
{
    private:

        static int totalSold;
        int numSold;
        int ID;

    public:

        HotDogStand();
        HotDogStand(int newID, int newNumSold);
        int getID();
        void setID(int newID);
        void JustSold();
        int GetNumSold();
        static int GetTotalSold();
};

int HotDogStand::totalSold = 0;

HotDogStand::HotDogStand()
{
    numSold = 0;
    ID = 0;
}

HotDogStand::HotDogStand(int newID, int newNumSold)
{
    numSold = newNumSold;
    ID = newID;
}

int HotDogStand::getID()
{
    return ID;
}

void HotDogStand::setID(int newID)
{
    ID = newID;
}

void HotDogStand::JustSold()
{
    numSold++;
    totalSold++;
}

int HotDogStand::GetNumSold()
{
    return numSold;
}

int HotDogStand::GetTotalSold()
{
    return totalSold;
}

int main()
{
    HotDogStand s1(1,0), s2(2,0), s3(3,0);

    s1.JustSold();
    s2.JustSold();
    s1.JustSold();

    cout << "Stand " << s1.getID() << " sold " << s1.GetNumSold() << endl;
    cout << "Stand " << s1.getID() << " sold " << s2.GetNumSold() << endl;
    cout << "Stand " << s1.getID() << " sold " << s3.GetNumSold() << endl;
    cout << "Total sold = " << s1.GetTotalSold() << endl;
    cout << "Total sold = " << HotDogStand::GetTotalSold() << endl;
    cout << endl;

    s3.JustSold();
    s1.JustSold();

    cout << "Stand " << s1.getID() << " sold " << s1.GetNumSold() << endl;
    cout << "Stand " << s1.getID() << " sold " << s2.GetNumSold() << endl;
    cout << "Stand " << s1.getID() << " sold " << s3.GetNumSold() << endl;
    cout << "Total sold = " << s1.GetTotalSold() << endl;
    cout << endl;

    return 0;
}