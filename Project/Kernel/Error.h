#pragma once
#include <string>
using namespace std;

class Error
{
public:
    enum Code {
        OK,
        InvalidFormat,
        DivisionByZero,
        InputError,
        DuplicateItem,
        ItemNotFound,
        YetNotImplemented,
    };
    static string explainCode(int code)
    {
        switch(code)
        {
        case OK:
            return "OK";
        case InvalidFormat:
            return "Invalid format";
        case DivisionByZero:
            return "Division by zero";
        case InputError:
            return "Input error";
        case DuplicateItem:
            return "Duplicate Item";
        case ItemNotFound:
            return "Item not found";
        case YetNotImplemented:
            return "Yet not implemented";
        default:
            return "???????";
        }
    }
};
