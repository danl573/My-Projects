#ifndef INC_21F_FINAL_PROJ_TEMPLATE_DOCUMENTO_H
#define INC_21F_FINAL_PROJ_TEMPLATE_DOCUMENTO_H

#include <sstream>
#include <set>
#include <unordered_map>
#include "DSAvl_Map.h"
#include "Morpheme.h"
#include "DSHashTable.h"
#include "wordInfo.h"

class Documento {
private:
    DSString id;
    DSString title;
    int wordCount;
    std::string first50;
    std::string path;

    int freq;


    std::unordered_map<std::string, int> wordList; // word, frequency
//    DSHashTable<DSString, int> authors;
//    DSHashTable<DSString, int> orgs;

public:
    Documento();
    Documento(const DSString&, const DSString&);
    bool operator==(const Documento&);
    bool operator<(const Documento&) const;

    DSString getID();
    DSString getTitle();
    int getWordCount() const;
    std::string getPath();
    std::string getFirst50();

    void setID(const DSString&);
    void setTitle(const DSString&);
    void setWordCount(int);
    int getWordListSize();
    void setPath(const std::string&);
    void setFirst50(const std::string&);

    std::string printWordList();
    void addWord(const std::string&, int);

    void processBodyText(DSAvl_Map<DSString, wordInfo>&, DSString&, std::set<std::string>&);
    int getwordFreq(std::vector<DSString>& words);

};


#endif //INC_21F_FINAL_PROJ_TEMPLATE_DOCUMENTO_H
