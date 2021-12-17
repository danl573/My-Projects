//
// Created by mark on 6/2/2021.
//

#include "DWString.h"

DWString::DWString() {
    data = nullptr;
}

DWString::DWString(const wchar_t* str) {
    if(str != nullptr) {
        data = new wchar_t[wcslen(str) + 1];
        wcscpy(data, str);
        data[wcslen(str)] = '\0';
    } else {
        data = new wchar_t[strlen("") + 1];
        wcscpy(data, str);
        data[wcslen(str)] = '\0';
    }
}

DWString::DWString(const DWString& str) {
    data = new wchar_t[wcslen(str.data) + 1];
    wcscpy(data, str.data);
}

DWString::~DWString() {
    delete[] data;
}

DWString& DWString::operator= (const wchar_t* str) {
    delete[] data;
    data = new wchar_t[wcslen(str) + 1];
    wcscpy(data, str);
    return *this;
}

DWString& DWString::operator= (const DWString& str) {
    delete[] data;
    data = new wchar_t[wcslen(str.data) + 1];
    wcscpy(data, str.data);
    return *this;
}

DWString DWString::operator+ (const DWString& str) {
    if(data != nullptr && str.data != nullptr) {
        DWString temp;
        temp.data = new wchar_t[wcslen(data) + wcslen(str.data) + 1];
        wcscpy(temp.data, data);
        wcscat(temp.data, str.data);
        return temp;
    } else if(data != nullptr) {
        DWString temp(data);
        return temp;
    }
    return DWString(L"");
}

bool DWString::operator== (const wchar_t* str) const {
    if(data != nullptr && str != nullptr)
        return (wcscmp(data, str) == 0);
    return false;
}

bool DWString::operator== (const DWString& str) const {
    if(data != nullptr && str.data != nullptr)
        return (wcscmp(data, str.data) == 0);
    return false;
}

bool DWString::operator!= (const wchar_t* str) const {
    if(data != nullptr && str != nullptr)
        return (wcscmp(data, str) != 0);
    return false;
}

bool DWString::operator!= (const DWString& str) const {
    if(data != nullptr && str.data != nullptr)
        return (wcscmp(data, str.data) != 0);
    return false;
}

bool DWString::operator> (const wchar_t* str) const {
    if(data != nullptr && str != nullptr)
        return (wcscmp(data, str) > 0);
    return false;
}

bool DWString::operator> (const DWString& str) const {
    if(data != nullptr && str.data != nullptr)
        return (wcscmp(data, str.data) > 0);
    return false;
}

bool DWString::operator>= (const wchar_t* str) const {
    if(data != nullptr && str != nullptr)
        return (wcscmp(data, str) >= 0);
    return false;
}

bool DWString::operator>= (const DWString& str) const {
    if(data != nullptr && str.data != nullptr)
        return (wcscmp(data, str.data) >= 0);
    return false;
}

bool DWString::operator< (const wchar_t* str) const {
    if(data != nullptr && str != nullptr)
        return (wcscmp(data, str) < 0);
    return false;
}

bool DWString::operator< (const DWString& str) const {
    if(data != nullptr && str.data != nullptr)
        return (wcscmp(data, str.data) < 0);
    return false;
}

bool DWString::operator<= (const wchar_t* str) const {
    if(data != nullptr && str != nullptr)
        return (wcscmp(data, str) <= 0);
    return false;
}

bool DWString::operator<= (const DWString& str) const {
    if(data != nullptr && str.data != nullptr)
        return (wcscmp(data, str.data) <= 0);
    return false;
}

wchar_t& DWString::operator[] (const int index) {
    if(data == nullptr || getLength() == 0) {
        //throw out_of_range exception
    }
    if(index > 0 && index < wcslen(data))
        return data[index];
    return data[0]; //or throw out_of_range exception
}

int DWString::getLength() {
    if(data != nullptr) {
        return wcslen(data);
    }
    return 0;
}


DWString DWString::substring(int start, int end) {
    //end = -1 if substring until end
    if(end == -1)
        end = wcslen(data);

    if(start > end || start < 0 || end > wcslen(data)+1)
        return *this;
    else if(start == end) {
        DWString temp (L"");
        return temp;
    }

    int length = end - start;
    auto* newStr = new wchar_t[length + 1];
    for(int i = 0; i < length; i++) {
        newStr[i] = data[i+start];
    }
    newStr[length] = '\0';
    return DWString(newStr);
}

wchar_t* DWString::c_str() {
    return data;
}

std::ostream &operator<<(std::ostream& os, const DWString& str) {
    os << str.data;
    return os;
}

void DWString::makeLower() {
    for(int i = 0; i < getLength(); i++) {
        data[i] = tolower(data[i]);
    }
}

wchar_t DWString::getFirstChar() {
    if(getLength() == 0)
        return ' ';
    return data[0];
}

std::vector<DWString> DWString::stringParser(wchar_t delim, int min, int max) {
    std::vector<DWString> words;
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

std::vector<DWString> DWString::stringParser(const wchar_t* delim, int min, int max) {
    std::vector<DWString> words;
    bool ifDelim = false;
    int i, j;
    for(i = 0, j = 0; i < getLength(); i++) {
        for(int k = 0; k < wcslen(delim); k++){
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