//
// Created by Daniel Ryan on 11/16/21.
//

#include "Parser.h"

Parser::Parser() {
    countDocs = 0;
    readStopWords();
}

void Parser::open_dir_using_filesystem(DSString dir) {
    std::cout << "Enter document amount: " << std::endl;
    std::cin >> max;
    countDocs = 0;
    std::cout << "\n\n";
    if(!fs::directory_iterator(dir.c_str())->is_directory())
        filesystem_folder(dir);
    else {
        for(const auto& folder : fs::directory_iterator(dir.c_str())) {
            if (folder.is_directory()) {
                DSString p = folder.path().c_str();
                filesystem_folder(p);
            }
//            if (countDocs >= max)
//                break;
        }
    }
}

void Parser::filesystem_folder(DSString& p) {

    for(const auto &entry: fs::directory_iterator(p.c_str())) {

        ++countDocs;
        if (countDocs % 100 == 0) {
            std::cout << ".";
            if (countDocs % 1000 == 0)
                std::cout << countDocs << std::endl;
            std::cout.flush();
        }
        DSString name = entry.path().c_str();


        if(name.getLastChar() == 'n')
            ParseFileStream(name);
//        if(count == 10000) break;
        if (countDocs >= max)
            break;
    }
}

void Parser::openSingleFile(std::string& p) {

    std::ifstream ifs(documents[p].getPath().c_str());
    std::cout << documents[p].getPath() << std::endl;
    if(ifs.is_open()) {
        rapidjson::IStreamWrapper isw(ifs);
        rapidjson::Document d;
        d.ParseStream(isw);
        std::cout << d["title"].GetString() << std::endl;
        std::cout << "   " << d["text"].GetString() << std::endl;
    }
//    fclose(fp);
    ifs.close();

}

void Parser::ParseFileStream(DSString filename) {
    FILE* fp = fopen(filename.c_str(), "r");

    if(fp != nullptr) {
        char readBuffer[65536];
        rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        rapidjson::Document d;
        d.ParseStream(is);
        DSString paperID = d["uuid"].GetString();
        if(paperID == "2dbe269257c2599401b6c1af747632a92c01c0e7")
            std::cout << paperID << std::endl;
        DSString titleName = d["title"].GetString();
        Documento doc(paperID, titleName);
        doc.setPath(std::string(filename.c_str()));
        DSString body_text = d["text"].GetString();
        ParseArray(d, "persons", doc);
        ParseArray(d, "organizations", doc);
        doc.processBodyText(words, body_text, stopWords);
        documents.insert(std::pair<std::string, Documento>(std::string(paperID.c_str()), doc));
        fclose(fp);
    } else
        std::cout << fp << std::endl;

}

void Parser::ParseArray(rapidjson::Document& document, DSString search, const Documento& doc) {
    int counter = 1;
    const rapidjson::Value& attributes = document["entities"][search.c_str()];
    for(rapidjson::Value::ConstValueIterator itr = attributes.Begin(); itr != attributes.End(); ++itr) {
        const rapidjson::Value& attribute = *itr;
        rapidjson::Value::ConstMemberIterator itr2 = attribute.MemberBegin();
            if(itr2->name.IsString() && itr2->value.IsString()) {
                if(strlen(itr2->value.GetString()) > 0) {
                    if(search == "persons") {
                        std::string name = itr2->value.GetString();
                        std::size_t index = name.find_last_of(' ');
                        if(index != std::string::npos)
                            name = name.substr(index+1);
                        persons.insert(name).push_back(doc);
                    } if(search == "organizations")
                        orgs.insert(itr2->value.GetString()).push_back(doc);
                }
            }
        }
        counter++;
    //}
}

std::vector<std::string> Parser::searchWord(DSString& w) {
    try {
        return words.getValue(w).wordDocs;
    } catch (std::runtime_error& e) {
        return {};
    }
}

void Parser::getTreeInfo() {
    std::cout << "\nNum Nodes: " << words.get_num_nodes() << std::endl;
    std::cout << "Num Calls to Insert: " << words.get_num_insert_calls() << std::endl;
    words.printTree();
}

void Parser::getWordDocIDs(DSString w) {
    std::cout << std::endl;
    w.makeLower();
    w.stem();
    int count = 0;
    std::string temp;

    try {
        for(auto& c : words.getValue(w).wordDocs) {
            if (c != temp) {
                std::cout << c << std::endl;
                count++;
            }
            temp = c;
        }
        std::cout << count << " Documents Found" << std::endl;
    } catch (std::runtime_error& e) {
        std::cout << "No Documents Found" << std::endl;
    }
}

void Parser::getInputDocs(std::vector<std::string> &set, DSString& word) {
    std::string temp;

    try {
        for(auto& c : words.getValue(word).wordDocs) {
            if(c != temp) {
                set.push_back(c);
            }
            temp = c;
        }
    } catch(std::runtime_error& e) {
    }
}

