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

class Field
{
    private:
        
        string name;
        int type;
        int dimension;

    public:

        Field(){};
        Field(string Name, int Type, int dim) : name(Name), type(Type), dimension(dim) {};
        
        string getName() const { return name; };
        int getType() const { return type; };
        int getDim() const { return dimension; };

        void setName(const string& newName) { name = newName; }
        void setType(const int& newType) { type = newType; }
        void setDim(const int& newDim) { dimension = newDim; }
};

class EntryBase
{
    public:
        virtual ~EntryBase() {};
};

template<typename T>
class Entry : public EntryBase
{
    private:
    
        T value;
    
    public:
        
        Entry() {};
        Entry(T val) : value(val) {};
        T getValue() {return value; };
};

class Table
{
    private:

       int fieldCounter; 
       string filename; 
       vector<Field> fields;
       vector < vector < vector<EntryBase*> > > entries;

    public:

        Table() : filename("data.txt"), fieldCounter(0) { entries.resize(10); }; 
        Table(string fileName) : filename(fileName), fieldCounter(0) { entries.resize(10); };
        ~Table();
        
        string getFilename() { return filename; };
        vector<Field> getFields() { return fields; };

        void parseFields();
        void parseEntries();
};

//################################################## TABLE FUNCTIONS ##################################################
Table::~Table()
{
    for (size_t i = 0; i < entries.size(); ++i) 
    {
        for (size_t j = 0; j < entries[i].size(); ++j) 
        {
            for (size_t k = 0; k < entries[i][j].size(); ++k) 
            {
                delete entries[i][j][k]; //free every pointer
            }
        }
    }
}

void Table::parseFields()
{
    ifstream file(filename);
    string tempNameSep, tempTypeSep, tempDimSep; //these are used while separating the fields
    
    string Name; 
    int Type, Dim; //these are used for assigning the values
    
    vector<string> unseparated_fields; //to hold fields divided by '|' character

    //check if the file is opened
    if (!file.is_open()) 
    {
        cout << filename << "could not been opened for field parsing!" << endl;
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
        getline(ss, tempNameSep, ':');
        Name = tempNameSep;
    //--------------------------------------
    
    //--------------take type--------------
        getline(ss, tempTypeSep, ':');

        if(tempTypeSep == "integer")
            Type = INT;

        else if(tempTypeSep == "double")
            Type = DOUBLE;

        else if(tempTypeSep == "float")
            Type = FLOAT;

        else if(tempTypeSep == "string")
            Type = STRING;
        
        else
            Type = DEFAULT_TYPE;
    //---------------------------------------
    
    //--------------take isArr--------------
        getline(ss, tempDimSep);

        if(tempDimSep == "single")    
            Dim = SINGLE;

        else if(tempDimSep == "multi")    
            Dim = MULTI;
        
        else
            Dim = DEFAULT_DIM;
    //---------------------------------------

        fields.push_back(Field(Name, Type, Dim));
    }

    //close the file
    file.close();

    /*for (int i = 0; i < fieldCounter; i++) 
    {
        cout << fields[i].getName() << ", " << fields[i].getType() << ", " << fields[i].getDim() << endl;
    }*/
}

void Table::parseEntries()
{
    ifstream file(filename);
    string entry, value, subentry; //currently processed entry and its value
    string line; //currently processed line
    vector<string> subentries;

    int intValue;
    double dblValue;
    float fltValue;

    if(!file.is_open())
    {
        cout << filename << "could not been opened for entry parsing!" << endl;
        exit(0);
    }

    if(getline(file, line)){} //if first line can be read, read and dont process it because its field line

    //parse every entry, check its type, then store it in entries with its type indicated in fields
    for(int i = 0; getline(file, line); i++) //then continue reading rest of the lines
    {
        stringstream ss(line);

        // Ensure there are enough rows
        if (entries.size() <= i)
        {
            entries.resize(i + 3);
        }

        for(int j = 0; getline(ss, entry, '|'); j++) //take every entry one by one
        {
            // Ensure there are enough columns in the current row
            if (entries[i].size() <= j)
            {
                entries[i].resize(j + 3);
            }
            
            if(fields[j].getDim() == SINGLE) //if entry will be stored as single
            {
                switch(fields[j].getType()) //learn the type of entry
                {
                    case INT: //if type is int

                        cout << "case:int," << entry << endl;
                        intValue = stoi(entry);
                        entries[i][j].push_back(new Entry<int>(intValue));  //create and push an entry with type int

                        break;

                    case DOUBLE:

                        cout << "case:double," << entry << endl;
                        dblValue = stod(entry);
                        entries[i][j].push_back(new Entry<double>(dblValue)); //create and push an entry with type double
                        
                        break;

                    case FLOAT:
                        
                        cout << "case:float," << entry << endl;
                        fltValue = stof(entry);
                        entries[i][j].push_back(new Entry<float>()); //create and push an entry with type float

                        break;

                    case STRING:

                        cout << "case:string," << entry << endl;
                        entries[i][j].push_back(new Entry<string>(entry)); //create and push an entry with type string

                        break;

                    case DEFAULT_TYPE: //default type is string
                        
                        cout << "case:default(string)," << entry << endl;
                        entries[i][j].push_back(new Entry<string>(entry)); //create and push an entry with type string
                }
            }

            /*else if(fields[i].getDim() == MULTI)
            {
                stringstream ssEntry(entry); //create string stream of entry to divide it to subentries
                
                switch(fields[j].getType()) //learn the type of entry
                {
                    case INT: //if type is int

                        getline(ssEntry, subentry, ':');
                        intValue = stoi(subentry);
                        entries[i].push_back(new Entry<int>(intValue));  //create and push an entry with type int

                        //cout << "case:int," << entry << endl;
                        while(getline(ssEntry, subentry, ':')) //add each subentry to subentries vector
                        {
                            intValue = stoi(subentry);
                            entries[i][j] = new Entry<int>(intValue); //add elements to entries[i][j] to create a array
                        }

                        break;

                    case DOUBLE:

                        cout << "case:double," << entry << endl;
                        dblValue = stod(entry);
                        entries[i].push_back(new Entry<double>(dblValue)); //create and push an entry with type double
                        
                        break;

                    case FLOAT:
                        
                        cout << "case:float," << entry << endl;
                        fltValue = stof(entry);
                        entries[i].push_back(new Entry<float>()); //create and push an entry with type float

                        break;

                    case STRING:

                        cout << "case:string," << entry << endl;
                        entries[i].push_back(new Entry<string>(entry)); //create and push an entry with type string

                        break;

                    case DEFAULT_TYPE: //default type is string
                        
                        cout << "case:default(string)," << entry << endl;
                        entries[i].push_back(new Entry<string>(entry)); //create and push an entry with type string
                }                
            }*/
        }
    }

    /*for(size_t i = 0; i < entries.size(); i++)
    {
        for(size_t j = 0; j < entries[i].size(); j++)
        {
            cout << entries[i][j] << ' ';
        }
        cout << endl;
    }*/
}

//################################################ END TABLE FUNCTIONS ##################################################

int main()
{
    Table table1;
    table1.parseFields();
    table1.parseEntries();
    return 0;
}
