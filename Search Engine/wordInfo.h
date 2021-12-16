#ifndef INC_21F_FINAL_PROJ_TEMPLATE_WORDINFO_H
#define INC_21F_FINAL_PROJ_TEMPLATE_WORDINFO_H

#include <vector>

class wordInfo {
public:
    std::vector<std::string> wordDocs;
    int wordFreq = 0;
    void setInfo(const wordInfo& wi) {
        this->wordDocs = wi.wordDocs;
        this->wordFreq = wi.wordFreq;
    }
};

#endif //INC_21F_FINAL_PROJ_TEMPLATE_WORDINFO_H
