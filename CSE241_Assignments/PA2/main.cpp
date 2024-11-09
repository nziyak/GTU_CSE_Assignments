#include <iostream>
#include <fstream>
#include <string>
//#include "SparseVector.h"
//#include "SparseMatrix.h"

using namespace std;

struct Data
{
    int index;
    double data;
};

class SparseVector //TODO: WRITE THE CONSTRUCTORS
{
    private:

        int max_index;
        vector<Data> allData;
        void findMaxIndex();
        void readFile(string filename); //reads the file and returns the vector in the file

    public:

        SparseVector(string filename, int maxIndexVal);
        SparseVector(int maxIndexVal);
        SparseVector();
        
        int getMaxIndex(void);
        const vector<Data>& getAllData();

        friend const SparseVector operator+(SparseVector& vector1, SparseVector& vector2);
        friend const SparseVector operator-(SparseVector& vector1, SparseVector& vector2);
        friend const SparseVector operator-(const SparseVector& positiveVector);
        friend ostream& operator<<(ostream& os, const SparseVector& toBePrintedVector);
        const SparseVector& operator=(const SparseVector& toBeAssignedVector);

        double dot(SparseVector& vector1, SparseVector& vector2);

};

class SparseMatrix //TODO: WRITE THE CONSTRUCTORS
{
    private:

        vector< vector<Data> > allData;
        int max_row, //max row with nonzero value(s) //HOLD EVERY MAX_ROW
            max_col; //max row with nonzero value(s)

    public:

        SparseMatrix(string filename, int maxRow, int maxCol);
        SparseMatrix(int maxRow, int maxCol);
        SparseMatrix();
        
        int getMaxRow(void);
        int getMaxCol(void);
        const vector< vector<Data> >& getAllData(void);

        friend const SparseMatrix operator+(SparseMatrix& matrix1, SparseMatrix& matrix2);
        friend const SparseMatrix operator-(SparseMatrix& matrix1, SparseMatrix& matrix2);
        friend const SparseMatrix operator-(const SparseMatrix& positiveMatrix);
        friend ostream& operator<<(ostream& os, const SparseMatrix& toBePrintedMatrix);
        const SparseMatrix& operator=(const SparseMatrix& toBeAssignedMatrix);

        double transpose(SparseMatrix& matrix);

};

int main()
{
    /*ofstream outfile;
    outfile.open("output.txt", ios::out | ios::trunc );
    
    //Creating a SparseVector from file
    SparseVector a1("a1.txt");
    outfile<<"a1"<<endl<<a1<<endl;
    
    //Binary operations and assignment
    a1 = a1 + a1;
    outfile<<"a1"<<endl<<a1<<endl;

    //Creating SparseMatrix from file
    SparseMatrix m1("m1.txt");
    SparseMatrix m2("m2.txt");

    outfile<<"m2"<<endl<<m2<<endl;
    
    //Transpose
    outfile<<m2.transpose()<<endl;
    
    //Dot product
    outfile<<dot(a1,a1)<<endl;*/
    
    srand(time(NULL));

    /*int maxIndex1 = 10, 
        maxIndex2 = 5;

    SparseVector v1("hello", maxIndex1), v2(maxIndex2), result(maxIndex1), negated(maxIndex1);
    double resultt;

    result = v1 + v2;

    cout << v1 << endl;
    cout << v2 << endl;
    cout << "sum result: \n" << result << endl;

    result = v1 - v2;

    cout << v1 << endl;
    cout << v2 << endl;
    cout << "subtraction result: \n" << result << endl;

    negated = -v1;

    cout << "negated v1: " << negated << endl << endl;

    resultt = v1.dot(v1, v2);

    cout << v1 << endl;
    cout << v2 << endl;
    cout << "dot product result: " << resultt << endl;*/

    SparseMatrix m1(5,10), m2(5,5), temp(5,10);

    temp = m1 + m2;

    cout << m1 << endl;
    cout << m2 << endl;
    cout << temp;

    cout << endl;

    temp = m1 - m2;

    cout << m1 << endl;
    cout << m2 << endl;
    cout << temp;

    cout << endl;

    temp = -m1;

    cout << m1 << endl;
    cout << temp;

    return 0;
}

