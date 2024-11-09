#include <iostream>
#include <fstream>
#include <sstream>
#include <vector> 
#include <string>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

using namespace std;

const int SINGLE = 1;
const int MULTI = 2;
const int DEFAULT_DIM = 7; //default dimension

const int CHAR = 2;
const int INT = 3;
const int DOUBLE = 4;
const int FLOAT = 5;
const int STRING = 6;
const int DEFAULT_TYPE = 7;

const int NUM_OF_EL_IN_SEARCH_LINE = 4; //required number of elements in search command line
const int NUM_OF_EL_IN_SORT_LINE = 2;  //required number of elements in sort command line

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
        virtual ~EntryBase() {}
        virtual void print() const = 0;
    
        virtual const void* getValue() const = 0; 
};

template<typename T>
class Entry : public EntryBase 
{
    private:
        T value;

    public:
        Entry() {}
        Entry(T val) : value(val) {}
        T getValueTyped() const { return value; } // Typed getValue
        void print() const override { std::cout << value << std::endl; }

        // Type-erased getValue implementation
        const void* getValue() const override 
        {
            return static_cast<const void*>(&value);
        }
};

class Command
{
    private:
        
        string operation; 
        string value;
        string field_name;
        bool isValid;
    
    public:

        Command() : isValid(true) {};
        Command(string op, string& f_name, bool isValiD) : operation(op), field_name(f_name), isValid(isValiD) {};
        Command(string op, string& val, string& f_name, bool isValiD) : operation(op), value(val), field_name(f_name), isValid(isValiD) {};
        
        string getOperation() const { return operation; };
        string getValue() const { return value; };
        string get_field_name() const { return field_name; };
        bool get_isValid() const { return isValid; };
        void setOperation(string &toSetOp) { operation = toSetOp; };
        void setValue(string &toSetVal) { value = toSetVal; };
        void set_field_name(string &toSetFieldName) { field_name = toSetFieldName; };
};

class Table
{
    private:

       int fieldCounter; 
       string data_file_name;
       string command_file_name; 
       string output_file_name;
       vector <Field> fields;
       vector < vector < vector <EntryBase*> > > entries;
       vector <string> firstColEntries;
       vector <string> unseparated_entries; //to create log
       vector <Command> commands;
       vector <string> unseparated_commands; //to create log

       string extractQuotedString(const string& input);

    public:

        Table() : data_file_name("data.txt"), command_file_name("command.txt"), output_file_name("output.txt"), fieldCounter(0) { entries.resize(10); }; 
        Table(string dataFileName, string commandFileName, string outFileName) : data_file_name(dataFileName), command_file_name(commandFileName), output_file_name(outFileName), fieldCounter(0) { entries.resize(10); };
        ~Table();
        
        string get_data_file_name() const { return data_file_name; };
        string get_command_file_name() const { return data_file_name; };
        vector<Field> getFields() const { return fields; };
        vector<Command> getCommands() const { return commands; };

        void parseFields();
        void parseEntries();
        void parseCommands();
        void executeCommands();

};

class WrongCommandException : public exception 
{
    public:
        
        const char* what() const noexcept override 
        {
            return "Exception: command is wrong";
        }
};

class DuplicateEntryException : public exception 
{
    public:
        
        const char* what() const noexcept override 
        {
            return "Exception: duplicate entry";
        }
};

class MissingFieldException : public exception 
{
    public:
        
        const char* what() const noexcept override 
        {
            return "Exception: missing field";
        }
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
    ifstream data_file(data_file_name);
    string tempNameSep, tempTypeSep, tempDimSep; //these are used while separating the fields
    
    string Name; 
    int Type, Dim; //these are used for assigning the values
    
    vector<string> unseparated_fields; //to hold fields divided by '|' character

    //check if the file is opened
    if (!data_file.is_open()) 
    {
        cout << data_file_name << "could not been opened for field parsing!" << endl;
        exit(0);
    }

    //read file line by line
    string line;
    string field;
    if(getline(data_file, line)) 
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

        if(tempTypeSep == "char")
            Type = CHAR;

        else if(tempTypeSep == "integer")
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
    
    //---------------take Dim----------------
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
    data_file.close();

    /*for (int i = 0; i < fieldCounter; i++) 
    {
        cout << fields[i].getName() << ", " << fields[i].getType() << ", " << fields[i].getDim() << endl;
    }*/
}

