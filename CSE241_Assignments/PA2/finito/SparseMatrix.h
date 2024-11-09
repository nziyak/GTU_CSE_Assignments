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

class SparseVector //TODO: WRITE THE CONSTRUCTORS
{
    private:

        int max_index;
        vector<Data> allData;
        void constructVector(string filename); //reads the file and returns the vector in the file

    public:

        SparseVector(string filename);
        SparseVector(int maxIndex);
        SparseVector() : max_index(-1), allData() {}
        
        int getMaxIndex(void) { return max_index; }
        void findMaxIndex();
        vector<Data>& getAllDataa() { return allData; }
        const vector<Data>& getAllData() { return allData; }
        void addData(const Data& data) { allData.push_back(data); }
        Index_t findIndex(int toBeSearchedIndex);

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
