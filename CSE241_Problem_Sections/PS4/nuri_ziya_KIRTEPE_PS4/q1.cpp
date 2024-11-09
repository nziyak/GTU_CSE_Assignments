#include <iostream>
#include <vector>

using namespace std;

class vector2D
{
    public:

        vector2D();
        vector2D(int newx, int newy);
        void setXY(int newx, int newy);
        int getX();
        int getY();
        int operator *(const vector2D &v2);

    private:

        int x, y;
};

vector2D::vector2D()
{
    x = 0;
    y = 0;
}

vector2D::vector2D(int newx, int newy)
{
    x = newx;
    y = newy;
}

int vector2D::getX()
{
    return x;
}

int vector2D::getY()
{
    return y;
}

int vector2D::operator* (const vector2D &v2)
{
    return (this->x*v2.x) + (this->y*v2.y);
}

int main()
{
    vector2D v1(10,0), v2(0,10), v3(10,10), v4(5,4);

    cout << "(" << v1.getX() << "," << v1.getY() << ") * (" << v2.getX()
         << "," << v2.getY() << ") = " << v1*v2 << endl;

    cout << "(" << v2.getX() << "," << v2.getY() << ") * (" << v3.getX()
         << "," << v3.getY() << ") = " << v2*v3 << endl;

    cout << "(" << v3.getX() << "," << v3.getY() << ") * (" << v4.getX()
         << "," << v4.getY() << ") = " << v3*v4 << endl;
}