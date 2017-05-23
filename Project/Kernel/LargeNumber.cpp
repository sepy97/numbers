//
//  Created by —ÂÏÂÌ œ¸ˇÌÍÓ‚ on 10.06.13.
//  Copyright (c) 2013 —ÂÏÂÌ œ¸ˇÌÍÓ‚. All rights reserved.
//

#include "LargeNumber.h"
#include "Error.h"
#include "NumberException.h"
#include <deque>
#include <math.h>
#include "Random.h"

static Random rnd;

LargeNumber::LargeNumber()
{
 //   cout << "new LargeNumber(@0)\n";
	body.push_back(0); 
	sign = false;
}

LargeNumber::LargeNumber(long long v)
{
	deque <dultype> tmp;
	sign = false;
	if (v<0) {
		sign = true;
		v = -v;
	}
	if (v == 0)
	{
		body.push_back(0);
		return;
	}
	while (v!=0)
	{
		tmp.push_back(v%RADIX);
		v/=RADIX;
	}

	for (int i = (int)tmp.size(); --i >= 0; )
	{
		body.push_back (tmp[i]);
	}
	fast_normalize(body);
}

void LargeNumber::init(string const &str) 
{
    body.resize(0);
	int ptr = 0;
    const int TEN = 10;
	sign = false;
	if(str[0] == '-')
	{
		// signed = true; // 
		sign = true;
		ptr = 1;
	}
    string s1 = "";
	int size = ptr;
	while (str[size] >= '0' && str[size] <= '9')
	{
		size++;
	}
    int pad = (size - ptr);
	pad %= DIGITS; 
    pad = (DIGITS - pad) % DIGITS;
    for (int i = 0; i < pad; i++)
    {
        s1.push_back('0');
    }
    for (; ptr < size; ptr++)
    {
        s1.push_back(str[ptr]);
    }
	for (int i = 0; i < (int)s1.size(); i += DIGITS)
	{
        int d = 0;
        for (int j = 0; j < DIGITS; j++)
        {
            d *= TEN;
            d += s1[i+j] - '0';
        }
		body.push_back(d);
	}
	fast_normalize(body);
}

LargeNumber::LargeNumber(string const &str)
{
    init(str);
}

LargeNumber::LargeNumber(const char *str)
{
    init(str);
}


LargeNumber::LargeNumber(const LargeNumber & v)
{
	sign = v.sign;
	body.clone(v.body);
	fast_normalize(body);
}


LargeNumber::~LargeNumber()
{
//   cout << "delete LargeNumber( " << val << ")\n";
}

LargeNumber & LargeNumber::operator =(const LargeNumber &v)
{
//    this->val = v.getLongLongVal();
	sign = v.sign;
	body.clone(v.body);
    return *this;
}


void
LargeNumber::add (const dul &cv1, const dul &cv2, dul &v3)
{
	int len1 = (int)cv1.size();
	int len2 = (int)cv2.size();
	int len;
	if (len1 > len2)
	{
		len = len1;
		int minlen = len2;
		int d = len1 - len2;
		v3.resize(len+1);
//		v3.denormalize();
		for (int i = (int)minlen; --i >=0;)
		{
			dultype t = cv2[i]+cv1[i+d];
			v3[i+d+1] = t; // cv2.body[i]+cv1.body[i+d];
		}
		for (int i = d; --i >= 0; )
		{
			v3[i+1] = cv1[i];
		}
		slow_normalize(v3);
		return;
	}
	else
	{
		len = len2;
		int minlen = len1;
		int d = len2 - len1;
		v3.resize(len+1);
		//v3.denormalize();
		for (int i = (int)minlen; --i >=0;)
		{
			v3[i+d+1] = cv1[i]+cv2[i+d];
		}
		for (int i = d; --i >= 0; )
		{
			v3[i+1] = cv2[i];
		}
		slow_normalize(v3);
		return;
	}
}



// long long sqrt(long long a)
// {
// 	long long appr = (long long)sqrt((double)a);
// 	if (a == 0) return 0;
// 	if (a < 4) return 1;
// 	if (a < 9) return 2;
// 	long long ret;
// 	for (ret = appr - 2; (ret+1)*(ret+1) <= a; ret++)
// 		;
// 	return ret;
// }



