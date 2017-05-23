#include "number.h"
#include <math.h>
#include <float.h>

Number::Number() 
{
	kind = RATIONAL_E;
	//        rational
} 
//Number(long long);
//Number(string const &);
Number::Number(const Number &oth) 
{
	kind = oth.kind;
	if (kind == REAL_E)
	{
		real = oth.real;
	}
	else if (kind == RATIONAL_E)
	{
		rational = oth.rational;
	}
}

Number::Number( const char *s )
{
	if (::strcmp(s, "INVALID") == 0) {
		kind = INVALID_E;
	}
	else if (::strcmp(s, "INFINITY") == 0) {
		kind = INFINITY_E;
	}
	else if (::strcmp(s, "INDEFINITE") == 0) {
		kind = INDEFINITE_E;
	}
	else if (::strchr(s,'.') != NULL) {
		real = DoubleNumber(s);
		kind = REAL_E;
	}
	else
	{
		rational = RationalNumber(s);
		kind = RATIONAL_E;
	}
}

Number::Number( double num ) : real(num)
{
// 	if (_isnan(real)) {
// 		kind = INDEFINITE;
// 	} else if (_isinf(real))
// 	{
// 		kind = INFINITY;
// 	}
	kind = REAL_E;
}

Number::Number( LargeNumber const &l ) : rational(l)
{
	kind = RATIONAL_E;
}

Number::Number( RationalNumber const &l ) : rational(l)
{
	kind = RATIONAL_E;
}

Number::Number( DoubleNumber const &l ) : real(l)
{
	kind = REAL_E;
}

Number::Number( string const &n, string const &d ) : rational(n,d) 
{
	kind = RATIONAL_E;	
}

Number::Number( string const &s )
{
	if (s == "INVALID") {
		kind = INVALID_E;
	}
	else if (s == "INFINITY") {
		kind = INFINITY_E;
	}
	else if (s == "INDEFINITE") {
		kind = INDEFINITE_E;
	}
	else if (::strchr(s.c_str(),'.') != NULL) {
		real = DoubleNumber(s.c_str());
		kind = REAL_E;
	}
	else
	{
		rational = RationalNumber(s.c_str());
		kind = RATIONAL_E;
	}

}


Number & Number::operator =(const Number &oth) 
{
	kind = oth.kind;
	if (kind == REAL_E)
	{
		real = oth.real;
	}
	else if (kind == RATIONAL_E)
	{
		rational = oth.rational;
	}
	return *this;
}

Number & Number::operator +=(const Number &oth) 
{ 
	if (kind == RATIONAL_E && oth.kind == RATIONAL_E) {
		rational += oth.rational;
	} else if (kind == REAL_E && oth.kind == REAL_E) {
		real += oth.real;
	} else if (kind == REAL_E && oth.kind == RATIONAL_E) {
		real += oth.rational.toDouble();
	} else if (kind == RATIONAL_E && oth.kind == REAL_E) {
		rational += oth.real.toRational();
	}
	return *this;
}

Number & Number::operator -=(const Number &oth) 
{ 
	if (kind == RATIONAL_E && oth.kind == RATIONAL_E) {
		rational -= oth.rational;
	} else if (kind == REAL_E && oth.kind == REAL_E) {
		real -= oth.real;
	} else if (kind == REAL_E && oth.kind == RATIONAL_E) {
		real -= oth.rational.toDouble();
	} else if (kind == RATIONAL_E && oth.kind == REAL_E) {
		rational -= oth.real.toRational();
	}
	return *this;
}

Number & Number::operator *=(const Number &oth) 
{ 
	if (kind == RATIONAL_E && oth.kind == RATIONAL_E) {
		rational *= oth.rational;
	} else if (kind == REAL_E && oth.kind == REAL_E) {
		real *= oth.real;
	} else if (kind == REAL_E && oth.kind == RATIONAL_E) {
		real *= oth.rational.toDouble();
	} else if (kind == RATIONAL_E && oth.kind == REAL_E) {
		rational *= oth.real.toRational();
	}
	return *this;
}

Number & Number::operator /=(const Number &oth) 
{ 
	if (kind == RATIONAL_E && oth.kind == RATIONAL_E) {
		rational /= oth.rational;
	} else if (kind == REAL_E && oth.kind == REAL_E) {
		real /= oth.real;
	} else if (kind == REAL_E && oth.kind == RATIONAL_E) {
		real /= oth.rational.toDouble();
	} else if (kind == RATIONAL_E && oth.kind == REAL_E) {
		rational /= oth.real.toRational();
	}
	return *this;
}

