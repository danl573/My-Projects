#include "catch.hpp"
#include "DSList.h"
#include "DSStack.h"
#include <string>

TEST_CASE("Tests for DSList class methods and operators", "[DSList]") {
    DSList<int> test1;
    ///TEST USING OTHER DATA TYPES

    SECTION("Pushback and pushfront functions") {
        test1.push_back(5);
        test1.push_back(6);
        REQUIRE(test1.front() == 5);
        REQUIRE(test1.back() == 6);


        test1.push_front(1);
        REQUIRE(test1.front() == 1);

    }

    SECTION("Insert and Remove functions") {
        test1.clear();
        test1.push_back(1);
        test1.push_back(3);
        test1.push_back(4);

        auto iter = test1.begin();
        test1.insert(iter, 2);
        ++iter;
        REQUIRE(*iter == 2);

        iter = test1.end();
        test1.remove(iter);
        REQUIRE(test1.back() == 3);

        test1.pop();
        REQUIRE(test1.back() == 2);


    }

    SECTION("front and back functions") {
        test1.clear();

        try{
            test1.front();
        } catch(const std::out_of_range& e) {
            std::string t = "cant return empty list";
            REQUIRE(t == e.what());
        }

        try{
            test1.back();
        } catch(const std::out_of_range& e) {
            std::string t = "cant return empty list";
            REQUIRE(t == e.what());
        }


        test1.push_back(1);
        test1.push_back(2);
        REQUIRE(test1.front() == 1);
        REQUIRE(test1.back() == 2);
    }

    SECTION("size functions") {
        test1.clear();
        REQUIRE(test1.getSize() == 0);
        REQUIRE(test1.isEmpty());

        test1.push_back(1);
        test1.push_back(2);
        REQUIRE(test1.getSize() == 2);
        REQUIRE(!test1.isEmpty());
    }

    SECTION("Iterator test (pls work)") {
        test1.push_back(1);
        test1.push_back(2);
        test1.push_back(3);
        test1.push_back(4);
        test1.push_back(5);

        auto iter = test1.begin();
        auto iter2 = test1.begin();
        int i = *iter;

        REQUIRE(*iter == 1);
        ++iter;
        REQUIRE(*iter == 2);
        --iter;
        REQUIRE(*iter == 1);


        iter = test1.end();
        REQUIRE(*iter == 5);
        --iter;
        REQUIRE(*iter == 4);
        ++iter;
        REQUIRE(*iter == 5);

        REQUIRE(iter != iter2);
        iter2 = test1.end();
        REQUIRE(!(iter != iter2));

        REQUIRE(iter == iter2);
        iter2 = test1.begin();
        REQUIRE(!(iter == iter2));

        ///TEST ITERATOR MORE

    }

    SECTION("Find and Contains functions") {
        test1.clear();
        test1.push_back(1);
        test1.push_back(2);
        test1.push_back(3);
        test1.push_back(4);

        auto iter = test1.find(3);
        REQUIRE(*iter == 3);
    }
}

TEST_CASE("Tests for DSStack functions", "[DSStack]") {
    DSStack<int> stack;

    SECTION("Push and pop methods") {
        stack.push(1);
        REQUIRE(stack.top() == 1);
        stack.push(2);
        REQUIRE(stack.top() == 2);

        stack.pop();
        REQUIRE(stack.top() == 1);
        stack.pop();
        try{
            stack.top();
        } catch(const std::out_of_range& e) {
            std::string t = "cant return empty list";
            REQUIRE(t == e.what());
        }

        stack.push(1);
        stack.push(2);
        REQUIRE(!stack.isEmpty());
        stack.clear();
        REQUIRE(stack.isEmpty());

    }
}