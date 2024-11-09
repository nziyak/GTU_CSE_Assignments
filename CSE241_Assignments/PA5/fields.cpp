#include <iostream>
#include <fstream>
#include <sstream>
#include <vector> 
#include <string>

using namespace std;

const int SINGLE = 1;
const int MULTI = 2;
const int DEFAULT_DIM = 7; //default dimension

const int INT = 3;
const int DOUBLE = 4;
const int FLOAT = 5;
const int STRING = 6;
const int DEFAULT_TYPE = 7;

class TableFields
{
    friend class Table;
    
    private:
        
        vector<string> names;
        vector<int> types;
        vector<int> dimensions;

    public:

        TableFields(){};
        vector<string> getNames() { return names; };
        vector<int> getTypes() { return types; };
        vector<int> getIsArrs() { return dimensions; };
};

class Entry
{
    private:
    
        void* value;
    
    public:
        
        Entry(void* val) : value(val) {};
        void* getValue() {return value; };
};

class Table
{
    private:

       int fieldCounter; 
       string filename; 
       TableFields fields;
       vector < vector<Entry> > entries;

    public:

        Table() : filename("data.txt"), fieldCounter(0) {}; 
        Table(string fileName) : filename(fileName), fieldCounter(0) {};
        
        string getFilename() { return filename; };
        TableFields getFields() { return fields; };

        void parseFields();
        void parseEntries();
};

//################################################## TABLE FUNCTIONS ##################################################
void Table::parseFields()
{
    ifstream file(filename);
    string tempName, tempType, tempIsArr;
    vector<string> unseparated_fields; //to hold fields divided by '|' character

    //check if the file is opened
    if (!file.is_open()) 
    {
        cout << filename << "could not been opened!" << endl;
        exit(0);
    }

    //read file line by line
    string line;
    string field;
    if(getline(file, line)) 
    {
        // divide line by "|" character
        stringstream ss(line);
        
        while (getline(ss, field, '|')) 
        {
            //add field to fields vector
            unseparated_fields.push_back(field);
            fieldCounter++;
        }
    }

    //separate each field into elements
    for(int i = 0; i < fieldCounter; i++)
    {
        stringstream ss(unseparated_fields[i]);
    //--------------take name--------------        
        getline(ss, tempName, ':');
        fields.names.push_back(tempName);
    //--------------------------------------
    
    //--------------take type--------------
        getline(ss, tempType, ':');

        if(tempType == "integer")
            fields.types.push_back(INT);

        else if(tempType == "double")
            fields.types.push_back(DOUBLE);

        else if(tempType == "float")
            fields.types.push_back(FLOAT);

        else if(tempType == "string")
            fields.types.push_back(STRING);
        
        else
            fields.types.push_back(DEFAULT_TYPE);
    //---------------------------------------
    
    //--------------take isArr--------------
        getline(ss, tempIsArr);

        if(tempIsArr == "single")    
            fields.dimensions.push_back(SINGLE);

        else if(tempIsArr == "multi")    
            fields.dimensions.push_back(MULTI);
        
        else
            fields.types.push_back(DEFAULT_DIM);
    //---------------------------------------
    }
    //close the file
    file.close();

    for (int i = 0; i < fieldCounter; i++) 
    {
        cout << fields.names[i] << ", " << fields.types[i] << ", " << fields.dimensions[i] << endl;
    }
}

void Table::parseEntries()
{

}
//################################################ END TABLE FUNCTIONS ##################################################

int main()
{
    Table table1;
    table1.parseFields();
    return 0;
}