//
// Created by Bernd Lappas on 31.10.15.
//

#ifndef CMAKE_ORG_TUTORIAL_CEREALEXAMPLECLASSES_H
#define CMAKE_ORG_TUTORIAL_CEREALEXAMPLECLASSES_H


#ifdef USE_CEREAL
#include <cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/types/base_class.hpp>
#include "CerealExampleClasses.h"
#include <fstream>
#endif

struct MyData
{
    int x, y, z;

    // This method lets cereal know which data members to serialize
    template<class Archive>
    void serialize(Archive & archive)
    {
        archive( CEREAL_NVP(x),
                 CEREAL_NVP(y),
                 CEREAL_NVP(z)
                            ); // serialize things by passing them to the archive
    }
};

enum Color { RED, GREEN, BLUE };
struct ColorVal
{
    Color col;

    template <class Archive>
    Color save_minimal(
            Archive const &,
            ColorVal const & c )
    {
        return c.col;
    }

    template <class Archive>
    void load_minimal( Archive const &,
                       ColorVal & c,
                       Color const & value )
    {
        c.col = value;
    }
};

struct Base
{
    int x;
    ColorVal col;
    template <class Archive>
    void serialize( Archive & ar )
    {
        ar( CEREAL_NVP(x), CEREAL_NVP(col.col) );
    }
};


struct Derived : public Base
{
    int y;
    template <class Archive>
    void serialize( Archive & ar )
    {
        // We pass this cast to the base type for each base type we
        // need to serialize.  Do this instead of calling serialize functions
        // directly
        ar( cereal::base_class<Base>( this ), y );
    }
};

struct VirtualBase
{
    int x;
    // Note the non-member serialize - trying to call serialize
    // from a derived class wouldn't work
};

template <class Archive>
void serialize( Archive & ar, VirtualBase & b )
{ ar( b.x ); }

struct Left : virtual VirtualBase
{
    int l;

    template <class Archive>
    void serialize( Archive & ar )
    {
        ar( cereal::virtual_base_class<VirtualBase>( this ), l );
    }
};

struct Right : virtual VirtualBase
{
    int r;

    template <class Archive>
    void serialize( Archive & ar )
    {
        ar( cereal::virtual_base_class<VirtualBase>( this ), r );
    }
};

struct VirtualDerived : virtual Left, virtual Right
{
    int y;
    template <class Archive>
    void serialize( Archive & ar )
    {
        // Since we've used virtual inheritance and virtual_base_class,
        // cereal will ensure that only one copy of each base class
        // is serialized
        ar( cereal::virtual_base_class<Left>( this ),
            cereal::virtual_base_class<Right>( this ),
            y );
    }
};

// With virtual inheritance and cereal::virtual_base_class, x, l, r, and y will be serialized exactly once.
// If we had not used virtual_base_class, two copies of the base class may have been serialized,
// resulting in duplicate x entries.

void TestCereal();

#endif //CMAKE_ORG_TUTORIAL_CEREALEXAMPLECLASSES_H
