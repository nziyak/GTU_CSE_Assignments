#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

#ifndef _SPARSEVECTOR_H_
#define _SPARSEVECTOR_H_

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

class SparseVector
{
    private:

        int max_index; //max_index of the vector
        vector<Data> allData;
        void constructVector(string filename); //reads the file and returns the vector in the file

    public:

        SparseVector(string filename);
        SparseVector(int maxIndex);
        SparseVector() : max_index(-1), allData() {}
        
        int getMaxIndex(void) { return max_index; } 
        void findMaxIndex(); //to find the max index value in the vector
        vector<Data>& getAllDataa() { return allData; }
        const vector<Data>& getAllData() const { return allData; }
        void addData(const Data& data) { allData.push_back(data); } //to add data to existing data
        Index_t findIndex(int toBeSearchedIndex); //finds the current operated index in vector

        friend const SparseVector operator+(SparseVector& vector1, SparseVector& vector2);
        friend const SparseVector operator-(SparseVector& vector1, SparseVector& vector2);
        friend const SparseVector operator-(SparseVector& positiveVector);
        friend ostream& operator<<(ostream& os, const SparseVector& toBePrintedVector);
        const SparseVector& operator=(const SparseVector& toBeAssignedVector);

        double dot(SparseVector& vector1, SparseVector& vector2);

};

#endif

#ifndef _SPARSEMATRIX_H_
#define _SPARSEMATRIX_H_

class SparseMatrix
{
    private:

        vector<int> rows;
        vector<SparseVector> allData;
        void constructMatrix(string filename); //reads the file and constructs matrix
        void findMaxRow(); //finds the max row in the vector
        int max_row; //max row with nonzero value(s) 

    public:

        SparseMatrix(string filename);
        SparseMatrix() {};
        
        int getMaxRow(void) const { return max_row; }
        const vector<int> getRows(void) const { return rows; } 
        vector<SparseVector>& getAllDataa(void) { return allData; }
        const vector<SparseVector>& getAllData(void) const { return allData; }
        Index_t findRow(int toBeSearchedRow);
    
        friend SparseMatrix operator+(SparseMatrix& matrix1, SparseMatrix& matrix2);
        friend SparseMatrix operator-(SparseMatrix& matrix1, SparseMatrix& matrix2);
        friend SparseMatrix operator-(SparseMatrix& positiveMatrix);
        friend ostream& operator<<(ostream& os, const SparseMatrix& toBePrintedMatrix);
        SparseMatrix& operator=(const SparseMatrix& toBeAssignedMatrix);
        friend SparseMatrix operator*(SparseMatrix& matrix1, SparseMatrix& matrix2);

        double transpose(SparseMatrix& matrix);

};

#endif

SparseMatrix::SparseMatrix(string filename)
{
    constructMatrix(filename);
    findMaxRow();
}

SparseMatrix operator+(SparseMatrix& matrix1, SparseMatrix& matrix2)
{
    double sum;
    unsigned int maxRow1 = matrix1.allData.size(),
                 maxRow2 = matrix2.allData.size(),
                 upperBoundRow = maxRow1, //upperBound of for loop, assign default value
                 upperBoundCol;

    if((maxRow1 < maxRow2)) //if maxIndex2 > maxIndex1
        upperBoundRow = maxRow2 + 1;

    SparseMatrix tempMatrix;
    SparseVector tempVector;
    Index_t sumRow1; //current to be summed row
    Index_t sumRow2;
    Index_t sumIndex1; //current to be summed index
    Index_t sumIndex2;

    for(unsigned int i = 0; i < upperBoundRow; i++) //sum elements of vector1 and vector2 and assign to temp
    {
        if(matrix1.allData[i].getMaxIndex() < matrix2.allData[i].getMaxIndex()) //if maxIndex2 > maxIndex1
            upperBoundCol = matrix2.allData[i].getMaxIndex() + 1; //upperbound of inner loop is size of the current row's of matrix2

        else //if maxIndex1 > maxIndex1
            upperBoundCol = matrix1.allData[i].getMaxIndex() + 1;

        sumRow1 = matrix1.findRow(i); //find where is the row i in matrix1
        sumRow2 = matrix2.findRow(i); 

        sumIndex1 = matrix1.allData[sumRow1.index].findIndex(i); //find where is the index i in the current row of the matrix1
        sumIndex2 = matrix2.allData[sumRow2.index].findIndex(i);

        if(sumIndex1.isExists && sumIndex2.isExists) //if the current row exists in the both matrices
        {
            tempVector = matrix1.allData[sumRow1.index] + matrix2.allData[sumRow2.index]; //sum rows with same indices
            tempMatrix.allData.push_back(tempVector); //add that sum to allData of the tempMatrix
        }

        else if(sumIndex1.isExists && !(sumIndex2.isExists))
        {
            tempVector = matrix1.allData[sumRow1.index];
            tempMatrix.allData.push_back(tempVector);
        }

        else if(!(sumIndex1.isExists) && (sumIndex2.isExists))
        {
            tempVector = matrix2.allData[sumRow2.index];
            tempMatrix.allData.push_back(tempVector);
        }
    }

    return tempMatrix;
}