SparseVector::SparseVector() {}

SparseVector::SparseVector(string filename, int maxIndexVal) 
{
    max_index = maxIndexVal;

    int vectorSize = max_index + 1;

    allData.resize(vectorSize);

    for(int i = 0; i < vectorSize; i++)
    {
        allData[i].data = rand() % 16;
    }
}

SparseVector::SparseVector(int maxIndexVal) 
{
    max_index = maxIndexVal;

    int vectorSize = max_index + 1;

    allData.resize(vectorSize);

    for(int i = 0; i < vectorSize; i++)
    {
        if(i % 2 == 0) allData[i].data = 1;
        else allData[i].data = -1;
    }
}

/*
SparseVector::SparseVector(string filename) 
{
    //open file named filename
    //read content and create the vector
    //assign max_index, too
}*/

int SparseVector::getMaxIndex(void)
{
    return max_index;
}

const vector<Data>& SparseVector::getAllData(void)
{
    return allData;
}

const SparseVector operator+(SparseVector& vector1, SparseVector& vector2)
{
    unsigned int maxIndex1 = vector1.max_index,
                 maxIndex2 = vector2.max_index,
                 i; //loop index
    
    if(maxIndex1 == maxIndex2)
    {
        SparseVector temp(maxIndex1);

        cout << endl << "temp size: " << temp.allData.size() << endl;
        cout << "vector1 size: " << vector1.allData.size() << endl;
        cout << "vector2 size: " << vector2.allData.size() << endl << endl;

        for(i = 0; i < maxIndex1; i++) //sum elements of vector1 and vector2 and assign to temp
        {
            temp.allData[i].data = vector1.allData[i].data + vector2.allData[i].data;
        }

        return temp;
    }
    
    else if(maxIndex1 > maxIndex2)
    {
        SparseVector temp(maxIndex1);

        cout << endl << "temp size: " << temp.allData.size() << endl;
        cout << "vector1 size: " << vector1.allData.size() << endl;
        cout << "vector2 size: " << vector2.allData.size() << endl << endl;

        for(i = 0; i < maxIndex2; i++) //sum elements of vector1 and vector2 and assign to temp
        {
            temp.allData[i].data = vector1.allData[i].data + vector2.allData[i].data;
        }

        for(; i < maxIndex1; i++) //when vector2 ends, consider the rest of the elements of vector 2 as 0
        {
            temp.allData[i].data = vector1.allData[i].data; //just assign vector1's elements because vector2's elements assumed to be zero
        }

        return temp;
    }

    else //if maxIndex2 > maxIndex1
    {
        SparseVector temp(maxIndex2);

        cout << endl << "temp size: " << temp.allData.size() << endl;
        cout << "vector1 size: " << vector1.allData.size() << endl;
        cout << "vector2 size: " << vector2.allData.size() << endl << endl;

        for(i = 0; i < maxIndex1; i++) //sum elements of vector1 and vector2 and assign to temp
        {
            temp.allData[i].data = vector1.allData[i].data + vector2.allData[i].data;
        }

        for(; i < maxIndex2; i++) //when vector2 ends, consider the rest of the elements of vector 2 as 0
        {
            temp.allData[i].data = vector2.allData[i].data; //just assign vector2's elements because vector1's elements assumed to be zero
        }

        return temp;
    }
}

