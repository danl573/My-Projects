//
// Created by Daniel Ryan on 9/1/21.
//

#ifndef PA01_SENTIMENT_PROCESSOR_H
#define PA01_SENTIMENT_PROCESSOR_H

#include <fstream>
#include "DSString.h"
#include <vector>
#include <stdlib.h>
#include <map>
#include <iomanip>

class Processor {
private:
    std::map<DSString, int> WordsSentiment;
    std::map<DSString, int> IDsSentiment;
    std::vector<DSString> incorrectTweets;
    double accuracy;
    int wordCount;

public:
    Processor();

    void ReadTweets(DSString);
    void AddWords(std::vector<DSString>&, int sentiment);
    void TestTweets(DSString);
    int FindSentiment(const std::vector<DSString>&);
    void CheckSentiment(DSString);
    void OutputAccuracy(DSString);
};


#endif //PA01_SENTIMENT_PROCESSOR_H
