#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "Processor.h"
#include "DSString.h"

int main(int argc, char** argv) {
    if(argc == 1) {
        return Catch::Session().run();
    } else {
        Processor p;
        p.ReadTweets(DSString(argv[1]));
        p.TestTweets(DSString(argv[2]));
        p.CheckSentiment(DSString(argv[3]));
        p.OutputAccuracy(DSString(argv[4]));
    }
    return 0;
}
