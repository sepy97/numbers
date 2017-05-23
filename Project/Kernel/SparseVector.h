#pragma once
#include <map>
#include <vector>
#include "Number.h"
using namespace std;

class SparseVector
{
public:
	SparseVector();
	~SparseVector();
	void adjustNumOfVars(int newNumOfVars);
	Number add(vector<int> index, Number const &num); // { -1, 4, 2} -> y^4 * z^2
	Number sub(vector<int> index, Number const &num);
	Number get(vector<int> index) const;
	vector<int> getMaxDegrees() const; // x^3+3^x -> {3}; y^2+x^2 -> {2, 2}
	int numOfVars() const { return (int)_m.size(); }
	int maxVarDegree(int varNum);
	void clear() { _m.clear(); } 
	bool operator ==(SparseVector const &oth) const;
private:
	vector< vector<Number> > _m;
};
