#include "LexicalScaner.h"
#include <string>
#include <deque>
using namespace std;

static const int MAX_VAR_LENGTH = 10;

LexicalScanner::LexicalScanner(string const &init)
{
	for (size_t i = 0; i < init.size(); i++)
	{
		s.push_back(init[i]);
	}
	doneReading = true;
	context = NULL;
	getFunc = NULL;
	lineNo = 1;
}

LexicalScanner::LexicalScanner(getCharFunction func, void *context)
{
	this->context = context;
	getFunc = func;
	doneReading = false;
	lineNo = 1;
}

int LexicalScanner::getChar()
{
	if (s.empty())
	{
		if (getFunc != NULL)
		{
			int c = getFunc(context);
			s.push_back(c);
		}
	}
	if (!s.empty())
	{
		int c = s[0];
		seen.push_back(c);
		s.pop_front();
		return c;
	}
	return -1;
}

int LexicalScanner::ungetChar(int c)
{
	s.push_front(c);
	seen.pop_back();
	return 0;
}

Token LexicalScanner::realGet()
{
	Token ret;
	int dots = 0;
	int slashes = 0;
	int es = 0;
	int max_var_length = MAX_VAR_LENGTH;

again:
	int c = getChar();
	max_var_length = MAX_VAR_LENGTH;
	switch(c)
	{
	case '\'':
		c = getChar();
		ret.val.push_back((char)c);
		if (c != -1)
		{
			c = getChar();
			if (c == '\'')
			{
				ret.code = Token::CharConst;
			}
			else 
			{
				ret.code = Token::Error;
				ret.val = "Bad char const";
			}
			return ret;
		}
		break;
	case '\"':
		c = getChar();
		while (c != '\"' && c != -1)
		{
			ret.val.push_back((char)c);
			c = getChar();
		}
		if (c == -1)
		{
			ret.code = Token::Error;
			ret.val = "Bad string const";
		}
		else
		{
			ret.code = Token::StringConst;
		}
		return ret;
	case '$': 
		max_var_length = 100;
		// no break!
	case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
	case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n': case 'o':
	case 'p': case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w':
	case 'x': case 'y': case 'z': 
	case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
	case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N': case 'O':
	case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V': case 'W':
	case 'X': case 'Y': case 'Z': 
		ret.code = Token::Identifier;
		ret.val.push_back((char)c);
		c = getChar();
		while (ret.val.size() < max_var_length &&  
			(c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '$')
		{
			ret.val.push_back((char)c);
			c = getChar();
		}
		ungetChar(c);
// 		if (ret.val == "sin") {
// 			ret.code = Token::OpSin;
// 		}
		return ret;
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		ret.code = Token::IntegerConst;
		ret.val.push_back((char)c);
		c = getChar();
		while ((c >= '0' && c <= '9') || c == '.' || c == '/' || c == 'e' || c == 'E')
		{
			ret.val.push_back((char)c);
			if (c == '.')
			{
				dots++;
			}
			else if (c == '/')
			{
				int d = getChar();
				if (d < '0' || d > '9')
				{
					ungetChar(d);
					ungetChar('/');
					ret.val.resize(ret.val.size()-1);
					ret.code = Token::IntegerConst;
					return ret;
				}
				ret.val.push_back((char)d);
				slashes++;
				dots = 0;
				es = 0;
				ret.code = Token::RationalConst;
			}
			else if (c == 'e' || c == 'E')
			{
				es++;
				ret.code = Token::RationalConst;
			}
			else
			{
				// digit
			}
			if (dots >= 2 || es >= 2)
			{
				ret.code = Token::Error;
				ret.val = "Malformed number";
				return ret;
			}
			c = getChar();
		}
		ungetChar(c);
		return ret; 
	case '-':
		ret.val.push_back((char)c);
		c = getChar();

		if (c == '=')
		{
			ret.val.push_back((char)c);
			ret.code = Token::OpAssignMinus;
		}
		else 
		{
			ungetChar(c);
			ret.code = Token::OpMinus;
		}
		return ret;
	case '+':
		ret.val.push_back((char)c);
		c = getChar();
		if (c == '=')
		{
			ret.val.push_back((char)c);
			ret.code = Token::OpAssignPlus;
		}
		else 
		{
			ungetChar(c);
			ret.code = Token::OpPlus;
		}
		return ret;
	case '*':
		ret.val.push_back((char)c);
		c = getChar();
		if (c == '=')
		{
			ret.val.push_back((char)c);
			ret.code = Token::OpAssignMul;
		}
		else 
		{
			ungetChar(c);
			ret.code = Token::OpMul;
		}
		return ret;
	case '/':
		ret.val.push_back((char)c);
		c = getChar();
		if (c == '=')
		{
			ret.val.push_back((char)c);
			ret.code = Token::OpAssignDiv;
		}
		else 
		{
			ungetChar(c);
			ret.code = Token::OpDiv;
		}
		return ret;
	case '!':
		ret.val.push_back((char)c);
		c = getChar();
		if (c == '=')
		{
			ret.val.push_back((char)c);
			ret.code = Token::OpNotEqualThan;
		}
		else 
		{
			ungetChar(c);
			ret.code = Token::OpFactorial;
		}
		return ret;
	case '%':
		ret.val.push_back((char)c);
		c = getChar();
		if (c == '=')
		{
			ret.val.push_back((char)c);
			ret.code = Token::OpAssignMod;
		}
		else 
		{
			ungetChar(c);
			ret.code = Token::OpMod;
		}
		return ret;
	case '^':
		ret.val.push_back((char)c);
		c = getChar();
		if (c == '=')
		{
			ret.val.push_back((char)c);
			ret.code = Token::OpAssignPow;
		}
		else 
		{
			ungetChar(c);
			ret.code = Token::OpPow;
		}
		return ret;
	case '<':
		ret.val.push_back((char)c);
		c = getChar();
		if (c == '-')
		{
			ret.val.push_back((char)c);
			ret.code = Token::OpBecome;
		}
		else if (c == '=')
		{
			ret.val.push_back((char)c);
			ret.code = Token::OpLessOrEqualThan;
		}
		else 
		{
			ungetChar(c);
			ret.code = Token::OpLessThan;
		}
		return ret;
	case '>':
		ret.val.push_back((char)c);
		c = getChar();
		if (c == '=')
		{
			ret.val.push_back((char)c);
			ret.code = Token::OpGreaterOrEqualThan;
		}
		else 
		{
			ungetChar(c);
			ret.code = Token::OpGreaterThan;
		}
		return ret;
	case '(':
		ret.val.push_back((char)c);
		ret.code = Token::OpLeftParen;
		return ret;
	case '_':
		ret.val.push_back((char)c);
		ret.code = Token::OpUnderscore;
		return ret;
	case ')':
		ret.val.push_back((char)c);
		ret.code = Token::OpRightParen;
		return ret;
	case '[':
		ret.val.push_back((char)c);
		ret.code = Token::OpLeftBracket;
		return ret;
	case ']':
		ret.val.push_back((char)c);
		ret.code = Token::OpRightBracket;
		return ret;
	case '{':
		ret.val.push_back((char)c);
		ret.code = Token::OpLeftBrace;
		return ret;
	case '}':
		ret.val.push_back((char)c);
		ret.code = Token::OpRightBrace;
		return ret;
	case '.':
		ret.val.push_back((char)c);
		ret.code = Token::OpPoint;
		return ret;
	case '?':
		ret.val.push_back((char)c);
		ret.code = Token::OpQuestion;
		return ret;

	case ',':
		ret.val.push_back((char)c);
		ret.code = Token::OpComma;
		return ret;
	case '=':
		ret.val.push_back((char)c);
		c = getChar();
		if (c == '=')
		{
			ret.val.push_back((char)c);
			ret.code = Token::OpEqualThan;
		}
		else 
		{
			ungetChar(c);
			ret.code = Token::OpAssign;
		}
		return ret;
	case '\n': 
		lineNo++; // no break!
	case ' ': case '\t': 
		goto again;
	case -1:
		ret.code = Token::OpEOF;
		return ret;
	default:
		ret.code = Token::Error;
		ret.val.push_back((char)c);
		return ret;
	}
	ret.code = Token::Error;
	ret.val = "Unknown";
	return ret;
}

string Token::toString() const
{
	switch (code)
	{
	case Empty: return "";
	case Identifier: return string("N=") + val;
	case IntegerConst: return string("I=") + val;
	case RationalConst: return string("R=") + val;
	case DoubleConst: return string("D=") + val;
	case StringConst: return string("\"") + val + string("\"");
	case CharConst: return string("'") + val + string("'");
	case OpPlus: return "+";
	case OpMinus: return "-";
	case OpMul: return "*";
	case OpDiv: return "/";
	case OpMod: return "%";
	case OpPow: return "^";
	case OpAssign: return "=";
	case OpAssignPlus: return "+=";
	case OpAssignMinus: return "-=";
	case OpAssignMul: return "*=";
	case OpAssignDiv: return "/=";
	case OpAssignMod: return "%=";
	case OpAssignPow: return "^=";
	case OpLeftParen: return "(";
	case OpRightParen: return ")";
	case OpLeftBracket: return "[";
	case OpRightBracket: return "]";
	case OpLeftBrace: return "{";
	case OpRightBrace: return "]";
	case OpPoint: return ".";
	case OpAnd: return "&";
	case OpOr: return "|";
	case OpNot: return "~";
	case OpXor: return "@";
	case OpComma: return ",";
	case OpAssignAnd: return "&=";
	case OpAssignOr: return "|=";
	case OpAssignXor: return "@=";
	case OpQuestion: return "?";
	case OpBecome: return "<-";
	case OpLessThan: return "<";
	case OpLessOrEqualThan: return "<=";
	case OpEqualThan: return "==";
	case OpNotEqualThan: return "!=";
	case OpGreaterThan: return ">";
	case OpGreaterOrEqualThan: return ">=";
	case OpUnderscore: return "_";
	case Error: return string("Error=") + val;
	case OpEOF: return "EOF";
	default: return "@#$%";
	}
}

Token LexicalScanner::peek()
{
	if (q.empty())
    {
		Token t = realGet();
		q.push_back(t);
	}
	return q[0];
}

Token LexicalScanner::get()
{
	if (q.empty())
	{
		Token t = realGet();
		return t;
	}
	Token t = q[0];
	q.pop_front();
	return t;
}

void LexicalScanner::unGet(Token t)
{
	q.push_front(t);
}
