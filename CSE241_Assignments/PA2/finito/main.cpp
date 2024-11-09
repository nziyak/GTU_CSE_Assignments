#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "SparseVector.h"
#include "SparseMatrix.h"

using namespace std;

int main()
{
    ofstream outfile;
    outfile.open("output.txt", ios::out | ios::trunc );
    
    //Creating a SparseVector from file
    SparseVector v1("/Users/nziyak/Documents/GitHub/GTU_CSE_Assignments/CSE241_Assignments/PA2/readFromfile/output/veri.txt");
    outfile<<"v1"<<endl<<v1<<endl;
    
    //Binary operations and assignment
    v1 = v1 + v1;
    outfile<<"v1+v1"<<endl<<v1<<endl;

    v1 = v1.dot(v1,v1);
    outfile<<"v1 dot v1"<<endl<<v1<<endl;

    v1 = v1 - v1;
    outfile<<"v1-v1"<<endl<<v1<<endl;

    SparseMatrix m1("/Users/nziyak/Documents/GitHub/GTU_CSE_Assignments/CSE241_Assignments/PA2/readFromfile/output/matrix1.txt");
    SparseMatrix m2("/Users/nziyak/Documents/GitHub/GTU_CSE_Assignments/CSE241_Assignments/PA2/readFromfile/output/matrix1.txt");
    outfile<<"m1"<<endl<<m1<<endl;
    
    //Binary operations and assignment
    m1 = m1 + m1;
    outfile<<"m1+m1"<<endl<<m1<<endl;

    outfile<<m1-m2<<endl;

    return 0;
}
