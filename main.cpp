// A simple program that computes the square root of a number

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>

#include "TutorialConfig.h"

#ifdef USE_CEREAL
#include <cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/types/base_class.hpp>
#include "CerealExampleClasses.h"
#include <fstream>
#endif

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

#ifdef USE_CEREAL
        {
        std::ofstream os("data.json");
        cereal::JSONOutputArchive archive(os);

        MyData m1;
        m1.x = 1, m1.y = 2, m1.z = 3;
        int someInt;
        double dou;
        Base b; b.x = 25;b.col.col=BLUE;
        Derived d; d.y = 50;

        archive( CEREAL_NVP(m1), // Names the output the same as the variable name
                 someInt,        // No NVP - cereal will automatically generate an enumerated name
                 cereal::make_nvp("this name is way better", dou), // specify a name of your choosing
                 cereal::make_nvp("Base", b) ,// specify a name of your choosing
            cereal::make_nvp("Derived", d) ); // specify a name of your choosing
    }

    {
        std::ifstream is("data.json");
        cereal::JSONInputArchive archive(is);

        MyData m1;
        int someInt;
        double dou;
        Base b;
        Derived d;

        archive( m1, someInt, dou, b, d ); // NVPs not strictly necessary when loading
        // but could be used (even out of order)
    }
#endif
    return 0;
}