void Parser::getPersonDocs(std::vector<std::string>& set, DSString& person) {
    DSString temp;
    try{
        for(auto& c : persons.get(std::string(person.c_str()))) {
            if(c.getID() != temp) {
                set.emplace_back(c.getID().c_str());
            }
            temp = c.getID();
        }
    } catch(std::runtime_error& e){
    }

}

void Parser::getOrgDocs(std::vector<std::string>& set, DSString& org) {
    DSString temp;
    try{
        for(auto& c : orgs.get(std::string(org.c_str()))) {
            if(c.getID() != temp) {
                set.emplace_back(c.getID().c_str());
            }
            temp = c.getID();
        }
    } catch(std::runtime_error& e){
    }
}

Documento& Parser::getDocumento(const std::string& docID) {
    return documents.at(docID);
}


void Parser::getWordStats() {
    std::vector<std::pair<DSString, wordInfo>> ranked;
    words.copyToVector(ranked);
    std::sort(ranked.begin(), ranked.end(), cmp);

    int avgWords = 0;
    if(documents.size() != 0) {
        for (auto &c: documents) {
            avgWords += c.second.getWordCount();
        }
        avgWords /= documents.size();
    }
    std::cout << "Articles read:                 " << documents.size() << std::endl;
    std::cout << "Words indexed:                 " << words.get_num_nodes() << std::endl;
    std::cout << "Avg words indexed per article: " << avgWords << std::endl;
    std::cout << "Persons read:                  " << persons.size() << std::endl;
    std::cout << "Orgs read:                     " << orgs.size() << std::endl;

    std::cout << "Top 50 most frequent words: " << std::endl;
    int count = (ranked.size() > 50) ? 50 : ranked.size();
    for(int i = 0; i < count; i++) {
        std::cout << ranked[i].first;
        if(((i+1) % 10) == 0)
            std::cout << std::endl;
        else
            std::cout << ", ";
    }
}

bool Parser::cmp(std::pair<DSString, wordInfo>& a, std::pair<DSString, wordInfo>& b) {
    return a.second.wordFreq > b.second.wordFreq;
}

void Parser::makePersistenceFiles() {
    std::ofstream docFile("/Users/danielryan/Desktop/CS2341/Persistence-Index/documentsIndex.txt");
    if(!docFile.is_open()) {
        std::cout << "Error opening doc file" << std::endl;
        return;
    }
    docFile.clear();
    docFile << documents.size() << std::endl;
    for(auto& doc : documents) {
        docFile << doc.second.getID() << std::endl
                << doc.second.getTitle() << std::endl
                << doc.second.getFirst50() << std::endl
                << doc.second.getPath() << std::endl
                << doc.second.getWordCount() << std::endl
                << doc.second.printWordList() << std::endl;

    }
    docFile.close();

    std::ofstream wordFile("/Users/danielryan/Desktop/CS2341/Persistence-Index/wordIndex.txt");
    if(!wordFile.is_open()) {
        std::cout << "Error opening word file" << std::endl;
        return;
    }
    wordFile.clear();
    wordFile << words.get_num_nodes() << std::endl;
    std::vector<std::pair<DSString, wordInfo>> tempList;
    words.copyToVector(tempList);
    for(auto& word : tempList) {
        wordFile << word.first << " " << word.second.wordFreq << " " << word.second.wordDocs.size() << "|";
        for(auto& d : word.second.wordDocs)
            wordFile << " " << d;
        wordFile << std::endl;
    }
    wordFile.close();

    std::ofstream personFile("/Users/danielryan/Desktop/CS2341/Persistence-Index/personIndex.txt");
    if(!personFile.is_open()) {
        std::cout << "Error opening word file" << std::endl;
        return;
    }
    personFile.clear();
    personFile << persons.size() << std::endl;
    std::vector<std::pair<std::string, std::vector<Documento>>> autList;
    persons.copyToVector(autList);
    for(auto& aut : autList) {
        personFile << aut.first << " ";
        personFile << aut.second.size() << " ";
        for(auto& a : aut.second)
            personFile  << a.getID() << " ";
        personFile << std::endl;
    }
    personFile.close();

    std::ofstream orgFile("/Users/danielryan/Desktop/CS2341/Persistence-Index/orgIndex.txt");
    if(!orgFile.is_open()) {
        std::cout << "Error opening word file" << std::endl;
        return;
    }
    orgFile.clear();
    orgFile << orgs.size() << std::endl;
    std::vector<std::pair<std::string, std::vector<Documento>>> orgList;
    orgs.copyToVector(orgList);
    for(auto& org : orgList) {
        orgFile << org.first << "|";
        orgFile << org.second.size() << "|";
        for(auto& o : org.second)
            orgFile << o.getID() << " ";
        orgFile << std::endl;
    }
    orgFile.close();
}

