#ifndef SITE_H
#define SITE_H

#include <string>

struct Site
{
    std::string name;
    std::string info;

    Site(std::string name, std::string info)
    {
        this->name = name;
        this->info = info;
    }
};

#endif