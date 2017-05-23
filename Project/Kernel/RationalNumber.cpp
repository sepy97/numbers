#include "RationalNumber.h"
#include "NumberException.h"
#include "Error.h"
#include <vector>
#include <set>
#include <cstdlib>
#include <cmath>

int RationalNumber::ROOT_DIGITS = 10;
RationalNumber RationalNumber::ROOT_GOOGOL("10000000000");
RationalNumber RationalNumber::ROOT_EPSILON("0.00000000001");
bool RationalNumber::presentationMode = false;

void RationalNumber::normalize()
{
	if (normalized) return;
    if (denominator.isZero())
    {
        throw NumberException (Error::DivisionByZero, "Division by zero", __FUNCTION__);
    }
	if (!denominator.isOne())
	{
		LargeNumber g = LargeNumber::GCD(numerator, denominator);
		if (!g.isOne())
		{
			numerator /= g;
			denominator /= g;
		}
	}
	normalized = true;
}

void RationalNumber::BringingToACommonDenominator(RationalNumber const &cv1, RationalNumber const &cv2, RationalNumber &v3, RationalNumber &v4)
{
    if (cv1.denominator.isZero() || cv2.denominator.isZero())
    {
        throw NumberException (Error::DivisionByZero, "Division by zero", __FUNCTION__);
    }
	if (cv1.denominator == cv2.denominator)
	{
		v3 = cv1;
		v4 = cv2;
		return;
	}
    RationalNumber v1 = cv1;
    RationalNumber v2 = cv2;
    LargeNumber temp = LargeNumber::LCM(cv2.denominator, cv1.denominator);
    LargeNumber temp1 = temp;
    temp /= cv2.denominator;
//	printf("about to div temp1=%s to %s\n", temp1.toString().c_str(), cv1.denominator.toString().c_str());
    temp1 /= cv1.denominator;
//	printf("result is temp1=%s\n", temp1.toString().c_str());
    v2.numerator *= temp;
    v2.denominator *= temp;
	//printf("about to mul %s to %s\n", v1.numerator.toString().c_str(), v1.denominator.toString().c_str());
    v1.numerator *= temp1;
	//printf("after mul1 %s to %s\n", v1.numerator.toString().c_str(), v1.denominator.toString().c_str());
    v1.denominator *= temp1;
	//printf("after mul2 %s to %s\n", v1.numerator.toString().c_str(), v1.denominator.toString().c_str());
    v3 = v1;
    v4 = v2;
}

RationalNumber::RationalNumber()
{
    numerator = LargeNumber::zero;
    denominator = 1;
	normalized = true;
}

RationalNumber::RationalNumber(LargeNumber const &v)
{
	numerator = v;
	denominator = 1;
	normalized = true;
}

RationalNumber::RationalNumber( LargeNumber const &num, LargeNumber const &denom /*= "1"*/ )
{
    numerator = num;
    if (denom.isZero())
    {
        throw NumberException(Error::DivisionByZero, "Division by zero", __FUNCTION__);
    }
    denominator = denom;
}

RationalNumber::RationalNumber(const char *str)
{
    string s = str;
    RationalNumber a = s;
    if (a.denominator.isZero())
    {
        throw NumberException(Error::DivisionByZero, "Division by zero", __FUNCTION__);
    }
    *this = a;
	normalized = false;
    //normalize();
}

RationalNumber::RationalNumber(double val) {
    char str[40];
    sprintf(str, "%.20g", val);
    RationalNumber a = str;
    *this = a;
    normalized = false;
}

bool
RationalNumber::parseDecimal(string const &str, LargeNumber &num, LargeNumber &den)
{
    bool dec = false;
    den = 1;
    string str1;
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == '.')
        {
            if (dec)
            {
                return false;
            }
            dec = true;
        }
        else
        {
            if (dec)
            {
                den *= 10;
            }
            str1.push_back(str[i]);
        }
    }
    num = str1;
    return true;
}

