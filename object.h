//
// Created by Bernd Lappas on 31.10.15.
//

#ifndef CMAKE_ORG_TUTORIAL_OBJECT_H
#define CMAKE_ORG_TUTORIAL_OBJECT_H

#include <ostream>
#include <memory>
#include <vector>
#include <cassert>

using std::string;
using std::ostream;
using std::endl;
using std::move;
using std::make_shared;
using std::shared_ptr;
using std::vector;

template<typename T>
void draw(const T &x, ostream &out, size_t position) { out << string(position, ' ') << x << endl; }

class object_t
{
public:
    template<typename T>
    object_t(T x) : m_Self(make_shared<model < T>>(move(x)))
    { }

    friend void draw(const object_t &x, ostream &out, size_t position) { x.m_Self->internal_draw(out, position); }

private:
    struct concept_t
    {
        virtual ~concept_t() = default;

        virtual void internal_draw(ostream &, size_t) const = 0;
    };

    template<typename T>
    struct model : concept_t
    {
        model(T x) : m_Data(move(x)) { }

        void internal_draw(ostream &out, size_t position) const { draw(m_Data, out, position); }

        T m_Data;
    };

    shared_ptr<const concept_t> m_Self;
};

//typedef vector<object_t> DocumentVector;
using DocumentVector = vector<object_t>;

class document_t
{
public:
//    typedef DocumentVector::const_iterator const_iterator;
    using const_iterator = DocumentVector::const_iterator;

    template <class... Args>
    void emplace_back(Args&&... args)
    {
        m_Childs.emplace_back(std::forward<Args>(args)...);
    }

    template <class... Args>
    typename DocumentVector::reference
    operator[](Args&&... args)
    {
        return m_Childs.operator[](std::forward<Args>(args)...);
    }

    template <class... Args>
    typename DocumentVector::reference
    operator[](Args&&... args) const
    {
        return m_Childs.operator[](std::forward<Args>(args)...);
    }

    DocumentVector::size_type size()
    {
        return m_Childs.size();
    }

    const_iterator begin() const
    {
        return m_Childs.begin();
    }

    const_iterator end() const
    {
        return m_Childs.end();
    }
private:

    DocumentVector m_Childs;
};

//using document_t = vector<object_t>;

void draw(const document_t &x, ostream &out, size_t position)
{
    out << string(position, ' ') << "<document>" << endl;
    for (auto &e : x)
        draw(e, out, position + 2);
    out << string(position, ' ') << "</document>" << endl;
}

using history_t = vector<document_t>;

void commit(history_t &x)
{
    assert(x.size());
    x.push_back(x.back());
}

void undo(history_t &x)
{
    assert(x.size());
    x.pop_back();
}

document_t &current(history_t &x)
{
    assert(x.size());
    return x.back();
}

#endif //CMAKE_ORG_TUTORIAL_OBJECT_H