LargeNumber LargeNumber::root(LargeNumber const &cv1, long long /*powr*/) const
{
	//		printf("sqrt(%s)... \n", cv1.toString().c_str());
	LargeNumber v1 = cv1;
	int iterations = 0;
	int dig = cv1.getNumberOfSignificantDigits();
	LargeNumber x;
	if (dig > 2 * DIGITS)
	{
		int groups = dig / 2 / DIGITS;
		LargeNumber v2(cv1);
		v2.fastDivPow10(groups * DIGITS * 2);
		x = root(v2, 2);
		x.fastMulPow10(groups * DIGITS);
	}
	else
	{
		long long val = cv1.getLongLongValue();
		long long rt = (long long)(::sqrt((double)val));
		rt--;
		while (rt * rt <= val)
		{
			rt++;
		}
		return rt-1;
	}
	LargeNumber xnew(x);
	for(;;)
	{
		iterations++;
		xnew *= xnew;
		xnew += cv1;
		xnew /= x;
		xnew /= 2;
		if(x == xnew)
		{
			break;
		}
		LargeNumber x1(x);
//		x1 += "1";
//		if(x1 == xnew)
//		{
//			printf("x=%s\n", x.toString().c_str());
//			printf("x1=%s\n", x1.toString().c_str());
//			printf("xnew=%s\n\n", xnew.toString().c_str());
//			break;
//		}
		//printf("x=%s\n", x.toString().c_str());
		//printf("x1=%s\n", x1.toString().c_str());
		//printf("xnew=%s\n\n", xnew.toString().c_str());
		x = xnew;
	}
	//		printf("sqrt(%s)=%s\n", cv1.toString().c_str(), x.toString().c_str());
// 	LargeNumber x2(x);
// 	//		x2 -= "5";
// 	for(;;)
// 	{
// 		LargeNumber x22(x2);
// 		x22 *= x22;
// 		if (x22 > cv1)
// 		{
// 			break;
// 		}
// 		x = x2;
// 		x2 += "1";
// 	}
	return x;
}


LargeNumber LargeNumber::sqrt() const
{
	return root(*this, 2);
}

// LargeNumber::dul 
// LargeNumber::sub (const dul &cv1, const dul &cv2)//‚˚˜ËÚ‡ÌËÂ
// {
//     if (eq(cv1, cv2))
//     {
//         dul ret(1); // 1 ÒËÏ‚ÓÎ!
//         return ret; 
//     }
// 	dul v1(cv1), v2(cv2);
// 	dul ret;
// 	for (int i = (int)v1.size()-(int)v2.size(); --i >= 0;)
// 	{
// 		v2.push_front(0);
// 	}
// 	for (int i = (int)v1.size(); --i >= 0;)
// 	{
// 		if (v1[i] >= v2[i])
// 		{
// 			ret.push_front(v1[i] - v2[i]);
// 		}
// 		else
// 		{
// 			ret.push_front(v1[i]+RADIX - v2[i]);
// 			v1[i-1]--;
// 		}
// 	}
// 	ret.normalize();
// 	return ret;
// }
// 

// LargeNumber::dul LargeNumber::sub (const dul &cv1, const dul &cv2)
// {
// 	// requirements: cv2.size() >= cv1.size()
// 	int l1 = cv1.size(); int l2 = cv2.size();
// 	int cl = l1 - l2; 
// 	dul v3(l1);
// 	int borrow = 0;
// 	for (int i = l1; --i >=cl;)
// 	{
// 		v3[i] = cv1[i] - cv2[i-cl] - borrow;
// 		borrow = 0;
//  		if ((long)v3[i] < 0)
//  		{
// 			borrow = 1;
// 			v3[i] += RADIX;
// 		}
// 	}
// 	for (int i = cl; --i >=0;)
// 	{
// 		v3[i] = cv1[i] - borrow;
// 		borrow = 0;
// 	}
// 	v3.fast_normalize();
// 	return v3;
// }

