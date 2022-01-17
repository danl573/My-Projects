#include "catch.hpp"
#include "DSHashTable.h"
#include <string>

TEST_CASE("Tests for methods for DSHashTable class", "[DSHashTable]") {
    DSHashTable<int , int> test01;

    SECTION("kachow") {
//        test01.insert(5, 10);
//        test01.insert(12,11);
//        test01.remove(5);
//
//        test01.insert(6);

        ///implement error handling for invalid inputs: Warnings or exceptions in all methods///
//        std::cout << test01.get(12) << std::endl;
        test01.printTable();
        //int 4 = test01.get(6);
        //test01.search(5);

    }

}