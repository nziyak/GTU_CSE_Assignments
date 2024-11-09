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