//
//  number.h
//  numbers
//
//  Created by Семен Пьянков on 10.06.13.
//  Copyright (c) 2013 Семен Пьянков. All rights reserved.
//

#ifndef __numbers__number__
#define __numbers__number__

#include <string>
#include "RationalNumber.h"
#include "DoubleNumber.h"
//#include "LargeNumber.h"
using namespace std;

class Number
{
public:
	Number();
    //Number(long long);
	Number(const char *);
    Number(string const &);
	Number(string const &, string const &);
	Number(double num);
	Number(const Number &oth);
	Number(LargeNumber const &);
	Number(RationalNumber const &);
	Number(DoubleNumber const &);
	Number & operator =(const Number &oth);
    Number & operator +=(const Number &oth); 
	Number & operator -=(const Number &oth); 
	Number & operator *=(const Number &oth); 
	Number & operator /=(const Number &oth); 
	bool operator <(const Number &oth) const;
	bool operator <=(const Number &oth) const;
	bool operator >(const Number &oth) const;
	bool operator >=(const Number &oth) const;
	bool operator ==(const Number &oth) const;
	bool operator !=(const Number &oth) const;
	bool isZero() const;
	bool isNegative() const;
	bool isInteger() const;
	bool isRealDouble() const;
	string toString() const;
	double toDouble() const;
	void setInvalid() {
		kind = INVALID_E;
		real = DoubleNumber("1E300");
	}
	void setInfinity() {
		kind = INFINITY_E;
		real = DoubleNumber("1E300");
	}
	Number & negate();
	Number abs() const;
	LargeNumber toIntegerTrunc() const;
	static Number pow(Number const &l, Number const &r);
	static Number pow(Number const &l, int r);
	bool isOne() const;
	void normalize();
	string toTexString() const;
	static void setPresentationMode(Number const &digits);
private:
    enum kind_e 
    {
//		LARGE = 0,
        RATIONAL_E = 1,
		REAL_E = 2,
//		INT64 = 3,
		INFINITY_E = 4,
		INDEFINITE_E = 5,
		INVALID_E = 6,
    } kind;
    DoubleNumber real;
    RationalNumber rational;
	static int digits;
	static Number invalid;
	static Number infinity;
//	LargeNumber large;
//	long long   int64bit;
};




#endif /* defined(__numbers__number__) */