void Table::parseEntries()
{
    ifstream data_file(data_file_name);
    string entry, value, subentry; //currently processed entry and its value
    string line; //currently processed line
    vector<string> subentries;

    char charValue;
    int intValue;
    double dblValue;
    float fltValue;

    if(!data_file.is_open())
    {
        cout << data_file_name << "could not been opened for entry parsing!" << endl;
        exit(0);
    }

    if(getline(data_file, line)){} //if first line can be read, read and dont process it because its field line

    //parse every entry, check its type, then store it in entries with its type indicated in fields
    for(int i = 0; getline(data_file, line); i++) //then continue reading rest of the lines
    {
        if(line.empty()) 
        {
            continue;
        }
       
        stringstream ss(line);

        // Ensure there are enough rows
        if (entries.size() <= i)
        {
            entries.resize(i + 1);
        }

        unseparated_entries.push_back(line + "\n"); //add line to unseparated entries

        for(int j = 0; getline(ss, entry, '|'); j++) //take every entry one by one
        {
            // Ensure there are enough columns in the current row
            if (entries[i].size() <= j)
            {
                entries[i].resize(j + 1);
            }

            if(j == 0) //take only the first column entries
                firstColEntries.push_back(entry);

            if(fields[j].getDim() == SINGLE) //if entry will be stored as single
            {
                switch(fields[j].getType()) //learn the type of entry
                {
                    case CHAR: //if type is int

                        charValue = entry[0];
                        entries[i][j].push_back(new Entry<char>(charValue));  //create and push an entry with type int

                        break;
                    
                    case INT: //if type is int

                        //cout << "case:int," << entry << endl;
                        intValue = stoi(entry);
                        entries[i][j].push_back(new Entry<int>(intValue));  //create and push an entry with type int

                        break;

                    case DOUBLE:

                        //cout << "case:double,j: " << entry << ", " << j << endl;
                        dblValue = stod(entry);
                        entries[i][j].push_back(new Entry<double>(dblValue)); //create and push an entry with type double
                        
                        break;

                    case FLOAT:
                        
                        //cout << "case:float," << entry << endl;
                        fltValue = stof(entry);
                        entries[i][j].push_back(new Entry<float>()); //create and push an entry with type float

                        break;

                    case STRING:

                        //cout << "case:string," << entry << endl;
                        entries[i][j].push_back(new Entry<string>(entry)); //create and push an entry with type string

                        break;

                    case DEFAULT_TYPE: //default type is string
                        
                        //cout << "case:default(string)," << entry << endl;
                        entries[i][j].push_back(new Entry<string>(entry)); //create and push an entry with type string
                }
            }

            else if(fields[j].getDim() == MULTI)
            {
                stringstream ssEntry(entry); //create string stream of entry to divide it to subentries
                
                switch(fields[j].getType()) //learn the type of entry
                {
                    case INT: //if type is int

                        //cout << "case: int & multi\n";
                        while(getline(ssEntry, subentry, ':')) //add each subentry to subentries vector
                        {
                            intValue = stoi(subentry);
                            //cout << "   subentry,j:" << intValue << "," << j << endl;
                            entries[i][j].push_back(new Entry<int>(intValue));  //add element to vector at coordinates i,j
                        }

                        break;

                    case DOUBLE:

                        //cout << "case: double & multi\n";
                        while(getline(ssEntry, subentry, ':')) //add each subentry to subentries vector
                        {
                            dblValue = stod(subentry);
                            //cout << "   subentry,j:" << dblValue << "," << j << endl;
                            entries[i][j].push_back(new Entry<double>(dblValue));  //add element to vector at coordinates i,j
                        }
                        
                        break;

                    case FLOAT:
                        
                        //cout << "case: float & multi\n";
                        while(getline(ssEntry, subentry, ':')) //add each subentry to subentries vector
                        {
                            fltValue = stof(subentry);
                            //cout << "   subentry,j:" << fltValue << "," << j << endl;
                            entries[i][j].push_back(new Entry<float>(fltValue));  //add element to vector at coordinates i,j
                        }

                        break;

                    case STRING:

                        //cout << "case: string & multi\n";
                        while(getline(ssEntry, subentry, ':')) //add each subentry to subentries vector
                        {
                            //cout << "   subentry,j:" << subentry << "," << j << endl;
                            entries[i][j].push_back(new Entry<string>(subentry));  //add element to vector at coordinates i,j
                        }

                        break;

                    case DEFAULT_TYPE: //default type is string
                        
                        //cout << "case: string & multi\n";
                        while(getline(ssEntry, subentry, ':')) //add each subentry to subentries vector
                        {
                            //cout << "   subentry:" << subentry << endl;
                            entries[i][j].push_back(new Entry<string>(subentry));  //add element to vector at coordinates i,j
                        }
                }                
            }
        }
    }

    data_file.close();
}