// LargeNumber::dul LargeNumber::new_sub (const dul &cv1, const dul &cv2)
// {
// 	// requirements: cv2.size() >= cv1.size()
// 	int l1 = (int)cv1.size(); int l2 = (int)cv2.size();
// 	int cl = l1 - l2; 
// 	dul v3(l1);
// 	for (int i = l1; --i >=cl;)
// 	{
// 		v3[i] = cv1[i] - cv2[i-cl];
// 	}
// 	for (int i = cl; --i >=0;)
// 	{
// 		v3[i] = cv1[i];
// 	}
// 	v3.denormalize();
// 	v3.slow_normalize();
// 	return v3;
// }

void
LargeNumber::sub (const dul &cv1, const dul &cv2, dul &v3)
{
	// requirements: cv2.size() >= cv1.size()
	int l1 = (int)cv1.size(); int l2 = (int)cv2.size();
	int cl = l1 - l2; 
	v3.resize(l1);
	for (int i = l1; --i >=cl;)
	{
		v3[i] += cv1[i] - cv2[i-cl];
		if (v3[i] < 0)
		{
			v3[i-1]--;
			v3[i] += RADIX;
		}
	}
	for (int i = cl; --i >=0;)
	{
		v3[i] += cv1[i];
		if (v3[i] < 0 && i > 0) 
		{
			v3[i-1]--;
			v3[i] += RADIX;
		}
	}
	fast_normalize(v3);
	return;
}

void
LargeNumber::mul(const dul &cv1, dultype d, dul &v1)
{
	v1.resize(cv1.size()+1);
    int cvs = (int)cv1.size();
	for (int i = cvs; --i >= 0;)
	{
		dultype a1 = cv1[i] * d;
		dultype d2 = a1 / RADIX;
		v1[i+1] += a1 % RADIX;
		v1[i] += d2;
		if (v1[i+1] >= RADIX)
		{
			v1[i+1] -= RADIX;
			v1[i]++;
		}
		
	}
	return;
}

void
LargeNumber::mul (const dul &cv1, const dul &cv2, dul &result)
{
	result.clear(); result.push_back(0); // resize(0);
	if (cv1.size() == 1 && cv1[0] == 0 ||
		cv2.size() == 1 && cv2[0] == 0)
	{
		return;
	}
//	size_t nsize = fast_deque::align_up(cv2.size()+cv1.size()+2);
//	fast_deque::dul *room = new fast_deque::dul[nsize * 2];
	for (int i = 0; i < (int)cv2.size(); i++)
	{
		dul mulres; //(room, nsize, NULL, 0);
		mul(cv1, cv2[i], mulres);
		for (int k = i; k < (int)cv2.size()-1; k++)
		{
			mulres.push_back(0);
		}
		dul r1; // (room + nsize, nsize, NULL, 0);
		add(result, mulres, r1);
		result.clone(r1);
	}
	// delete [] room;
	return;
}

