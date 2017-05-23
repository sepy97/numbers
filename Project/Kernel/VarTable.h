#pragma once

#include <map>
using namespace std;
#include "Variable.h"
#include "Error.h"


class VarTable
{
public:
    typedef map<string, Variable >::iterator iterator;
    typedef map<string, Variable >::const_iterator const_iterator;
    //template<typename T>
    //typename MyTemplate<T>::Inner  MyTemplate<T>::met()
    //{
    //  return typename MyTemplate<T>::Inner();
    //}
    // template<typename T> typedef Variable<T> vt;
    typedef map<string, Variable > msv;
    map<string, Variable> variables;
    VarTable()
    {
		Variable pi; pi.name = "PI"; pi.values.push_back(Number("3141592653589793238/1000000000000000000")); add(pi);
		Variable e; e.name = "E"; e.values.push_back(Number("2718281828459045235/1000000000000000000")); add(e);
    }

    ~VarTable()
    {
    }

    int add( Variable const &var )
    {
        iterator val = variables.find(var.name);
        if (val != variables.end())
        {
            return Error::DuplicateItem;
        }
        variables.insert(make_pair(var.name, var));
        return Error::OK;
    }

    int find(string const &name, Variable &ret) const
    {
        const_iterator val = variables.find(name);
        if (val == variables.end())
        {
            return Error::ItemNotFound;
        }
        ret = val->second;
        return Error::OK;
    }

    int setValue( string const &name, Number const& value)
    {
        iterator val = variables.find(name);
        if (val == variables.end())
        {
            return Error::ItemNotFound;
        }
        if (val->second.values.empty())
        {
            val->second.values.push_back(value);
        }
        else
        {
            val->second.values[0] = value;
        }
        return Error::OK;

    }

    int clearNonSystem()
    {
        msv newVars;
        for (iterator it = variables.begin(); it != variables.end(); it++)
        {
            if ( (it->first.size() > 0 && it->first[0] == '$') || it->first == "PI" || it->first == "E")
            {
                newVars.insert(make_pair(it->first, it->second));
            }
        }
        variables = newVars;
        return Error::OK;
    }


    vector<string> getAllNames() const
    {
        vector<string> ret;
        for (const_iterator it = variables.begin(); it != variables.end(); it++)
        {
            if ( (it->first.size() > 0 && it->first[0] == '$') || it->first == "PI" || it->first == "E")
            {
                continue;
            }
            ret.push_back(it->first);
        }
        return ret;
    }
};

