#include "Tree.h"
#include "DoubleNumber.h"
#include "RationalNumber.h"
#include "VarTable.h"

const double PI = 3.14159265356793;

Tree::Tree()
{
	this->op = O_EMPTY;
	flags = 0;
}

Tree::Tree( int op, vector<Tree> nodes)
{
	this->op = (op_e)op;
	this->nodes = nodes;
	flags = 0;
}

Tree::Tree( int op)
{
	this->op = (op_e)op;
	flags = 0;
}

Tree::Tree( int op, Tree const &node0)
{
	this->op = (op_e)op;
	this->nodes.push_back(node0);
	flags = 0;
}

Tree::Tree( int op, Tree const &node0, Tree const &node1)
{
	this->op = (op_e)op;
	this->nodes.push_back(node0);
	this->nodes.push_back(node1);
	flags = 0;
}

Tree::Tree( int op, Tree const &node0, Tree const &node1, Tree const &node2)
{
	this->op = (op_e)op;
	this->nodes.push_back(node0);
	this->nodes.push_back(node1);
	this->nodes.push_back(node2);
	flags = 0;
}

Tree::Tree( Number const &num )
{
	op = O_NUM;
	flags = 0;
	this->num = num;
}

Tree::Tree( Variable var )
{
	op = O_VAR;
	flags = 0;
	this->var = var;
}

Tree::Tree( int op, Tree const &node0, Tree const &node1, Tree const &node2, Tree const &node3 )
{
	this->op = (op_e)op;
	this->nodes.push_back(node0);
	this->nodes.push_back(node1);
	this->nodes.push_back(node2);
	this->nodes.push_back(node3);
	flags = 0;
}


Tree::~Tree()
{
}

string Tree::toString() const
{
	string out;
	if (op == O_VAR) return var.name;
	if (op == O_NUM) return num.toString();
	out += "(";
	for (size_t i = 0; i < nodes.size(); i++) {
		string s = nodes[i].toString();
		out += s;
		if (i != nodes.size() - 1) {
			out += opToString();
		}
	}
	out += ")";
	return out;
}

string Tree::debugPrint(string const &prefix, int level) const
{
	string out;
	for (int i = 0; i < level; i++)
	{
		out += "  ";
	}
	if (op == O_VAR)
	{
		out += prefix;
		out += var.name;
		out += "\n";
		return out;
	}
	if (op == O_NUM)
	{
		out += prefix;
		out += num.toString();
		out += "\n";
		return out;
	}
	out += prefix; 
	out += opToString();
	out += "\n";
	for (size_t i = 0; i < nodes.size(); i++)
	{
		string s = nodes[i].debugPrint("", level+1);
		out += s;
	}
	return out;
}

string Tree::opToString() const
{
	switch(op)
	{
	case O_DIV: return "/";
	case O_MUL: return "*";
	case O_SUB: return "-";
	case O_ADD: return "+";
	case O_POWER: return "^";
	case O_VAR: return var.name;
	case O_NUM: num.toString();
	case O_ASSIGN: return "=";
	case O_UNARYPLUS: return "+";
	case O_UNARYMINUS: return "-";
	case O_FACTORIAL: return "!";
	case O_SQRT: return "sqrt";
	case O_SIN: return "sin";
	case O_COS: return "cos";
	case O_TAN: return "tan";
	case O_COT: return "cot";
	case O_LOG: return "log";
	case O_ASIN: return "asin";
	case O_ACOS: return "acos";
	case O_ATAN: return "atan";
	case O_ACTG: return "actg";

	default: return "!@#$%";
	}
}

string Tree::debugOpToString() const
{
	switch(op)
	{
	case O_DIV: return "/";
	case O_MUL: return "*";
	case O_SUB: return "-";
	case O_ADD: return "+";
	case O_POWER: return "^";
	case O_VAR: return var.name + var.values[0].toString();
	case O_NUM: return string("NUM ") + num.toString();
	case O_ASSIGN: return "=";
	case O_UNARYPLUS: return "+";
	case O_UNARYMINUS: return "-";
	case O_FACTORIAL: return "!";
	case O_SQRT: return "sqrt";
	case O_SIN: return "sin";
	default: return "!@#$%";
	}
}