void
LargeNumber::fast_mul(const dul &A,const dul &B, dul &result)
{
	const int THRESHOLD = 240000;
	if(A.size()<THRESHOLD || B.size()<THRESHOLD)
	{
		mul(A,B, result);
		return;
	}
//	printf("fast_mul: A=%s B=%s\n", A.toString().c_str(), B.toString().c_str());

	int i = (int)(A.size() + B.size()) / 4;
	if (i >= (int)A.size())
		i = (int)A.size() / 2;
	if (i >= (int)B.size())
		i = (int)B.size() / 2;
	fast_deque::dul *room = new fast_deque::dul[A.size() + B.size() + 12];
	size_t room_ptr = 0;
	dul a(room+room_ptr, (size_t)A.size()-i, &A[0], A.size()-i);
	room_ptr += (size_t)A.size()-i;
	dul b(room+room_ptr, (size_t)i, &A[A.size()-i], i);
	// b.insertToBegin(&A[A.size()-i], i);
	room_ptr += i;
//	printf("fast_mul: b=%s\n", b.toString().c_str());
	dul c(room+room_ptr, B.size()-i, &B[0], B.size()-i); 
	room_ptr += B.size()-i;
	//c.insertToBegin(&B[0], B.size()-i);
//	printf("fast_mul: c=%s\n", c.toString().c_str());
	dul d(room+room_ptr, i, &B[B.size()-i],i); 
	room_ptr += i;
	// d.insertToBegin(&B[B.size()-i],i);
//	printf("fast_mul: d=%s\n", d.toString().c_str());
	dul ac; // (room+room_ptr, a.size() + b.size() + 4, NULL, 0); 
	// room_ptr += a.size() + b.size() + 4;
	fast_mul(a, c, ac);
//	printf("fast_mul: ac=%s\n", ac.toString().c_str());
	dul bd; fast_mul(b, d, bd);
//	printf("fast_mul: bd=%s\n", bd.toString().c_str());
//	dul a_b = add(a, b);
//	dul c_d = add(c, d);
	dul ab_cd;
	dul ab; add(a,b,ab);
//	printf("fast_mul: ab=%s\n", ab.toString().c_str());
	dul cd; add(c,d,cd);
//	printf("fast_mul: cd=%s\n", cd.toString().c_str());
	fast_mul(ab, cd, ab_cd);
//	printf("fast_mul: ab_cd=%s\n", ab_cd.toString().c_str());
	dul ac_bd; add(ac, bd, ac_bd);
//	printf("fast_mul: ac_bd=%s\n", ac_bd.toString().c_str());
	dul ad_bc; sub(ab_cd, ac_bd, ad_bc);
//	printf("fast_mul: ad_bc=%s\n", ad_bc.toString().c_str());
	
	ad_bc.resize(ad_bc.size() + i);
//	printf("fast_mul: ad_bc new=%s\n", ad_bc.toString().c_str());
	ac.resize(ac.size()+i+i);
//	printf("fast_mul: ac new=%s\n", ac.toString().c_str());
	dul bd_ad_bc; add(bd, ad_bc, bd_ad_bc);
//	printf("fast_mul: bd_ad_bc=%s\n", bd_ad_bc.toString().c_str());
	add(ac,bd_ad_bc, result);
//	printf("fast_mul: result=%s\n", result.toString().c_str());
	delete [] room;
}

void
LargeNumber::divmod(const dul &cv1, const dul &cv2, dul &result, dul &remain)
{
	if (cmp(cv1, cv2) < 0)
	{
		result.resize(1);
		result[0] = 0;
		remain.clone(cv1);
		return;
	}
	if (cv2.size() == 1 && cv2[0] == 1)
	{
		result.clone(cv1);
		remain.resize(1);
		remain[0] = 0;
		return;
	}
	const size_t ROOM_SIZE = (cv2.size() + 2) * 32; // + cv2.size() + 1 + cv2.size() + cv1.size() + 32;
	size_t room_ptr = 0;
	fast_deque::dul *room = new fast_deque::dul[ROOM_SIZE];
	dul q;
    fast_deque cv2pow2[32];
    dul v2; 
	v2.clone(cv2); 
    dultype pow2 = 1;
    unsigned ind2 = 0;
	while (pow2 < RADIX) 
    {
		cv2pow2[ind2].init(room+room_ptr, v2.size()+1, &v2[0], v2.size());
		room_ptr += v2.size() + 1;
		// p->clone(v2);
		//cv2pow2[ind2]->clone(v2);
		if (LargeNumber::cmp(v2, cv1) > 0)
		{
			break;
		}
		dul v22; 
		add(v2, v2, v22);
		v2.clone(v22);
        pow2 += pow2;
        ind2 ++;
    }
	dul r; 
	for (int j = 0; j < (int)cv1.size(); j++)
	{
		r.push_back(cv1[j]);
        fast_normalize(r);
		int dgt = 0;
        dultype p2 = pow2;
        for (int i2 = (int)ind2; --i2 >= 0; p2 >>= 1) 
        {
			if (r.size() == 1 && r[0] == 0)
			{
				break; 
			}
    		if (cmp(r, cv2pow2[i2]) >= 0)
		    {
			    dul rs;
				room_ptr += r.size()+1;
				sub(r, cv2pow2[i2], rs);
				dgt += (1 << i2);
//				printf("sub(%s,%s)=%s\n", r.toString().c_str(), cv2pow2[i2]->toString().c_str(), rs.toString().c_str());
				r.clone(rs);
//				printf("r after clone=%s\n", r.toString().c_str());
            }
		}
		q.push_back(dgt);
	}
	fast_normalize(q);
	fast_normalize(r);
//  	for (unsigned i = 0; i < ind2; i++)
//  	{
//  		delete cv2pow2[i]; // ->free(); //= (dul *)alloca(sizeof (dul) * 32);
// 	}
	delete [] room;
	result.clone(q);
	remain.clone(r);
}