const SparseVector operator-(SparseVector& vector1, SparseVector& vector2)
{
    unsigned int maxIndex1 = vector1.max_index,
                 maxIndex2 = vector2.max_index,
                 i; //loop index
    
    if(maxIndex1 > maxIndex2)
    {
        SparseVector temp(maxIndex1);

        cout << endl << "temp size: " << temp.allData.size() << endl;
        cout << "vector1 size: " << vector1.allData.size() << endl;
        cout << "vector2 size: " << vector2.allData.size() << endl << endl;

        for(i = 0; i < maxIndex2; i++) //sum elements of vector1 and vector2 and assign to temp
        {
            temp.allData[i].data = vector1.allData[i].data - vector2.allData[i].data;
        }

        for(; i < maxIndex1; i++) //when vector2 ends, consider the rest of the elements of vector 2 as 0
        {
            temp.allData[i].data = vector1.allData[i].data; //just assign vector1's elements because vector2's elements assumed to be zero
        }

        return temp;
    }

    else if(maxIndex2 > maxIndex1)
    {
        SparseVector temp(maxIndex2);

        cout << endl << "temp size: " << temp.allData.size() << endl;
        cout << "vector1 size: " << vector1.allData.size() << endl;
        cout << "vector2 size: " << vector2.allData.size() << endl << endl;

        for(i = 0; i < maxIndex1; i++) //sum elements of vector1 and vector2 and assign to temp
        {
            temp.allData[i].data = vector1.allData[i].data - vector2.allData[i].data;
        }

        for(; i < maxIndex2; i++) //when vector2 ends, consider the rest of the elements of vector 2 as 0
        {
            temp.allData[i].data = vector2.allData[i].data; //just assign vector2's elements because vector1's elements assumed to be zero
        }

        return temp;
    }

    else
    {
        SparseVector temp(maxIndex1);

        cout << endl << "temp size: " << temp.allData.size() << endl;
        cout << "vector1 size: " << vector1.allData.size() << endl;
        cout << "vector2 size: " << vector2.allData.size() << endl << endl;

        for(i = 0; i < maxIndex1; i++) //sum elements of vector1 and vector2 and assign to temp
        {
            temp.allData[i].data = vector1.allData[i].data - vector2.allData[i].data;
        }

        return temp;
    }
}

const SparseVector operator-(const SparseVector& vector1)
{
    unsigned int maxIndex = vector1.max_index;
    
    SparseVector temp(maxIndex);

    for(double i = 0; i < maxIndex; i++)
    {
        temp.allData[i].data = -(vector1.allData[i].data);
    }

    return temp;
}

const SparseVector& SparseVector::operator=(const SparseVector& toBeAssignedVector)
{
    if (this != &toBeAssignedVector) // Check for self-assignment
    {
        this->max_index = toBeAssignedVector.max_index;
        this->allData = toBeAssignedVector.allData;
    }
    return *this;
}

ostream& operator<<(ostream& os, const SparseVector& toBePrintedVector)
{
    int maxIndex = toBePrintedVector.max_index;

    for(int i  = 0; i < maxIndex; i++)
    {
        os << toBePrintedVector.allData[i].index << ":" << toBePrintedVector.allData[i].data << " ";
    }
    return os;
}

double SparseVector::dot(SparseVector& vector1, SparseVector& vector2)
{
    double result = 0;
    unsigned int maxIndex1 = vector1.getMaxIndex(),
                 maxIndex2 = vector2.getMaxIndex();
    
    if(maxIndex1 > maxIndex2)
    {
        vector2.allData.resize((maxIndex1 + 1));
    }

    else if(maxIndex2 > maxIndex1)
    {
        vector1.allData.resize((maxIndex2 + 1));
    }

    for(unsigned int i = 0; i < maxIndex1; i++)
    {
        result += vector1.allData[i].data * vector2.allData[i].data;
    }

    return result;
}

void SparseVector::readFile(string filename)
{
    ifstream vectorFile(filename);
    Data element;

    if(!vectorFile) 
    {
        cerr << "file open error!" << endl;
        exit(1);
    }

    char delim; //to take the ':' character
    while (vectorFile >> element.index >> delim >> element.data) //read the file 3 by 3
    {
        if (delim == ':') 
        {
            allData.push_back(element);
        }
    }

    vectorFile.close();
}

void SparseVector::findMaxIndex()
{
    max_index = allData[0].index;

    for(int i = 0; i < allData.size(); i++)
    {
        if(max_index < allData[i].index) 
            max_index = allData[i].index;
    } 
}

