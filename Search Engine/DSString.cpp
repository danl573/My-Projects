#include "DSString.h"

DSString::DSString() {
    data = nullptr;
}

DSString::DSString(const char* str) {
    if(str != nullptr) {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
        data[strlen(str)] = '\0';
    } else {
        data = new char[strlen("") + 1];
        strcpy(data, str);
        data[strlen(str)] = '\0';
    }
}

DSString::DSString(const DSString& str) {
    data = new char[strlen(str.data) + 1];
    strcpy(data, str.data);
}

DSString::~DSString() {
    delete[] data;
}

DSString& DSString::operator= (const char* str) {
    delete[] data;
    data = new char[strlen(str) + 1];
    strcpy(data, str);
    return *this;
}

DSString& DSString::operator= (const DSString& str) {
    delete[] data;
    data = new char[strlen(str.data) + 1];
    strcpy(data, str.data);
    return *this;
}

DSString DSString::operator+ (const DSString& str) {
    if(data != nullptr && str.data != nullptr) {
        DSString temp;
        temp.data = new char[strlen(data) + strlen(str.data) + 1];
        strcpy(temp.data, data);
        strcat(temp.data, str.data);
        return temp;
    } else if(data != nullptr) {
        DSString temp(data);
        return temp;
    }
    return DSString("");
}

bool DSString::operator== (const char* str) const {
    if(data != nullptr && str != nullptr)
        return (strcmp(data, str) == 0);
    return false;
}

bool DSString::operator== (const DSString& str) const {
    if(data != nullptr && str.data != nullptr)
        return (strcmp(data, str.data) == 0);
    return false;
}

bool DSString::operator!= (const char* str) const {
    if(data != nullptr && str != nullptr)
        return (strcmp(data, str) != 0);
    return false;
}

bool DSString::operator!= (const DSString& str) const {
    if(data != nullptr && str.data != nullptr)
        return (strcmp(data, str.data) != 0);
    return false;
}

bool DSString::operator> (const char* str) const {
    if(data != nullptr && str != nullptr)
        return (strcmp(data, str) > 0);
    return false;
}

bool DSString::operator> (const DSString& str) const {
    if(data != nullptr && str.data != nullptr)
        return (strcmp(data, str.data) > 0);
    return false;
}

bool DSString::operator>= (const char* str) const {
    if(data != nullptr && str != nullptr)
        return (strcmp(data, str) >= 0);
    return false;
}

bool DSString::operator>= (const DSString& str) const {
    if(data != nullptr && str.data != nullptr)
        return (strcmp(data, str.data) >= 0);
    return false;
}

bool DSString::operator< (const char* str) const {
    if(data != nullptr && str != nullptr)
        return (strcmp(data, str) < 0);
    return false;
}

bool DSString::operator< (const DSString& str) const {
    if(data != nullptr && str.data != nullptr)
        return (strcmp(data, str.data) < 0);
    return false;
}

bool DSString::operator<= (const char* str) const {
    if(data != nullptr && str != nullptr)
        return (strcmp(data, str) <= 0);
    return false;
}

bool DSString::operator<= (const DSString& str) const {
    if(data != nullptr && str.data != nullptr)
        return (strcmp(data, str.data) <= 0);
    return false;
}

char& DSString::operator[] (const int index) {
    if(data == nullptr || getLength() == 0) {
        //throw out_of_range exception
    }
    if(index > 0 && index < strlen(data))
        return data[index];
    return data[0]; //or throw out_of_range exception
}

int DSString::getLength() {
    if(data != nullptr) {
        return strlen(data);
    }
    return 0;
}


DSString DSString::substring(int start, int end) {
    //end = -1 if substring until end
    if(end == -1)
        end = strlen(data);

    if(start > end || start < 0 || end > strlen(data)+1)
        return data;
    else if(start == end) {
        DSString temp = "";
        return temp;
    }

    int length = end - start;
    char* newStr = new char[length + 1];
    for(int i = 0; i < length; i++) {
        newStr[i] = data[i+start];
    }
    newStr[length] = '\0';
    return DSString(newStr);
}

char* DSString::c_str() {
    return data;
}

std::ostream &operator<<(std::ostream& os, const DSString& str) {
    os << str.data;
    return os;
}

void DSString::makeLower() {
    for(int i = 0; i < getLength(); i++) {
        data[i] = tolower(data[i]);
    }
}

char DSString::getFirstChar() {
    if(getLength() == 0)
        return ' ';
    return data[0];
}

char DSString::getLastChar() {
    if(getLength() == 0)
        return ' ';
    return data[getLength()-1];
}

std::vector<DSString> DSString::stringParser(char delim, int min, int max) {
    std::vector<DSString> words;
    int i, j;
    for(i = 0, j = 0; i < getLength(); i++) {
        if(data[i] == delim) {
            if(i > j && (i-j) > min && (i-j) < max)
                words.push_back(substring(j, i));
            j = i + 1;
        }
    }
    if(j != getLength() && (i-j) > min && (i-j) < max)
        words.push_back(substring(j, -1));
    return words;
}

std::vector<DSString> DSString::stringParser(const char* delim, int min, int max) {
    std::vector<DSString> words;
    bool ifDelim = false;
    int i, j;
    for(i = 0, j = 0; i < getLength(); i++) {
        for(int k = 0; k < strlen(delim); k++){
            if(data[i] == delim[k])
                ifDelim = true;
        }
        if(ifDelim) {
            if(i > j && (i-j) > min && (i-j) < max) {
                words.push_back(substring(j, i));
            }
            j = i + 1;
            ifDelim = false;
        }
    }
    if(j != getLength() && (i-j) > min && (i-j) < max)
        words.push_back(substring(j, -1));
    return words;
}

void DSString::stem() {
    stemming::english_stem<> StemEnglish;
    auto* UnicodeTextBuffer = new wchar_t[getLength()+1];
    std::wmemset(UnicodeTextBuffer, 0, getLength()+1);
    std::mbstowcs(UnicodeTextBuffer, data, getLength());
    std::wstring word(UnicodeTextBuffer);
    StemEnglish(word);
    delete[] UnicodeTextBuffer;

    delete[] data;
    data = new char[word.size() + 1];
    memset(data, 0, word.size() + 1);
    wcstombs(data, word.c_str(), word.size());

}

//std::vector<DSString> DSString::ParseStem(const char *delim) {
//    std::vector<DSString> words;
//    DSString temp;
//    bool ifDelim = false;
//    int i, j;
//    for(i = 0, j = 0; i < getLength(); i++) {
//        for(int k = 0; k < strlen(delim); k++){
//            if(data[i] == delim[k])
//                ifDelim = true;
//        }
//        if(ifDelim) {
//            temp = substring(j,i);
//            temp.stem();
//            words.push_back(temp);
//            j = i + 1;
//            ifDelim = false;
//        }
//    }
//    temp = substring(j, -1);
//    temp.stem();
//    words.push_back(temp);
//    return words;
//}