RationalNumber::RationalNumber(string const &v)
{
	size_t i = 0;
    string nums;
	while(i < v.size() && v[i] != '/')
	{
		nums.push_back(v[i]);
		i++;
	}
	i++;
    LargeNumber numsnum;
    LargeNumber numsden;
    if (!parseDecimal(nums,numsnum, numsden))
    {
        throw NumberException(Error::InvalidFormat, "Parse error in numerator", __FUNCTION__);
    }
    if (i >= v.size())
    {
        numerator = numsnum;
        denominator = numsden;
    }
    else
    {
        string dens;
        LargeNumber densnum;
        LargeNumber densden;
	    while(i < v.size() && i != v.size())
	    {
		    dens.push_back(v[i]);
            i++;
	    }
        if (!parseDecimal(dens,densnum, densden))
        {
            throw NumberException(Error::InvalidFormat, "Parse error in denominator", __FUNCTION__);
        }

	    numerator = numsnum;
        numerator *= densden;
        denominator = densnum;
        denominator *= numsden;
        if (denominator.isZero())
        {
            throw NumberException(Error::DivisionByZero, "Division by zero", __FUNCTION__);
        }
    }
	normalized = false;
    //normalize();
}

RationalNumber::~RationalNumber()
{
}

RationalNumber & RationalNumber::operator =(const RationalNumber &v)
{
    numerator = v.numerator;
    denominator = v.denominator;
	normalized = v.normalized;
    return *this;
}

RationalNumber & RationalNumber::operator =(const LargeNumber &v)
{
	numerator = v;
	denominator = "1";
	normalized = true;
	return *this;
}

string RationalNumber::toString() const
{
    if (presentationMode )
    {
        return toStringDecimal();
    }
    string ret(numerator.toString());
    if (denominator == LargeNumber::one) return ret;
    ret.push_back('/');
    ret += denominator.toString();
    return ret;
}

string RationalNumber::toTexString() const
{
	if (presentationMode )
	{
		return toStringDecimal();
	}
	string ret(numerator.toString());
	if (denominator == LargeNumber::one) return ret;
	ret = "\\frac{" + ret;
	ret += "}{";
	ret += denominator.toString();
	ret += "} ";
	return ret;
}

RationalNumber & RationalNumber::operator+= (RationalNumber const &v)
{
    RationalNumber cv = v;
    RationalNumber v3;
    RationalNumber v4;
    BringingToACommonDenominator(*this, cv, v3, v4);
//	printf("R+=(%s,%s)=(%s,%s)\n", toString().c_str(), cv.toString().c_str(), v3.toString().c_str(), v4.toString().c_str());
    v3.numerator += v4.numerator;
	v3.normalized = false;
    //v3.normalize();
    *this = v3;
//	printf("R+= return %s\n", toString().c_str());
    return *this;
}

RationalNumber & RationalNumber::operator-= (RationalNumber const &v)
{
    RationalNumber cv = v;
    RationalNumber v3, v4;
    BringingToACommonDenominator(*this, cv, v3, v4);
    v3.numerator -= v4.numerator;
	v3.normalized = false;
    //v3.normalize();
    *this = v3;
    return *this;
}

RationalNumber & RationalNumber::operator*= (const RationalNumber &v)
{
    numerator *= v.numerator;
    denominator *= v.denominator;
	normalized = false;	
    //normalize();
    return *this;
}

RationalNumber & RationalNumber::operator/= (const RationalNumber &v)
{
    if (v.denominator.isZero())
    {
        throw NumberException(Error::DivisionByZero, "Division by zero", __FUNCTION__);
    }
    numerator *= v.denominator;
    denominator *= v.numerator;
	normalized = false;
    //normalize();
    return *this;
}

bool RationalNumber::operator== (RationalNumber const &oth) const
{
    return ((numerator == oth.numerator) && (denominator == oth.denominator));
}

bool RationalNumber::operator!= (RationalNumber const &oth) const
{
	return ((numerator != oth.numerator) || (denominator != oth.denominator));
}

