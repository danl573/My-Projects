#ifndef INC_21F_FINAL_PROJ_TEMPLATE_PARSER_H
#define INC_21F_FINAL_PROJ_TEMPLATE_PARSER_H

#include <iostream>
#include <fstream>
#include <dirent.h>
#include <filesystem>
#include "Morpheme.h"
#include "Documento.h"
#include "DSAvl_Map.h"
#include "wordInfo.h"
#include "unordered_map"
#include "DSHashTable.h"
#include "map"

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "rapidjson/filereadstream.h"

namespace fs = std::filesystem;

class Parser {
private:

    DSString path = "/Users/danielryan/Desktop/CS2341/Sample_Data";
    int countDocs;
    int max;
    //char* filename = "/Users/danielryan/Desktop/CS2341/Sample_Data/blogs_0007314.json";
    DSAvl_Map<DSString, wordInfo> words;
    std::unordered_map<std::string, Documento> documents;
    std::set<std::string> stopWords;


    DSHashTable<std::string, std::vector<Documento>> persons;
    DSHashTable<std::string, std::vector<Documento>> orgs;

    static bool cmp(std::pair<DSString, wordInfo>& a, std::pair<DSString, wordInfo>& b);

public:
    Parser();
    void open_dir_using_filesystem(DSString p);
    void filesystem_folder(DSString& p);
    void openSingleFile(std::string& p);
    void Parse(DSString);
    void ParseFileStream(DSString);
    void ParseArray(rapidjson::Document& , DSString, const Documento& doc);

    void readStopWords();

    void getWordDocIDs(DSString w);
    void getTreeInfo();
    std::vector<std::string> searchWord(DSString& w);

    void getWordStats();
    void clearIndex();

    void getInputDocs(std::vector<std::string>&, DSString&);
    void getPersonDocs(std::vector<std::string>&, DSString&);
    void getOrgDocs(std::vector<std::string>&, DSString&);

    Documento& getDocumento(const std::string&);

    void makePersistenceFiles();
    void readPersistenceFiles();
};


#endif //INC_21F_FINAL_PROJ_TEMPLATE_PARSER_H
