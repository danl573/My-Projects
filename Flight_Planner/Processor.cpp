//
// Created by Daniel Ryan on 10/27/21.
//

#include "Processor.h"

///Kachow my dudes\\\

void Processor::readFlights(const std::string& flightData) {
    std::cout << "~~~ Welcome to the Flight Planner Palooza. Please buckle your seatbelts for this fun ride! ~~~" << std::endl<<std::endl;
    //opens flight data
    std::ifstream flightFile;
    flightFile.open(flightData.c_str());

    //iterator for the list of existing cities
    auto iter = cities.begin();

    //creates vars for reading the file
    char* buffer = new char[1024];
    int lines, time, cost;
    std::string airline, destName;

    flightFile >> lines;
    flightFile.getline(buffer, 1024);

    //reading file, only reads necessary lines given
    std::cout << "Reading Flight Data file..." << std::endl;
    for(int i = 0; i < lines; i++) {
        //creates an Originating City object with given city name
        flightFile.getline(buffer, 1024, ' ');
        OrigCity orig(buffer);

        //saving line info
        flightFile.getline(buffer, 1024, ' ');
        destName = buffer;
        flightFile >> cost;
        flightFile >> time;
        flightFile.getline(buffer, 1024);
        airline = buffer;
        airline = airline.substr(1);

        //Creates a Destination City object
        DestCity dest(destName, cost, time, airline);

        //adds or updates list of existing cities
        for(int j = 0; j < 2; j++) {
            //adds orig city to existing cities list if new city
            if(!cities.contains(orig)) {
                cities.push_back(orig);
                iter = cities.find(orig);
                iter.operator*().addCity(dest);
            //otherwise, updates the orig city's destination cities list
            } else {
                iter = cities.find(orig);
                iter.operator*().addCity(dest);
            }
            //swaps dest and orig cities
            dest.setCity(orig.getName());
            orig.setName(destName);
        }
    }

    std::cout << "Finished reading " << lines << " lines of data!" << std::endl << std::endl;
    flightFile.close();
}

void Processor::readItinerary(const std::string& itineraryData) {
    //opens requested flights file
    std::ifstream itineraryFile;
    itineraryFile.open(itineraryData.c_str());

    //iterator for list of existing cities
    auto citiesIter = cities.begin();

    std::string depart, arrive;
    char sort;

    char* buffer = new char[1024];
    int lines;
    itineraryFile >> lines;
    itineraryFile.getline(buffer, 1024);

    //loop for reading requested lines
    std::cout << "Reading Requested Flight Itineraries..." << std::endl;
    for(int i = 0; i < lines; i++) {
        //reads and stores necessary info
        DestCity source, dest;
        itineraryFile.getline(buffer, 1024, ' ');
        source.setCity(buffer);
        itineraryFile.getline(buffer, 1024, ' ');
        dest.setCity(buffer);
        itineraryFile >> sort;
        itineraryFile.getline(buffer, 1024);

        //resets the inner destination cities iterator for each originating city
        while(!citiesIter.ifNull()) {
            citiesIter.operator*().resetIter();
            ++citiesIter;
        }

        //adds the source city into the stack
        paths.push(source);
        currCities.push_back(source);   //list of current cities in the stack

        //The beginning of the greatest exhaustive search method in the history of the world: Iterative Backtracking
        //uses the pseudocode provided by the great Eric Miao
        while(!paths.isEmpty()) {
            if(paths.top() == dest) {
                //saves the current flight path as path object if destination is reached
                path newPath;
                newPath.setSourceDest(source.getCity(), dest.getCity());
                newPath.processPath(paths, sort, source); //adds cost and time of path
                currPaths.push_back(newPath);

                //removes top of stack to continue searching
                paths.pop();
                currCities.remove(currCities.end());
            } else {
                //retrieves the most recently added city from existing cities list
                OrigCity top(paths.top().getCity());
                citiesIter = cities.find(OrigCity(paths.top().getCity()));
                OrigCity* currCity = &(citiesIter.operator*());     //pointer to city to avoid clutter//                    std::cout << currCity->iter.operator*().getCity()<< std::endl;

                if(currCity->iter.ifNull()) {
                    //removes most recent city if all destination cities have been searched
                    currCities.remove(currCities.end());
                    paths.pop();
                    currCity->resetIter();
                } else if(currCities.contains(currCity->iter.operator*()))
                    currCity->iter.operator++();    //doesn't add cities if already on stack
                else {
                    //pushes city on the stack
                    paths.push(currCity->iter.operator*());
                    currCities.push_back(currCity->iter.operator*());
                    currCity->iter.operator++();
                }
            }

        }

        //determines which ranking method to call
        if(sort == 'T')
            rankPathsTime();
        else
            rankPathsCost();
        currPaths.clear();  //clears list of cities on stack

    }

    std::cout << "Finished reading " << lines << " itinerary requests!" << std::endl << std::endl;
    itineraryFile.close();


}

