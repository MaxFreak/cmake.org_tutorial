//
// Created by Bernd Lappas on 31.10.15.
//

#ifndef CMAKE_ORG_TUTORIAL_OBJECT_H
#define CMAKE_ORG_TUTORIAL_OBJECT_H

#include <ostream>
#include <memory>
#include <vector>

using std::string;
using std::ostream;
using std::endl;
using std::move;
using std::make_shared;
using std::shared_ptr;
using std::vector;

template <typename T>
void draw(const T& x, ostream& out, size_t position)
{
    out << string(position, ' ') << x << endl;
}

class object_t
{
public:
    template<typename T>
    object_t(T x) : m_Self(make_shared<model < T>>(move(x)))
    {
    }

    friend void draw(const object_t &x, ostream &out, size_t position)
    {
        x.m_Self->draw_intern(out, position); 
    }

private:
    struct concept_t
    {
        virtual ~concept_t() = default;

        virtual void draw_intern(ostream &, size_t) const = 0;
    };

    template<typename T>
    struct model : concept_t
    {
        model(T x) : m_Data(move(x)) 
        {
        }

        void draw_intern(ostream &out, size_t position) const
        {
            draw(m_Data, out, position);
        }

        T m_Data;
    };

    shared_ptr<const concept_t> m_Self;
};

using document_t = vector<object_t>;

void draw(const document_t &x, ostream &out, size_t position)
{
    out << string(position, ' ') << "<document>" << endl;
    for (auto &e : x)
        draw(e, out, position + 2);
    out << string(position, ' ') << "</document>" << endl;
}

#endif //CMAKE_ORG_TUTORIAL_OBJECT_H