SparseMatrix operator-(SparseMatrix& matrix1, SparseMatrix& matrix2)
{
    double sum;
    unsigned int maxRow1 = matrix1.allData.size(),
                 maxRow2 = matrix2.allData.size(),
                 upperBoundRow = maxRow1, //upperBound of for loop, assign default value
                 upperBoundCol;

    if((maxRow1 < maxRow2)) //if maxIndex2 > maxIndex1
        upperBoundRow = maxRow2 + 1;

    SparseMatrix tempMatrix;
    SparseVector tempVector;
    Index_t sumRow1; //current to be summed row
    Index_t sumRow2;
    Index_t sumIndex1; //current to be summed index
    Index_t sumIndex2;

    for(unsigned int i = 0; i < upperBoundRow; i++) //sum elements of vector1 and vector2 and assign to temp
    {
        if(matrix1.allData[i].getMaxIndex() < matrix2.allData[i].getMaxIndex()) //if maxIndex2 > maxIndex1
            upperBoundCol = matrix2.allData[i].getMaxIndex() + 1;

        else //if maxIndex1 > maxIndex1
            upperBoundCol = matrix1.allData[i].getMaxIndex() + 1;

        sumRow1 = matrix1.findRow(i); //find where is the row i in matrix 1
        sumRow2 = matrix2.findRow(i); 

        sumIndex1 = matrix1.allData[sumRow1.index].findIndex(i); //find where is the index i in the vector1
        sumIndex2 = matrix2.allData[sumRow2.index].findIndex(i);

        if(sumIndex1.isExists && sumIndex2.isExists)
        {
            tempVector = matrix1.allData[sumRow1.index] - matrix2.allData[sumRow2.index];
            tempMatrix.allData.push_back(tempVector);
        }

        else if(sumIndex1.isExists && !(sumIndex2.isExists))
        {
            tempVector = matrix1.allData[sumRow1.index];
            tempMatrix.allData.push_back(tempVector);
        }

        else if(!(sumIndex1.isExists) && (sumIndex2.isExists))
        {
            tempVector = matrix2.allData[sumRow2.index];
            tempMatrix.allData.push_back(tempVector);
        }
    }

    return tempMatrix;
}

SparseMatrix operator-(SparseMatrix& matrix)
{
    int maxRow = matrix.allData.size();
    
    SparseMatrix temp;

    for(double i = 0; i < maxRow; i++)
    {
        temp.allData[i] = -(matrix.allData[i]);
    }

    return temp;
}

SparseMatrix& SparseMatrix::operator=(const SparseMatrix& toBeAssignedMatrix)
{
    if (this != &toBeAssignedMatrix) // Check for self-assignment
    {
        this->max_row = toBeAssignedMatrix.max_row;
        this->allData = toBeAssignedMatrix.allData;
    }
    return *this;
}

ostream& operator<<(ostream& os, const SparseMatrix& toBePrintedMatrix)
{
    unsigned int maxRow = toBePrintedMatrix.allData.size();
    SparseVector toBePrintedVector;

    for(int i = 0; i < maxRow; i++) //traverse matrix's every row and print them
    {
        toBePrintedVector = toBePrintedMatrix.allData[i];
        os << toBePrintedVector << endl;
    }

    return os;
}

SparseMatrix operator*(SparseMatrix& matrix1, SparseMatrix& matrix2)
{
    return matrix1;
}

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
        iss.clear(); //clean the previous content
        iss.str(line); //adjust the newline
        
        iss >> row; //take the row at the beginning of the line
        rows.push_back(row); //adds that row to rows vector

        allData.push_back(SparseVector()); //resize the allData vector by adding one empty element to it

        while(iss >> element.index >> delim >> element.data) //read the file 3 by 3
        {
            if (delim == ':') 
            {
                allData[i].addData(element); //add the read element to allData
                allData[i].findMaxIndex(); //find max index in the allData vector for later operations
            }
        }

        i++;
    }

    max_row = i; //assign member max_row
    
    matrixFile.close();
}

void SparseMatrix::findMaxRow()
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

Index_t SparseMatrix::findRow(int toBeSearchedRow)
{
    Index_t temp;

    for(int i = 0; rows[i] <= toBeSearchedRow; i++) //search while the rows are less than the to be searched row
    {
        if(rows[i] == toBeSearchedRow)
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

double SparseMatrix::transpose(SparseMatrix& matrix)
{
    return 1;
}