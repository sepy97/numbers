//
//  number.cpp
//  numbers
//
//  Created by Семен Пьянков on 10.06.13.
//  Copyright (c) 2013 Семен Пьянков. All rights reserved.
//

#include "SmallNumber.h"
#include "NumberException.h"
#include "Error.h"


SmallNumber::SmallNumber()
{
 //   cout << "new SmallNumber(@0)\n";
    val = 0;
}

SmallNumber::SmallNumber(long long v)
{
//    cout << "new SmallNumber( " << v << ")\n";
    val = v;
}

SmallNumber::SmallNumber(const SmallNumber & v)
{
//    cout << "new SmallNumber@( " << v << ")\n";
    val = v.val;
}

SmallNumber::SmallNumber(string const &s)
{
    val = 0;
    for (size_t i = 0; i < s.size(); i++)
    {
        val *= 10;
        val += s[i] - '0';
    }
}

SmallNumber::~SmallNumber()
{
//   cout << "delete SmallNumber( " << val << ")\n";
}

SmallNumber & SmallNumber::operator =(const SmallNumber &v)
{
    this->val = v.getLongLongVal();
    return *this;
}


SmallNumber & SmallNumber::operator +=(const SmallNumber &v)
{
    this->val += v.getLongLongVal();
    return *this;
}

SmallNumber & SmallNumber::operator -=(const SmallNumber &v)
{
    this->val -= v.getLongLongVal();
    return *this;
}

SmallNumber & SmallNumber::operator *=(const SmallNumber &v)
{
    this->val *= v.getLongLongVal();
    return *this;
}

SmallNumber & SmallNumber::operator /=(const SmallNumber &v)
{
    if (v.getLongLongVal() == 0)
    {
        throw NumberException(Error::DivisionByZero, "Division by zero", __FUNCTION__);
    }
    this->val /= v.getLongLongVal();
    return *this;
}

SmallNumber & SmallNumber::operator %=(const SmallNumber &v)
{
    if (v.getLongLongVal() == 0)
    {
        throw NumberException(Error::DivisionByZero, "Division by zero", __FUNCTION__);
    }
    this->val %= v.getLongLongVal();
    return *this;
}

bool SmallNumber::operator ==(const SmallNumber &oth) const
{
    return this->val == oth.getLongLongVal();
}

bool 
SmallNumber::isZero() const
{
	return this->val == 0;
}


SmallNumber 
SmallNumber::gcd(SmallNumber first, SmallNumber second)
{
    do {
        SmallNumber t = first;
        t%=second;
        first = second;
        second = t;
    }
    while (!second.isZero());
    return first;
}

ostream & operator <<(ostream &str, SmallNumber const &num)
{
    str << num.getLongLongVal();
    return str;
}

SmallNumber operator +(const SmallNumber &f1, const SmallNumber &f2)
{
    SmallNumber tmp(f1);
    tmp += f2;
    return tmp;
}


