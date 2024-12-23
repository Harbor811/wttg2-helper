#ifndef CODE_H
#define CODE_H

#include <string>

struct Code
{
    std::string hash = "*";
    int wiki;

    Code()
    {
        hash = "|#x_MISSING|";
        wiki = -1;
    }
};

#endif