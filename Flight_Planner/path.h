#ifndef INC_21F_FLIGHT_PLANNER_PATH_H
#define INC_21F_FLIGHT_PLANNER_PATH_H

#include <climits>
#include <iostream>
#include "DSList.h"
#include "DestCity.h"
#include "DSStack.h"

class path {
private:
    DSList<DestCity> itin;
    DSList<DestCity>::Iterator iter;

    std::string sort;
    std::string source, dest;
    int cost;
    int time;



public:
    /**
     * Default constructor
     */
    path();

    /**
     *  Sets whether the path is sorted by cost or time
     *  @param n C for cost, T for time
     */
    void setSort(char);

    /**
     *  Returns how the path is sorted, cost or time
     * @return either Cost or Time depending on given sort
     */
    std::string getSort() const;

    /**
     *  Sets the source and dest variables to given parameter values
     */
    void setSourceDest(std::string, std::string);

    /**
     *  returns source and dest respectively
     */
    std::string getSource() const;
    std::string getDest() const;

    /**
     *  Returns the total cost of the flight path
     * @return cost
     */
    int getCost() const;

    /**
     *  Returns the total time of the flight path
     * @return time
     */
    int getTime() const;

    /**
     *  Pops given stack one by one to add up the cost and time
     */
    void processPath(DSStack<DestCity>, char, const DestCity&);

    ///Iterator methods for the path
    DestCity setToFront();
    DestCity setToBack();
    DestCity setNext();
    DestCity& getData();



};


#endif //INC_21F_FLIGHT_PLANNER_PATH_H
