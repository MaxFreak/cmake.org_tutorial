//
// Created by Bernd Lappas on 08.11.15.
//

#ifndef CMAKE_ORG_TUTORIAL_GSL_SAMPLE_H
#define CMAKE_ORG_TUTORIAL_GSL_SAMPLE_H

#include <GSL.h>

using namespace::gsl;

class GSL_Sample
{

public:
    GSL_Sample();
    virtual ~GSL_Sample();
    void Sample();
    not_null<GSL_Sample *> NotNullFunction(not_null<GSL_Sample*> pGSL_Sample);

    void Span() const;
};


#endif //CMAKE_ORG_TUTORIAL_GSL_SAMPLE_H
