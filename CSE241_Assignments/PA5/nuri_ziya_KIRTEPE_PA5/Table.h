#ifndef _TABLE_H_
#define _TABLE_H_

#include <iostream>
#include <fstream>
#include <sstream>

#include <unordered_map>
#include <unordered_set>
#include <vector> 
#include <map>
#include <set>

#include <string>

#include "Field.h"
#include "Entry.h"
#include "Command.h"
#include "Exceptions.h"
#include "Constants.h"

using namespace std;

namespace PA5
{
    class Table
    {
        private:
            int fieldCounter;
            string data_file_name;
            string command_file_name;
            string output_file_name;
            vector<Field> fields;
            vector<vector<vector<EntryBase*>>> entries;
            vector<string> firstColEntries;
            vector<string> unseparated_entries;
            vector<Command> commands;
            vector<string> unseparated_commands;

            string extractQuotedString(const string& input);

        public:
            Table() : data_file_name("data.txt"), command_file_name("command.txt"), output_file_name("output.txt"), fieldCounter(0) { entries.resize(10); };
            Table(string dataFileName, string commandFileName, string outFileName) : data_file_name(dataFileName), command_file_name(commandFileName), output_file_name(outFileName), fieldCounter(0) { entries.resize(10); };
            ~Table();

            string get_data_file_name() const { return data_file_name; };
            string get_command_file_name() const { return command_file_name; };
            vector<Field> getFields() const { return fields; };
            vector<Command> getCommands() const { return commands; };

            void parseFields();
            void parseEntries();
            void parseCommands();
            void executeCommands();
    };
}

#endif
