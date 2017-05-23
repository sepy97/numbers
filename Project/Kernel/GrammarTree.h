#ifndef GRAMMAR_TREE_H
#define GRAMMAR_TREE_H 1
#include <stdio.h>
#include <string>
#include "LexicalScaner.h"
#include "Tree.h"

using namespace std;

class GrammarTree {
public:
	GrammarTree(string const &expr) : ls(expr)
	{
		parse();
	}
	~GrammarTree() {}
    Tree getTree()
	{
		return root;
	}
private:
	LexicalScanner ls;
    Tree root;
    Tree parsePostfixExpr();
    Tree parseArgumentListExpr();
    Tree parseRelationalExpr();
    Tree parseEqualityExpr();
    Tree parseAssignmentExpr();

    void parse();
    Tree parseExpression();
    Tree parseAdditiveExpr();
    Tree parseMultiplicativeExpr();
    Tree  parsePowerExpr();
    Tree parseUnaryExpr();
    Tree parsePrimaryExpr();

    void syntaxError(string const &msg);

};


#endif
