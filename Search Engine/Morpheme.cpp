//
// Created by Daniel Ryan on 11/16/21.
//

#include "Morpheme.h"


Morpheme::Morpheme() : DSString() {
    wordFreq = 0;
}

Morpheme::Morpheme(const char* s) : DSString(s) {
    wordFreq = 0;
}

Morpheme::Morpheme(const DSString& d) :DSString(d) {
    wordFreq = 0;
}

void Morpheme::calculateIDF(int totalDocs, int wordDocs) {
    IDF = log10(totalDocs/wordDocs);
}

bool Morpheme::operator<(const Morpheme& that) {
    return this->wordFreq < that.wordFreq;
}

bool Morpheme::operator==(const Morpheme& that) {
    return this->data == that.data;
}
