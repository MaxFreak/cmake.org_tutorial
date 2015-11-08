//
// Created by Bernd Lappas on 08.11.15.
//

#include <string>
#include <ostream>
#include <iostream>
#include "GSL_Sample.h"

using std::cout;
using std::endl;

GSL_Sample::GSL_Sample()
{
 cout << "GSL_Sample() " << std::hex << this << std::dec << endl;
}

GSL_Sample::~GSL_Sample()
{
    cout << "~GSL_Sample() " << std::hex << this << std::dec << endl;
}

void GSL_Sample::Sample()
{
    {
        owner<GSL_Sample *> pGSL_Sample = new GSL_Sample;
        delete pGSL_Sample;
        Expects(pGSL_Sample != nullptr);
        pGSL_Sample = nullptr;
    }

    owner<GSL_Sample *> pGSL_Sample = new GSL_Sample;
    owner<GSL_Sample *> pGSL_Sample2 = NotNullFunction(pGSL_Sample);
    delete pGSL_Sample2;
    Expects(pGSL_Sample2 != nullptr);
    pGSL_Sample2 = nullptr;
    Expects(pGSL_Sample2 == nullptr);
    Ensures(pGSL_Sample2 == nullptr);

    Span();


}

void GSL_Sample::Span() const
{
    auto ptr = as_span(new int[10], 10);
    fill(ptr.begin(), ptr.end(), 99);
    for (int num : ptr)
    {
        Expects(num == 99);
    }

    delete[] ptr.data();

    using std::string;

    string str = "abcdefghijklmnopqrstuvwxyz    "; // size = 26
    auto t = str.data();
    auto av3 = as_span(str);
//    overloaded_func(av3.as_span(dim<>(1), dim<3>(), dim<5>()), 't');
    auto av4 =av3.as_span(dim<>(2), dim<>(3), dim<>(5));

    auto width = 5, height = 20;

    auto imgSize = width * height;
    auto image_ptr = new int[imgSize][3];

    // size check will be done
    auto image_view = as_span(image_ptr, imgSize).as_span(dim<>(height), dim<>(width), dim<3>());

    iota(image_view.begin(), image_view.end(), 1);

    for (auto i = 0; i < height; i++)
    {
        for (auto j = 0; j < width; j++)
        {
            int r = image_view[i][j][0];
            int g = image_view[i][j][1];
            int b = image_view[i][j][2];

            std::cout << " r:" << r << " g:" << g << " b:" << b << std::endl;
        }
    }

}

not_null<GSL_Sample *> GSL_Sample::NotNullFunction(not_null<GSL_Sample *> pGSL_Sample)
{
    return gsl::not_null<GSL_Sample *>(pGSL_Sample);
}
