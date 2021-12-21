/**
 * Fall 2021 PA 02 Template Repo.
 */

#include <iostream>
#include <fstream>

/**
 * catch_setup.h and catch_setup.cpp contain the #define directive for
 * the CATCH2 framework.  You can see in main below how I'm calling the
 * runCatchTests() function which is declared in this header.
 *
 * On average, this should reduce the build time for your project on your local
 * machine.
 */
#include "catch_setup.h"
#include "Processor.h"

int main(int argc, char** argv) {
    if(argc == 1) {
        runCatchTests();
    }
    else {
        Processor p;
        p.ReadBook(argv[1]);
        p.PrintIndex(argv[2]);
    }
    return 0;
}
