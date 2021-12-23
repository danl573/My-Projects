# 🐥Tweet Sentiment Classifier 

The Tweet Sentiment Classifier is a C++ program that, given a dataset of pre-classified tweets based on sentiment (positive or negative), can predict the sentiment value of non-classified tweets.

This program analyzes the frequency of occurrence of words to develop a classification scheme which classifies the tweets.

## Installation

The Project folder already contains a main.cpp needs 4 command line arguments to functions: the paths or name of the training CSV dataset, the testing CSV data set, the sentiment CSV file for the testing data, and the output file.

## Usage
### Input File Formatting


```
Sentiment,id,Date,Query,User,Tweet
4,2014351367,Wed Jun 03 01:14:33 PDT 2009,NO_QUERY,cathyleehart,I can't wait for New Moon after seeing the trailer
0,1984531826,Sun May 31 15:17:28 PDT 2009,NO_QUERY,carlawaslike,ughhhh nothing on tv ready to get out of this house
```
The training dataset for developing the classification scheme is formatted as above. The first line shows what each value represents. The sentiment value will be 4 for positive sentiment and 0 for negative. The program will parse through the tweets and associate words with a sentiment level based on their frequency in tweets.

```
id,Date,Query,User,Tweet
2056534645,Sat Jun 06 11:19:19 PDT 2009,NO_QUERY,taisoliveira,i think will be great!
```
The dataset used for testing the program is formatted in a exactly the same, but without the sentiment column. The program will then parse through the tweets and assign each tweet a sentiment value a based on the classification scheme formulated in the training data.

```
Sentiment,id
4,2056534645
0,1685365352
```
Lastly, the program will then check the accuracy of its classifications with this last dataset. The dataset will contain the list of tweet ids as well as the correct sentiment associated with them. 

### Output File
```
0.632
2323232323
1132553423
```
The program will calculate the accuracy of its classifications based on the sentiment dataset and print the decimal value onto an output file provided by the user. The file will also contain a list of the incorrectly classified tweet ids.




## ❤️Credits

The Oleander Stemming Library was used in stemming the tweet words, more information can be found [here](http://www.oleandersolutions.com/stemming/stemming.html).

The tweet data used were originally retrieved from [Kaggle](https://www.kaggle.com/kazanova/sentiment140), but has been processed by Dr.Fontenot for the purposes of this project.

All data structures and algorithms were completed by me, Daniel Ryan, as a programming assignment for CS 2341 taught by Dr. Fontenot at SMU.

Thank you to Dr. Fonteot and the CS2341 teaching assistants for supporting me through it all.