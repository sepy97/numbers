//
//  SmallNumber.h
//  numbers
//
//  Created by Семен Пьянков on 24.06.13.
//  Copyright (c) 2013 Семен Пьянков. All rights reserved.
//

#ifndef numbers_SmallNumber_h
#define numbers_SmallNumber_h

#include <iostream>
#include <string>
using namespace std;

class SmallNumber
{
public:
    SmallNumber();
    SmallNumber(long long);
    SmallNumber(string const &);
	SmallNumber(const SmallNumber &);
    SmallNumber & operator =(const SmallNumber &);
    ~SmallNumber();

    SmallNumber & operator +=(const SmallNumber &);
    SmallNumber & operator -=(const SmallNumber &);
    SmallNumber & operator *=(const SmallNumber &);
    SmallNumber & operator /=(const SmallNumber &);
    SmallNumber & operator %=(const SmallNumber &);
    bool operator ==(SmallNumber const &oth) const;
	bool isZero() const;
    long long getLongLongVal() const { return val; }
	static SmallNumber gcd(SmallNumber first, SmallNumber second);
private:
    long long val;
};

ostream & operator <<(ostream &str, SmallNumber const &num);

#endif