Number Tree::evaluate(Number const *x)
{
	switch (op)
	{
	case O_NUM: return num;
	case O_VAR:
		if (x == NULL) {
			if (var.values.size() == 0) {
				if (vartable().find(var.name, var) != Error::OK)
				{
					throw Error::ItemNotFound;
				}
				if (var.values.size() == 0)
				{
					throw Error::ItemNotFound;
				}
			}
			return var.values[0];
		}
		else {
			return *x;
		}
	case O_ADD:
		{
			Number l(nodes[0].evaluate(x));
			for (size_t i = 1; i < nodes.size(); i++)
			{
				l += nodes[i].evaluate(x);
			}
			return l;
		}
	case O_UNARYPLUS:
		{
			Number l(nodes[0].evaluate(x));
			return l;
		}
	case O_UNARYMINUS:
		{
			Number l(nodes[0].evaluate(x));
			l.negate();
			return l;
		}
	case O_FACTORIAL:
		{
			Number l(nodes[0].evaluate(x));
			LargeNumber q = l.toIntegerTrunc();
			LargeNumber ret(1);
			for (LargeNumber i(2); i <= q; i += LargeNumber::one)
			{
				ret *= i;
			}
			return Number(ret);
		}
	case O_SIN:
		{
			Number l = nodes[0].evaluate(x);
			Number ret = ::sin(l.toDouble());
			return ret;
		}
	case O_COS:
		{
			Number l = nodes[0].evaluate(x);
			Number ret = ::cos(l.toDouble());
			return ret;
		}
	case O_TAN:
		{
			Number l = nodes[0].evaluate(x);
			Number ret = ::tan(l.toDouble());
			return ret;
		}
	case O_COT:
		{
			Number l = nodes[0].evaluate(x);
			double v = ::tan(l.toDouble());
			if (v == 0) {
				Number ret;
				ret.setInfinity();
				return ret;
			} else {
				Number ret(1. / v);
				return ret;
			}
		}

	case O_LOG:
		{
			Number r = nodes[0].evaluate(x);
			Number l = nodes[1].evaluate(x);
			Number ret = ::log(l.toDouble()) / ::log(r.toDouble());
			return ret;
		}

	case O_ASIN:
		{
			Number l = nodes[0].evaluate(x);
			double val = l.toDouble();
			if (val < -1 || val > 1) {
				Number ret;
				ret.setInvalid();
				return ret;
			}
			Number ret = ::asin(val);
			return ret;
		}
	case O_ACOS:
		{
			Number l = nodes[0].evaluate(x);
			double val = l.toDouble();
			if (val < -1 || val > 1) {
				Number ret;
				ret.setInvalid();
				return ret;
			}
			Number ret = ::acos(val);
			return ret;
		}
	case O_ATAN:
		{
			Number l = nodes[0].evaluate(x);
			double val = l.toDouble();
			Number ret = ::atan(val);
			return ret;
		}
	case O_ACTG:
		{
			Number l = nodes[0].evaluate(x);
			double val = l.toDouble();
			Number ret = ::atan(val) - PI/2;
			return ret;
		}


	case O_SQRT:
		{
			Number l = nodes[0].evaluate(x);
            double val = ::sqrt(l.toDouble());
            if (l.isRealDouble()) return DoubleNumber(val);
            return RationalNumber(val);
		}
	case O_SUB:
		{
			Number l(nodes[0].evaluate(x));
			l -= nodes[1].evaluate(x);
			return l;
		}
	case O_MUL:
		{
			Number l(nodes[0].evaluate(x)); // @@
			l *= nodes[1].evaluate(x);
			return l;
		}
	case O_DIV:
		{
			Number l(nodes[0].evaluate(x));
			l /= nodes[1].evaluate(x);
			return l;
		}
	case O_POWER:
		{
			Number l(nodes[0].evaluate(x));
			Number r(nodes[1].evaluate(x));
			return Number::pow(l, r);
		}
	case O_RBCKT:
		{
			return Number();
		}
	case O_LBCKT:
		{
			return Number();
		}
	case O_ASSIGN:
		{
			Variable v;
			string name = nodes[0].var.name;
			int code = vartable().find(name, v);
			if (code != Error::OK)
			{
				throw NumberException(code, string("Variable '") + name +  "' not found", __FUNCTION__);
			}
			Number r(nodes[1].evaluate(x));
			vartable().setValue(name, r);
			return r;
		}

	default: return Number();
	}
	//    return RationalNumber("0");
}

