//
// Created by Daniel Ryan on 10/26/21.
//

#include "DestCity.h"

DestCity::DestCity() {
    city = "";
    cost = 0;
    time = 0;
    airline = "";
}

DestCity::DestCity(const std::string& city, int cost, int time, const std::string& airline) {
    this->city = city;
    this->cost = cost;
    this->time = time;
    this->airline = airline;
}

void DestCity::setCity(const std::string& newCity) {
    this->city = newCity;
}

void DestCity::setCost(int newCost) {
    this->cost = newCost;
}

void DestCity::setTime(int newTime) {
    this->time = newTime;
}

void DestCity::setAirline(const std::string& newAirline) {
    this->airline = newAirline;
}

std::string DestCity::getCity() {
    return this->city;
}

int DestCity::getCost() const {
    return this->cost;
}

int DestCity::getTime() const {
    return this->time;
}

std::string DestCity::getAirline() {
    return this->airline;
}

bool DestCity::operator==(const DestCity& c) {
    return city == c.city;
}


