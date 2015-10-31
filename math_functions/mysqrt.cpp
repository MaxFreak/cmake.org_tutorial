//
// Created by Bernd Lappas on 30.10.15.
//

#include <math.h>
#include "mysqrt.h"

double mysqrt(double inputValue)
{
#if defined (HAVE_LOG) && defined (HAVE_EXP)
    result = exp(log(x)*0.5);
#else // otherwise use an iterative approach
        return sqrt(inputValue);
#endif
}