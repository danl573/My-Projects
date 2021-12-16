//
// Created by Daniel Ryan on 11/17/21.
//

#include "Query.h"

void Query::SearchWord(const DSString& file) {

    std::cout << "\n-_-_-_-_-_-Welcome to the Finance Search Engine!!-_-_-_-_-_-" << std::endl;
    std::cout << "-_-Brought to you by one sad and lonely Momo Hirai Fanboy-_-" << std::endl;
    IndexingOptions(file);

    std::string num = "1";
    while(num != "0") {
        std::cout << "\n==================================" << std::endl;
        std::cout << "Please choose an option:" << std::endl;
        std::cout << "[1]Search" << std::endl;
        std::cout << "[2]Get Statistics" << std::endl;
        std::cout << "[3]Open Article" << std::endl;
        std::cout << "[4]Clear Index" << std::endl;
        std::cout << "[5]Make Persistent Index" << std::endl;
        std::cout << "[6]Load Index" << std::endl;
        std::cout << "[0]Quit" << std::endl;
        std::cout << "==================================\n" << std::endl;
//        std::getline(std::cin, num);
        std::cin >> num;

        if (num == "1") {
            std::string word;
            std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            std::cout << "Enter Word: " << std::endl;
            std::cin >> word;
            DSString condition(word.c_str());
            Search(condition);
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << std::endl;
        } else if (num == "2") {
            std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            p.getWordStats();
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << std::endl;
        } else if (num == "3") {
            std::string word;
            std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            std::cout << "Enter Article ID: ";
            std::cin >> word;
            p.openSingleFile(word);
        } else if (num == "4") {
            std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            p.clearIndex();
            std::cout << "Index successfully cleared" << std::endl;
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << std::endl;
        }else if (num == "5") {
            std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            p.makePersistenceFiles();
            std::cout << "Persistence files created" << std::endl;
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << std::endl;
        } else if(num == "6") {
            p.clearIndex();
            IndexingOptions(file);
        } else if(num == "0") {
            std::cout << "~~~~~~~~~~~~Adios, Thanks for stopping by!!~~~~~~~~~~~~" << std::endl;
        } else{
            std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            std::cout << "Error: not a valid option" << std::endl;
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << std::endl;
            num = "1";
        }
    }
}

void Query::IndexingOptions(const DSString& file) {
    std::string num = "-1";

    while(num == "-1") {
        std::cout << "\n==================================" << std::endl;
        std::cout << "Please choose an option:" << std::endl;
        std::cout << "[1]Read from Persistent Index" << std::endl;
        std::cout << "[2]Read from Documents" << std::endl;
        std::cout << "[0]Quit" << std::endl;
        std::cin >> num;
        if(num == "1") {
            std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            std::cout << "Loading..." << std::endl;
            p.readPersistenceFiles();
            std::cout << "Index successfully loaded" << std::endl;
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << std::endl;
        } else if(num == "2") {
            std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            std::cout << "Loading..." << std::endl;
            p.open_dir_using_filesystem(file);
            std::cout << "\nFiles successfully read" << std::endl;
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << std::endl;
        } else if(num == "0")
            std::cout << "~~~~~~~~~~~~Adios, Thanks for stopping by!!~~~~~~~~~~~~" << std::endl;
        else{
            std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            std::cout << "Error: not a valid option" << std::endl;
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << std::endl;
            num = "-1";
        }
    }
}

void Query::singleWordSearch(DSString searchWord) {
    std::string temp;
    searchWord.stem();
    orWords.push_back(searchWord);
    allWords.push_back(searchWord);
    processOR();
    printResults();
//    std::vector<std::string> docIDs = p.searchWord(searchWord);
//    std::cout << "Results: " << std::endl;
//
//    if(docIDs.empty())
//        std::cout << "   No Results found" << std::endl;
//    else {
//        for (auto &i: docIDs) {
//            if(i != temp)
//                std::cout << "   " << i << ": " << p.getDocumento(i).getTitle() << std::endl;
//            temp = i;
//        }
//    }
}

//void Query::multipleWordSearch(DSString condition) {
//    condition.makeLower();
//    if(condition != "and" && condition != "or")
//        singleWordSearch(condition);
//    else {
//        std::vector<std::vector<Documento>> sets;
//        std::vector<DSString> words;
//        std::string temp;
//        std::getline(std::cin, temp);
//        std::stringstream ss(temp);
//        while(ss.good()) {
//            std::string buffer;
//            ss >> buffer;
//            DSString word(buffer.c_str());
//            word.makeLower();
//            words.push_back(word);
//
//            std::vector<std::string> docs;
//            p.getInputDocs(docs, word);
//            sets.push_back(docs);
//        }
//
//        for(int i = 0; i < sets.size(); i++) {
//            std::cout << words[i] << ": ";
//            for(int j = 0; j < sets[i].size(); j++)
//                std::cout << sets[i][j].getID() << ", ";
//            std::cout << std::endl;
//        }
//        if(condition == "and")
//            processAND(words);
////        if(condition == "or")
//    }
//}

