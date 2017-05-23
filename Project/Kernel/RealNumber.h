#ifndef _real_number_included
#define _real_number_included

#include <math.h>
class RealNumber
{
public:
    RealNumber() { body = 0; } 
    RealNumber(const RealNumber &oth) 
    {
        body = oth.body;
    }

    RealNumber & operator =(const RealNumber &oth) 
    {
        body = oth.body;
        return *this; 
    }

    RealNumber & operator +=(const RealNumber &oth) 
    { 
        body += oth.body;
        return *this; 
    }

    RealNumber & operator -=(const RealNumber &oth) 
    { 
        body -= oth.body;
        return *this; 
    }

    RealNumber & operator *=(const RealNumber &oth) 
    { 
        body *= oth.body;
        return *this; 
    }

    RealNumber & operator /=(const RealNumber &oth) 
    { 
        body /= oth.body;
        return *this; 
    }

    RealNumber & operator %=(const RealNumber &oth) 
    { 
        body = fmod(body, oth.body);
        return *this; 
    }

    bool operator ==(RealNumber const &oth) const 
    {
        return body == oth.body;
    }

    bool isZero() const
    {
        return body == 0;
    }
private:
    double body;
};



#endif
