// A simple program that computes the square root of a number

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <string>

#include "TutorialConfig.h"
#include "object.h"

#include "CerealExampleClasses.h"

#ifdef USE_MYMATH
#include "mysqrt.h"
#endif

class my_class_t
{
/* ... */
};

void draw(const my_class_t&, std::ostream& out, size_t position)
{
    out << std::string(position, ' ') << "my_class_t" << std::endl;
}

class their_class_t
{
/* ... */
};

void TestCereal();

void draw(const their_class_t&, std::ostream& out, size_t position)
{
    out << std::string(position, ' ') << "their_class_t" << std::endl;
}

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
    TestCereal();
#endif

    using std::cout;

    cout << endl;
    cout << endl;

    history_t h(1);

    current(h).m_Childs.emplace_back(0);
    current(h).m_Childs.emplace_back(string("Hello!"));

    draw(current(h), cout, 0);
    cout << "--------------------------" << endl;

    commit(h);

    current(h).m_Childs.emplace_back(current(h));
    current(h).m_Childs.emplace_back(my_class_t());
    current(h).m_Childs[1] = string("World");
    current(h).m_Childs.emplace_back(their_class_t());

    draw(current(h), cout, 0);
    cout << "--------------------------" << endl;

    undo(h);

    draw(current(h), cout, 0);

    return 0;
}

