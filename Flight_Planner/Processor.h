#ifndef INC_21F_FLIGHT_PLANNER_PROCESSOR_H
#define INC_21F_FLIGHT_PLANNER_PROCESSOR_H

#include <fstream>
#include <climits>
#include "OrigCity.h"
#include "DSStack.h"
#include "DSList.h"
#include "path.h"

class Processor {
private:
    //im the list MASTER, some of these could've been local but eh
    DSList<OrigCity> cities;
    DSStack<DestCity> paths;
    DSList<DestCity> currCities;
    DSList<path> currPaths;
    DSList<path> minPaths;

public:
    Processor() = default;

    void readFlights(const std::string& flightData);
    void readItinerary(const std::string& itineraryData);
    void rankPathsTime();
    void rankPathsCost();
    void printPaths(const std::string& output01);

};


#endif //INC_21F_FLIGHT_PLANNER_PROCESSOR_H