void Table::parseCommands()
{
    ifstream command_file(command_file_name);

    if(!command_file.is_open())
    {
        cout << command_file_name << "could not been opened for command parsing!" << endl;
        exit(0);
    }

    string line, element;
    vector<string> elements; //to hold elements in a line
    string op, val, f_name, check; //check is for if there is more info then we want
    bool isvalid = true;
    int elementCtr = 0;

    size_t first_quote_pos;
    size_t second_quote_pos;
    size_t third_quote_pos;
    size_t fourth_quote_pos;

    while (getline(command_file, line)) 
    {
        stringstream ssline(line);

        unseparated_commands.push_back(line+"\n");

        isvalid = true; //first assume that current command line is valid
        elements.clear(); //clear elements to take new command line
        elementCtr = 0; //initialize element counter to 0

        while (getline(ssline, element, ' ')) 
        {
            elements.push_back(element);
        }

        if(elements[0] == "search") //if command is search
        {
            op = elements[0]; //take operation
            elementCtr++;

            //find position of the 1st "
            first_quote_pos = line.find('"');
            //find position of the 2nd "
            second_quote_pos = line.find('"', first_quote_pos + 1);

            //start from the position of the 1st ", take the substr to the 2nd " 
            val = line.substr(first_quote_pos + 1, second_quote_pos - first_quote_pos - 1);
            elementCtr++;

            //start from the position of the 2nd ",find position of the 3rd "
            third_quote_pos = line.find('"', second_quote_pos + 1);
            //find position of the 4th "
            fourth_quote_pos = line.find('"', third_quote_pos + 1);

            //start from the position of the 3rd ", take the substr to the 4th " 
            f_name = line.substr(third_quote_pos + 1, fourth_quote_pos - third_quote_pos - 1);
            elementCtr++;

            //cout << op << endl << val << endl << f_name << endl; 

            stringstream subssline(line.substr(fourth_quote_pos+1)); //to check if extra infos exists(fourth_quote_pos+1 because of the second ")

            if (elementCtr < 3 || subssline >> check || val.empty() || f_name.empty()) //if not enough elements exist OR any extra info exists OR value or field_name could not been taken
            {
                isvalid = false;
            }

            else //if still valid check if given field name exists in table
            {
                auto it = find_if(fields.begin(), fields.end(), [&f_name](const Field& field) { return field.getName() == f_name; }); //look if field name is valid with a lambda function

                if (it == fields.end()) //if field name could not been found in fields, command is not valid
                    isvalid = false;
            }
            
            commands.push_back(Command(op, val, f_name, isvalid));
        }

        else if(elements[0] == "sort") //TODO: TEST WITH COMMAND.TXT WITH SORT COMMAND LINES
        {
            op = elements[0]; // operation
            elementCtr++;

            //find position of the 1st "
            first_quote_pos = line.find('"');
            //find position of the 2nd "
            second_quote_pos = line.find('"', first_quote_pos + 1);

            //start from the position of the 1st ", take the substr to the 2nd " 
            f_name = line.substr(first_quote_pos + 1, second_quote_pos - first_quote_pos - 1);
            elementCtr++;

            stringstream subssline(line.substr(second_quote_pos+1)); //to check if extra infos exists

            if (elementCtr < 2 || subssline >> check || f_name.empty()) //if not enough elements exist OR any extra info exists OR field_name could not been taken
            {
                isvalid = false;
            }

            else
            {
                auto it = find_if(fields.begin(), fields.end(), [&f_name](const Field& field) { return field.getName() == f_name; }); //look if field name is valid with a lambda function

                if (it == fields.end()) //if field name could not been found in fields, command is not valid
                    isvalid = false;
            }

            commands.push_back(Command(op, f_name, isvalid));
        }
    }

    command_file.close();
}