//*******************************************************************************************************************

SparseMatrix::SparseMatrix(int maxRow, int maxCol)
{
    max_row = maxRow;
    max_col = maxCol;
    
    allData.resize(maxRow+1);

    for(int i = 0; i < maxRow; i++)
    {
        allData[i].resize(maxCol+1);
        for(int j = 0; j < maxCol; j++)
        {
            allData[i][j].data = 1;
        }
    }
}

int SparseMatrix::getMaxRow(void)
{
    return max_row;
}

int SparseMatrix::getMaxCol(void)
{
    return max_col;
}

const vector< vector<Data> >& SparseMatrix::getAllData(void)
{
    return allData;
}

const SparseMatrix operator+(SparseMatrix& matrix1, SparseMatrix& matrix2)
{
    unsigned int maxRow1 = matrix1.max_row,
                 maxRow2 = matrix2.max_row,
                 maxCol1 = matrix1.max_col,
                 maxCol2 = matrix2.max_col,
                 i, j; //loop indices

    if(maxRow1 == maxRow2)
    {
        if(maxCol1 == maxCol2)
        {
            SparseMatrix temp(maxRow1, maxCol1);

            for(i = 0; i < maxRow1; i++)
            {
                for(j = 0; j < maxCol1; j++) //sum column elements of matrix1 and matrix2 and assign to temp
                {
                    temp.allData[i][j].data = matrix1.allData[i][j].data + matrix2.allData[i][j].data;
                }
            }

            return temp;
        }

        else if(maxCol1 > maxCol2)
        {
            SparseMatrix temp(maxRow1, maxCol1);

            for(i = 0; i < maxRow1; i++)
            {
                for(j = 0; j < maxCol2; j++) //sum elements of matrix1 and matrix2 and assign to temp
                {
                    temp.allData[i][j].data = matrix1.allData[i][j].data + matrix2.allData[i][j].data;
                }

                for(; j < maxCol1; j++) //when column of matrix2 ends, consider the rest of the elements of matrix2 as 0
                {
                    temp.allData[i][j].data = matrix1.allData[i][j].data; //just assign matrix1's elements because matirx2's elements assumed to be zero
                }
            }

            return temp;
        }
        
        else if(maxCol2 > maxCol1)
        {
            SparseMatrix temp(maxRow1, maxCol2);

            for(i = 0; i < maxRow1; i++)
            {
                for(j = 0; j < maxCol1; j++) //sum column elements of matrix1 and matrix2 and assign to temp
                {
                    temp.allData[i][j].data = matrix1.allData[i][j].data + matrix2.allData[i][j].data;
                }

                for(; j < maxCol2; j++) //when column of matrix2 ends, consider the rest of the elements of matrix2 as 0
                {
                    temp.allData[i][j].data = matrix2.allData[i][j].data; //just assign matrix1's elements because matirx2's elements assumed to be zero
                }
            }

            return temp;
        }
    }
    
    else if(maxRow1 > maxRow2)
    {
        if(maxCol1 == maxCol2)
        {
            SparseMatrix temp(maxRow1, maxCol1);

            for(i = 0; i < maxRow2; i++)
            {
                for(j = 0; j < maxCol1; j++) //sum column elements of matrix1 and matrix2 and assign to temp
                {
                    temp.allData[i][j].data = matrix1.allData[i][j].data + matrix2.allData[i][j].data;
                }
            }

            for(; i < maxRow1; i++)
            {
                for(j = 0; j < maxCol1; j++) //sum column elements of matrix1 and matrix2 and assign to temp
                {
                    temp.allData[i][j].data = matrix1.allData[i][j].data;
                }
            }

            return temp;
        }
        
        else if(maxRow1 > maxRow2)
        {
            if(maxCol1 > maxCol2)
            {
                SparseMatrix temp(maxRow1, maxCol1);

                for(i = 0; i < maxRow2; i++)
                {
                    for(j = 0; j < maxCol2; j++) //sum elements of matrix1 and matrix and assign to temp
                    {
                        temp.allData[i][j].data = matrix1.allData[i][j].data + matrix2.allData[i][j].data;
                    }
                }

                for(; i < maxRow1; i++)
                {
                    for(j = 0; j < maxCol1; j++) //assign matrix1's elements to temp
                    {
                        temp.allData[i][j].data = matrix1.allData[i][j].data;
                    }
                }

                return temp;
            }
        }

        
        else if(maxCol2 > maxCol1)
        {
            SparseMatrix temp(maxRow1, maxCol2);

            for(i = 0; i < maxRow1; i++)
            {
                for(j = 0; j < maxCol1; j++) //sum column elements of matrix1 and matrix2 and assign to temp
                {
                    temp.allData[i][j].data = matrix1.allData[i][j].data + matrix2.allData[i][j].data;
                }

                for(; j < maxCol2; j++) //when column of matrix2 ends, consider the rest of the elements of matrix2 as 0
                {
                    temp.allData[i][j].data = matrix2.allData[i][j].data; //just assign matrix1's elements because matirx2's elements assumed to be zero
                }
            }

            return temp;
        }
    }

    else //if maxRow2 > maxRow1
    {
        if(maxCol1 == maxCol2)
        {
            SparseMatrix temp(maxRow2, maxCol1);

            for(i = 0; i < maxRow1; i++)
            {
                for(j = 0; j < maxCol1; j++) //sum column elements of matrix1 and matrix2 and assign to temp
                {
                    temp.allData[i][j].data = matrix1.allData[i][j].data + matrix2.allData[i][j].data;
                }
            }

            for(; i < maxRow2; i++)
            {
                for(j = 0; j < maxCol1; j++) //sum column elements of matrix1 and matrix2 and assign to temp
                {
                    temp.allData[i][j].data = matrix2.allData[i][j].data;
                }
            }

            return temp;
        }

        else if(maxCol1 > maxCol2)
        {
            SparseMatrix temp(maxRow2, maxCol1);

            for(i = 0; i < maxRow2; i++)
            {
                for(j = 0; j < maxCol2; j++) //sum elements of matrix1 and matrix and assign to temp
                {
                    temp.allData[i][j].data = matrix1.allData[i][j].data + matrix2.allData[i][j].data;
                }

                for(; j < maxCol1; j++) //when column of matrix2 ends, consider the rest of the elements of matrix2 as 0
                {
                    temp.allData[i][j].data = matrix1.allData[i][j].data; //just assign matrix1's elements because matirx2's elements assumed to be zero
                }
            }

            return temp;
        }
        
        else if(maxCol2 > maxCol1)
        {
            SparseMatrix temp(maxRow2, maxCol2);

            /*cout << endl << "temp size: " << temp.max_row << " " << temp.max_col << endl;
            cout << endl << "matrix1 size: " << matrix1.max_row << " " << matrix1.max_col << endl;
            cout << endl << "matrix2 size: " << matrix2.max_row << " " << matrix2.max_col << endl;*/

            for(i = 0; i < maxRow2; i++)
            {
                for(j = 0; j < maxCol1; j++) //sum column elements of matrix1 and matrix2 and assign to temp
                {
                    temp.allData[i][j].data = matrix1.allData[i][j].data + matrix2.allData[i][j].data;
                }

                for(; j < maxCol2; j++) //when column of matrix2 ends, consider the rest of the elements of matrix2 as 0
                {
                    temp.allData[i][j].data = matrix2.allData[i][j].data; //just assign matrix1's elements because matirx2's elements assumed to be zero
                }
            }

            return temp;
        }
    }
}

