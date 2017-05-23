//
//  Fractional_Polynom.h
//  Numbers_zeta
//
//  Created by Семен Пьянков on 01.11.13.
//  Copyright (c) 2013 Семен Пьянков. All rights reserved.
//

#pragma once
#include "Polynom.h"

class Fractional_Polynom
{
    public:
        Fractional_Polynom();
        Fractional_Polynom(Tree const & init);
        Fractional_Polynom(Polynom const & init);
        Fractional_Polynom(Polynom const & numerator, Polynom const & denominator);
        ~Fractional_Polynom();
    
        void initialize(Fractional_Polynom const &init);
        Polynom get_numerator() const;
        Polynom get_denominator() const;
    private:
        Polynom numerator;
        Polynom denominator;
};
