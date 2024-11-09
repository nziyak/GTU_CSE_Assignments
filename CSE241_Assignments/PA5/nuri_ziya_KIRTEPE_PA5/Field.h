#ifndef _FIELD_H_
#define _FIELD_H_

#include <string>

using namespace std;

namespace PA5
{
    class Field
    {
        private:
            string name;
            int type;
            int dimension;

        public:
            Field() {};
            Field(string Name, int Type, int dim) : name(Name), type(Type), dimension(dim) {};

            string getName() const { return name; };
            int getType() const { return type; };
            int getDim() const { return dimension; };

            void setName(const string& newName) { name = newName; };
            void setType(const int& newType) { type = newType; };
            void setDim(const int& newDim) { dimension = newDim; };
    };
}

#endif
