#include "catch.hpp"
#include "DSVector.h"
#include "DSString.h"

TEST_CASE("DSVector operators and functions", "[DSVector]") {
    DSVector<int> test1;
    DSVector<int> test2;

    SECTION("Push_back and insert functions"){
        test1.push_back(5);
        test1.push_back(7);
        test1.push_back(8);
        REQUIRE(test1[0] == 5);
        REQUIRE(test1[1] == 7);
        REQUIRE(test1[2] == 8);

        test1.insert(4, 0);
        test1.insert(6, 2);
        test1.insert(9, 5);
        REQUIRE(test1[0] == 4);
        REQUIRE(test1[2] == 6);
        REQUIRE(test1[5] == 9);

        try{
            test1.insert(10, -20);
        } catch (const std::out_of_range& e) {
            DSString t = "bad index value";
            REQUIRE(t == e.what());
        }

    }

    SECTION("Copy constructor and = operator") {
        DSVector<int> copyTest1(test1);
        REQUIRE(copyTest1.getSize() == 0);
        REQUIRE(copyTest1.getCapacity() == 10);

        test1.push_back(5);
        test1.push_back(7);
        test1.push_back(8);
        DSVector<int> copyTest2(test1);
        REQUIRE(test1[1] == copyTest2[1]);
        REQUIRE(test1[0] == copyTest2[0]);

        copyTest2 = copyTest1;
        REQUIRE(copyTest2.getSize() == 0);
        REQUIRE(copyTest2.getCapacity() == 10);

    }

    SECTION("Size and capacity functions") {
        REQUIRE(test1.getSize() == 0);
        REQUIRE(test1.getCapacity() == 10);

        for(int i = 0; i < 11; i++)
            test1.push_back(i);
        REQUIRE(test1.getSize() == 11);
        REQUIRE(test1.getCapacity() == 20);

    }

    SECTION("Element access methods") {
        test1.push_back(5);
        test1.push_back(7);
        test1.push_back(8);
        REQUIRE(test1[0] == 5);
        REQUIRE(test1.at(1) == 7);
        REQUIRE(test1.front() == 5);
        REQUIRE(test1.back() == 8);

        try{
            test1[5];
        } catch (const std::out_of_range& e) {
            DSString t = "bad index value";
            REQUIRE(t == e.what());
        }
    }

    SECTION("Pop_back and remove methods") {
        try{
            test1.pop_back();
        } catch (const std::out_of_range& e) {
            DSString t = "can't pop empty array";
            REQUIRE(t == e.what());
        }

        test1.push_back(5);
        test1.push_back(7);
        test1.push_back(8);
        test1.pop_back();
        REQUIRE(test1.back() == 7);
        test1.removeIndex(0);
        REQUIRE(test1.getSize() == 1);
        test1.removeObject(7);
        REQUIRE(test1.getSize() == 0);
        REQUIRE(test1.getCapacity() == 10);

        try{
            test1.removeIndex(9);
        } catch (const std::out_of_range& e) {
            DSString t = "bad index value";
            REQUIRE(t == e.what());
        }

        //check bool return
        REQUIRE(test1.removeObject(8) == false);

    }

    SECTION("Clear method") {
        test1.push_back(5);
        test1.push_back(7);
        test1.push_back(8);
        REQUIRE(test1.getSize() == 3);
        test1.clear();
        REQUIRE(test1.getSize() == 0);
        REQUIRE(test1.getCapacity() == 10);

        //clearing empty vector
        test1.clear();
        REQUIRE(test1.getSize() == 0);

        //checking capacity
        for(int i = 0; i < 11; i++)
            test1.push_back(i);
        REQUIRE(test1.getCapacity() == 20);
        test1.clear();
        REQUIRE(test1.getCapacity() == 20);

    }

    SECTION("Sort and swap methods") {

        //swap test
        test1.push_back(5);
        test1.push_back(7);
        test1.push_back(8);

        test1.swap(0,2);
        REQUIRE(test1[0] == 8);
        REQUIRE(test1[2] == 5);

        try {
            test1.swap(0, 5);
        } catch (const std::out_of_range& e){
            DSString t = "bad index value";
            REQUIRE(t == e.what());
        }

        //sort test
        test1.clear();
        test1.push_back(8);
        test1.push_back(7);
        test1.push_back(5);
        test1.push_back(2);
        test1.push_back(0);
        test1.sort();
        REQUIRE(test1.front() == 0);
        REQUIRE(test1.back() == 8);

    }

    SECTION("find method") {
        //empty vector
        REQUIRE(test1.find(5) == -1);

        test1.push_back(8);
        test1.push_back(7);
        test1.push_back(5);
        test1.push_back(2);
        test1.push_back(0);
        REQUIRE(test1.find(5) == 2);
        REQUIRE(test1.find(39209) == -1);

    }
}
