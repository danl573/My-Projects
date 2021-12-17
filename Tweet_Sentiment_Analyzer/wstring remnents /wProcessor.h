//
// Created by Daniel Ryan on 9/1/21.
//

#ifndef PA01_SENTIMENT_PROCESSOR_H
#define PA01_SENTIMENT_PROCESSOR_H

#include <fstream>
#include "DWString.h"
#include "../DSString.h"
#include <vector>
#include <stdlib.h>
#include <map>
#include <iomanip>

class Processor {
private:
    std::map<DWString, int> WordsSentiment;
    std::map<DWString, int> IDsSentiment;
    std::vector<DWString> incorrectTweets;
    double accuracy;
    int wordCount;

public:
    Processor();

    void ReadTweets(DSString);
    void AddWords(std::vector<DWString>&, int sentiment);
    void TestTweets(DSString);
    int FindSentiment(const std::vector<DWString>&);
    void CheckSentiment(DSString);
    void OutputAccuracy(DSString);
};


#endif //PA01_SENTIMENT_PROCESSOR_H
