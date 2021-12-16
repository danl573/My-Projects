#include <iostream>
#include "catch_setup.h"
#include "Parser.h"
#include "Query.h"


int main(int argc, char** argv) {
//    if(argc == 1) {
//        runCatchTests();
//    } else {
//        Parser p;
//        p.open_dir_using_dirent();
//        p.open_dir_using_filesystem(DSString(argv[1]));
//        p.getTreeInfo();
        Query q;
        q.SearchWord(DSString(argv[1]));

//        p.getTreeInfo();

//        if(argc == 3)
//            p.getWordDocIDs(DSString(argv[2]));
//    }
    return 0;
}
