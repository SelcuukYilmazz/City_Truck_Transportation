//
// Created by Selcuk on 8.12.2020.
//
#pragma once
#include <iostream>


//Package class has id attribute
class Packages {
public:
    Packages();
    Packages(std::string xid);
    ~Packages();
    std::string id;

};

Packages::Packages()
{
}

Packages::Packages(std::string xid)
{
    id =xid;
}

Packages::~Packages()
{
}





