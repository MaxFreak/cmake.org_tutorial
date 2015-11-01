//
// Created by Bernd Lappas on 01.11.15.
//

#include "TutorialConfig.h"

#include "CerealExampleClasses.h"

void TestCereal()
{
    {
        std::ofstream os("data.json");
        cereal::JSONOutputArchive archive(os);
        cereal::JSONOutputArchive archive2(std::__1::cout);

        MyData m1;
        m1.x = 1, m1.y = 2, m1.z = 3;
        int someInt;
        double dou;
        Base b;
        b.x = 25;
        b.col.col = BLUE;
        Derived d;
        d.y = 50;

        archive(CEREAL_NVP(m1), // Names the output the same as the variable name
                someInt,        // No NVP - cereal will automatically generate an enumerated name
                cereal::make_nvp("this name is way better", dou), // specify a name of your choosing
                cereal::make_nvp("Base", b),// specify a name of your choosing
                cereal::make_nvp("Derived", d)); // specify a name of your choosing
        archive2(CEREAL_NVP(m1), // Names the output the same as the variable name
                 someInt,        // No NVP - cereal will automatically generate an enumerated name
                 cereal::make_nvp("this name is way better", dou), // specify a name of your choosing
                 cereal::make_nvp("Base", b),// specify a name of your choosing
                 cereal::make_nvp("Derived", d)); // specify a name of your choosing

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
}