bool Tree::isLetter(int c)
{
	if (c == '$') return true;
	if (c >= 'a' && c <= 'z') return true;
	if (c >= 'A' && c <= 'Z') return true;
	return false;
}

bool Tree::isDigit(int c)
{
	if (c >= '0' && c <= '9') return true;
	return false;
}

bool Tree::isSpace(int c)
{
	if (c == ' ' || c == '\t') return true;
	return false;
}

bool Tree::isVar(string const &s)
{
	int ptr = 0;
	if (!isLetter(s[ptr])) return false;
	ptr++;
	while (ptr < (int)s.size())
	{
		if (isLetter(s[ptr]) || isDigit(s[ptr]))
		{
			ptr++;
		}
		else
		{
			return false;
		}
	}
	return true;
}

vector<string> Tree::splitStringToTokens(string const &s)
{
	vector<string> ret;
	string tok;
	int ptr = 0;
	while (ptr < (int)s.size())
	{
		while (ptr < (int)s.size() && isSpace(s[ptr]))
		{
			ptr++;
		}
		while (ptr < (int)s.size() && !isSpace(s[ptr]))
		{
			tok.push_back(s[ptr]);
			ptr++;
		}
		if (tok.size() > 0)
		{
			ret.push_back(tok);
			tok.clear();
		}
	}
	return ret;
}

bool Tree::isNumber(string const &s)
{
	int ptr = 0;
	if (!isDigit(s[ptr])) return false;
	bool slashFound = false;
	int dotsFound = 0;

	ptr++;
	for (;;)
	{
		if (ptr >= (int)s.size()) return true;
		if (isDigit(s[ptr]))
		{
		}
		else if (s[ptr] == '.')
		{
			dotsFound++;
			if (dotsFound > 2 || (dotsFound == 2 && !slashFound))
			{
				return false;
			}
		}
		else if (s[ptr] == '/')
		{
			if (slashFound)
			{
				return false;
			}
			slashFound = true;
		}
		else
		{
			return false;
		}
		ptr++;
	}
}

bool Tree::isOperation(string const &s)
{
	switch(s[0])
	{
	case '+':
	case '-':
	case '/':
	case '%':
	case '^':
	case '*':
	case '=':
	case '?':
		return true;
	}
	return false;
}

int Tree::fromString( string const &s )
{
	nodes.clear();
	vector<string> tokens = splitStringToTokens(s);
	if (tokens.size() == 0)
	{
		return -1;
	}
	// test-test-test!!! assignment operator
	if (tokens.size() == 1)
	{
		if (isVar(tokens[0]))
		{
			Variable v;
			if (vartable().find(tokens[0], v) != Error::OK)
			{
				throw NumberException(Error::ItemNotFound, string("Variable ") + tokens[0], __FUNCTION__);
			}
			var = v;
			op = O_VAR;
		}
	}
	if (tokens.size() == 3)
	{
		if (isVar(tokens[0]) && isOperation(tokens[1]) && isNumber(tokens[2]))
		{
			Variable var;
			if (vartable().find(tokens[0], var) != Error::OK)
			{
				vartable().add(tokens[0]);
			}
			if (tokens[1][0] != '=')
			{
				throw NumberException(Error::YetNotImplemented, string("Token ") + tokens[1], __FUNCTION__);
			}
			RationalNumber num(tokens[2]);
			Tree t0(num);
			var.name = tokens[0];
			Tree t1(var);
			op = O_ASSIGN;
			nodes.push_back(t1);
			nodes.push_back(t0);
		}
	}
	return -1;
}

