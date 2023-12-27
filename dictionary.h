#pragma once
#include<iostream>
#include<Windows.h>
#include<string>
#include<sstream>
#include<fstream>
#include<conio.h>
#include<cstdlib>
#include<iomanip>

using namespace std;
#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define UNDERLINE   "\033[4m"
#define GRAY        "\033[90m"
#define RED         "\033[91m"
#define GREEN       "\033[92m"
#define YELLOW      "\033[93m"
#define BLUE        "\033[94m"
#define MAGENTA     "\033[95m"
#define CYAN        "\033[96m"
#define PINK        "\033[95;91m"
#define LIGHT_BLUE  "\033[38;5;39m"

class trienode {
public:
	trienode* alphates[26];
	bool endofword;
	string meaningofword;
	trienode();
};
class Dictionary {
	trienode* root;
	string suggestions[10];
	int num;
public:
	Dictionary();
	string meaning1(int index);
		trienode*& getroot();
bool existance(char ch);
void insertingwordinadictionary(string word, string meaningofword1);
void deletedictionary(trienode* node);
void line();
void loading();
int getMenuChoice();
void addword(string word, string meaning);
void updatewordinfile(const string& word, const string& newMeaning);
bool updateword(string word, string meaning);
bool wordexistornot(string word);
void searchword(string word);
bool wordexistindictionaryornot(string word);
bool deleteWordFromDictionary(string word, trienode*& node);
void deleteword(string word, trienode*& node, int x);
void deletefromfile(const string& word);
void wordsuggestion(string word);
void livesuggestions(string word, int& count, trienode* temp);
string check(string word, string print);
void makingsuggestionsempty();
void print(int count);
string leftAlign(const string& str, size_t width);
~Dictionary();
};