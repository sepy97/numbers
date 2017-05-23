//
//  LargeNumber.h
//  numbers
//
//  Created by Семен Пьянков on 24.06.13.
//  Copyright (c) 2013 Семен Пьянков. All rights reserved.
//

#ifndef numbers_LargeNumber_h
#define numbers_LargeNumber_h


#include <iostream>
#include <cstring>//new
#include <string>
//#include <deque>
#include <vector>
#include "fast_deque.h"
using namespace std;

class LargeNumber
{
public:
	typedef long long dultype;
	typedef fast_deque dul;
    LargeNumber();
    LargeNumber(long long);
    LargeNumber(string const &);
	LargeNumber(string const &, int radix);
    LargeNumber(const char *);
	LargeNumber(const LargeNumber &);
    LargeNumber & operator =(const LargeNumber &);
    ~LargeNumber();

    LargeNumber sqrt() const;
    LargeNumber root(LargeNumber const &cv1, long long powr) const;
    LargeNumber & operator +=(const LargeNumber &);
    LargeNumber & operator -=(const LargeNumber &);
    LargeNumber & operator *=(const LargeNumber &);
    LargeNumber & operator /=(const LargeNumber &);
    LargeNumber & operator %=(const LargeNumber &);
    LargeNumber & abs() { sign = false; return *this; }
	static void divmod(LargeNumber const &left, LargeNumber const &right, LargeNumber &quot, LargeNumber &remain);
	LargeNumber operator-();
	static int cmp(LargeNumber const &first, LargeNumber const &second);
	static int cmp(dul const &first, dul const &second);
	bool operator ==(LargeNumber const &oth) const { return cmp(*this, oth) == 0; }
	bool operator !=(LargeNumber const &oth) const { return cmp(*this, oth) != 0; }
	bool operator < (LargeNumber const &oth) const { return cmp(*this, oth) < 0; }
	bool operator <= (LargeNumber const &oth) const { return cmp(*this, oth) <= 0; }
	bool operator > (LargeNumber const &oth) const { return cmp(*this, oth) > 0; }
	bool operator >= (LargeNumber const &oth) const { return cmp(*this, oth) >= 0; }
    bool isEven() const { return body[body.size()-1] & 1; }//проверка на четность
    bool isNegative() const;
	void negate() { sign = !sign; }
	string getStringVal() const
	{
		string ret;
		if (sign)
		{
			ret.push_back('-');
		}
		for (size_t i = 0; i < body.size(); i++)
		{
            dultype d = body[i];
            char buf[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0}, *pbuf = buf;

            for (int j = 0; j < DIGITS; j++)
            {
                *pbuf++ = (char)(d % 10 + '0');
                d /= 10;
                if (i == 0 && d == 0) break; // Для первого блока лидирующие нули не нужны. Для остальных - нужны.
            }
            for (int j = (int)strlen(buf); --j >= 0; )
            {
                ret.push_back(buf[j]);
            }
		} 
        if (ret.size() == 0 || (sign && ret.size() == 1))
        {
            ret.push_back('0');
        }
		return ret;
	}

    int getNumberOfSignificantDigits() const
    {
        int ret = 0;
        for (size_t i = 0; i < body.size(); i++)
        {
            dultype d = body[i];
            for (int j = 0; j < DIGITS; j++)
            {
                ret++;
                d /= 10;
                if (i == 0 && d == 0) break; // Для первого блока лидирующие нули не нужны. Для остальных - нужны.
            }
        } 
        return ret;
    }

    long long getLongLongValue() const
    {
        long long ret = (long long)body[0];

        for (size_t i = 1; i < body.size(); i++)
        {
            dultype d = body[i];
            ret *= RADIX;
            ret += d;
        } 
        if (sign)
        {
            ret = -ret;
        }
        return ret;
    }

	void fastDivPow10(int pow)
	{
		pow /= DIGITS;
		while (--pow >= 0)
		{
			body.pop_back();
		}
	}

	void fastMulPow10(int pow)
	{
		pow /= DIGITS;
		while (--pow >= 0)
		{
			body.push_back(0);
		}
	}


	static LargeNumber GCD(LargeNumber const &n1, LargeNumber const &n2);
    static LargeNumber LCM(LargeNumber const & cv1, LargeNumber const & cv2 );
    string toString() const;
    static LargeNumber zero;
    static LargeNumber one;
    static LargeNumber two;
	static LargeNumber ten;
    static LargeNumber random(LargeNumber &limit);
    static LargeNumber pow(LargeNumber const &x, long p);
    static LargeNumber powmod(LargeNumber const &x, long p, LargeNumber const &modulus);
	enum {
		//RADIX = 10,
		//DIGITS = 1
		RADIX = 1000000000,
		DIGITS = 9
	};
	bool isZero() const
	{
		for (size_t i = 0; i < body.size(); i++)
		{
			if (body[i] != 0)
			{
				return false;
			}
		}
		return true;
	}
	static bool isZero(dul const &t) 
	{
		for (size_t i = 0; i < t.size(); i++)
		{
			if (t[i] != 0)
			{
				return false;
			}
		}
		return true;
	}

	bool isOne() const
	{
		if (body.size() == 1 && body[0] == 1) return true;
		return false;
	}
	void setZero()
	{
		body.resize(1);
		body[0] = 0;
//		normalized = true;
	}
	void setOne()
	{
		body.resize(1);
		body[0] = 1;
//		normalized = true;
	}
	static int parse(string const &, int radix, LargeNumber &ret);

private:
    void init(string const &);

	// typedef long long signed_dultype;
	fast_deque body;
// 	void init(vector<dultype> const& v)
// 	{
// 		if (v.size() > 0)
// 		{
// 			body.resize(v.size());
// 			for (size_t i = 0; i < v.size(); i++)
// 			{
// 				body[i] = v[i];
// 			}
// 		}
// 		else
// 		{
// 			body.clear();
// 		}
// 	}

		
// 	void denormalize()
// 	{
// 		normalized = false;
// 	}

	static void fast_normalize(dul &d)
	{
		while (d.size() > 1 && d[0] == 0)
		{
			d.pop_front();
		}
//		normalized = true;
	}


	static void slow_normalize(dul &d)
	{
		//            called++;
// 		if (!normalized)
// 		{
			int cont2 = (int)d.size();
			for (int i = cont2; --i >=0; )
			{
				while (d[i] >= RADIX)
				{
					d[i] -= RADIX;
					d[i-1]++;
				}
				while (d[i] < 0)
				{
					d[i] += RADIX;
					d[i-1]--;
				}
			}
			while (d.size() > 1 && d[0] == 0)
			{
				d.pop_front();
			}
//			normalized = true;
//		}
	}


//	bool normalized;
	void print(const char *pref) const 
	{
		printf("dul %s: ", pref);
		for (int i = 0; i < (int)body.size(); i++)
		{
			printf("%lld", body[i]);
		}
		printf("\n");
	}
	bool sign;
	static void add (const dul &cv1, const dul &cv2, dul &result);
	static void sub (const dul &cv1, const dul &cv2, dul &result); 
	static void mul (const dul &cv1, dultype d, dul &result);
	static void mul (const dul &cv1, const dul &cv2, dul &result);
	static void fast_mul (const dul &cv1, const dul &cv2, dul &result);
	static void divmod (const dul &cv1, const dul &cv2, dul &q, dul &r);
	static void gcd(const dul &v1, const dul &v2, dul &result);
	static void lcm(const dul &v1, const dul &v2, dul &result);
    static int ROOT_DIGITS;
    //static void normalize(dul &v);
};

ostream & operator <<(ostream &str, LargeNumber const &num);

#endif
