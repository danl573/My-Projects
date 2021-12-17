//
// Created by Daniel Ryan on 9/21/21.
//

#include "Processor.h"

Processor::Processor() = default;

void Processor::ReadBook(DSString bookName) {
    //Read file
    std::ifstream bookFile;
    bookFile.open(bookName.c_str());

    //Creates buffer char to read each page
    char* bookLine = new char[10024];
    DSString line;
    DSString pageNum;

    //Reads the first < for consistency
    bookFile.getline(bookLine, 80, '<');

    //Loop until end of file
    while(!bookFile.eof()) {

        //Reads the page number and exits loop if page is -1
        bookFile.getline(bookLine, 80);
        line = bookLine;
        pageNum = line.substring(0, line.getLength() - 1);
        pageList.push_back(pageNum.convertInt());
        if(pageNum == "-1")
            break;
        else {

            //Reads until the next '<' and searches for keywords
            bookFile.getline(bookLine, 10024, '<');
            line = bookLine;
            line.makeLower();
            FindKeywords(line, pageNum.convertInt());
        }
    }

    //Sorts the words alphabetically
    keywords.sort();
    for(int i = 0; i < keywords.getSize(); i++) {
        std::cout << keywords[i] << ": ";
        keywords[i].printPageNumber();
    }
}

void Processor::FindKeywords(DSString page, int pageNum) {
    //Vector functioning as a stack
    DSVector<int> stack;

    //Loops through each char of the page
    for(int i = 0; i < page.getLength(); i++) {
        //Searches for '[' and saves index
        if(page[i] == '[')
            stack.push_back(i);
        //Searches for ']' and creates substring using both indexes
        else if(page[i] == ']') {
            IndexEntry temp(page.substring(stack.back(), i + 1));
            temp.makeLower();
            stack.pop_back();

            //Removes '[' ']' '\n'
            temp = temp.removeChars();

            //Updates keywords list and the word's page numbers
            if(keywords.find(temp) != -1)
                keywords[keywords.find(temp)].addPageNumber(pageNum);
            else {
                keywords.push_back(temp);
                keywords.back().addPageNumber(pageNum);
            }
        }
    }
}

void Processor::PrintIndex(DSString indexName) {
    //Open output file
    std::ofstream indexFile;
    indexFile.open(indexName.c_str());

    //Creates index header for each existing starting char
    char curr = ' ';
    for(int i = 0; i < keywords.getSize(); i++) {
        if(curr != keywords[i].getFirstChar()) {
            curr = keywords[i].getFirstChar();
            indexFile << "[" << curr << "]\n";
        }

        //prints keywords followed by page numbers
        indexFile << keywords[i] << ": ";
        keywords[i].printPageNumber(indexFile);
    }
}