void Processor::rankPathsTime() {
    auto iter = currPaths.begin();

    //simple algorithm for finding the 3 minimums of a list, O(n)
    std::cout << "  Ranking the current path based on TIME..." ;
    path min1, min2, min3;
    while (!iter.ifNull()) {
        int comp = iter.operator*().getCost();

        //sorry for long conditionals
        //it was weird to account for tied amounts
        if(comp < min1.getTime() || (comp == min1.getTime() && iter.operator*().getCost() < min1.getCost())) {
            min3 = min2;
            min2 = min1;
            min1 = iter.operator*();
        } else if(comp < min2.getTime() || (comp == min2.getTime() && iter.operator*().getCost() < min2.getCost())) {
            min3 = min2;
            min2 = iter.operator*();
        } else if(comp < min3.getTime() || (comp == min3.getTime() && iter.operator*().getCost() < min3.getCost()))
            min3 = iter.operator*();
        ++iter;
    }

    //kachow
    //adds path to minPaths list, used for printing
    minPaths.push_back(min1);
    minPaths.push_back(min2);
    minPaths.push_back(min3);
    std::cout << "Ranking successful >:) (i am always no.1)" << std::endl;

}

void Processor::rankPathsCost() {
    auto iter = currPaths.begin();

    //same as previous ranking method but for cost rather than time
    std::cout << "  Ranking the current path based on COST..." ;
    path min1, min2, min3;
    while (!iter.ifNull()) {
        int comp = iter.operator*().getCost();

        if(comp < min1.getCost() || (comp == min1.getCost() && iter.operator*().getTime() < min1.getTime())) {
            min3 = min2;
            min2 = min1;
            min1 = iter.operator*();
        } else if(comp < min2.getCost() || (comp == min2.getCost() && iter.operator*().getTime() < min2.getTime())) {
            min3 = min2;
            min2 = iter.operator*();
        } else if(comp < min3.getCost() || (comp == min3.getCost() && iter.operator*().getTime() < min3.getTime()))
            min3 = iter.operator*();

        ++iter;
    }

    //kachow but for cost
    //adds path to minPaths list, used for printing
    minPaths.push_back(min1);
    minPaths.push_back(min2);
    minPaths.push_back(min3);
    std::cout << "Ranking successful :P (Daniel never loses)" << std::endl;

}

void Processor::printPaths(const std::string& output01) {
    //opens output file to print itinerary
    std::ofstream outputFile;
    outputFile.open(output01.c_str());

    int reqNum = minPaths.getSize() / 3;
    auto iter = minPaths.begin();       //for iterating through the selected paths

    //printing loop, prints flight information
    std::cout << "Printing all the beautiful flight paths..." << std::endl;
    int count = 0;
    for(int i = 1; i <= reqNum; i++) {
        //resets iterator
        iter.operator*().setToFront();
        path* currPath = &(iter.operator*());   //pointer to reduce clutter
        std::string source = currPath->getSource();
        std::string dest = currPath->getDest();

        if(currPath->getCost() != INT_MAX) {
            //only prints if path exists (doesnt have an invalid cost)
            //prints according to example output
            outputFile << "Flight " << i <<": ";
            outputFile << source << ", " << dest << " (" << currPath->getSort() << ")\n";
            outputFile << "  Itinerary 1:\n";
            while(currPath->getData().getCity() != dest) {
                outputFile << "    " << currPath->getData().getCity() << " -> "
                           << currPath->setNext().getCity();
                outputFile << " (" << currPath->getData().getAirline() << ")\n";
            }
            outputFile << "    Totals for Itinerary 1: Time: " << currPath->getTime() << " Cost: " << currPath->getCost() << ".00\n";
            count++;
        } else {
            //prints error if no flights are found
            outputFile << "ERROR: No flights found for Flight " << i << "\n";
        }

        //increments iterator and resets it
        ++iter;
        currPath = &(iter.operator*());
        currPath->setToFront();
        if(currPath->getCost() != INT_MAX) {
            //only prints if path is valid
            outputFile << "  Itinerary 2:\n";
            while(currPath->getData().getCity() != dest) {
                outputFile << "    " << currPath->getData().getCity() << " -> "
                           << currPath->setNext().getCity();
                outputFile << " (" << currPath->getData().getAirline() << ")\n";
            }
            outputFile << "    Totals for Itinerary 2: Time: " << currPath->getTime() << " Cost: " << currPath->getCost() << ".00\n";
            count++;
        }

        //increments and resets iterator
        ++iter;
        currPath = &(iter.operator*());
        currPath->setToFront();
        if(currPath->getCost() != INT_MAX) {
            //only prints if path is valid
            outputFile << "  Itinerary 3:\n";
            while(currPath->getData().getCity() != dest) {
                outputFile << "    " << currPath->getData().getCity() << " -> "
                           << currPath->setNext().getCity();
                outputFile << " (" << currPath->getData().getAirline() << ")\n";
            }
            outputFile << "    Totals for Itinerary 3: Time: " << currPath->getTime() << " Cost: " << currPath->getCost() << ".00\n";
            count++;
        }
        ++iter;
        outputFile << "\n";

    }
    outputFile.close();
    std::cout << "Finished printing " << reqNum << " flights and " << count << " itineraries!" << std::endl <<std::endl;
    std::cout << "~~~ Thank you for attending this amazing Flight Planner Palooza, please come again! ~~~" << std::endl;
}