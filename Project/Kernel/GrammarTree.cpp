#include "GrammarTree.h"

void GrammarTree::parse()

{
	Token t = ls.get();
	if (t.code == Token::Identifier && ls.peek().code == Token::OpAssign)
	{
		Variable v(t.val);
		ls.get();
		root = Tree(O_ASSIGN, v, parseExpression());
	}
	else
	{
		ls.unGet(t);
		root = parseExpression();
	}
	return;
}

Tree GrammarTree::parseExpression()
{
	return parseAdditiveExpr();
}

Tree GrammarTree::parseAdditiveExpr()
{
	Tree left = parseMultiplicativeExpr();
	for (;;)
	{
		Token t = ls.peek();
		if (t.code == Token::OpPlus)
		{
			ls.get();
			Tree right = parseMultiplicativeExpr();
			left = Tree(O_ADD, left.clone(), right.clone());
		}
		else if (t.code == Token::OpMinus)
		{
			ls.get();
			Tree right = parseMultiplicativeExpr();
			left = Tree (O_SUB, left.clone(), right.clone());
		}
		else
		{
			return left.clone();
		}
	}
}

Tree GrammarTree::parseMultiplicativeExpr()
{
	Tree left = parsePowerExpr();
	for (;;)
	{
		Token t = ls.peek();
		if (t.code == Token::OpMul)
		{
			ls.get();
			Tree right = parsePowerExpr();
			left = Tree(O_MUL, left.clone(), right.clone());
		}
		else if (t.code == Token::OpDiv)
		{
			ls.get();
			Tree right = parsePowerExpr();
			left = Tree(O_DIV, left.clone(), right.clone());
		}
		else if (t.code == Token::OpMod)
		{
			ls.get();
			Tree right = parsePowerExpr();
			left = Tree(O_MOD, left.clone(), right.clone());
		}
		else if (t.code == Token::Identifier || t.code == Token::OpLeftParen)
		{
			// 2x или 2(2x+3)
			Tree right = parsePowerExpr();
			left = Tree(O_MUL, left.clone(), right.clone());
		}
		else
		{
			return left.clone();
		}
	}
}

Tree  GrammarTree::parsePowerExpr()
{
	Tree left = parseUnaryExpr();
	Token t = ls.peek();
	if (t.code == Token::OpPow)
	{
		ls.get();
		Tree right = parseUnaryExpr();
		Tree ret(O_POWER, left.clone(), right.clone());
		return ret;
	}
	else if (t.code == Token::OpFactorial)
	{
		ls.get();
		Tree ret(O_FACTORIAL, left.clone());
		return ret;
	}
	else
	{
		return left.clone();
	}
}

Tree GrammarTree::parseUnaryExpr()
{
	Token t = ls.get();
	Tree left;
	if (t.code == Token::OpPlus)
	{
		left = parsePrimaryExpr();
		Tree ret(O_UNARYPLUS, left.clone());
		return ret;
	}
	else if (t.code == Token::OpMinus)
	{
		left = parsePrimaryExpr();
		Tree ret(O_UNARYMINUS, left.clone());
		return ret;
	}
	else
	{
		ls.unGet(t);
		left = parsePrimaryExpr();
		return left.clone();
	}
}


Tree GrammarTree::parsePrimaryExpr()
{
	Token t = ls.peek();
	Number nn;
	if (t.code == Token::Identifier &&
		(t.val == "sqrt" || t.val == "sin" || t.val == "cos" || t.val == "ln" || t.val == "log" || t.val == "exp" || t.val == "tan" || t.val == "cot"
		|| t.val == "asin" || t.val == "acos" || t.val == "atan" || t.val == "actg" || t.val == "lg"))
	{
		ls.get();
		if (ls.peek().code == Token::OpLeftParen)
		{
			ls.get();
			Tree left = parseExpression();
			Tree right;
			Token t1 = ls.peek();
			if (t1.code == Token::OpComma) {
				ls.get();
				right = parseExpression();
				t1 = ls.get();
			}
			ls.get();
			if (t1.code != Token::OpRightParen)
			{
				syntaxError("Missing )");
			}
			op_e op = O_EMPTY;
			op_e op1 = O_EMPTY;
			if (t.val == "sqrt")
			{
				op = O_SQRT;
			}
			else if (t.val == "sin")
			{
				op = O_SIN;
			} 
			else if (t.val == "cos")
			{
				op = O_COS;
			} else if (t.val == "exp")
			{
				op = O_EXP;
			}
			else if (t.val == "ln")
			{
				op1 = O_NUM;
				right = left;
				left = Tree(Number("2.718281828459045")); //@@
				op = O_LOG;

			}
			else if (t.val == "tan")
			{
				op = O_TAN;
			}
			else if (t.val == "cot")
			{
				op = O_COT;
			}
			else if (t.val == "log")
			{
				op1 = O_NUM;
				op = O_LOG;
			}
			else if (t.val == "lg")
			{
				right = left;
				left = Tree(Number("10")); //@@
				op1 = O_NUM;
				op = O_LOG;
			}
			else if (t.val == "asin")
			{
				op = O_ASIN;
			} 
			else if (t.val == "acos") 
			{
				op = O_ACOS;
			}
			else if (t.val == "atan") 
			{
				op = O_ATAN;
			}
			else if (t.val == "actg")
			{
				op = O_ACTG;
			}
			else
			{
				op = O_EMPTY;
			}
			if (op1 == O_EMPTY) {
				Tree l = Tree(op, left);
				return l.clone();
			} else {
				Tree l = Tree(op, left, right);
				return l.clone();
			}
		}
	}
	t = ls.get();
	if (t.code == Token::Identifier)
	{
		Variable v(t.val);
		Tree left(v);
		return left;
	}
	else if (t.code == Token::IntegerConst || t.code == Token::RationalConst)
	{
		Number rn(t.val);
		Tree left(rn);
		return left;
	}
	else if (t.code == Token::OpLeftParen)
	{
		Tree left = parseExpression();
		if (ls.get().code != Token::OpRightParen)
		{
			syntaxError("Missing )");
		}
		return left.clone();
	}
	else
	{
		syntaxError(string("Unexpected ") + t.toString());
		return Tree();
	}
}

void
GrammarTree::syntaxError(string const &msg)
{
	printf("Error: %s\n", msg.c_str());
}




