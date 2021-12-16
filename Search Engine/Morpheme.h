#ifndef INC_21F_FINAL_PROJ_TEMPLATE_MORPHEME_H
#define INC_21F_FINAL_PROJ_TEMPLATE_MORPHEME_H

#include <vector>
#include <sstream>
#include <set>
#include "DSString.h"
#include "DSAvl_Map.h"
//#include "Documento.h"


class Morpheme : public DSString{
private:
    int wordFreq;
    double IDF;


public:
    Morpheme();
    Morpheme(const char*);
    Morpheme(const DSString&);
    void calculateIDF(int, int);
    bool operator<(const Morpheme&);
    bool operator==(const Morpheme&);

//    void ParseStem(const char *delim, DSAvl_Map<DSString, std::vector<Documento>>&, const Documento&);
//    void ParseStem(const char& delim, DSAvl_Map<DSString, std::vector<Documento>>&, const Documento&);
//    void ParseSS(DSAvl_Map<DSString, std::vector<Documento>>&, const Documento&);
};


#endif //INC_21F_FINAL_PROJ_TEMPLATE_MORPHEME_H
