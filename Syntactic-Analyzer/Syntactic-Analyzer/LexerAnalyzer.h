#pragma once
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class LexerAnalyzer
{
public:
	LexerAnalyzer();
	~LexerAnalyzer();

	// main methods
	void analyzeLexeme();
	void printLexeme();

	// state methods
	void stateOne();
	void stateTwo();
	void stateThree();
	void stateFour();
	void stateFive();
	void stateSix();
	void stateSeven();
	void stateEight();
	void stateNine();
	void stateTen();

	bool isSeperator(char ch);
	bool isOperator(char ch);
	bool isKeyword(char buffer[]);

	void loadTextFile(string textFile);
	void isTextFileOpen();
	char getNextCharacter();
	vector<string> getTokens();
	vector<string> getLexemes();
private:
	unsigned int section;
	unsigned int currentState;

	int table[10][7] = {
		2, 6, 5, 4, 7, 4, 1,
		2, 2, 3, 3, 3, 3, 3,
		1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1,
		8, 6, 8, 8, 8, 9, 8,
		7, 7, 7, 7, 1, 7, 7,
		1, 1, 1, 1, 1, 1, 1,
		8, 9, 8, 8, 8, 8, 8,
		1, 1, 1, 1, 1, 1, 1
	};
	fstream fin;
	string currentFile;

	vector<string> tokens;
	vector<string> tokensType;

	char *buffer;
	int j;
	char ch;
	bool isFirstRun;
};

