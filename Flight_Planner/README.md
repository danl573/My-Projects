# Flight Planner  

The Flight Planner is a C++ project/library that will produce the 3 best paths, sorted by either time or cost, given a list of cities and the list of requested flights.

This program stores the list of cities and their possible connections with use of a custom **Adjacency Linked List** and finds the best paths through an exhaustive search using **Iterative Backtracking** on a Stack object.

## Installation

After downloading the Flight Planner folder, just include the Processor.h file into your main .

```cpp
#include "Processor.h"
```

## Usage
### Input File Formatting

``` 
5
Dallas Austin 98 47 Spirit
Dallas Austin 98 59 American
Austin Houston 95 39 United
Dallas Houston 101 51 Spirit
Austin Chicago 144 192 American
```
This is the *Flight Data* file, which contains the list of all connections and information regarding the cities. The top of the file contains an integer indicating the number of rows. Each subsequent line is formatted as follows:

<Originating City> <Destination City> <cost of flight> <time of flight> <Airline>

Each city and airline will always be input with no spaces, so "El Paso" should appear as "El_Paso"

```
2
Dallas Houston T
Chicago Dallas C
```
This is the *Requested Itineraries* file, which contains the space-delimited pairs of cities in which the exhaustive path searching will take place to find the most efficient flight paths based on time(T) or cost(C). The top of the file, again, contains an integer for the number of rows. Each subsequent line is formatted as follows:

<Starting city> <Ending City> <sort by time(T)/cost(C)>

The program will take into account assumed additional cost and time penalties for layovers. This will be 43 minutes and $23 for each layover.

### Output File

```
Flight 1: Dallas, Houston (Time)
  Itinerary 1:
    Dallas -> Houston (Spirit)
    Totals for Itinerary 1: Time: 51 Cost: 101.00
  Itinerary 2:
    Dallas -> Austin (Spirit)
    Austin -> Houston (United)
    Totals for Itinerary 2: Time: 156 Cost: 216.00
  Itinerary 3:
    Dallas -> Austin (American)
    Austin -> Houston (United)
    Totals for Itinerary 3: Time: 168 Cost: 216.00
```
This is an example output file for the first request of Dallas to Houston based on Time. The output will show the list of flights and airlines, as well as the total time and cost for each path.

### Example
```cpp
#include "Processor.h"

Processor p;
p.readFlights("Path_To_Flight-Data_textFile");
p.readItinerary("Path_To_Itineraries_textFile");
p.printPaths("Path_To_output_textFile");
```
The library contains 3 functions for generating the output paths, the readFlights(), readItinerary() and printPaths(). Notice how each functions requires one parameter, being the name or path to the file it is reading/writing to.


## Credits

All data structures and algorithms were completed by me, Daniel Ryan, as a programming assignment for CS 2341 taught by Dr. Fontenot at SMU.

Thank you to Dr. Fonteot and the CS2341 TAs for supporting me.

