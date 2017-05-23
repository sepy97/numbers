#pragma once

#include <string>
using namespace std;

class NumberException
{
public:
    NumberException(int code, string message, string source)
    {
        this->code = code;
        this->message = message;
        this->source = source;
    }
    ~NumberException() {}
    int getCode() const { return code; }
    string getMessage() const { return message; }
    string getSource() const { return source; }
private:
    int code;
    string message;
    string source;
};
