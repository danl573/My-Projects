# Search Engine

This Search Engine is a C++ project for searching .json files, allowing the user to perform searching, receive relevancy ranked results, select and open articles, and create a persistence index.

Although the project was originally created to search through Finance Articles, it will function with any .json files.

## About

The program uses RapidJson to help parse through the documents, where the words will be filtered from stop words and stemmed using the Oleander Stemmer. in which the words, persons, and organizations are stored in an **inverted file index** as an **AVL Tree** for the words and a **Hash Table** for the persons and orgs. Which can then be used in searching through the Query Processor.

The Query Processor is used for parsing the queries entered by the user, it can process simple prefix Boolean queries. The program will perform a relevancy ranking for the results, showing the top 15 results.

There are additional functions including reading and writing to a persistence index, getting basic statistics of the Search Engine, and clearing and rereading the index, which can all be found in the User Interface.

## Installation
The Search Engine folder already contains a main.cpp only needs a single command line argument to run, the path to the folder containing the input json files. 

This program has previously  functioned with 300,000 .json input files read. However, depending on the size of the file and speed of the machine this program is run on, results and speeds may vary significantly.


## Usage

```
-_-_-_-_-_-Welcome to the Finance Search Engine!!-_-_-_-_-_-
-_-_-_-_-_-_-_-Brought to you by: Daniel Ryan-_-_-_-_-_-_-_-

==================================
Please choose an option:
[1]Read from Persistent Index
[2]Read from Documents
[0]Quit
```
When first running the program, this is the first prompt you should receive. If this is your first time running the program or you have not created a Persistence Index for the current data set being used, option 2 should be chosen, where you will be asked how many documents you wish to read. Otherwise, if a Persistent Index has been created already, pick option 1.

```
==================================
Please choose an option:
[1]Search
[2]Get Statistics
[3]Open Article
[4]Clear Index
[5]Make Persistent Index
[6]Load Index
[0]Quit
==================================
```
Once the index has been created, the User Interface will be shown, providing the user with various options.

### Searching
This program can handle simple prefix Boolean queries entered by the user. For a single word searches with no additional operators, only the word has to be entered.

The expression will be prefixed with a Boolean operator of either AND or OR for multiple word searches. Following operators are optional:
- NOT <words> operator will indicate that articles with these words will be removed from the results
- PERSON <names of persons> operator will search a special index related to people mentioned in the article's entity metadata 
- ORG <names of orgs> operator will search a special index related to organizations mentioned in the article's entity metadata

The program will go through a relevancy ranking in which the top 15 articles will be shown , with the article's title, id, and first 30 words being returned.

### Statistics
Choosing the Get Statistics option will show a list of various statistics of the Search Engine, include article count, word count, top 50 most frequent words, etc.

### Open Article
By providing the article id (which are shown in the search results), the program will output the article's body text

### Persistent Index
The program provides an option to create and read from a Persistence Index, which allows for faster reading times in comparison to reading the documents in their entirety. 

*Notice that the making and reading of the Persistence Index is still a bit buggy for large data sets, updates are on the way.

## Credits
The Oleander Stemming Library was used in stemming the article words when reading the files, more information can be found [here](http://www.oleandersolutions.com/stemming/stemming.html).

RapidJson was also used in this project to read and parse through the many .json files, more information can be found [here](https://rapidjson.org/).

All data structures and algorithms were completed by me, Daniel Ryan, as the final programming assignment for CS 2341 taught by Dr. Fontenot at SMU.

Thank you to Dr. Fonteot and the CS2341 teaching assistants for supporting me through it all.