void Query::Search(DSString condition) {
    condition.makeLower();
    std::string temp;
    if(condition == "person" || condition == "org") {
    } else if(condition != "and" && condition != "or" && condition != "not") {
        singleWordSearch(condition);
        return;
    }

    std::getline(std::cin, temp);
    std::stringstream ss(temp);
    while(ss.good()) {
        ss >> temp;
        DSString word(temp.c_str());
        word.makeLower();
        if(word == "and")
            condition = "and";
        else if(word == "or")
            condition = "or";
        else if(word == "not")
            condition = "not";
        else if(word == "person")
            condition = "person";
        else if(word == "org")
            condition = "org";
        else {
            if(condition != "person" && condition != "org") {
                word.stem();
                allWords.push_back(word);
            }
            if(condition == "and")
                andWords.push_back(word);
            else if(condition == "or")
                orWords.push_back(word);
            else if(condition == "not")
                notWords.push_back(word);
            else if(condition == "person")
                personWords.push_back(word);
            else if(condition == "org")
                orgWords.push_back(word);
        }
    }
    if(andWords.empty())
        processOR();
    else
        processAND();
    processNOT();

    printResults();
}

void Query::processAND() {
    std::unordered_map<std::string, int> docIDs;
    for(auto& word : andWords) {
        std::vector<std::string> docs;
        p.getInputDocs(docs,word);

        for(auto& c : docs)
            if(!docIDs.count(c))
                docIDs.insert(std::pair<std::string, int>(c, 1));
            else
                docIDs.at(c)++;
    }
    for(auto& person : personWords) {
        std::vector<std::string> docs;
        p.getPersonDocs(docs, person);
        for(auto& c : docs)
            if(!docIDs.count(c))
                docIDs.insert(std::pair<std::string, int>(c, 1));
            else
                docIDs.at(c)++;
    }
    for(auto& org : orgWords) {
        std::vector<std::string> docs;
        p.getOrgDocs(docs, org);

        for(auto& c : docs)
            if(!docIDs.count(c))
                docIDs.insert(std::pair<std::string, int>(c, 1));
            else
                docIDs.at(c)++;
    }
    if(!docIDs.empty())
        for(auto& c : docIDs) {
            if (c.second == andWords.size() + personWords.size()) {
                std::string temp = c.first;
                p.getDocumento(temp).getwordFreq(allWords);
                result.insert(p.getDocumento(temp));
            }
        }
    std::cout << "Finished AND words" << std::endl;
}

void Query::processOR() {
    std::set<std::string> docIDs;
    for(auto& word : orWords) {
        std::vector<std::string> docs;
        p.getInputDocs(docs,word);

        for(auto& c : docs)
            if(!docIDs.count(c))
                docIDs.insert(c);
    }
    for(auto& person : personWords) {
        std::vector<std::string> docs;
        p.getPersonDocs(docs, person);

        for(auto& c : docs)
            if(!docIDs.count(c))
                docIDs.insert(c);
    }
    for(auto& org : orgWords) {
        std::vector<std::string> docs;
        p.getOrgDocs(docs, org);

        for(auto& c : docs)
            if(!docIDs.count(c))
                docIDs.insert(c);
    }
    if(!docIDs.empty())
        for(auto& c : docIDs) {
            p.getDocumento(c).getwordFreq(allWords);
            result.insert(p.getDocumento(c));
//            result.insert(std::pair<std::string, int>(c, p.getDocumento(c).getwordFreq(allWords)));
//            result.insert(c);
        }
    std::cout << "Finished OR word" << std::endl;
}

void Query::processNOT() {
    for(auto& word : notWords) {
        std::vector<std::string> docs;
        p.getInputDocs(docs, word);
        for(auto& c : docs) {
            if(result.count(p.getDocumento(c)))
                result.erase(p.getDocumento(c));
        }
    }
}

void Query::rankResults() {



}

void Query::printResults() {
    int count = 0;
    std::cout << "Results: " << std::endl;
    for(Documento c : result) {
        if(count > 14)
            break;
//        std::cout << "   " << c.getID() << ": " << c.getTitle() << std::endl;
        std::cout << "   " << c.getTitle() << "\n   [" << c.getID() << "] " << std::endl;
        std::cout << "      " << c.getFirst50() << "..." << std::endl << std::endl;
        count++;
    }
    std::cout << "   " << count << " documents returned" << std::endl;
    result.clear();
    andWords.clear();
    orWords.clear();
    notWords.clear();
    personWords.clear();
    orgWords.clear();
}


