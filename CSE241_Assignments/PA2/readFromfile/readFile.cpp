#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

using namespace std;

struct Data
{
    int index;
    double data;
};

vector<Data> allData;

vector<Data> readFile(string filename); //reads the file and returns the vector in the file
void findMaxIndex(int& max_index);

int main() 
{
    int max_index;
    
    allData = readFile("veri.txt");

    for(size_t i = 0; i < allData.size(); i++)
    {
        cout << allData[i].index << ":" << allData[i].data;
        cout << endl;
    }

    findMaxIndex(max_index);

    cout << endl << "max_index: " << max_index;

    return 0;
}

vector<Data> readFile(string filename)
{
    ifstream vectorFile(filename);
    vector<Data> allData;
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
    
    return allData;
}

void findMaxIndex(int &max_index)
{
    max_index = allData[0].index;

    for(int i = 0; i < allData.size(); i++)
    {
        if(max_index < allData[i].index) 
            max_index = allData[i].index;
    } 
}