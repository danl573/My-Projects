//
// Created by Daniel Ryan on 9/21/21.
//

#ifndef INC_21F_PA02_PROCESSOR_H
#define INC_21F_PA02_PROCESSOR_H

#include "IndexEntry.h"
#include <fstream>

class Processor {
private:
    DSVector<IndexEntry> keywords;
    DSVector<int> pageList;

    /**
     * Uses a DSVector as a stack to find brackets and extract
     * the key words inside them to store the words and the pages
     * they appear on
     * @param page the actual page text being read
     * @param pageNum the number of the page being read
     */
    void FindKeywords(DSString page, int pageNum);
public:
    Processor();

    /**
     * Reads the book page by page and stops when page is -1,
     * calls FindKeywords() after reading page
     * @param bookName Name of the book text file
     */
    void ReadBook(DSString bookName);

    /**
     * Prints the index of the book onto an output file,
     * sorted alphabetically
     * @param indexName Name of the output text file
     */
    void PrintIndex(DSString indexName);

};


#endif //INC_21F_PA02_PROCESSOR_H
