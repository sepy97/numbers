#ifndef LEXICAL_SCANNER_H
#define LEXICAL_SCANNER_H
#include <string>
#include <deque>
using namespace std;

struct Token {
	enum {
		Empty,
		Identifier,
		IntegerConst,
		RationalConst,
		DoubleConst,
		StringConst,
		CharConst,
		OpPlus,
		OpMinus,
		OpMul,
		OpDiv,
		OpMod,
		OpPow,
		OpAssign,
		OpAssignPlus,
		OpAssignMinus,
		OpAssignMul,
		OpAssignDiv,
		OpAssignMod,
		OpAssignPow,
		OpLeftParen,
		OpRightParen,
		OpLeftBracket,
		OpRightBracket,
		OpLeftBrace,
		OpRightBrace,
		OpPoint,
		OpAnd,
		OpOr,
		OpNot,
		OpXor,
		OpComma,
		OpAssignAnd,
		OpAssignOr,
		OpAssignXor,
		OpQuestion,
		OpBecome,
		OpLessThan,
		OpLessOrEqualThan,
		OpEqualThan,
		OpNotEqualThan,
		OpGreaterThan,
		OpGreaterOrEqualThan,
        OpFactorial,
        OpSQRT,
        OpSin,
        OpCos,
        OpTan,
        OpCot,
        OpLn,
        OpLog,
        OpExp,
		OpUnderscore,
		OpEOF,
		Error,
	} code;
	string val;
	Token()
	{
		code = Empty;
		val = "";
	}
	string toString() const;
};

class LexicalScanner
{
public:
	LexicalScanner(string const &init);
	typedef int (* getCharFunction)(void *context);
	LexicalScanner(getCharFunction func, void *context);
	Token peek(); // Get next lexical element but does not advance
	Token get();
	void unGet(Token element);
	deque<int> getSeen() const { return seen; }
	int getLineNo() const { return lineNo; }
private:
	Token realGet();
	deque<Token> q;
	deque<int>  s;
	deque<int> seen;
	bool doneReading;
	int lineNo;
	void *context;

	getCharFunction getFunc;
	int getChar();
	int ungetChar(int c);
};

#endif
