#include <iostream>
#include <fstream>
#include <sstream>
#include <vector> 

using namespace std;

const int SINGLE = 1;
const int MULTI = 2;

class catalog
{
    private:

        vector< vector<field> > fields;
        void separator(string filename); //function to separate the format line to fields
        string filename;

    public:

        catalog() : filename("data.txt") {}; 
        catalog(string fileName) : filename(fileName) {};
        vector< vector<field> > getFields() { return fields; };
};

class field
{
    private:

        string name;
        string type;
        void* value; //value of entry
        int isArr;

    public:

        field(string fieldName, string fieldType, int fieldIsArr) : name(fieldName), type(fieldType), isArr(fieldIsArr) {};  
        void createEntries();
        string getName() { return name; };
        string getType() { return type; };
        int getIsArr() { return isArr; };
};

class command
{
    private:

        vector<string> values;
        vector<string> field_names;
        string filename;

    public:
        
        command() : filename("command.txt") {};
        command(string fileName) : filename(fileName) {};
        void separator();
        string get_value_at(int index) { return values[index]; }; //get the value at given index
        string get_field_name_at(int index) { return field_names[index]; }; //get the field name at given index
        void search();
        void sort();
};

template<typename T>
void catalog<T>::separator(string filename)
{
    ifstream file(filename);

    //check if the file is opened
    if (!file.is_open()) 
    {
        cout << filename << "could not been opened!" << endl;
        return 1;
    }

    //read file line by line
    string line;
    while (getline(file, line)) 
    {
        // divide line by "|" character
        stringstream ss(line);
        string field;
        while (getline(ss, field, '|')) 
        {
            //add field to fields vector
            fields.push_back(field);
        }
    }

    //print fields
    for (const string& field : fields) 
    {
        cout << field << endl;
    }

    //close the file
    file.close();
}

int main()
{
    catalog catalog1("data.txt");

    return 0;
}