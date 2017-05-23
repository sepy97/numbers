#ifndef _CLANGMAP_H_
#define _CLANGMAP_H_	1

// 
// File format:
//
// textstring
// replacestring
// #
// textstring
// replacestring
// #

#include <string>
using namespace std;

class CLangMap
{
public:
	CLangMap();
	~CLangMap();
	int		registerFile(string const &name);	// Register exact file; return not 0 if error
	string  map(string const &str) const;	// translate string to mapped string; If str is not found then return str
	string  operator[](string const &str) const { return map(str); }	// Alias for map
	string  mapChecked(string const &str) const;	// translate string to mapped string; If str is not found then raise exception
	void	setCheck(bool checkOnOff);
private:
	int     close ();
	void	*_mapData;
	bool	_check;
};

#endif
