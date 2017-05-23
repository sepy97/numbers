#include "CLangMap.h"

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

using namespace std;

typedef std::map<string, string> CMapSSA;

int 
CLangMap::close()
{
	if (_mapData != NULL)
	{
		delete (CMapSSA *)_mapData;
		_mapData = NULL;
	}
	return 0;
}

CLangMap::~CLangMap()
{
	close();
}

CLangMap::CLangMap()
{
	_check = false;
	_mapData = (void *) new CMapSSA;
}

static string
escape(string const &str)
{
	string ret;
	for (int i = 0; i < (int)str.size(); )
	{
		if (str[i] != '\\')
		{
			ret.push_back(str[i++]);
		}
		else
		{
			if (i == (int)str.size() - 1)
			{
				ret.push_back('\\');
				break;
			}
			switch (str.at(++i))
			{
			case 'n':	
				ret.push_back('\n');
				++i;
				break;
			case 'r':
				ret.push_back('\r');
				++i;
				break;
			case 't':
				ret.push_back('\t');
				++i;
				break;
			case '\\':
				ret.push_back('\\');
				++i;
				break;
			case '\"':
				ret.push_back('\"');
				++i;
				break;
			case '\'':
				ret.push_back('\'');
				++i;
				break;
			case '0':
				ret.push_back('\0');
				++i;
				break;
			default:
				ret.push_back(str[i]);
				++i;
				break;
			}
		}
	}
	return ret;
}

int
CLangMap::registerFile(string const &inp)
{
	CMapSSA *_map = (CMapSSA *)_mapData;
	ifstream ifs(inp, ios_base::in | ios_base::binary);
	if (!ifs) return 1;
	ios::pos_type fileSize;
	ifs.seekg(0, ios::end);
	fileSize = ifs.tellg();
	ifs.seekg(0, ios::beg);

    for (;;)
    {
	    try
	    {
            char inp[512];
            char repl[512];
            char check[512] = "@@@@@";
		    string orig, mapped;
            ifs.getline(inp, 512);
            ifs.getline(repl, 512);
            ifs.getline(check, 512);
            if (check[0] != '#') break;
		    string escOrig = escape(inp);
		    string escMapped = escape(repl);
		    _map->insert(make_pair(escOrig, escMapped));
	    }
	    catch (...)
	    {
            ifs.close();
		    return 1;
	    }
    }
    ifs.close();
	return 0;
}

void
CLangMap::setCheck(bool checkOnOff)
{
	_check = checkOnOff;
}

string
CLangMap::mapChecked(string const &str) const
{
	CMapSSA *_map = (CMapSSA *)_mapData;
	if (_map == NULL || _map->size() == 0)
	{
		return str;
	}
	std::string ret;
	try
	{
		CMapSSA::const_iterator ci = _map->find(str);
		if (ci != _map->end())
		{
			return ci->second.c_str();
		}
		else
		{
			if (_check)
			{
				std::string ret = "String '";
				ret += str;
				ret += "' not found";
			}
			throw ret;
		}
	}
	catch (...)
	{
		throw "fail";
	}
}

string
CLangMap::map(string const &str) const
{
    try
    {
	    return mapChecked(str);
    }
    catch (...)
    {
        return str;
    }
}

