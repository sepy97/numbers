#pragma once
#include <string>
#include <vector>
#include "Number.h"
using namespace std;


class Variable
{
public:
    string name;
    vector<Number> values;

    Variable()
    {
    }

    Variable( string const &name )
    {
        this->name = name;
    }

    ~Variable()
    {
    }

};

inline bool operator<(Variable const &l, Variable const &r)
{
    return l.name < r.name;
}

