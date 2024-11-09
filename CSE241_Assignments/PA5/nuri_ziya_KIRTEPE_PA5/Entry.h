#ifndef _ENTRY_H_
#define _ENTRY_H_

//#include <iostream>

using namespace std;

namespace PA5
{
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
            T getValueTyped() const { return value; }
            void print() const override { cout << value << endl; }

            const void* getValue() const override
            {
                return static_cast<const void*>(&value);
            }
    };
}

#endif