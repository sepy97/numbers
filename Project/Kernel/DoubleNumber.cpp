#include "DoubleNumber.h"
#include "RationalNumber.h"

DoubleNumber::DoubleNumber() 
{ 
	val = 0; 
}

DoubleNumber::DoubleNumber(LargeNumber const &v) 
{ 
	val = (double)v.getLongLongValue(); 
}

DoubleNumber::DoubleNumber(double v) 
{ 
	val = v; 
}

DoubleNumber::DoubleNumber(LargeNumber const &num, LargeNumber const &denom)
{ 
	val = num.getLongLongValue() / (double)denom.getLongLongValue(); 
}

DoubleNumber::DoubleNumber(string const &v) 
{ 
	size_t slash = v.find('/');
	if (slash == string::npos) {
		val = atof(v.c_str()); 
	}
	else {
		val = atof(v.c_str()) / atof(&v[slash+1]);
	}
}

DoubleNumber::DoubleNumber(const char *str) 
{ 
	val = atof(str); 
}

DoubleNumber::~DoubleNumber() 
{

}
	
string DoubleNumber::toString() const 
{ 
	char x[32]; 
	sprintf(x, "%g", val); 
	return x; 
}

string 
DoubleNumber::toTexString() const 
{ 
	return toString(); 
}

string 
DoubleNumber::toStringWithPeriod() const 
{ 
	return toString(); 
}
	
string 
DoubleNumber::toStringDecimal() const 
{ 
	return toString(); 
}

DoubleNumber & DoubleNumber::operator +=(DoubleNumber const &v) 
{ 
	val += v.val; 
	return *this; 
}

DoubleNumber & 
DoubleNumber::operator -=(DoubleNumber const &v) 
{ 
	val -= v.val; 
	return *this; 
}

DoubleNumber & 
DoubleNumber::operator *=(DoubleNumber const &v) 
{ 
	val *= v.val; 
	return *this; 
}

DoubleNumber & 
DoubleNumber::operator /=(DoubleNumber const &v) 
{ 
	val /= v.val; 
	return *this; 
}

DoubleNumber & 
DoubleNumber::operator =(DoubleNumber const &v) 
{ 
	DoubleNumber::val = v.val; 
	return *this; 
}

DoubleNumber & 
DoubleNumber::operator =(LargeNumber const &v) 
{ 
	val = (double)v.getLongLongValue(); 
	return *this; 
}

DoubleNumber 
DoubleNumber::GCD(DoubleNumber const & /*cv1*/, DoubleNumber const & /*cv2*/) 
{ 
	return 1; 
} //@@

DoubleNumber DoubleNumber::LCM(DoubleNumber const & /*cv1*/, DoubleNumber const & /*cv2*/) 
{ 
	return 1; 
} //@@

bool 
DoubleNumber::isLargeNumber() const 
{ 
	return true; 
}

LargeNumber 
DoubleNumber::getNumerator() const 
{
	return (LargeNumber)(long long)val; 
}

LargeNumber 
DoubleNumber::getDenominator() const 
{ 
	return LargeNumber(1); 
}

bool 
DoubleNumber::isNegative() const 
{ 
	return val < 0; 
}

void DoubleNumber::negate() 
{ 
	val = -val; 
}

DoubleNumber &
DoubleNumber::abs() 
{ 
	val = val < 0 ? -val : val; 
	return *this; 
}

bool 
DoubleNumber::operator < (DoubleNumber const &oth) const 
{ 
	return val < oth.val; 
}

bool 
DoubleNumber::operator <= (DoubleNumber const &oth) const 
{ 
	return val <= oth.val; 
}

bool 
DoubleNumber::operator > (DoubleNumber const &oth) const 
{ 
	return val > oth.val; 
}

bool 
DoubleNumber::operator >= (DoubleNumber const &oth) const 
{ 
	return val >= oth.val; 
}

bool 
DoubleNumber::operator ==(DoubleNumber const &oth) const 
{ 
	return val == oth.val; 
}

bool 
DoubleNumber::operator !=(DoubleNumber const &oth) const 
{ 
	return val != oth.val; 
}

DoubleNumber 
DoubleNumber::pow(DoubleNumber const &x, int n) 
{ 
	if (x.val == 0) return 0.;
	if (n == 0) return 1.;
	if (n > 0) {
		double ret = 1;
		while (--n >= 0) ret *= x.val;
		return ret;
	}
	return exp(log(x.val) * n); 
}

DoubleNumber 
DoubleNumber::pow(DoubleNumber const &x, DoubleNumber const &n) 
{ 
	if (x.val == 0) return 0.;
	if (n.val == 0) return 1.;
	long q = (long)n.val;
	if (fabs((double)q - n.val) < 0.00000001) {
		if (q > 0) {
			double ret = 1;
			while (--q >= 0) {
				ret *= x.val;
			}
			return ret;
		}
	}
	return exp(log(x.val) * n.val); 
}

DoubleNumber 
DoubleNumber::root(LargeNumber   const &cv1, long long powr) 
{ 
	return ::sqrt((double)cv1.getLongLongValue()); 
} // @@

DoubleNumber DoubleNumber::root(DoubleNumber const &cv1, long long powr) 
{ 
	return ::sqrt(cv1.val); 
}

void 
DoubleNumber::setPrecision(int precision) 
{
}  //@@
	
int DoubleNumber::getPrecision() 
{ 
	return ROOT_DIGITS; 
}

bool 
DoubleNumber::isGoodEnough(LargeNumber &appr) const 
{ 
	return true; 
} // @@

void 
DoubleNumber::round(int precision) 
{

} // @@
	
bool 
DoubleNumber::isZero() const 
{ 
	return val == 0; 
}

DoubleNumber 
DoubleNumber::sqrt() const 
{ 
	return ::sqrt(val); 
}

void DoubleNumber::normalize() 
{

}

double 
DoubleNumber::toDouble() const 
{ 
	return val; 
}

void DoubleNumber::setPresentationMode(int flag)
{
    ROOT_DIGITS = flag;
}

RationalNumber DoubleNumber::toRational() const
{
	char buf[512];
	sprintf(buf, "%.17f", val);
	RationalNumber ret(buf);
	return ret;
}

int DoubleNumber::ROOT_DIGITS = 10;
//RationalNumber RationalNumber::ROOT_GOOGOL;
//RationalNumber RationalNumber::ROOT_EPSILON;
DoubleNumber DoubleNumber::ROOT_GOOGOL("10000000000");
DoubleNumber DoubleNumber::ROOT_EPSILON("0.00000000001");

