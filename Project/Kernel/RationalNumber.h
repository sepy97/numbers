#pragma once

#include "LargeNumber.h"
#include "DoubleNumber.h"

class RationalNumber
{
public:
    RationalNumber();
    RationalNumber(LargeNumber const &v);
    RationalNumber(LargeNumber const &num, LargeNumber const &denom);
    RationalNumber(string const &v);
    RationalNumber(const char *str);
    RationalNumber(double val);
    ~RationalNumber();
    string toString() const;
	string toTexString() const;
    string toStringWithPeriod() const;
	string toStringDecimal() const;

    RationalNumber & operator +=(RationalNumber const &v);
    RationalNumber & operator -=(RationalNumber const &v);
    RationalNumber & operator *=(RationalNumber const &v);
    RationalNumber & operator /=(RationalNumber const &v);
    RationalNumber & operator =(RationalNumber const &v);
	RationalNumber & operator =(LargeNumber const &v);
    static RationalNumber GCD(RationalNumber const &cv1, RationalNumber const &cv2);
    static RationalNumber LCM(RationalNumber const &cv1, RationalNumber const &cv2);
    bool isLargeNumber() const;
    LargeNumber getNumerator() const { return numerator; }
    LargeNumber getDenominator() const { return denominator; }
    bool isNegative() const;
	void negate();
    RationalNumber &abs();
    bool operator < (RationalNumber const &oth) const;
	bool operator <= (RationalNumber const &oth) const;
    bool operator > (RationalNumber const &oth) const;
	bool operator >= (RationalNumber const &oth) const;
	bool operator ==(RationalNumber const &oth) const;
	bool operator !=(RationalNumber const &oth) const;
    static RationalNumber pow(RationalNumber const &x, int n);
    static RationalNumber pow(RationalNumber const &x, RationalNumber const &n);
    static RationalNumber root(LargeNumber   const &cv1, long long powr);
    static RationalNumber root(RationalNumber const &cv1, long long powr);
    static void setPrecision(int precision);
	static int getPrecision() { return ROOT_DIGITS; }
    bool isGoodEnough(LargeNumber &appr) const;
    void round(int precision);
    bool isZero() const;
    RationalNumber sqrt() const;
    void normalize();
	static int ROOT_DIGITS; 
	static RationalNumber ROOT_EPSILON;
	static RationalNumber ROOT_GOOGOL;
    static void setPresentationMode(int flag);
	DoubleNumber toDouble() const;
	bool isOne() const;
private:
    static void BringingToACommonDenominator (RationalNumber const &cv1, RationalNumber const &cv2, RationalNumber &v3, RationalNumber &v4);
    bool parseDecimal(string const &str, LargeNumber &num, LargeNumber &den);
	LargeNumber numerator;
    LargeNumber denominator;
	bool normalized;
    static bool presentationMode;
};
ostream & operator <<(ostream &str, RationalNumber const &num);
