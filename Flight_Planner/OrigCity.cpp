#include "OrigCity.h"
#include <iostream>

OrigCity::OrigCity() {
    name = "";
    iter = cities.begin();
}

OrigCity::OrigCity(std::string city) {
    name = city;
}

void OrigCity::printCities() {
    auto tempIter = cities.begin();

    while(tempIter != cities.end()) {
        std::cout << tempIter.operator*().getCity() << ", ";
        ++tempIter;
    }

}

void OrigCity::addCity(DestCity& city) {
    cities.push_back(city);
}

void OrigCity::setName(std::string& city) {
    name = city;
}

std::string OrigCity::getName() {
    return name;
}

bool OrigCity::operator==(const OrigCity& city) {
    return (this->name == city.name);
}

void OrigCity::resetIter() {
    iter = cities.begin();
}