const SparseMatrix operator-(SparseMatrix& matrix1, SparseMatrix& matrix2)
{
    unsigned int maxRow1 = matrix1.max_row,
                 maxRow2 = matrix2.max_row,
                 maxCol1 = matrix1.max_col,
                 maxCol2 = matrix2.max_col,
                 i, j; //loop indices

    if(maxRow1 == maxRow2)
    {
        if(maxCol1 == maxCol2)
        {
            SparseMatrix temp(maxRow1, maxCol1);

            for(i = 0; i < maxRow1; i++)
            {
                for(j = 0; j < maxCol1; j++) //sum column elements of matrix1 and matrix2 and assign to temp
                {
                    temp.allData[i][j].data = matrix1.allData[i][j].data - matrix2.allData[i][j].data;
                }
            }

            return temp;
        }

        else if(maxCol1 > maxCol2)
        {
            SparseMatrix temp(maxRow1, maxCol1);

            for(i = 0; i < maxRow1; i++)
            {
                for(j = 0; j < maxCol2; j++) //sum elements of matrix1 and matrix2 and assign to temp
                {
                    temp.allData[i][j].data = matrix1.allData[i][j].data - matrix2.allData[i][j].data;
                }

                for(; j < maxCol1; j++) //when column of matrix2 ends, consider the rest of the elements of matrix2 as 0
                {
                    temp.allData[i][j].data = matrix1.allData[i][j].data; //just assign matrix1's elements because matirx2's elements assumed to be zero
                }
            }

            return temp;
        }
        
        else if(maxCol2 > maxCol1)
        {
            SparseMatrix temp(maxRow1, maxCol2);

            for(i = 0; i < maxRow1; i++)
            {
                for(j = 0; j < maxCol1; j++) //sum column elements of matrix1 and matrix2 and assign to temp
                {
                    temp.allData[i][j].data = matrix1.allData[i][j].data - matrix2.allData[i][j].data;
                }

                for(; j < maxCol2; j++) //when column of matrix2 ends, consider the rest of the elements of matrix2 as 0
                {
                    temp.allData[i][j].data = matrix2.allData[i][j].data; //just assign matrix1's elements because matirx2's elements assumed to be zero
                }
            }

            return temp;
        }
    }
    
    else if(maxRow1 > maxRow2)
    {
        if(maxCol1 == maxCol2)
        {
            SparseMatrix temp(maxRow1, maxCol1);

            for(i = 0; i < maxRow2; i++)
            {
                for(j = 0; j < maxCol1; j++) //sum column elements of matrix1 and matrix2 and assign to temp
                {
                    temp.allData[i][j].data = matrix1.allData[i][j].data - matrix2.allData[i][j].data;
                }
            }

            for(; i < maxRow1; i++)
            {
                for(j = 0; j < maxCol1; j++) //sum column elements of matrix1 and matrix2 and assign to temp
                {
                    temp.allData[i][j].data = matrix1.allData[i][j].data;
                }
            }

            return temp;
        }
        
        else if(maxRow1 > maxRow2)
        {
            if(maxCol1 > maxCol2)
            {
                SparseMatrix temp(maxRow1, maxCol1);

                for(i = 0; i < maxRow2; i++)
                {
                    for(j = 0; j < maxCol2; j++) //sum elements of matrix1 and matrix and assign to temp
                    {
                        temp.allData[i][j].data = matrix1.allData[i][j].data - matrix2.allData[i][j].data;
                    }
                }

                for(; i < maxRow1; i++)
                {
                    for(j = 0; j < maxCol1; j++) //assign matrix1's elements to temp
                    {
                        temp.allData[i][j].data = matrix1.allData[i][j].data;
                    }
                }

                return temp;
            }
        }

        
        else if(maxCol2 > maxCol1)
        {
            SparseMatrix temp(maxRow1, maxCol2);

            for(i = 0; i < maxRow1; i++)
            {
                for(j = 0; j < maxCol1; j++) //sum column elements of matrix1 and matrix2 and assign to temp
                {
                    temp.allData[i][j].data = matrix1.allData[i][j].data - matrix2.allData[i][j].data;
                }

                for(; j < maxCol2; j++) //when column of matrix2 ends, consider the rest of the elements of matrix2 as 0
                {
                    temp.allData[i][j].data = matrix2.allData[i][j].data; //just assign matrix1's elements because matirx2's elements assumed to be zero
                }
            }

            return temp;
        }
    }

    else //if maxRow2 > maxRow1
    {
        if(maxCol1 == maxCol2)
        {
            SparseMatrix temp(maxRow2, maxCol1);

            for(i = 0; i < maxRow1; i++)
            {
                for(j = 0; j < maxCol1; j++) //sum column elements of matrix1 and matrix2 and assign to temp
                {
                    temp.allData[i][j].data = matrix1.allData[i][j].data - matrix2.allData[i][j].data;
                }
            }

            for(; i < maxRow2; i++)
            {
                for(j = 0; j < maxCol1; j++) //sum column elements of matrix1 and matrix2 and assign to temp
                {
                    temp.allData[i][j].data = matrix2.allData[i][j].data;
                }
            }

            return temp;
        }

        else if(maxCol1 > maxCol2)
        {
            SparseMatrix temp(maxRow2, maxCol1);

            for(i = 0; i < maxRow2; i++)
            {
                for(j = 0; j < maxCol2; j++) //sum elements of matrix1 and matrix and assign to temp
                {
                    temp.allData[i][j].data = matrix1.allData[i][j].data - matrix2.allData[i][j].data;
                }

                for(; j < maxCol1; j++) //when column of matrix2 ends, consider the rest of the elements of matrix2 as 0
                {
                    temp.allData[i][j].data = matrix1.allData[i][j].data; //just assign matrix1's elements because matirx2's elements assumed to be zero
                }
            }

            return temp;
        }
        
        else if(maxCol2 > maxCol1)
        {
            SparseMatrix temp(maxRow2, maxCol2);

            /*cout << endl << "temp size: " << temp.max_row << " " << temp.max_col << endl;
            cout << endl << "matrix1 size: " << matrix1.max_row << " " << matrix1.max_col << endl;
            cout << endl << "matrix2 size: " << matrix2.max_row << " " << matrix2.max_col << endl;*/

            for(i = 0; i < maxRow2; i++)
            {
                for(j = 0; j < maxCol1; j++) //sum column elements of matrix1 and matrix2 and assign to temp
                {
                    temp.allData[i][j].data = matrix1.allData[i][j].data - matrix2.allData[i][j].data;
                }

                for(; j < maxCol2; j++) //when column of matrix2 ends, consider the rest of the elements of matrix2 as 0
                {
                    temp.allData[i][j].data = matrix2.allData[i][j].data; //just assign matrix1's elements because matirx2's elements assumed to be zero
                }
            }

            return temp;
        }
    }
}

