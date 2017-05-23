#pragma once

#include "Number.h"
//#include "DoubleNumber.h"
#include "Variable.h"
#include "VarTable.h"
#include "NumberException.h"
#include <set>

enum op_e 
{
    O_EMPTY,
    O_VAR,
    O_NUM,
    O_ADD,
    O_SUB,
    O_MUL,
    O_DIV,
    O_MOD,
    O_POWER,
    O_RBCKT,
    O_LBCKT,
    O_ASSIGN,
    O_LIST,
	O_UNARYPLUS,
	O_UNARYMINUS,
    O_FACTORIAL,
    O_SQRT,
    O_SIN,
    O_COS,
    O_TAN,
    O_COT,
    O_LOG,
    O_EXP,
	O_ASIN,
	O_ACOS,
	O_ATAN,
	O_ACTG,
	O_PI,
	O_E,
    O_PRINT,
};



class Tree
{
public:
    typedef int (* intWalkFunction)(Tree const *);
    static inline VarTable &vartable() {
        static VarTable vt;
        return vt;
    }
	bool isEmpty() const { return op == O_EMPTY; }
	op_e op;
    vector<Tree> nodes;
    Number num;
    Variable var;
	int  flags;
    Tree();
    Tree( int op, vector<Tree> nodes);
    Tree( int op);
    Tree( int op, Tree const &node0);
    Tree( int op, Tree const &node0, Tree const &node1);
    Tree( int op, Tree const &node0, Tree const &node1, Tree const &node2);
    Tree( Number const &num );
    Tree( Variable var );
    Tree( int op, Tree const &node0, Tree const &node1, Tree const &node2, Tree const &node3 );
    ~Tree();
    string toString() const;
    string debugPrint(string const &prefix, int level) const;
    string opToString() const;
    string debugOpToString() const;
    Number evaluate(Number const *x);

    static bool isLetter(int c);
    static bool isDigit(int c);
    static bool isSpace(int c);
    static bool isVar(string const &s);
    static vector<string> splitStringToTokens(string const &s);
    static bool isNumber(string const &s);
    static bool isOperation(string const &s);
    int fromString( string const &s );
    void canonify();
    bool usedVariables(set<Variable> &vars) const;
	bool doubleize();
	vector<Number> findRoots(Number from, Number to, Number const &eps);
	bool  findRoot(Number from, Number to, Number const &eps, Number &ret);

    Tree clone() const;
};