void LargeNumber::divmod( LargeNumber const &left, LargeNumber const &right, LargeNumber &quot, LargeNumber &remain )
{
    if (right.isZero())
    {
        throw NumberException(Error::DivisionByZero, "Division by zero", __FUNCTION__);
    }
	if (left.isZero())
	{
		quot = left;
		remain = LargeNumber::zero;
		return;
	}
    remain.sign = false;
    quot.sign = false;
	divmod(left.body, right.body, quot.body, remain.body);

	// 7 / 3 = {2, 1} //#1
	// -7 / 3 = {-3, 2} //#2
	// 7 / -3 = {-2, -1}  //#3
	// -7 / -3 = {3, -2}  //#4
	remain.sign = right.sign;
	if (!remain.sign) // #1, #2
	{
		quot.sign = left.sign;	
		if (left.sign && !remain.isZero()) // {-2, 1} -> {-3, 2}
		{
			quot -= LargeNumber::one;
			remain.negate();
			remain += right;
		}
	}
	else // #3, #4
	{
		quot.sign = !left.sign;
		if (left.sign && !remain.isZero())
		{
			quot += LargeNumber::one;
			remain.sign = true;
			remain.negate();
			remain += right;
			remain.negate();
		}
	}
}


LargeNumber & LargeNumber::operator +=(const LargeNumber &v)
{
//    this->val += v.getLongLongVal();
	dul c;
	if (sign == v.sign)
	{
		add(body, v.body, c);
		body.clone(c);
	}
	else 
	{
		int cmpf = cmp(body, v.body);
		if (sign == true && v.sign == false)
		{
			if (cmpf < 0)
			{
				sub(v.body,  body, c);
				body.clone(c);
				sign = false;
			}
			else if (cmpf > 0)
			{
				sub(body, v.body,c);
				body.clone(c);
				sign = true;
			}
			else
			{
				body.clear();
				body.push_back(0);
				sign = false;
			}
		}
		else
		{
			if (cmpf < 0)
			{
				sub(v.body, body,c);
				body.clone(c);
				sign = true;
			}
			else if (cmpf > 0)
			{
				sub(body, v.body,c);
				body.clone(c);
				sign = false;
			}
			else
			{
				body.clear();
				body.push_back(0);
				sign = false;
			}
		}
	}
	fast_normalize(body);
    return *this;
}

LargeNumber & LargeNumber::operator -=(const LargeNumber &v)
{
//    LargeNumber cv = v;
//    cv.sign = !cv.sign;
//    return operator +=(cv);
	dul c;
	if (sign != v.sign)
	{
		add(body, v.body,c);
		body.clone(c);
	}
	else 
	{
		int cmpf = cmp(body, v.body);
		if (sign == true && v.sign == true)
		{
			if (cmpf < 0)
			{
				sub(v.body,  body, c);
				body.clone(c);
				sign = false;
			}
			else if (cmpf > 0)
			{
				sub(body, v.body,c );
				body.clone(c);
				sign = true;
			}
			else
			{
				body.clear();
				body.push_back(0);
				sign = false;
			}
		}
		else
		{
			if (cmpf < 0)
			{
				sub(v.body, body,c);
				body.clone(c);
				sign = true;
			}
			else if (cmpf > 0)
			{
				sub(body, v.body, c);
				body.clone(c);
				sign = false;
			}
			else
			{
				body.clear();
				body.push_back(0);
				sign = false;
			}
		}
	}
	fast_normalize(body);
    return *this;

}

LargeNumber  LargeNumber::operator-()
{
	LargeNumber ret = *this;
	ret.sign = !ret.sign;
	return ret;
}

