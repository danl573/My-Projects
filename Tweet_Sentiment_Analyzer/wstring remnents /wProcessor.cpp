//
// Created by Daniel Ryan on 9/1/21.
//

#include "../Processor.h"

Processor::Processor() {
    wordCount = 0;
    accuracy = 0;
}

void Processor::ReadTweets(DSString trainingName) {
    //Opening training file
    std::wifstream trainingFile;
    trainingFile.open(trainingName.c_str());

    //Initialize buffer and reading first line
    wchar_t* tweetLine = new wchar_t[1024];
    int sentiment = 0;
    trainingFile.getline(tweetLine, 1024);
    std::cout << "Reading tweets..." << std::endl;

    //Reading the rest of the training tweets
//    while(!trainingFile.eof()) {
    for(int i = 0; i < 10; i++) {
        //Read sentiment value
        trainingFile.getline(tweetLine, 1024, ',');
        sentiment = wcstol(tweetLine, nullptr, 10);

        //Skip to actual tweet
        for(int i = 0; i < 4; i++)
            trainingFile.getline(tweetLine, 1024, ',');
        trainingFile.getline(tweetLine, 1024);

        //Parse tweet
        DWString tweet(tweetLine);
        tweet.makeLower();
        std::vector<DWString> tempVec = tweet.stringParser(L" ,?!.\";", 3, 10);
        wordCount += tempVec.size();

        AddWords(tempVec, sentiment);
    }

//    for(auto& tweet : WordsSentiment) {
//        std::wcout << tweet.first ;
//        std::cout << ": " << tweet.second << std::endl;
//    }

    std::cout << wordCount << " words read" << std::endl;
    std::cout << "Finished reading tweets" << std::endl << std::endl;
    delete[] tweetLine;
    trainingFile.close();
}

void Processor::AddWords(std::vector<DWString>& tweets, int sentiment) {
    //Iterates through the parsed tweet to add words
    for(auto & tweet : tweets) {
        //ignores usernames
        if(tweet.getFirstChar() != '@') {
            //Checks if the word already exists in list
            if(WordsSentiment.find(tweet) == WordsSentiment.end()) {
                WordsSentiment.insert(std::pair<DWString, int>(tweet, sentiment));
            } else {
                //If word already added, updates sentiment value
                WordsSentiment.at(tweet) += (sentiment == 0) ? -1 : 1;
            }
        }
    }
}

void Processor::TestTweets(DSString testingName) {
    //Open testing file
    std::wifstream testingFile;
    testingFile.open(testingName.c_str());

    //initializes buffer and ignores first line
    wchar_t* tweetLine = new wchar_t[1024];
    DWString id;
    int sentiment = 0;
    testingFile.getline(tweetLine, 1024);
    std::cout << "Testing tweets..." << std::endl;

    //Reads the rest of the tweets
    while(!testingFile.eof()) {
        //Reads tweet ID and adds to list
        testingFile.getline(tweetLine, 1024, ',');
        DWString temp (tweetLine);
        IDsSentiment.insert(std::pair<DWString, int>(temp, 0));

        //Skips to tweet
        for(int i = 0; i < 3; i++)
            testingFile.getline(tweetLine, 1024, ',');
        testingFile.getline(tweetLine, 1024);

        //Reads and parses through tweet
        DWString tweet(tweetLine);
        tweet.makeLower();
        std::vector<DWString> tempVec = tweet.stringParser(L" ,?!.\";", 3, 10);

        //Determine a sentiment for tweet
        sentiment = FindSentiment(tempVec);
        IDsSentiment.at(temp) = (sentiment < 0) ? 0 : 4;
    }

    std::cout << IDsSentiment.size() << " tweets read" << std::endl;
    std::cout << "Finished testing tweets" << std::endl << std::endl;
    delete[] tweetLine;
    testingFile.close();
}

int Processor::FindSentiment(const std::vector<DWString>& tweet) {
    //Iterates through parsed tweets and determines sentiment
    int sentiment = 0;
    for(auto & i : tweet) {
        if(WordsSentiment.find(i) != WordsSentiment.end())
            sentiment += WordsSentiment.at(i);
    }
    return sentiment;
}

void Processor::CheckSentiment(DSString sentimentName) {
    //Opening sentiment file
    std::wifstream sentimentFile;
    sentimentFile.open(sentimentName.c_str());

    //Initialize buffer and skip first line
    auto line = new wchar_t[1024];
    sentimentFile.getline(line, 1024);
    int sentiment = 0;
    int correctTweets = 0;
    int totalTweets = 0;
    std::cout << "Checking sentiment..." << std::endl;

    //Read through rest of IDs
    while(!sentimentFile.eof()) {
        //Reads sentiment
        sentimentFile.getline(line, 1024, ',');
        sentiment = wcstol(line, nullptr, 10);

        //Read tweet ID
        sentimentFile.getline(line, 1024);

        //Check whether sentiment matches
        if(IDsSentiment.find(DWString(line)) != IDsSentiment.end() && IDsSentiment.at(DWString(line)) == sentiment) {
            correctTweets++;
        } else {
            incorrectTweets.emplace_back(line);
        }
        totalTweets++;
    }

    std::cout << "Finished checking sentiment" << std::endl;
    delete[] line;
    accuracy = correctTweets / (double)totalTweets;
    std::cout << std::endl;
    std::cout << "Accuracy: " << accuracy << std::endl;
    sentimentFile.close();
}

void Processor::OutputAccuracy(DSString outputName) {
    //Open output file
    std::ofstream outputFile;
    outputFile.open(outputName.c_str());

    //Print accuracy
    outputFile << std::fixed;
    outputFile << std::setprecision(3) << accuracy << std::endl;

    //Print incorrect tweet IDs
    for(auto& id : incorrectTweets) {
        outputFile << id << std::endl;
    }

    outputFile.close();
}