const SparseMatrix operator-(const SparseMatrix& matrix)
{
    int maxRow = matrix.max_row,
        maxCol = matrix.max_col;
    
    SparseMatrix temp(maxRow, maxCol);

    for(double i = 0; i < maxRow; i++)
    {
        for(double j = 0; j < maxCol; j++)
        {
            temp.allData[i][j].data = -(matrix.allData[i][j].data);
        }
    }

    return temp;
}

const SparseMatrix& SparseMatrix::operator=(const SparseMatrix& toBeAssignedMatrix)
{
    if (this != &toBeAssignedMatrix) // Check for self-assignment
    {
        this->max_row = toBeAssignedMatrix.max_row;
        this->max_col = toBeAssignedMatrix.max_col;
        this->allData = toBeAssignedMatrix.allData;
    }
    return *this;
}

ostream& operator<<(ostream& os, const SparseMatrix& toBePrintedMatrix)
{
    int maxRow = toBePrintedMatrix.max_row,
        maxCol = toBePrintedMatrix.max_col;
    
    for(int i  = 0; i < maxRow; i++)
    {
        os << i << " ";

        for(int j  = 0; j < maxCol; j++)
        {
            os << toBePrintedMatrix.allData[i][j].index << ":" << toBePrintedMatrix.allData[i][j].data << " ";
        }

        os << endl;
    }

    return os;
}