void Parser::readPersistenceFiles() {
    std::ifstream docFile("/Users/danielryan/Desktop/CS2341/Persistence-Index/documentsIndex.txt");
    if(!docFile.is_open()) {
        std::cout << "Error opening doc file" << std::endl;
        return;
    }
    char buffer[10000];
    int size = 0;
    docFile.getline(buffer, 1000);
    std::stringstream s(buffer);
    s >> size;
    for(int i = 0; i < size; i++) {
        Documento doc;
        docFile.getline(buffer, 1000);
        doc.setID(DSString(buffer));
        docFile.getline(buffer, 1000);
        doc.setTitle(DSString(buffer));
        docFile.getline(buffer, 1000);
        doc.setFirst50(std::string(buffer));
        docFile.getline(buffer, 1000);
        doc.setPath(std::string(buffer));
        docFile.getline(buffer, 1000);
        std::stringstream num(buffer);
        int x = 0;
        num >> x;
        doc.setWordCount(x);

        std::string word;
        docFile.getline(buffer, 10000);
        std::stringstream line(buffer);
        for(int j = 0; j < doc.getWordCount(); j++) {
            line >> word;
            line >> x;
            doc.addWord(word, x);
        }
        documents.insert(std::pair<std::string, Documento>(std::string(doc.getID().c_str()), doc));

    }
    std::cout  << "Documents: " << documents.size() << std::endl;
    docFile.close();

    std::ifstream wordFile("/Users/danielryan/Desktop/CS2341/Persistence-Index/wordIndex.txt");
    if(!wordFile.is_open()) {
        std::cout << "Error opening word file" << std::endl;
        return;
    }
    wordFile >> size;
    wordFile.getline(buffer, 1000);
    for(int i = 0; i < size; i++) {
        wordFile.getline(buffer, 1000, ' ');
        std::string word = buffer;
        wordFile.getline(buffer, 1000, '|');
        std::stringstream line(buffer);
        int num = 0;
        int freq = 0;
        line >> freq;
        line >> num;
        wordInfo temp;
        temp.wordFreq = freq;
        wordFile.getline(buffer, 1000, ' ');
        for(int j = 0; j < num; j++) {

            if(j+1 == num)
                wordFile.getline(buffer, 1000);
            else
                wordFile.getline(buffer, 1000, ' ');
            std::string id = buffer;
            temp.wordDocs.push_back(id);
        }

        words.insert(DSString(word.c_str())).setInfo(temp);
    }
    wordFile.close();
    std::cout  << "Words:     " << words.get_num_nodes() << std::endl;


    std::ifstream personFile("/Users/danielryan/Desktop/CS2341/Persistence-Index/personIndex.txt");
    if(!personFile.is_open()) {
        std::cout << "Error opening person file" << std::endl;
        return;
    }
    personFile >> size;
    personFile.getline(buffer, 1000);
    for(int i = 0; i < size; i++) {
        personFile.getline(buffer, 1000, ' ');
        std::string name = buffer;
        personFile.getline(buffer, 1000,' ');
        std::stringstream line(buffer);
        int num = 0;
        line >> num;
        persons.insert(name);
        for(int j = 0; j < num; j++) {
            personFile.getline(buffer, 1000, ' ');
            std::string id = buffer;
            persons.insert(name).push_back(documents.at(id));
            std::cout << id<< std::endl;
        }
        personFile.getline(buffer, 1000);
    }
    personFile.close();
    std::cout  << "Persons:   " << persons.size() << std::endl;

    std::ifstream orgFile("/Users/danielryan/Desktop/CS2341/Persistence-Index/orgIndex.txt");
    if(!orgFile.is_open()) {
        std::cout << "Error opening org file" << std::endl;
        return;
    }
    orgFile >> size;
    orgFile.getline(buffer, 1000);
    for(int i = 0; i < size; i++) {
        orgFile.getline(buffer, 1000, '|');
        std::string name = buffer;
        orgFile.getline(buffer, 1000, '|');
        std::stringstream line(buffer);
        int num = 0;
        line >> num;
        orgs.insert(name);
        for(int j = 0; j < num; j++) {
            orgFile.getline(buffer, 1000, ' ');
            std::string id = buffer;
            orgs.insert(name).push_back(documents.at(id));
        }
        orgFile.getline(buffer, 1000);
    }
    orgFile.close();
    std::cout  << "Orgs:      " << orgs.size() << std::endl;
}

void Parser::clearIndex() {
    words.clear();
    documents.clear();
    persons.clear();
    orgs.clear();

}

void Parser::readStopWords() {
    stopWords.clear();
    std::ifstream ifs("/Users/danielryan/Desktop/CS2341/21f-srch-ngn-momo-hirai-fanboy/stopWords.txt");
    if(!ifs.is_open())
        return;
    char buffer[100];
    while(!ifs.eof()) {
        ifs.getline(buffer, 100);
        std::string stop = buffer;
        stopWords.insert(stop);
    }
}