void Table::executeCommands()
{
    ofstream outfile(output_file_name);

//------------------------------print table------------------------------
    int i;

    //first print fields
    for(i = 0; i < fields.size(); i++)
    {
        outfile << fields[i].getName();
        
        if (i != fields.size() - 1) 
            outfile << "|";
    }
    outfile << endl;

    /*for(i = 0; i < unseparated_entries.size(); i++)
    {
        outfile << unseparated_entries[i];
    }*/
//-----------------------------------------------------------------------
//----------------------print num of unique entries----------------------
    int unique_ctr;

    unordered_set<string> unique_elements(firstColEntries.begin(), firstColEntries.end()); //take unique entries of the first column(unordered set holds unique elements)

    unique_ctr = unique_elements.size(); //take num of unique entries
    
    outfile << unique_ctr << " unique entries\n";
//-----------------------------------------------------------------------
//----------------------------throw exceptions---------------------------
    //---------------------duplicate entry exception---------------------
        unordered_map<string, int> firstColMap; //to hold num of occurences of first col entries

        //traverse firstColEntriesVec vector and calculate num of occurences
        for(const string& entry : firstColEntries) 
        {
            firstColMap[entry]++;
        }

        for(const auto& pair : firstColMap) //throw duplicate entry exceptions by occurence numbers of the first fields
        {
            try
            {
                if(pair.second > 1) //if the current element occured more than once
                {
                    throw(DuplicateEntryException()); //throw exception
                }
            }
            catch(DuplicateEntryException& d)
            {
                for(i = 0; i < firstColEntries.size(); i++) 
                {
                    if(firstColEntries[i] == pair.first) //find the index of the more than once occured entry
                    {    
                        outfile << d.what() << endl;
                        outfile << unseparated_entries[i]; //print the line which includes repeated entry
                    }
                }
            }
        }
    //-------------------------------------------------------------------
    //----------------------wrong command exception----------------------
        for(i = 0; i < commands.size(); i++) //throw wrong command exceptions by invalidity of commands
        {
            try
            {
                if(!commands[i].get_isValid())
                {
                    throw(WrongCommandException());
                }
            }
            catch(WrongCommandException& c)
            {
                outfile << c.what() << endl;
                outfile << unseparated_commands[i];
            }
        }
    //-------------------------------------------------------------------
    //----------------------missing field exception----------------------
        for(i = 0; i < entries.size(); i++)
        {
            try
            {
                if(entries[i].size() < fields.size())
                {
                    throw(MissingFieldException());
                }
            }
            catch(MissingFieldException& m)
            {
                outfile << m.what() << endl;
                outfile << unseparated_entries[i];
            }
        }
    //-------------------------------------------------------------------
//-----------------------------------------------------------------------
//----------------------------execute commands---------------------------
    const Entry<string>* stringEntryPtr;
    const Entry<double>* dblEntryPtr;
    const Entry<int>* intEntryPtr;
    const Entry<char>* charEntryPtr;

    string fieldName, toBeSearched_valueStr, comparison_valueStr;
    double comparison_valueDbl, toBeSearched_valueDbl;
    int comparison_valueInt, toBeSearched_valueInt;
    char comparison_valueCh, toBeSearched_valueCh;
    int j, k;


    for(i = 0; i < commands.size(); i++) //traverse all commands
    {
        if(commands[i].get_isValid()) //execute command if only its a valid command
        {
            outfile << unseparated_commands[i]; //first print the command

            fieldName = commands[i].get_field_name(); //take the to be used field name

            for(j = 0; j < fields.size(); j++) //search which fields has the given name
            {
                if(fields[j].getName() == fieldName) 
                    break;
            }
            
            if(commands[i].getOperation() == "search") //if command is search
            {
                toBeSearched_valueStr = commands[i].getValue(); //take the to be searched value

                if(fields[j].getDim() == SINGLE) //if field is single look at just its [k][j][0] indiced elements
                {
                    for(k = 0; k < entries.size(); k++) //look at every row of the entries
                    {   
                        //look at the entries at same column j, which is the field we search in

                        if (fields[j].getType() == STRING) //if type of the column is string
                        {
                            stringEntryPtr = dynamic_cast<const Entry<string>*>(entries[k][j][0]); //try to cast EntryBase* to Entry<string>* to be able to compare
                            
                            comparison_valueStr = stringEntryPtr->getValueTyped();
                            
                            if(comparison_valueStr.find(toBeSearched_valueStr) != string::npos) //if current string at line includes to be searched string
                            {
                                outfile << unseparated_entries[k];
                                //break; //if found dont continue looking
                            } 
                        }

                        else if (fields[j].getType() == DOUBLE) //if double* cast is succesful
                        {
                            dblEntryPtr = dynamic_cast<const Entry<double>*>(entries[k][j][0]); //try to cast EntryBase* to Entry<string>* to be able to compare
                            
                            comparison_valueDbl = dblEntryPtr->getValueTyped();
                            toBeSearched_valueDbl = stod(toBeSearched_valueStr);
                            
                            if (comparison_valueDbl == toBeSearched_valueDbl) 
                            {
                                outfile << unseparated_entries[k];
                                //break;
                            } 
                        }

                        else if (fields[j].getType() == INT) //if int* cast is succesful
                        {
                            intEntryPtr = dynamic_cast<const Entry<int>*>(entries[k][j][0]); //try to cast EntryBase* to Entry<string>* to be able to compare
                            
                            comparison_valueInt = intEntryPtr->getValueTyped();
                            toBeSearched_valueInt = stoi(toBeSearched_valueStr);
                            
                            if (comparison_valueInt == toBeSearched_valueInt) 
                            {
                                outfile << unseparated_entries[k];
                                //break;
                            } 
                        }

                        else if (fields[j].getType() == CHAR) //if int* cast is succesful
                        {
                            charEntryPtr = dynamic_cast<const Entry<char>*>(entries[k][j][0]); //try to cast EntryBase* to Entry<string>* to be able to compare
                            
                            comparison_valueCh = charEntryPtr->getValueTyped();
                            toBeSearched_valueCh = toBeSearched_valueStr[0];
                            
                            if (comparison_valueCh == toBeSearched_valueCh) 
                            {
                                outfile << unseparated_entries[k];
                                //break;
                            } 
                        }

                        else  
                            cout << "cast unsuccesful\n";
                    }
                }

                else if(fields[j].getDim() == MULTI) //if field is multi look at all elements vertically
                {
                    for(k = 0; k < entries.size(); k++) //look at every row of the entries
                    {   
                        //look at the entries at same column j, which is the field we search in

                        if (fields[j].getType() == STRING) //if type of the column is string
                        {
                            for(int p = 0; p < entries[k][j].size(); p++) //look whole vector at the position k, j
                            {
                                stringEntryPtr = dynamic_cast<const Entry<string>*>(entries[k][j][p]); //try to cast EntryBase* to Entry<string>* to be able to compare
                                
                                comparison_valueStr = stringEntryPtr->getValueTyped();
                                
                                if(comparison_valueStr.find(toBeSearched_valueStr) != string::npos) //if current string at line includes to be searched string
                                {
                                    outfile << unseparated_entries[k];
                                    break; //if found dont continue looking
                                } 
                            }    
                        }

                        else if (fields[j].getType() == DOUBLE) //if double* cast is succesful
                        {
                            for(int p = 0; p < entries[k][j].size(); p++) //look whole vector at the position k, j
                            {
                                dblEntryPtr = dynamic_cast<const Entry<double>*>(entries[k][j][p]); //try to cast EntryBase* to Entry<string>* to be able to compare
                                
                                comparison_valueDbl = dblEntryPtr->getValueTyped();
                                toBeSearched_valueDbl = stod(toBeSearched_valueStr);
                                
                                if (comparison_valueDbl == toBeSearched_valueDbl) 
                                {
                                    outfile << unseparated_entries[k];
                                    break;
                                } 
                            }
                        }

                        else if (fields[j].getType() == INT) //if int* cast is succesful
                        {
                            for(int p = 0; p < entries[k][j].size(); p++) //look whole vector at the position k, j
                            {
                                intEntryPtr = dynamic_cast<const Entry<int>*>(entries[k][j][p]); //try to cast EntryBase* to Entry<string>* to be able to compare
                                
                                comparison_valueInt = intEntryPtr->getValueTyped();
                                toBeSearched_valueInt = stoi(toBeSearched_valueStr);
                                
                                if (comparison_valueInt == toBeSearched_valueInt) 
                                {
                                    outfile << unseparated_entries[k];
                                    break;
                                } 
                            }
                        }

                        else if (fields[j].getType() == CHAR) //if int* cast is succesful
                        {
                            for(int p = 0; p < entries[k][j].size(); p++) //look whole vector at the position k, j
                            {
                                charEntryPtr = dynamic_cast<const Entry<char>*>(entries[k][j][p]); //try to cast EntryBase* to Entry<string>* to be able to compare
                                
                                comparison_valueCh = charEntryPtr->getValueTyped();
                                toBeSearched_valueCh = toBeSearched_valueStr[0];
                                
                                if (comparison_valueCh == toBeSearched_valueCh) 
                                {
                                    outfile << unseparated_entries[k];
                                    break;
                                } 
                            }
                        }

                        else  
                            cout << "cast unsuccesful\n";
                    }
                }
            }

            else if(commands[i].getOperation() == "sort")
            {
                map<string, int> ToBeOperatedFieldStr; //key is entry, value is row index
                map<int, int> ToBeOperatedFieldInt; //key is entry, value is row index
                map<double, int> ToBeOperatedFieldDbl; //key is entry, value is row index
                map<char, int> ToBeOperatedFieldCh; //key is entry, value is row index
                
                //before execute the command create an unique-elemented and sorted copy of the field that operations will be held on (no sort will be held on multi fields)
                
                if (fields[j].getType() == STRING) //if type of the column is string
                {
                    for(k = 0; k < entries.size(); k++) 
                    {
                        stringEntryPtr = dynamic_cast<const Entry<string>*>(entries[k][j][0]); //try to cast EntryBase* to Entry<string>* to be able to compare
                        ToBeOperatedFieldStr.insert({stringEntryPtr->getValueTyped(), k}); //add entries and their row indices as pairs
                    }

                    for(auto pair: ToBeOperatedFieldStr)
                    {
                        outfile << unseparated_entries[pair.second]; //print entry lines in a order which indicated in map ToBeOperatedField
                    }
                }

                else if (fields[j].getType() == INT) //if type of the column is string
                {
                    for(k = 0; k < entries.size(); k++) 
                    {                        
                        intEntryPtr = dynamic_cast<const Entry<int>*>(entries[k][j][0]); //try to cast EntryBase* to Entry<string>* to be able to compare
                        ToBeOperatedFieldInt.insert({intEntryPtr->getValueTyped(), k}); //add entries and their row indices as pairs
                    }

                    for(auto pair: ToBeOperatedFieldInt)
                    {
                        outfile << unseparated_entries[pair.second]; //print entry lines in a order which indicated in map ToBeOperatedField
                    } 
                }

                else if (fields[j].getType() == DOUBLE) //if type of the column is string
                {
                    for(k = 0; k < entries.size(); k++) 
                    {
                        dblEntryPtr = dynamic_cast<const Entry<double>*>(entries[k][j][0]); //try to cast EntryBase* to Entry<string>* to be able to compare
                        ToBeOperatedFieldDbl.insert({dblEntryPtr->getValueTyped(), k}); //add entries and their row indices as pairs
                    }

                    for(auto pair: ToBeOperatedFieldDbl)
                    {
                        outfile << unseparated_entries[pair.second]; //print entry lines in a order which indicated in map ToBeOperatedField
                    }
                }  

                else if (fields[j].getType() == CHAR) //if type of the column is string
                {
                    for(k = 0; k < entries.size(); k++) 
                    {
                        charEntryPtr = dynamic_cast<const Entry<char>*>(entries[k][j][0]); //try to cast EntryBase* to Entry<string>* to be able to compare
                        ToBeOperatedFieldCh.insert({charEntryPtr->getValueTyped(), k}); //add entries and their row indices as pairs
                    }

                    for(auto pair: ToBeOperatedFieldCh)
                    {
                        outfile << unseparated_entries[pair.second]; //print entry lines in a order which indicated in map ToBeOperatedField
                    }
                }           
            }
        }
    }
//-----------------------------------------------------------------------
    outfile.close();
}

string Table::extractQuotedString(const string& input) 
{
    size_t start = input.find('"'); //find first quote
    
    if (start != string::npos) //if first quote is found look for the second quote
    {
        size_t end = input.find('"', start + 1); //look for the second quote, start looking from the index just after the first quote
        
        if (end != string::npos) 
        {
            return input.substr(start + 1, end - start - 1); //return the string between quotes
        }
    }
    return "";
}
//################################################ END TABLE FUNCTIONS ##################################################

int main()
{
    Table table1;
    table1.parseFields();
    table1.parseEntries();
    table1.parseCommands();
    //table1.printTable();
    table1.executeCommands();
    return 0;
}
