#include "catch.hpp"
#include "DSString.h"
#include "IndexEntry.h"

TEST_CASE("DSString operators and functions", "[DSString]") {
    DSString test1("potato");
    DSString test2("strawberry");
    DSString emptyTest("");
    DSString nullTest;
    DSString testCopy;

    SECTION("DSString == and != operators") {
        testCopy = "potato";
        REQUIRE(test1 == testCopy);
        REQUIRE(!(test1 != testCopy));
        testCopy = "POTATO";
        REQUIRE(!(test1 == testCopy));
        REQUIRE(test1 != testCopy);
        testCopy = "";
        REQUIRE(emptyTest == testCopy);
        REQUIRE(!(nullTest == testCopy));
        REQUIRE(!(emptyTest != testCopy));
        REQUIRE(!(nullTest != testCopy));
    }

    SECTION("DSString > and >= operators") {
        testCopy = "raspberry";
        REQUIRE(!(test1 > testCopy));
        REQUIRE(test2 > testCopy);
        REQUIRE(testCopy > emptyTest);
        REQUIRE(!(nullTest > testCopy));

        REQUIRE(!(test1 >= testCopy));
        REQUIRE(test2 >= testCopy);
        REQUIRE(testCopy >= emptyTest);
        REQUIRE(!(nullTest >= testCopy));
        testCopy = "potato";
        REQUIRE(test1 >= testCopy);
    }

    SECTION("DSString < and <= operators") {
        testCopy = "raspberry";
        REQUIRE(test1 < testCopy);
        REQUIRE(!(test2 < testCopy));
        REQUIRE(!(testCopy < emptyTest));
        REQUIRE(!(nullTest < testCopy));

        REQUIRE(test1 <= testCopy);
        REQUIRE(!(test2 <= testCopy));
        REQUIRE(!(testCopy <= emptyTest));
        REQUIRE(!(nullTest <= testCopy));
        testCopy = "potato";
        REQUIRE(test1 <= testCopy);
    }

    SECTION("DSString [] bracket operator") {
        REQUIRE(test1[0] == 'p');
        //If index not in bounds, outputs first char
        REQUIRE(test1[-5] == 'p');
        REQUIRE(test1[500] == 'p');
        //testCopy[1] = 'l';
        //REQUIRE(testCopy[1] == 'l');

        //figure something out for empty string
        //REQUIRE(emptyTest[0] == 0);
        //REQUIRE(nullTest[0] == 0);
    }

    SECTION("DSString = and + operators") {
        testCopy = test1 + test2;
        REQUIRE(testCopy == "potatostrawberry");

        testCopy = test1 + "lemon";
        REQUIRE(testCopy == "potatolemon");
        testCopy = test1 + "";
        REQUIRE(testCopy == "potato");
        testCopy = test1 + nullTest;
        REQUIRE(testCopy == "potato");
        testCopy = nullTest + test1;
        REQUIRE(testCopy == "");
    }

    SECTION("DSString substring method") {
        testCopy = test1.substring(2, 5);
        REQUIRE(testCopy == "tat");
        testCopy = test1.substring(5, 2);
        REQUIRE(testCopy == "potato");
        testCopy = test1.substring(-1, 3);
        REQUIRE(testCopy == "potato");
        testCopy = test1.substring(2, 400);
        REQUIRE(testCopy == "potato");
        testCopy = test1.substring(2,2);
        REQUIRE(testCopy == "");
        testCopy = test1.substring(2,-1);
        REQUIRE(testCopy == "tato");
    }

    SECTION("DSString makeLower method") {
        testCopy = "POTATO";
        testCopy.makeLower();
        REQUIRE(testCopy == "potato");
        testCopy = "LeMoN";
        testCopy.makeLower();
        REQUIRE(testCopy == "lemon");
        testCopy = "taco.,<;";
        testCopy.makeLower();
        REQUIRE(testCopy == "taco.,<;");
    }

    SECTION("DSString parsing method") {
        testCopy = "Hello there I am pacman";
        std::vector<DSString> words = testCopy.stringParser(' ');
        REQUIRE(words[0] == "Hello");
        REQUIRE(words[4] == "pacman");

        testCopy = "Hello! there. I am \"pacman";
        words.clear();
        words = testCopy.stringParser(" .!\"");
        REQUIRE(words[0] == "Hello");
        REQUIRE(words[4] == "pacman");
    }

    SECTION("DSString getFirstChar method") {
        REQUIRE(test1.getFirstChar() == 'p');
        REQUIRE(emptyTest.getFirstChar() == ' ');
        REQUIRE(nullTest.getFirstChar() == ' ');
    }

    SECTION("DSString stemming method") {
        DSString stem("producer");
        stem.stem();
        REQUIRE(stem == "produc");

        stem = "eating";
        stem.stem();
        REQUIRE(stem == "eat");

        stem = "exciting";
        stem.stem();
        REQUIRE(stem == "excit");
    }

}

TEST_CASE("IndexEntry methods and functions", "[IndexEntry]") {
    IndexEntry test("word");

    SECTION("IndexEntry page number methods") {
        test.addPageNumber(5);
        test.addPageNumber(8);
        REQUIRE(test.getPageNumber(0) == 5);
        REQUIRE(test.getPageNumber(1) == 8);
        REQUIRE(test.getPageNumberSize() == 2);
    }

    SECTION("IndexEntry removeChars method") {
        IndexEntry test1("[HI] there \n im [john]");
        IndexEntry test2 = test1.removeChars();
        REQUIRE(test2 == "HI there  im john");

        test1 = "";
        test2 = test1.removeChars();
        REQUIRE(test2 == "");

        test1 = "[[[[\n]]]]";
        test2 = test2.removeChars();
        REQUIRE(test2 == "");
    }
}
// data/test_book.txt output.txt