# Auto Text Indexer 

The Auto-Indexer is a C++ library that automatically provides an index on a formatted text file.


The program reads each page in the text file, reading the bracketed entries with the help of a custom vector functioning as a stack object.

## Installation

After downloading the Auto Indexer folder, just include the Processor.h file into your main .

```cpp
#include "Processor.h"
```

## Usage
### Input File Formatting

``` 
<3>
Preface:

[Advanced [Data Structures] and [Algorithm Implementation]] is a new exciting
text from Mustang Publishers aimed at upper division
undergraduate courses or introductory graduate courses.
<4>
Some of the topics covered are:
* [Fast String Matching]
* [[B+ Tree] Implementation]
* [A* Graph Traversal]
<10>
In a [B+ Tree], the leaf nodes are connected as a [doubly linked list].
<-1>
```
Notice that each page number is placed before its page within angled brackets and the words/phrases that will be indexed are in square braces.
The program will stop reading pages once page <-1> is reached.

Note that nested brackets are supported and will be read as separate entries.

### Output File

```
[a]
a* graph traversal: 4
advanced data structures and algorithm implementation: 3
algorithm implementation: 3
[b]
b+ tree: 4, 10
b+ tree implementation: 4
[d]
data structures: 3
doubly linked list: 10
[f]
fast string matching: 4
```

The indexed file will be formatted as shown above. It will be in all lowercase in alphabetical order.

### Example
```cpp
#include "Processor.h"

Processor p;
p.ReadBook("Path_To_Book_textFile");
p.PrintIndex("Path_To_Index_textFile");
```
The library contains 2 functions for generating an index, the ReadBook() and PrintIndex(). Notice how both functions require one parameter, being the name or path to the file it is reading/writing to.


## Credits
The Oleander Stemming Library, although not used in this project specifically, is implemented. More information can be found [here](http://www.oleandersolutions.com/stemming/stemming.html).

All data structures and algorithms were completed by me, Daniel Ryan, as a programming assignment for CS 2341 taught by Dr. Fontenot at SMU.

Thank you to Dr. Fonteot and the CS2341 TAs for supporting me.
