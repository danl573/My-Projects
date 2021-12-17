//
// Created by Daniel Ryan on 9/25/21.
//

#include "IndexEntry.h"

IndexEntry::IndexEntry() : DSString() {}

IndexEntry::IndexEntry(const char* chr) : DSString(chr) {}

IndexEntry::IndexEntry(const DSString& word) : DSString(word) {}

void IndexEntry::addPageNumber(int page) {
    //checks to see if page number already exists in vector
    bool temp = false;
    for(int i = 0; i < pageNums.getSize(); i++)
        if (pageNums[i] == page)
            temp = true;

    if(!temp)
        pageNums.push_back(page);
}

std::ostream& IndexEntry::printPageNumber(std::ostream& os) {
    for(int i = 0; i < pageNums.getSize()-1; i++)
        os << pageNums[i] << ", ";
    os << pageNums.back() << std::endl;
    return os;
}

int IndexEntry::getPageNumberSize() {
    return pageNums.getSize();
}

int IndexEntry::getPageNumber(int index) {
    return pageNums[index];
}

DSString IndexEntry::removeChars() {
    //copies chars, skipping unnecessary chars
    char* newStr = new char[this->getLength() + 1];
    int len = 0;
    for(int i = 0, j = 0; i < this->getLength() + 1; i++, j++) {
        if(this->operator[](i) != '[' && this->operator[](i) != ']' && this->operator[](i) != '\n') {
            newStr[j] = this->operator[](i);
            len++;
        } else
            j--;
    }
    newStr[len] = '\0';

    return DSString(newStr);
}





