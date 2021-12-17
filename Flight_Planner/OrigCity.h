#ifndef INC_21F_FLIGHT_PLANNER_ORIGCITY_H
#define INC_21F_FLIGHT_PLANNER_ORIGCITY_H

#include "DestCity.h"
#include "DSList.h"

class OrigCity {
private:
    std::string name;
    DSList<DestCity> cities;


public:
    ///Iterator for the list of Destination Cities (sorry i was too lazy to implement it differently)
    DSList<DestCity>::Iterator iter;

    /**
     * Constructors and operator functions
     */
    OrigCity();
    OrigCity(std::string);
    bool operator==(const OrigCity&);

    /**
     *  Mutator and operator functions for name class variable
     */
    void setName(std::string&);
    std::string getName();

    /**
     *  Prints all the destination cities
     */
    void printCities();

    /**
     *  Adds a city to the end of cities list
     */
    void addCity(DestCity&);

    /**
     *  resets the cities iterator to the front of the list
     */
    void resetIter();
};


#endif //INC_21F_FLIGHT_PLANNER_ORIGCITY_H
