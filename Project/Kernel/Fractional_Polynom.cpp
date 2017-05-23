//
//  Fractional_Polynom.cpp
//  Numbers_zeta
//
//  Created by Семен Пьянков on 01.11.13.
//  Copyright (c) 2013 Семен Пьянков. All rights reserved.
//

#include "Fractional_Polynom.h"

Fractional_Polynom::Fractional_Polynom()
{
    Polynom a;
    numerator.initialize(a);
}

Fractional_Polynom::~Fractional_Polynom()
{
    
}

Fractional_Polynom::Fractional_Polynom(Polynom const &init)
{
    numerator = init;
    Polynom a;
    denominator.initialize(a);
}

Fractional_Polynom::Fractional_Polynom(Polynom const &num, Polynom const &den)
{
    numerator = num;
    denominator = den;
}

Polynom Fractional_Polynom::get_numerator() const{
    return numerator;
}

Polynom Fractional_Polynom::get_denominator() const{
    return denominator;
}

void Fractional_Polynom::initialize(Fractional_Polynom const &init)
{
    numerator = init.numerator;
    denominator = init.denominator;
}
