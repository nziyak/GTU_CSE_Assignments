#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <string>

using namespace std;

namespace PA5
{
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
}

#endif
