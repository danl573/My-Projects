//
// Created by Daniel Ryan on 11/3/21.
//

#include "path.h"


path::path() {
    cost = INT_MAX;
    time = INT_MAX;
    iter = itin.begin();
}

void path::setSort(char n) {
    if(n == 'T')
        sort = "Time";
    else
        sort = "Cost";
}

std::string path::getSort() const {
    return sort;
}

void path::processPath(DSStack<DestCity> newPath, char s, const DestCity& sourceCity) {
    DestCity temp;
    cost = 0;
    time = 0;

    std::string airline;

    while (!newPath.isEmpty()) {
        temp = newPath.top();
        itin.push_front(temp);
        newPath.pop();
        if(!newPath.isEmpty()) {
            if((!(newPath.top() == sourceCity) && temp.getAirline() != newPath.top().getAirline()))
                time += 27;
            cost += (temp.getCost() + 23);
            time += (temp.getTime() + 43);

        }

    }

    if(s == 'T')
        sort = "Time";
    else
        sort = "Cost";

    cost -= 23;
    time -= 43;

}

int path::getCost() const {
    return cost;

}

int path::getTime() const {
    return time;
}

void path::setSourceDest(std::string s, std::string d) {
    source = s;
    dest = d;
}

std::string path::getSource() const {
    return source;
}

std::string path::getDest() const {
    return dest;
}

DestCity path::setToFront() {

    iter = itin.begin();
    if(itin.getSize() > 1)
        return iter.operator*();
    return {};
}

DestCity path::setToBack() {
    iter = itin.end();
    if(itin.getSize() > 1)
        return iter.operator*();
    return {};
}

DestCity path::setNext() {
    if(!(iter == itin.end()))
        ++iter;
    return iter.operator*();
}

DestCity& path::getData() {
    return iter.operator*();
}
