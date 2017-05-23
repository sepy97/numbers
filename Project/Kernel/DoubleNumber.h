#ifndef DOUBLENUMBER_H
#define DOUBLENUMBER_H

#pragma once

#include "LargeNumber.h"

class RationalNumber;
#include <math.h>

class DoubleNumber
{
public:
    DoubleNumber();
    DoubleNumber(LargeNumber const &v);
    DoubleNumber(double v);
    DoubleNumber(LargeNumber const &num, LargeNumber const &denom = "1");
    DoubleNumber(string const &v);
    DoubleNumber(const char *str);
    ~DoubleNumber();
    string toString() const;
    string toTexString() const;
    string toStringWithPeriod() const;
    string toStringDecimal() const;
	RationalNumber toRational() const;

    DoubleNumber & operator +=(DoubleNumber const &v);
    DoubleNumber & operator -=(DoubleNumber const &v);
    DoubleNumber & operator *=(DoubleNumber const &v);
    DoubleNumber & operator /=(DoubleNumber const &v);
    DoubleNumber & operator =(DoubleNumber const &v);
    DoubleNumber & operator =(LargeNumber const &v);
    static DoubleNumber GCD(DoubleNumber const &cv1, DoubleNumber const &cv2);
    static DoubleNumber LCM(DoubleNumber const &cv1, DoubleNumber const &cv2);
    bool isLargeNumber() const;
    LargeNumber getNumerator() const;
    LargeNumber getDenominator() const;
    bool isNegative() const;
    void negate();
    DoubleNumber &abs();
    bool operator < (DoubleNumber const &oth) const;
    bool operator <= (DoubleNumber const &oth) const;
    bool operator > (DoubleNumber const &oth) const;
    bool operator >= (DoubleNumber const &oth) const;
    bool operator ==(DoubleNumber const &oth) const;
    bool operator !=(DoubleNumber const &oth) const;
    static DoubleNumber pow(DoubleNumber const &x, int n);
    static DoubleNumber pow(DoubleNumber const &x, DoubleNumber const &n);
    static DoubleNumber root(LargeNumber   const &cv1, long long powr);
    static DoubleNumber root(DoubleNumber const &cv1, long long powr);
    static void setPrecision(int precision);
    static int getPrecision();
    bool isGoodEnough(LargeNumber &appr) const;
    void round(int precision);
    bool isZero() const;
    DoubleNumber sqrt() const;
    void normalize();
    static int ROOT_DIGITS;
    static DoubleNumber ROOT_EPSILON;
    static DoubleNumber ROOT_GOOGOL;
    static void setPresentationMode(int flag);
    double toDouble() const;
private:
//    static void BringingToACommonDenominator (DoubleNumber const &cv1, DoubleNumber const &cv2, DoubleNumber &v3, DoubleNumber &v4);
    bool parseDecimal(string const &str, double &val);
    double val;
//  static bool presentationMode;
};
ostream & operator <<(ostream &str, DoubleNumber const &num);


#endif // DOUBLENUMBER_H
