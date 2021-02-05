//
// Created by Selcuk on 8.12.2020.
//
#pragma once


// Truck class has power and id attributes



class Truck{
public:
    Truck();
    ~Truck();
    Truck(std::string id,std::string power);
    std::string id;
    std::string power;
};

Truck::Truck()
{
}

Truck::~Truck()
{
}

//Constructor

Truck::Truck(std::string xid,std::string xpower)
{
    id =xid;
    power = xpower;
}