bool Number::isZero() const
{
	if (kind == REAL_E)
	{
		return real.isZero();
	}
	else if (kind == RATIONAL_E)
	{
		return rational.isZero();
	}
	return false;
}

bool Number::isNegative() const
{
	if (kind == REAL_E)
	{
		return real.isNegative();
	}
	else if (kind == RATIONAL_E)
	{
		return rational.isNegative();
	}
	return false;
}

LargeNumber Number::toIntegerTrunc() const
{
	if (kind == REAL_E) {
		RationalNumber rn(real.toRational());
		LargeNumber ret = rn.getNumerator();
		ret /= rn.getDenominator();
		return ret;
	}
	else if (kind == RATIONAL_E) {
		LargeNumber ret = rational.getNumerator();
		ret /= rational.getDenominator();
		return ret;
	}
	return LargeNumber::zero;
//	throw std::logic_error("The method or operation is not implemented.");
}

bool Number::isOne() const
{
	if (kind == REAL_E) return real.toDouble() == 1.0;
	else if (kind == RATIONAL_E) return rational.isOne();
	else return false;
}

string Number::toTexString() const
{
	if (kind == REAL_E) return real.toTexString();
	else if (kind == RATIONAL_E) return rational.toTexString();
	else if (kind == INFINITY_E) return "\\\\infty";
	else if (kind == INDEFINITE_E) return "NaN";
	else return "NaN";
}

bool Number::isInteger() const
{
	if (kind == RATIONAL_E && rational.getDenominator().isOne()) return true;
	return false;
}

void Number::setPresentationMode( Number const &d )
{
	digits = (int)d.toIntegerTrunc().getLongLongValue();
    if (d.kind == RATIONAL_E) {
        RationalNumber::setPresentationMode(digits);
    } else if (d.kind == REAL_E) {
        DoubleNumber::setPresentationMode(digits);
    }
}

void Number::normalize()
{
	if (kind == RATIONAL_E) {
		rational.normalize();
	}
}

string Number::toString() const
{
	if (kind == REAL_E) return real.toString();
	else if (kind == RATIONAL_E) return rational.toString();
	else if (kind == INFINITY_E) return "INF";
	else if (kind == INDEFINITE_E) return "IND";
	else if (kind == INVALID_E) return "NaN";
	else return "BADNUMBER";
}

Number Number::pow( Number const &l, Number const &r )
{
	if (l.kind == RATIONAL_E && r.kind == REAL_E)     return Number(DoubleNumber::pow(l.rational.toDouble(), r.real));
	if (l.kind == REAL_E && r.kind == REAL_E)     return Number(DoubleNumber::pow(l.real, r.real));
	if (l.kind == REAL_E && r.kind == RATIONAL_E) return Number(DoubleNumber::pow(l.real, r.rational.toDouble()));
	if (l.kind == RATIONAL_E && r.kind == RATIONAL_E) return Number(RationalNumber::pow(l.rational, r.rational));
	return Number::invalid;
}

Number Number::pow( Number const &l, int r )
{
	if (l.kind == REAL_E)     return Number(DoubleNumber::pow(l.real, r));
	if (l.kind == RATIONAL_E) return Number(RationalNumber::pow(l.rational, r));
	return Number::invalid;
}

Number & Number::negate()
{
	if (kind == RATIONAL_E) rational.negate();
	else if (kind == REAL_E) real.negate();
	else if (kind == INFINITY_E) kind = INFINITY_E;
	return *this;
}

Number Number::abs() const 
{
	Number ret;
	ret.kind = kind;
	if (kind == RATIONAL_E) {
		ret.rational = rational;
		if (rational.isNegative()) {
			ret.rational.negate();
		}
	} else if (kind == REAL_E) {
		ret.real = real;
		if (real.isNegative()) {
			ret.real.negate();
		}
	} 
	return ret;
}

double Number::toDouble() const
{
	if (kind == REAL_E) return real.toDouble();
	else if (kind == RATIONAL_E) return rational.toDouble().toDouble();
	else if (kind == INFINITY_E) return HUGE;
	else return HUGE;
}

bool Number::isRealDouble() const 
{
	return kind == REAL_E;
}

bool Number::operator<(const Number &oth) const
{
	if (oth.kind == INDEFINITE_E || oth.kind == INFINITY_E) return true;
	if (kind == RATIONAL_E && oth.kind == RATIONAL_E) return rational < oth.rational;
	if (kind == REAL_E && oth.kind == REAL_E) return real < oth.real;
	//@@@@@@
	return true;
}

Number Number::invalid("INVALID");
Number Number::infinity("PLUSINFINITY");
int Number::digits;


