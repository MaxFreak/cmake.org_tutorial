// A simple program that computes the square root of a number

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "TutorialConfig.h"

#ifdef USE_MYMATH
#include "mysqrt.h"
#endif

int main (int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stdout,"%s Version %d.%d.%d\n",
                argv[0],
                BUILD_VERSION_MAJOR,
                BUILD_VERSION_MINOR,
                BUILD_VERSION_MICRO);
        fprintf(stdout,"Usage: %s number\n",argv[0]);
        return 1;
    }

    double inputValue = atof(argv[1]);

#ifdef USE_MYMATH
    fprintf(stdout,"USE_MYMATH ON\n");
    double outputValue = mysqrt(inputValue);
#else
    fprintf(stdout,"USE_MYMATH OFF\n");
    double outputValue = sqrt(inputValue);
#endif

    fprintf(stdout,"The square root of %g is %g\n",
            inputValue, outputValue);
    return 0;
}