RationalNumber RationalNumber::GCD( RationalNumber const &cv1, RationalNumber const &cv2 )
{
    RationalNumber result;
    RationalNumber v1 = cv1;
    RationalNumber v2 = cv2;
    RationalNumber v3, v4;
    BringingToACommonDenominator(v1, v2, v3, v4);
    v1 = v3; v2 = v4;
    if (v1.numerator.isZero() || v2.numerator.isZero())
    {
        throw NumberException(Error::DivisionByZero, "Division by zero", __FUNCTION__);
    }
    result.numerator = LargeNumber::GCD(v1.numerator, v2.numerator);
    result.denominator = v1.denominator;
	result.normalized = false;
    //result.normalize();
    return result;
}

RationalNumber RationalNumber::LCM( RationalNumber const &cv1, RationalNumber const &cv2 )
{
    RationalNumber result;
    RationalNumber v1, v2;
    v1 = cv1;
    v2 = cv2;
    if (v1.numerator.isZero() || v2.numerator.isZero())
    {
        throw NumberException(Error::DivisionByZero, "Division by zero", __FUNCTION__);
    }
    //LargeNumber GCDNum = LargeNumber::GCD(v1.numerator, v2.numerator);
    //LargeNumber GCDDen = v1.denominator;

    v1/=RationalNumber::GCD(v1,v2);
    v2 *= v1;
    result = v2;
    /*
    //@@@@@@ пока неверно.
    result.numerator = LargeNumber::LCM(v1.numerator, v2.numerator);
    result.denominator = v1.denominator;*/
	result.normalized = false;
    //result.normalize();
    return result;
}

string RationalNumber::toStringWithPeriod() const
{
    LargeNumber integerPart;
    LargeNumber remainder;
    LargeNumber::divmod(numerator, denominator, integerPart, remainder);
    string ret = integerPart.toString();
    if (remainder.isZero())
    {
        return ret;
    }
    ret += ".";
    // здесь  0 < remainder < denominator;
    // теперь шаг за шагом получаем десятичные цифры ответа.
    set<LargeNumber> c;
    vector<LargeNumber> d;
    bool done = false;
    vector<LargeNumber> remainders;
    while (!done)
    {
        LargeNumber intpart;
        remainder*=10;
        LargeNumber::divmod(remainder, denominator, intpart, remainder);
        if (c.find(remainder) != c.end()) 
        {
            done = true;
        }
        c.insert(remainder);
        remainders.push_back(remainder);
        d.push_back(intpart);
    } // while (c.find(remainder) == c.end() || c.size() <= 1);
    //// @@@@

    int firstPeriodIndex;
    for (firstPeriodIndex = (int)remainders.size()-1; --firstPeriodIndex >= 0 && !(remainders[firstPeriodIndex] == remainder); )
        ;
    int periodSize = (int)remainders.size() - firstPeriodIndex - 1;
    if (d[firstPeriodIndex] == d[d.size()-1])
    {
        firstPeriodIndex--;
    }
    for (int j = 0; j <= firstPeriodIndex; j++)
    {
        ret += d[j].toString();
    }
    ret += "(";
    int lastPeriodIndex = firstPeriodIndex + periodSize;
    for (int j = firstPeriodIndex+1; j <= lastPeriodIndex; j++)
    {
        ret += d[j].toString();
    }
    ret += ")";
    // @@ если обнаружили период, то выводим его в скобках и на этом заканчиваем.
    if(d.size() == 0)
    {
        //Error
        return 0;
    }
    return ret;
}

