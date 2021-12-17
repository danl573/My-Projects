//
// Created by Daniel Ryan on 9/8/21.
//

#ifndef PA01_SENTIMENT_DWSTRING_H
#define PA01_SENTIMENT_DWSTRING_H

#include <iostream>
#include <cstring>
#include <wchar.h>
#include <climits>
#include <vector>

class DWString {
    /**
        *  You will need to add some private data members here.
        *  This is up to your discretion.  However, we **strongly**
        *  encourage you to implement your string class as a wrapper
        *  for typical null-terminated c-strings.  In doing this, you
        *  may use c-sting functions in the methods in this class such
        *  as:
        *    * strlen(...)
        *    * strcpy(...)
        *    * strcmp(...)
        *    * strncpy(...)
        *    * strcat(...)
        *    * strncat(...)
        *
        *    A quick google search will return plenty of references on
        *    the c-string functions.
        **/

    wchar_t* data;

public:

    /**
     * Constructors and destructor
     *
     * Make sure you do proper memory management.
     **/
    DWString();
    explicit DWString(const wchar_t*);
    DWString(const DWString&);
    ~DWString();

    /**
     * Overloaded Assignment Operators
     */
    DWString& operator= (const wchar_t*);
    DWString& operator= (const DWString&);

    /**
     * Overloaded non-modifying string concat
     * @return
     */
    DWString operator+ (const DWString&);

    /**
     * Standard relational operators.  Feel free to add additional.
     *
     * Note that for each operator, there are two overloaded versions:
     *    one that takes a DWString object
     *    one that takes a null-terminated c-string
     *
     **/

    bool operator== (const wchar_t*) const;
    bool operator== (const DWString&)const;
    bool operator!= (const wchar_t*) const;
    bool operator!= (const DWString&)const;
    bool operator> (const DWString&) const;
    bool operator> (const wchar_t*) const;
    bool operator>= (const DWString&) const;
    bool operator>= (const wchar_t*) const;
    bool operator< (const DWString&) const;
    bool operator< (const wchar_t*) const;
    bool operator<= (const DWString&) const;
    bool operator<= (const wchar_t*) const;

    /**
     * Subscript operator to access a particular character of a DWString object
     * @return the character requested by reference
     */
    wchar_t& operator[] (const int);

    /**
     * getLength() returns the number (count) of characters in the string.
     **/
    int getLength();

    /**
     * The substring method returns a string object that contains a
     * sequence of characters from this string object.
     *
     * param start - the index of where to start
     * param numChars - the index of where to end
     * @return a DWString object containing the requested substring
     **/
    DWString substring(int start, int end);

    /**
     * the c_str function returns a null-terminated c-string holding the
     * contents of this object.
     **/
    wchar_t* c_str();

    /**
     * Overloaded stream insertion operator to print the contents of this
     * string to the output stream in the first argument.
     **/
    friend std::ostream& operator<< (std::ostream&, const DWString&);

    //You are free to add more functionality to the class.  For example,
    //you may want to add a find(...) function that will search for a
    //string within a string.  (just an example)
    //
    //Further - you will be able to update and modify this class as the
    //semester progresses.
    void makeLower();
    wchar_t getFirstChar();
    std::vector<DWString> stringParser(wchar_t, int min = 0, int max = INT_MAX);
    std::vector<DWString> stringParser(const wchar_t*, int min = 0, int max = INT_MAX);


};


#endif //PA01_SENTIMENT_DWSTRING_H
