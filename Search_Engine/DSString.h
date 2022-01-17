#ifndef PA01_SENTIMENT_DSSTRING_H
#define PA01_SENTIMENT_DSSTRING_H

#include <iostream>
#include <cstring>
#include <climits>
#include <vector>
#include "OleanderStemmingLibrary-master/include/olestem/stemming/english_stem.h"


class DSString{

protected:
    char* data;

public:

    /**
     * Constructors and destructor
     *
     * Make sure you do proper memory management.
     **/
    DSString();
    DSString(const char*);
    DSString(const DSString&);
    ~DSString();

    /**
     * Overloaded Assignment Operators
     */
    DSString& operator= (const char*);
    DSString& operator= (const DSString&);

    /**
     * Overloaded non-modifying string concat
     * @return
     */
    DSString operator+ (const DSString&);

    /**
     * Standard relational operators.  Feel free to add additional.
     *
     * Note that for each operator, there are two overloaded versions:
     *    one that takes a DSString object
     *    one that takes a null-terminated c-string
     *
     **/

    bool operator== (const char*) const;
    bool operator== (const DSString&)const;
    bool operator!= (const char*) const;
    bool operator!= (const DSString&)const;
    bool operator> (const DSString&) const;
    bool operator> (const char*) const;
    bool operator>= (const DSString&) const;
    bool operator>= (const char*) const;
    bool operator< (const DSString&) const;
    bool operator< (const char*) const;
    bool operator<= (const DSString&) const;
    bool operator<= (const char*) const;

    /**
     * Subscript operator to access a particular character of a DSString object
     * @return the character requested by reference
     */
    char& operator[] (const int);

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
     * @return a DSString object containing the requested substring
     **/
    DSString substring(int start, int end);

    /**
     * the c_str function returns a null-terminated c-string holding the
     * contents of this object.
     **/
    char* c_str();

    /**
     * Overloaded stream insertion operator to print the contents of this
     * string to the output stream in the first argument.
     **/
    friend std::ostream& operator<< (std::ostream&, const DSString&);

    /**
     * Converts the string into all lowercase
     */
    void makeLower();

    /**
     * Returns the first char of the string, if string has a length greater than
     * 1
     * @return first char of string
     */
    char getFirstChar();
    char getLastChar();

    /**
     * The stringParser function will separate the string along any character that is the delim.
     * It will store and return the separated pieces that are within the bounds of min and
     * max into a vector
     * @param delim - delimeter that the string will parse along
     * @param min - minimum character length being stored
     * @param max - maximum character length being stored
     * @return a vector containing the separated pieces of the parsed string
     */
    std::vector<DSString> stringParser(char delim, int min = 0, int max = INT_MAX);

    /**
     * The overloaded stringParser function is the same except for inclusion of
     * a char array delim, allowing for multiple delimiters for parsing
     * @param delim - delimeter that the string will parse along
     * @param min - minimum character length being stored
     * @param max - maximum character length being stored
     * @return a vector containing the separated pieces of the parsed string
     */
    std::vector<DSString> stringParser(const char* delim, int min = 0, int max = INT_MAX);

    /**
     * The stem method uses the Oleander Stemming Library to stem the string into
     * only its root
     */
    void stem();

//    std::vector<DSString> ParseStem(const char* delim,);

};



#endif //PA01_SENTIMENT_DSSTRING_H