LargeNumber & LargeNumber::operator *=(const LargeNumber &v)
{
	if (sign == v.sign)
	{
		sign = false;
	}
	else
	{
		sign = true;
	}
	dul c;
	fast_mul(body, v.body, c);
	body.clone(c);
//	body = d0;
	fast_normalize(body);
    return *this;
}

LargeNumber & LargeNumber::operator /=(const LargeNumber &v)
{
    if (v.isZero())
    {
        throw NumberException(Error::DivisionByZero, "Division by zero", __FUNCTION__);
    }
	LargeNumber tmp;
    LargeNumber tmp1;
    divmod(*this, v, tmp, tmp1);
    body.clone(tmp.body);
    sign = tmp.sign;
	return *this;
}

LargeNumber & LargeNumber::operator %=(const LargeNumber &v)
{
    if (v.isZero())
    {
        throw NumberException(Error::DivisionByZero, "Division by zero", __FUNCTION__);
    }
	LargeNumber tmp;
    LargeNumber tmp1;
	divmod(*this, v, tmp, tmp1);
    body.clone(tmp1.body);
    sign = tmp1.sign;
    return *this;
}


void
LargeNumber::gcd(dul const &v1,dul const &v2, dul &ret)
{

	if ( (v1.size() == 1 && v1[0] == 1) ||
		(v2.size() == 1 && v2[0] == 1))
	{
		ret.resize(1);
		ret[0] = 1;
		return;
	}
	dul first; first.clone(v1);
	dul second; second.clone(v2);
	dul zero; zero.push_back(0);
	dul tmp;
	dul t;
	divmod(first, second, tmp, t);
    while (!isZero(t))
	{
		first.clone(second);
		second.clone(t);
		divmod(first, second, tmp, t);
	}
	fast_normalize(second);
    ret.clone(second);
}

void
LargeNumber::lcm(const dul &v1, const dul &v2, dul &ret) 
{
	dul first;
	dul result;
	dul tmp;
	dul v12; 
	gcd(v1, v2, v12);
	divmod(v1, v12, first, tmp);
     mul(first, v2, ret);
	fast_normalize(ret);
}

LargeNumber LargeNumber::LCM( LargeNumber const & cv1, LargeNumber const & cv2 )
{
    LargeNumber ret;
    lcm(cv1.body, cv2.body, ret.body);
    return ret;
}

LargeNumber LargeNumber::GCD( LargeNumber const & cv1, LargeNumber const & cv2 )
{
    LargeNumber ret;
    if (cv2.isZero()) return cv1;
    gcd(cv1.body, cv2.body, ret.body);
	fast_normalize(ret.body);
//	printf("GCD(%s,%s)=%s\n", cv1.toString().c_str(), cv2.toString().c_str(), ret.toString().c_str());
    return ret;
}

string LargeNumber::toString() const
{
    return getStringVal();
}

#if 0
bool LargeNumber::operator ==(const LargeNumber &v) const
{
	if (sign == v.sign)
	{
		return eq_normalized(body, v.body);
	}
	return false;
}

bool LargeNumber::operator !=(const LargeNumber &v) const
{
	if (sign != v.sign)
	{
		return true;
	}
	return !eq_normalized(body, v.body);
}

bool LargeNumber::operator > ( LargeNumber const &oth ) const
{
	if (!sign && oth.sign) return true;
	if (sign && !oth.sign) return false;
	bool ret = gt_normalized(body, oth.body);
	if (!sign) return ret;
	return !ret;
}

bool LargeNumber::operator <= ( LargeNumber const &oth ) const
{
	if (!sign && oth.sign) return false;
	if (sign && !oth.sign) return true;
	bool ret = gt_normalized(body, oth.body);
	if (sign) return ret;
	return !ret;
}


bool LargeNumber::operator ==(const LargeNumber &v) const
{
	if (sign == v.sign)
	{
		return eq_normalized(body, v.body);
	}
	return false;
}

bool LargeNumber::operator !=(const LargeNumber &v) const
{
	if (sign != v.sign)
	{
		return true;
	}
	return !eq_normalized(body, v.body);
}

