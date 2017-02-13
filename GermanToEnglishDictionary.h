#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <io.h>
#include <iomanip>

using std::cout;
using std::cin;
using std::string;
using std::right;
using std::ofstream;
using std::ifstream;
using std::setw;
using std::ios_base;

string wordTypes[] = { "noun", "verb", "preposition", "adjective", "adverb", "cardinal number" };

class GermanToEnglishWord{

public:
	string germanTrans, englishTrans;
	int wordType;
};

void printMenu();
bool loadGtEWordsArray(GermanToEnglishWord dict[], int size);
GermanToEnglishWord getGtEW();
string getGermanWord();
void sortDictionary(GermanToEnglishWord dict[], int size);
void saveDictionary(GermanToEnglishWord dict[], int size, const char *file);
void loadDictionary(GermanToEnglishWord dict[], int size, const char *file);
string cleanGermanWord(string word, int type);
string ignoreArticle(string word);
string exchangeGermanLettering(string word);
void lookUpDefinition(GermanToEnglishWord dict[], int size);
int getWordIndex(GermanToEnglishWord dict[], int size, string word);
void printDictionary(GermanToEnglishWord dict[], int size, int type);
void printDefinition(GermanToEnglishWord dict[], int i);
string addSpaces(int numSpaces);