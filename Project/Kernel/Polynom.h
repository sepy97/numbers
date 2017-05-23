#pragma once

#include "Tree.h"
#include <deque>

class Polynom
{
public:
    Polynom();
	Polynom(Polynom const &oth);
    Polynom(Tree const &init);
	Polynom &operator=(Polynom const &oth);
	bool isValid() const;
    bool initialize(Tree const &init);
	bool initialize(Polynom const &p);
	bool initialize(vector<Variable> const &vv, vector<Number> const &sv);
	bool initialize(string const &s);
	// Polynom(vector<Variable> const &v, vector<deque<RationalNumber> > const &c);
    Polynom & operator +=(Polynom const &oth); 
    Polynom & operator -=(Polynom const &oth); 
    Polynom & operator *=(Polynom const &oth);
    deque<Polynom> factor() const;
	bool isPureNumberic() const;
    static void pow(Polynom &what, Number const &p);
    static void divmod(Polynom const &left, Polynom const &right, Polynom &quot, Polynom &rem);
	bool operator ==(Polynom const &oth);
    string toString() const;
	string toTexString() const;
	Number evaluate(vector<Number> const &vars);
    Number evaluate(Number const &var);
	Number evaluate(); // Just simplify expression
	Number evaluate(VarTable const &vt); 
	Polynom derivative(string const &varname) const;
	void add(string const &var, int pow, Number const &num);
    bool root(Number &val);
	Tree getTree();
    ~Polynom();
    //int treeToPolynom()
private:
    vector<Variable> vars;
    vector< vector<Number> > coeffs;
	Tree tree;
	bool treeIntact;
	bool initialized;
	void rebuildTree();
    void normalize();
	void mergeVars(Polynom &oth);
	bool isPureVar();
	// void pad(int c, int n);
    // x^2-2x+6 --> vars{"x"}, coeffs{ {6, -2, 1} };
    // x^2 + 2xy + y^2 -> vars{"x", "y"} {{0, 0, 1},{0, 2, 0}, {1, 0, 0}}
};