void Tree::canonify()
{
	for (int i = 0; i < (int)nodes.size(); i++)
	{
		nodes[i].canonify();
	}
	if (op == O_MUL)
	{
		if (nodes[0].op == O_NUM && nodes[0].num.isOne())
		{
			//			printf("Before canonify0: '%s'\n", toString().c_str());
			op = nodes[1].op;
			num = nodes[1].num;
			var = nodes[1].var;
			flags = nodes[1].flags;
			vector<Tree> newnodes = nodes[1].nodes;
			nodes = newnodes;
			//			printf("After canonify0: '%s'\n", toString().c_str());
		}
		else if (nodes[1].op == O_NUM && nodes[1].num.isOne())
		{
			//			printf("Before canonify1: '%s'\n", toString().c_str());
			op = nodes[0].op;
			num = nodes[0].num;
			var = nodes[0].var;
			flags = nodes[0].flags;
			vector<Tree> newnodes = nodes[0].nodes;
			nodes = newnodes;
			//			printf("After canonify1: '%s'\n", toString().c_str());
		}
	}
	else if (op == O_POWER)
	{
		if (nodes[1].op == O_NUM && nodes[1].num.isOne())
		{
			//			printf("Before canonify2: '%s'\n", toString().c_str());
			op = nodes[0].op;
			num = nodes[0].num;
			var = nodes[0].var;
			flags = nodes[0].flags;
			vector<Tree> newnodes = nodes[0].nodes;
			nodes = newnodes;
			//			printf("After canonify2: '%s'\n", toString().c_str());
		}
	}
	else if (op == O_ADD) {
		if (nodes[0].op == O_NUM && nodes[0].num.isZero()) {
			//			printf("Before canonify3: '%s'\n", toString().c_str());
			op = nodes[1].op;
			num = nodes[1].num;
			var = nodes[1].var;
			flags = nodes[1].flags;
			vector<Tree> newnodes = nodes[1].nodes;
			nodes = newnodes;
			//			printf("After canonify3: '%s'\n", toString().c_str());
		}
		else if (nodes[1].op == O_NUM && nodes[1].num.isZero()) {
			//			printf("Before canonify4: '%s'\n", toString().c_str());
			op = nodes[0].op;
			num = nodes[0].num;
			var = nodes[0].var;
			flags = nodes[0].flags;
			vector<Tree> newnodes = nodes[0].nodes;
			nodes = newnodes;
			//			printf("After canonify4: '%s'\n", toString().c_str());
		}
	}
}

bool Tree::doubleize()
{
	bool ret = true;
	for (int i = 0; i < (int)nodes.size(); i++)
	{
		ret &= nodes[i].doubleize();
		if (!ret) return ret;
	}
	if (op == O_NUM) {
		if (num.isRealDouble()) return true;
		Number newNum(num.toDouble());
		num = newNum;
		return true;
	}
	return true;
}

bool Tree::usedVariables(set<Variable> &vars) const
{
	if (op == O_VAR)
	{
		vars.insert(var);
		return true;
	}
	for (int i = 0; i < (int)nodes.size(); i++)
	{
		nodes[i].usedVariables(vars);
	}
	return true;
}

Tree Tree::clone() const
{
	Tree t;
	t.nodes.resize(nodes.size());
	for (int i = 0; i < (int)nodes.size(); i++)
	{
		t.nodes[i] = nodes[i].clone();
	}
	t.op = op;
	t.num = num;
	t.var = var;
	return t;
}

// Ищем корни на интервале
vector<Number> Tree::findRoots(Number from, Number to, Number const &eps)
{
	vector<Number> ret;
	// Попытка найти участки знакопеременности
	Number step = to;
	step -= from;
	step /= 256;
	for (Number a(from); a < to; a += step) {
		Number fa = evaluate(&a);
		Number b = a;
		b += step;
		Number fb = evaluate(&b);
		Number m = fb;
		m *= fa;
//		printf("f(%s)=%s, f(%s)=%s\n", a.toString().c_str(), fa.toString().c_str(), b.toString().c_str(), fb.toString().c_str());
		if (m.isNegative()) { // Есть корень на интервале? Функция может быть и разрывной, кстати
			Number r;
			if (findRoot(a, b, eps, r)) {
				ret.push_back(r);
			}
		}
	}
	return ret;
}

// Ищем корни на интервале
bool Tree::findRoot(Number from, Number to, Number const &eps, Number &ret)
{
	Number fa = evaluate(&from); bool fan = fa.isNegative();
	Number fb = evaluate(&to);   bool fbn = fb.isNegative();
	Number delta(0.000001);
	if (fa.abs() < eps) {
		ret = fa; return true;
	}
	if (fb.abs() < eps) {
		ret = fb; return true;
	}
	Number a(from);
	Number b(to);
	Number half(0.5);
	Number dif(b);
	dif -= a;
	while (delta < dif) {
		Number c = a;
		c += b;
		c *= half;
		Number fc = evaluate(&c); bool fcn = fc.isNegative();
		Number t = fc;
		if (t.abs() < eps) {
			ret = c;
			return true;
		}
		if ((fan && fcn) || (!fan && !fcn)) {
			a = c; fa = fc; fan = fcn;
		} else {
			b = c; fb = fc; fbn = fcn;
		}
	}
	return false;
}
