#ifndef INC_21F_FINAL_PROJ_TEMPLATE_QUERY_H
#define INC_21F_FINAL_PROJ_TEMPLATE_QUERY_H

#include "Parser.h"


class Query {
private:
    Parser p;
//    std::vector<std::string> result;
//    std::set<std::string> result;
    std::set<Documento> result;
//    std::unordered_map<std::string, int> result;

    std::vector<DSString> allWords;
    std::vector<DSString> andWords;
    std::vector<DSString> orWords;
    std::vector<DSString> notWords;
    std::vector<DSString> personWords;
    std::vector<DSString> orgWords;
//    std::unordered_map<std::string, Documento> result;
public:
    void SearchWord(const DSString&);
    void IndexingOptions(const DSString&);
    void singleWordSearch(DSString);
//    void multipleWordSearch(DSString);
    void Search(DSString);

    void processAND();
    void processOR();
    void processNOT();

    void printStatistics();

    void rankResults();
    void printResults();
};


#endif //INC_21F_FINAL_PROJ_TEMPLATE_QUERY_H