string RationalNumber::toStringDecimal() const
{
	LargeNumber integerPart;
	LargeNumber remainder;
	LargeNumber absNumerator(numerator);
	absNumerator.abs();
	LargeNumber absDenominator(denominator);
	absDenominator.abs();
	bool sign = numerator.isNegative() != denominator.isNegative();
	LargeNumber::divmod(absNumerator, absDenominator, integerPart, remainder);
//	printf("divmod(%s,%s,%s,%s)\n", absNumerator.toString().c_str(),
//		                            absDenominator.toString().c_str(),
//									integerPart.toString().c_str(),
//									remainder.toString().c_str());

	string ret = (sign ? "-" : "") + integerPart.toString();
	if (remainder.isZero())
	{
		return ret;
	}
	ret += ".";
	// здесь  0 < remainder < denominator;
	// теперь шаг за шагом получаем десятичные цифры ответа.
	for (int i = 0; i < ROOT_DIGITS+1; i++)
	{
		LargeNumber intpart;
//		printf("remainder before=%s\n", remainder.toString().c_str());
		remainder *= LargeNumber::ten;
//		printf("remainder after mul=%s\n", remainder.toString().c_str());
		LargeNumber newRemainder;
		LargeNumber::divmod(remainder, absDenominator, intpart, newRemainder);
//		printf("divmod2(%s,%s,%s,%s)\n", remainder.toString().c_str(),
//			absDenominator.toString().c_str(),
//			intpart.toString().c_str(),
//			newRemainder.toString().c_str());
		remainder = newRemainder;
		ret += intpart.toString();
	} 
    if (ret[ret.size()-1] >= '5')
    {
        RationalNumber tmp(ret);
        tmp.numerator += LargeNumber("5");
        LargeNumber l,r;
        LargeNumber::divmod(tmp.numerator, tmp.denominator, l, r);
        ret = l.toString();
        if (!(r < LargeNumber("5")))
        {
            ret += ".";
            string ls = r.toString();
            ls.resize(ls.size()-1);
            for (int i = (int)ls.size(); i < ROOT_DIGITS; i++)
            {
                ret.push_back('0');
            }
            ret += ls;
        }
    }
    else
    {
        ret.resize(ret.size()-1);
    }
	return ret;
}

bool RationalNumber::isLargeNumber() const
{
    return denominator.isOne();
}

bool 
RationalNumber::isZero() const
{
    return numerator.isZero();
}

bool RationalNumber::operator <( RationalNumber const &oth ) const
{
    RationalNumber cv1, cv2;
    BringingToACommonDenominator(*this, oth, cv1, cv2);
    return (cv1.numerator<cv2.numerator);
}

bool RationalNumber::operator>( RationalNumber const &oth ) const
{
    RationalNumber cv1, cv2;
    BringingToACommonDenominator(*this, oth, cv1, cv2);
    return (cv1.numerator>cv2.numerator);
}

ostream & operator <<(ostream &str, RationalNumber const &num)
{
    string s = num.toString();
    str << s;
    return str;
}

RationalNumber RationalNumber::pow(RationalNumber const &_l, int _pow)
{
    RationalNumber l(_l);
    //l.normalize();
    long long p(_pow);
    if (p < 0)
    {
        LargeNumber retden = LargeNumber::pow(l.getNumerator(), (unsigned long)p);
        LargeNumber retnum = LargeNumber::pow(l.getDenominator(), (unsigned long)p);
        RationalNumber ret(retnum, retden);
        return ret;
    }
    LargeNumber retnum = LargeNumber::pow(l.getNumerator(), (unsigned long)p);
    LargeNumber retden = LargeNumber::pow(l.getDenominator(), (unsigned long)p);
    RationalNumber ret(retnum, retden);
    return ret;
}

RationalNumber RationalNumber::pow( RationalNumber const &l, RationalNumber const &p )
{
    LargeNumber cp = p.numerator;
    cp /= p.denominator;
    RationalNumber retnum = pow(l, cp.getLongLongValue());
    cp = p.numerator;
    cp %=p.denominator;
    RationalNumber retcop = pow(l, cp.getLongLongValue());
    retnum *= root(retcop, p.denominator.getLongLongValue());
    return retnum;
}

