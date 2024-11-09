#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//#include "SparseVector.h"
//#include "SparseMatrix.h"

using namespace std;

struct Data
{
    int index;
    double data;
};

struct Index_t
{
    int index;
    bool isExists;
};

class SparseVector //TODO: WRITE THE CONSTRUCTORS
{
    private:

        int max_index;
        vector<Data> allData;
        void constructVector(string filename); //reads the file and returns the vector in the file
        Index_t findIndex(int toBeSearchedIndex);

    public:

        SparseVector(string filename);
        SparseVector(int maxIndex);
        SparseVector() : max_index(-1), allData() {}
        
        int getMaxIndex(void) { return max_index; }
        void findMaxIndex();
        const vector<Data>& getAllData() { return allData; }
        void addData(const Data& data) { allData.push_back(data); }

        friend const SparseVector operator+(SparseVector& vector1, SparseVector& vector2);
        friend const SparseVector operator-(SparseVector& vector1, SparseVector& vector2);
        friend const SparseVector operator-(SparseVector& positiveVector);
        friend ostream& operator<<(ostream& os, const SparseVector& toBePrintedVector);
        const SparseVector& operator=(const SparseVector& toBeAssignedVector);

        double dot(SparseVector& vector1, SparseVector& vector2);

};

class SparseMatrix //TODO: WRITE THE CONSTRUCTORS
{
    private:

        vector<int> rows;
        vector<SparseVector> allData;
        void constructMatrix(string filename);
        int findMaxRow();
        int max_row; //max row with nonzero value(s) 

    public:

        SparseMatrix(string filename);
        SparseMatrix() {};
        
        int getMaxRow(void) { return max_row; }
        const vector<SparseVector>& getAllData(void);

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

    SparseVector v1("/Users/nziyak/Documents/GitHub/GTU_CSE_Assignments/CSE241_Assignments/PA2/readFromfile/output/veri.txt"), 
                 v2("/Users/nziyak/Documents/GitHub/GTU_CSE_Assignments/CSE241_Assignments/PA2/readFromfile/output/veri1.txt"); 
                 //result(maxIndex1), 
                 //negated(maxIndex1);
   
    /*cout << v1 + v2 << endl << endl;
    cout << v1 - v2 << endl;
    cout << -v1 << endl;
    cout << v1.dot(v1,v2) << endl;*/

    SparseMatrix m1("/Users/nziyak/Documents/GitHub/GTU_CSE_Assignments/CSE241_Assignments/PA2/readFromfile/output/matrix1.txt");

    return 0;
}

SparseVector::SparseVector(int maxIndex) 
{
    max_index = maxIndex;
}

SparseVector::SparseVector(string filename) 
{
    constructVector(filename);

    findMaxIndex();
}

const SparseVector operator+(SparseVector& vector1, SparseVector& vector2)
{
    double sum;
    int maxIndex1 = vector1.max_index,
        maxIndex2 = vector2.max_index,
        upperBound = maxIndex1 + 1; //upperBound of for loop, assign default value

    if((maxIndex1 < maxIndex2)) //if maxIndex2 > maxIndex1
        upperBound = maxIndex2 + 1;

    SparseVector temp(upperBound-1);
    Data tempStruct;
    Index_t sumIndex1;
    Index_t sumIndex2;

    for(int i = 0; i < upperBound; i++) //sum elements of vector1 and vector2 and assign to temp
    {
        sumIndex1 = vector1.findIndex(i);
        sumIndex2 = vector2.findIndex(i);
    
        if(sumIndex1.isExists && sumIndex2.isExists)
        {
            sum = vector1.allData[sumIndex1.index].data + vector2.allData[sumIndex2.index].data;
            
            if(sum) //if sum is not 0, store it and its index
            {
                tempStruct.data = sum;
                tempStruct.index = i;
                temp.allData.push_back(tempStruct);
            }
        }

        else if(sumIndex1.isExists && !(sumIndex2.isExists))
        {
            tempStruct.data = vector1.allData[sumIndex1.index].data;
            tempStruct.index = i;
            temp.allData.push_back(tempStruct);
        }

        else if(!(sumIndex1.isExists) && (sumIndex2.isExists))
        {
            tempStruct.data = vector2.allData[sumIndex2.index].data;
            tempStruct.index = i;
            temp.allData.push_back(tempStruct);
        }
    }

    return temp;
}

const SparseVector operator-(SparseVector& vector1, SparseVector& vector2)
{
    double subtraction;
    int maxIndex1 = vector1.max_index,
        maxIndex2 = vector2.max_index,
        upperBound = maxIndex1 + 1; //upperBound of for loop, assign default value

    if((maxIndex1 < maxIndex2)) //if maxIndex2 > maxIndex1
        upperBound = maxIndex2 + 1;

    SparseVector temp(upperBound-1);
    Data tempStruct;
    Index_t subtractIndex1, subtractIndex2; //to find exact indices of to be summed indices 

    for(int i = 0; i < upperBound; i++) //sum elements of vector1 and vector2 and assign to temp
    {
        subtractIndex1 = vector1.findIndex(i);
        subtractIndex2 = vector2.findIndex(i);
    
        if(subtractIndex1.isExists && subtractIndex2.isExists)
        {
            subtraction = vector1.allData[subtractIndex1.index].data - vector2.allData[subtractIndex2.index].data;
            
            if(subtraction) //if sum is not 0, store it and its index
            {
                tempStruct.data = subtraction;
                tempStruct.index = i;
                temp.allData.push_back(tempStruct);
            }
        }

        else if(subtractIndex1.isExists && !(subtractIndex2.isExists))
        {
            tempStruct.data = vector1.allData[subtractIndex1.index].data;
            tempStruct.index = i;
            temp.allData.push_back(tempStruct);
        }

        else if(!(subtractIndex1.isExists) && (subtractIndex2.isExists))
        {
            tempStruct.data = vector2.allData[subtractIndex2.index].data;
            tempStruct.index = i;
            temp.allData.push_back(tempStruct);
        }
    }

    return temp;
}

