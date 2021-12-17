#ifndef INC_21F_FLIGHT_PLANNER_DESTCITY_H
#define INC_21F_FLIGHT_PLANNER_DESTCITY_H

#include <string>

class DestCity {
private:
    std::string city;
    int cost;
    int time;
    std::string airline;

public:
    /**
     *  Constructors and operator functions
     */
    DestCity();
    DestCity(const std::string&, int, int, const std::string&);
    bool operator==(const DestCity&);

    /**
     *  Set data variables to given parameter
     */
    void setCity(const std::string&);
    void setCost(int);
    void setTime(int);
    void setAirline(const std::string&);

    /**
     *  Accessor methods to retrieve class data variables
     * @return the respective data variable
     */
    std::string getCity();
    int getCost() const;
    int getTime() const;
    std::string getAirline();

};


#endif //INC_21F_FLIGHT_PLANNER_DESTCITY_H