RationalNumber RationalNumber::root(LargeNumber const &cv1, long long powr)
{
    LargeNumber v1 = cv1;
//	cout << "root of " << cv1.toString() << endl;
    string tenpower = "1";
    string denom = "1";
    string zeros = "";
    int iterations = 0;
    int dig = cv1.getNumberOfSignificantDigits();
    string xinit = "1";
    for (int i = 0; i < dig + ROOT_DIGITS; i++)
    {
        xinit += "0";
    }

    for (long long i = 0; i < powr; i++)
    {
        zeros += "0";
    }

    for (int i = 0; i < ROOT_DIGITS; i++)
    {
        tenpower += zeros;
        denom += "0";
    }
    v1 *= tenpower;

    LargeNumber x(xinit); //@@
    LargeNumber xnew(v1);
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
		x = xnew;
//		cout << "iter=" << iterations << " " << x.toString() << endl;
	
//         for (long long i = 1; i < powr; i++)
//         {
//             xnew/=x;
//         }
//         for (long long i = 1; i < powr; i++)
//         {
//             xnew += x;
//         }
//         xnew /= powr;
//         if(x == xnew)
//         {
//             break;
//         }
//         x = xnew;
//         xnew = v1;
    }

    RationalNumber ret(x, denom);
//    cout << "pow= " << powr << "  iter=" << iterations << endl;
    return ret;
}

RationalNumber RationalNumber::sqrt() const
{
	RationalNumber retnum = root(numerator, 2);
	RationalNumber retden = root(denominator, 2);
	retnum /= retden;
	return retnum;
}

RationalNumber RationalNumber::root( RationalNumber const &cv1, long long powr )
{
    RationalNumber retnum = root(cv1.numerator, powr);
    RationalNumber retden = root(cv1.denominator, powr);
    retnum /= retden;
    return retnum;
}

bool RationalNumber::isNegative() const
{
    return numerator.isNegative();
}

void RationalNumber::negate()
{
	numerator.negate();
}

bool RationalNumber::isGoodEnough( LargeNumber &appr ) const
{
    LargeNumber rem, quot;
    LargeNumber copyNum(numerator);
    copyNum.abs();
    LargeNumber copyDen(denominator);
    copyDen.abs();
    LargeNumber::divmod(copyNum, copyDen, quot, rem);
    LargeNumber tmp(rem);
    tmp *= ROOT_GOOGOL.getNumerator();
    if (tmp < copyDen)
    {
        appr = quot;
		if (numerator.isNegative())
		{
			appr.negate();
		}
        return true;
    }
    tmp = copyDen;
    tmp -= rem;
    tmp *= ROOT_GOOGOL.getNumerator();
    if (tmp < copyDen)
    {
        appr = quot;
		if (numerator.isNegative())
		{
			appr.negate();
			appr -= LargeNumber::one;
		}
		else
		{
			appr += LargeNumber::one;
		}
        return true;
    }
    return false;
}

RationalNumber & RationalNumber::abs()
{
    denominator.abs();
    numerator.abs();
    return *this;
}

void RationalNumber::round( int precision )
{
    int numDigits = numerator.getNumberOfSignificantDigits();
    int denDigits = denominator.getNumberOfSignificantDigits();
    int minDigits = numDigits < denDigits ? numDigits : denDigits;
    if (minDigits > precision)
    {
        string one("1");
        while (minDigits > precision)
        {
            one.push_back('0');
            minDigits--;
        }
        LargeNumber tmp;
        LargeNumber::divmod(numerator,   one, numerator, tmp);
        LargeNumber::divmod(denominator, one, denominator, tmp);
    }
}

void RationalNumber::setPrecision( int precision )
{
	int oldPrecision = ROOT_DIGITS;
	if (precision != oldPrecision)
	{
		ROOT_DIGITS = precision;
        string s("1");
        for (int i = 0; i < precision; i++)
        {
            s += "0";
        }
        ROOT_GOOGOL = RationalNumber(s,"1");
        ROOT_EPSILON = RationalNumber("1", s);
	}
}

void RationalNumber::setPresentationMode( int flag )
{
    if (flag > 0)
    {
        setPrecision(flag);
        presentationMode = true;
    }
    else
    {
        presentationMode = false;
    }
}

DoubleNumber RationalNumber::toDouble() const
{
	//@@
	if (denominator.isZero()) return DoubleNumber(HUGE);
	DoubleNumber ret((double)numerator.getLongLongValue() / (double)denominator.getLongLongValue());
	return ret;
}

bool RationalNumber::isOne() const
{
	return denominator == numerator;
}
