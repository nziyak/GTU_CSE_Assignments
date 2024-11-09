#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <exception>

using namespace std;

namespace PA5
{
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
}

#endif
