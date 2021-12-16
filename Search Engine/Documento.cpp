//
// Created by Daniel Ryan on 11/16/21.
//

#include "Documento.h"

Documento::Documento() {
    id = "";
    title = "";
    wordCount = 0;
    freq = 0;
    first50 = "";
}

Documento::Documento(const DSString& uuid, const DSString& t) {
    id = uuid;
    title = t;
    wordCount = 0;
}

DSString Documento::getID() {
    return id;
}

DSString Documento::getTitle() {
    return title;
}

int Documento::getWordCount() const {
    return wordCount;
}

std::string Documento::getPath() {
    return path;
}

std::string Documento::getFirst50() {
    return first50;
}

void Documento::setID(const DSString& i) {
    id = i;
}

void Documento::setTitle(const DSString& t) {
    title = t;
}

void Documento::setWordCount(int w) {
    wordCount = w;
}

void Documento::setPath(const std::string& p) {
    path = p;
}

void Documento::setFirst50(const std::string& f) {
    first50 = f;
}

bool Documento::operator==(const Documento& that) {
    return this->id == that.id;
}

bool Documento::operator<(const Documento& that) const {
    if(that.freq == this->freq)
        return this->title < that.title;
    else
        return this->freq < that.freq;
}

void Documento::processBodyText(DSAvl_Map<DSString, wordInfo>& words, DSString& text, std::set<std::string>& stopWords) {
    std::unordered_map<std::string, int> tempList;
    DSString temp;
    int count = 0;
    std::string b;
    std::stringstream ss(text.c_str());
    while(ss.good()) {
        ss >> b;
        if(count < 30)
            first50 = first50 + b + " ";
        count++;
        if (b.length() < 3 || b.length() > 20 || !isalpha(b.at(0)))
            continue;

//        tempList.insert(std::pair<std::string, int>(b, 1));
        temp = b.c_str();
        temp.stem();
        temp.makeLower();
        if(stopWords.count(temp.c_str()))
            continue;
        if(tempList.count(temp.c_str())){
            tempList.at(temp.c_str())++;
            words.getValue(temp).wordFreq++;
            continue;
        }
        words.insert(temp).wordDocs.emplace_back(id.c_str());
        words.getValue(temp).wordFreq++;
        tempList.insert(std::pair<std::string, int>(std::string(temp.c_str()), 1));
    }
    wordList = tempList;
    wordCount = wordList.size();
}

int Documento::getWordListSize() {
    return wordList.size();
}

int Documento::getwordFreq(std::vector<DSString> &words) {
    freq = 0;
    for(auto& word : words) {
        if(wordList.count(word.c_str()))
            freq += wordList.find(word.c_str())->second;
    }
    return freq;
}

std::string Documento::printWordList() {
    std::string printList;
    for(auto& c : wordList) {
        printList += c.first;
        printList += " ";
        printList += std::to_string(c.second);
        printList += " ";
    }

    return printList;
}

void Documento::addWord(const std::string& word, int f) {
    wordList.insert(std::pair<std::string, int>(word, f));
}
