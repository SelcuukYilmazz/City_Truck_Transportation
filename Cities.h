//
// Created by Selcuk on 8.12.2020.
//
#pragma once
#include <string>
#include "Stack.h"
#include "Queue.h"
#include "Packages.h"

class Cities{
public:
    Cities();
    Cities(std::string city, Stack<struct Packages> *package,Queue<struct Truck> *trucks);
    ~Cities();

    const std::string &getCityName() const;

    //Stations have packages insisde it

    Stack<Packages> packages;

    //Stations garage is here

    Queue<Truck> trucks;

private:
    std::string city_name;
};

Cities::Cities()
{

}

Cities::Cities(std::string city, Stack<struct Packages> *package,Queue<struct Truck> *truck)
{
    city_name=city;
    packages = *package;
    trucks = *truck;
}

Cities::~Cities() {

}

const std::string &Cities::getCityName() const {
    return city_name;
}
