//
// Created by Daniel Ryan on 9/25/21.
//

#ifndef INC_21F_PA02_INDEXENTRY_H
#define INC_21F_PA02_INDEXENTRY_H


#include "DSString.h"
#include "DSVector.h"

class IndexEntry : public DSString {
private:
    //list of page numbers for keyword
    DSVector<int> pageNums;

public:
    /**
     *  Constructors
     */
    IndexEntry();
    IndexEntry(const char*);
    IndexEntry(const DSString&);

    /**
     * Adds a page number into vector
     * @param page number to be added
     */
    void addPageNumber(int page);

    /**
     *  Prints comma-separated page numbers onto a given stream
     * @param os stream to be printed to
     * @return the printed stream
     */
    std::ostream& printPageNumber(std::ostream& os = std::cout);

    /**
     *  Returns the number of page numbers stored in vector
     * @return size of page number vector
     */
    int getPageNumberSize();

    /**
     *  Returns a given page number from index
     * @param index location of page number in vector
     * @return page number at index
     */
    int getPageNumber(int index);

    /**
     *  Removes '[' ']' '\n' chars from the string
     * @return updated string
     */
    DSString removeChars();

};


#endif //INC_21F_PA02_INDEXENTRY_H