const SparseVector operator-(SparseVector& positiveVector)
{
    unsigned int maxIndex = positiveVector.max_index;
    
    SparseVector temp(maxIndex);
    Data tempStruct;
    Index_t negationIndex;

    for(int i = 0; i < maxIndex+1; i++)
    {
        negationIndex = positiveVector.findIndex(i);

        if(negationIndex.isExists)
        {
            tempStruct.data = -(positiveVector.allData[negationIndex.index].data);
            tempStruct.index = i;
            temp.allData.push_back(tempStruct);
        }
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
    for(unsigned int i = 0; i < toBePrintedVector.allData.size(); i++)
    {
        os << toBePrintedVector.allData[i].index << ":" << toBePrintedVector.allData[i].data << " ";
    }
    return os;
}

double SparseVector::dot(SparseVector& vector1, SparseVector& vector2)
{
    double result = 0;
    int maxIndex1 = vector1.max_index,
        maxIndex2 = vector2.max_index,
        lowerBound = maxIndex1 + 1; //upperBound of for loop, assign default value

    if((maxIndex2 < maxIndex1)) //if maxIndex1 > maxIndex2
        lowerBound = maxIndex2 + 1;

    Index_t sumIndex1, sumIndex2; //to find exact indices of to be summed indices 

    for(int i = 0; i < lowerBound; i++) //sum elements of vector1 and vector2 and assign to temp
    {
        sumIndex1 = vector1.findIndex(i);
        sumIndex2 = vector2.findIndex(i);
    
        if(sumIndex1.isExists && sumIndex2.isExists)
        {
            result += vector1.allData[sumIndex1.index].data * vector2.allData[sumIndex2.index].data;
        }
    }
    
    return result;
}

void SparseVector::constructVector(string filename)
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

    for(unsigned int i = 0; i < allData.size(); i++)
    {
        if(max_index < allData[i].index) 
            max_index = allData[i].index;
    } 
}

Index_t SparseVector::findIndex(int toBeSearchedIndex)
{
    Index_t temp;

    for(int i = 0; allData[i].index <= toBeSearchedIndex; i++) //search while the indices 
    {
        if(allData[i].index == toBeSearchedIndex)
        {
            temp.isExists = true; //if found set flag true
            temp.index = i; //and set the index
            return temp;
        }
    }

    temp.isExists = false;
    temp.index = -1;
    return temp; 
}

//*******************************************************************************************************************

SparseMatrix::SparseMatrix(string filename)
{
    constructMatrix(filename);
    findMaxRow();
}

const vector<SparseVector>& SparseMatrix::getAllData(void)
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

// const SparseMatrix operator-(const SparseMatrix& matrix)
// {
//     int maxRow = matrix.max_row,
//         maxCol = matrix.max_col;
    
//     SparseMatrix temp(maxRow, maxCol);

//     for(double i = 0; i < maxRow; i++)
//     {
//         for(double j = 0; j < maxCol; j++)
//         {
//             temp.allData[i][j].data = -(matrix.allData[i][j].data);
//         }
//     }

//     return temp;
// }

// const SparseMatrix& SparseMatrix::operator=(const SparseMatrix& toBeAssignedMatrix)
// {
//     if (this != &toBeAssignedMatrix) // Check for self-assignment
//     {
//         this->max_row = toBeAssignedMatrix.max_row;
//         this->max_col = toBeAssignedMatrix.max_col;
//         this->allData = toBeAssignedMatrix.allData;
//     }
//     return *this;
// }

// ostream& operator<<(ostream& os, const SparseMatrix& toBePrintedMatrix)
// {
//     int maxRow = toBePrintedMatrix.max_row,
//         maxCol = toBePrintedMatrix.max_col;
    
//     for(int i  = 0; i < maxRow; i++)
//     {
//         os << i << " ";

//         for(int j  = 0; j < maxCol; j++)
//         {
//             os << toBePrintedMatrix.allData[i][j].index << ":" << toBePrintedMatrix.allData[i][j].data << " ";
//         }

//         os << endl;
//     }

//     return os;
// }

void SparseMatrix::constructMatrix(string filename)
{
    //read file
    //ifstream matrixFile(filename);
    //take the first number into vector of rows
    //take the rest in the same way taking vectors from vector.txt files
    
    ifstream matrixFile(filename);
    istringstream iss; //to convert line string to a inputstringstream
    string line;
    Data element;
    char delim; //to take the ':' character
    int row;
 
    if (!matrixFile) 
    {
        cerr << "File open error!" << endl;
        exit(1);
    }

    int i = 0;
    while (getline(matrixFile, line)) 
    {
        iss.clear(); // önceki içeriği temizle
        iss.str(line); // yeni satırı ayarla
        
        iss >> row;
        rows.push_back(row);

        allData.push_back(SparseVector());

        while(iss >> element.index >> delim >> element.data) //read the file 3 by 3
        {
            if (delim == ':') 
            {
                allData[i].addData(element);
            }
        }

        i++;
    }

    max_row = i;
    
    matrixFile.close();
}

int SparseMatrix::findMaxRow()
{
    int maxRow = 0;
    int lineNum = max_row;

    for(int i = 0; i < lineNum; i++)
    {
        if(rows[i] > maxRow)
            maxRow = rows[i];
    }

    max_row = maxRow;
}