bool LargeNumber::operator > ( LargeNumber const &oth ) const
{
	if (!sign && oth.sign) return true;
	if (sign && !oth.sign) return false;
	bool ret = gt_normalized(body, oth.body);
	if (!sign) return ret;
	return !ret;
}

bool LargeNumber::operator <= ( LargeNumber const &oth ) const
{
	if (!sign && oth.sign) return false;
	if (sign && !oth.sign) return true;
	bool ret = gt_normalized(body, oth.body);
	if (sign) return ret;
	return !ret;
}

bool LargeNumber::operator<( LargeNumber const &oth ) const
{
	if (!sign && oth.sign) return false;
	if (sign && !oth.sign) return true;
    bool ret = ge_normalized(body, oth.body);
	if (sign) return ret;
	return !ret;
}
#endif

LargeNumber LargeNumber::one("1");
LargeNumber LargeNumber::zero("0");
LargeNumber LargeNumber::two("2");
LargeNumber LargeNumber::ten("10");


LargeNumber
LargeNumber::random(LargeNumber &limit)
{
	dul b; b.resize(limit.body.size());
	for (size_t i = 0; i < b.size(); i++)
	{
		b[i] = rnd.nextInt(0x7FFFFFFF) % RADIX;
	}
	dul q;
	LargeNumber ret;
	divmod(b, limit.body, q, ret.body);
	fast_normalize(ret.body);
	return ret;
}

LargeNumber LargeNumber::pow( LargeNumber const &x, long p )
{
	if (p < 0) 
	{
		throw NumberException(Error::InvalidFormat, "Negative power", "pow");
	}
    if (p == 0) return 1;
    if (p == 1) return x;
    if (p & 1) 
    {
        LargeNumber q = pow(x, p-1); return q *= x; 
    }
    else
    {
        LargeNumber q = pow(x, p/2); return q *= q; 
    }
}

LargeNumber LargeNumber::powmod( LargeNumber const &x, long p, LargeNumber const &modulus)
{
	if (p < 0) 
	{
		throw NumberException(Error::InvalidFormat, "Negative power", "pow");
	}
    if (p == 0) return 1;
    if (p == 1) return x;
    if (p & 1) 
    {
        LargeNumber q = powmod(x, p-1, modulus); 
		q *= x;
		return q %= modulus;
    }
    else
    {
        LargeNumber q = powmod(x, p/2, modulus); 
		q *= q; 
		return q %= modulus;
    }
}

bool LargeNumber::isNegative() const
{
    return sign;
}

int LargeNumber::cmp( LargeNumber const &l1, LargeNumber const &l2)
{
// 	if (!l1.body.normalized || !l2.body.normalized) 
// 	{
// 		throw "Using denormalized numbers in cmp";
// 	}
	if (l1.sign && !l2.sign) 
	{
		return -1;
	}
	if (!l1.sign && l2.sign) 
	{
		return 1;
	}
	int s = l1.sign ? -1 : 1;
	if (l1.body.size() > l2.body.size())
	{
		return s;
	}
	else if (l1.body.size() < l2.body.size())
	{
		return -s;
	}

	for (size_t i = 0; i < l1.body.size(); i++)
	{
		if (l1.body[i] > l2.body[i])
		{
			return s;
		}
		else if (l2.body[i] > l1.body[i])
		{
			return -s;
		}
	}
	return 0;
}

int LargeNumber::cmp( dul const &l1, dul const &l2)
{
	if (l1.size() > l2.size())
	{
		return 1;
	}
	else if (l1.size() < l2.size())
	{
		return -1;
	}

	for (size_t i = 0; i < l1.size(); i++)
	{
		if (l1[i] > l2[i])
		{
			return 1;
		}
		else if (l2[i] > l1[i])
		{
			return -1;
		}
	}
	return 0;
}

ostream & operator <<(ostream &str, LargeNumber const &num)
{
	string s = num.getStringVal();
    str << s;
    return str;
}

LargeNumber operator +(const LargeNumber &f1, const LargeNumber &f2)
{
    LargeNumber tmp(f1);
    tmp += f2;
    return tmp;
}


