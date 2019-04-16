#include "LexerAnalyzer.h"
#include <fstream>
#include <iostream>
#include <ctype.h>
#include <vector>
#include <stdio.h>
#include <iomanip>

/*
 CONSTRUCTOR
 */
LexerAnalyzer::LexerAnalyzer()
{
	isFirstRun = true;
	currentState = 1;
	buffer = new char[10000];
	j = 0;
}

/*
 DECONSTRUCTOR
*/
LexerAnalyzer::~LexerAnalyzer()
{
	delete buffer;
}

/*
 ANALYZE LEXEME
 This is the main function of the Lexeme Analysis.
*/
void LexerAnalyzer::analyzeLexeme()
{
	if (fin.is_open()) {
		do {
			switch (currentState) {
			case 1:
				// cout << "In state one\n";
				stateOne();
				break;
			case 2:
				// cout << "In state two\n";
				stateTwo();
				break;
			case 3:
				// cout << "In state three\n";
				stateThree();
				break;
			case 4:
				// cout << "In state four\n";
				stateFour();
				break;
			case 5:
				// cout << "In state five\n";
				stateFive();
				break;
			case 6:
				// cout << "In state six\n";
				stateSix();
				break;
			case 7:
				// cout << "In state seven\n";
				stateSeven();
				break;
			case 8:
				// cout << "In state eight\n";
				stateEight();
				break;
			case 9:
				// cout << "In state nine\n";
				stateNine();
				break;
			case 10:
				// cout << "In state ten\n";
				stateTen();
			case 0:
				break;
			}
			// cout << "Finished State " << currentState << endl;
			currentState = table[currentState - 1][section - 1];
		} while (!fin.eof());
		printLexeme();
		fin.close();
	}
	else {
		printf("No FILES to analyze.\n");
	}
}

/*
 PRINTING LEXEME RESULT METHOD
 After text file has completely scanned, it will display the
 tokens along with the tokens type.
*/
void LexerAnalyzer::printLexeme()
{
	cout << setw(20) << "Lexemes" << setw(30) << "TOKENS\n";
	for (int i = 0; i < tokens.size() && i < tokensType.size(); i++) {
		cout << setw(20) << tokens[i] << setw(30) << tokensType[i] << endl;
	}
}

/*
 STATE ONE METHOD
 State one is the initial state.
 Retrieves next character of the text file.
 Character determines what state it goes to.
*/
void LexerAnalyzer::stateOne()
{
	ch = getNextCharacter();
	// cout << "'" << ch << "'" << endl;
	if (isOperator(ch)) {
		section = 3;
	}
	else if (isSeperator(ch)) {
		if (ch == '!') section = 5;
		else section = 4;
	}
	else if (isalpha(ch) && ch != '\n') {
		buffer[j++] = ch;
		section = 1;
	}
	else if (isdigit(ch)) {
		buffer[j++] = ch;
		section = 2;
	}
	else {
		// cout << "Error has occurred\n";
		// cout << "Value causing problems is: " << ch << endl;
		section = 7;
	}
}

/*
 STATE TWO METHOD
 A letter was detected.
 Scans for more letter / digits after it until seperator or operator shows.
*/
void LexerAnalyzer::stateTwo()
{ 
	ch = getNextCharacter();
	// cout << "'" << ch << "'" << endl;
	if (isalpha(ch)) {
		buffer[j++] = ch;
		section = 1;
	}
	else if (isdigit(ch)) {
		buffer[j++] = ch;
		section = 2;
	}
	else if (ch == '$') {
		buffer[j++] = ch;
		section = 1;
	}
	else if(isOperator(ch) || isSeperator(ch)){
		section = 3;
	}
	else section = 3;
}

/*
 STATE THREE METHOD
 The end of finding a identifier.
 Checks if the identifier is a keyword.
 Adds the following seperator / operator to the token / tokentype.
 Then, returns back to one.
*/
void LexerAnalyzer::stateThree()
{
	buffer[j] = '\0';
	j = 0;
	if (isKeyword(buffer)) {
		tokens.push_back(buffer);
		tokensType.push_back("keyword");
	}
	else {
		tokens.push_back(buffer);
		tokensType.push_back("identifier");
	}

	if (isSeperator(ch)) {
		if (ch != ' ') {
			tokens.push_back(string(1, ch));
			tokensType.push_back("seperator");
			section = 4;
		}
	}
	else if (isOperator(ch)) {
		tokens.push_back(string(1, ch));
		tokensType.push_back("operator");
		section = 3;
	}
}

/*
 STATE FOUR METHOD
 A seperator character was found.
 Putting character in token / tokenType as a seperator.
 Then returns back to state one.
*/
void LexerAnalyzer::stateFour()
{
	// cout << "'" << ch << "'" << endl;
	if (ch == ' ') {
		return;
	}
	tokens.push_back(string(1, ch));
	tokensType.push_back("seperator");
	section = 4;
}

/*
 STATE FIVE METHOD
 An operator character was found.
 Putting the character in token / tokenType as a operator.
 Then returns back to state one.
*/
// state five is when a operator is found
void LexerAnalyzer::stateFive()
{
	// cout << "'" << ch << "'" << endl;
	tokens.push_back(string(1, ch));
	tokensType.push_back("operator");
	section = 2;
}


/*
 STATE SIX METHOD
 A digit character was found.
 Scans for any others digits following it.
 Then returns back to state one.
*/
void LexerAnalyzer::stateSix()
{
	ch = getNextCharacter();
	// cout << "'" << ch << "'" << endl;

	// found a letter, ending the search for integers
	// integer is put into the token and
	if (isalpha(ch) && ch != '\n') {
		// send integer to token
		buffer[j] = '\0';
		j = 0;
		tokens.push_back(buffer);
		tokensType.push_back("integer");
		section = 1;
	}
	else  if (isdigit(ch)) {
		buffer[j++] = ch;
		section = 2;
	}
	else if (isOperator(ch)) {
		// send integer to token
		buffer[j] = '\0';
		j = 0;
		tokens.push_back(buffer);
		tokensType.push_back("integer");
		section = 3;
	}
	else if (isSeperator(ch)) {
		if (ch == '.') {
			buffer[j++] = ch;
			section = 6;
		}
		else {
			// send integer to token
			buffer[j] = '\0';
			j = 0;
			tokens.push_back(buffer);
			tokensType.push_back("integer");
			section = 4;
		}
	}
	else {
		// cout << "Error has occurred\n";
		// cout << "Value causing problems is: " << ch << endl;
		section = 7;
	}
}

/*
 STATE SEVEN METHOD
 detected a comment. scans for all comment character.
 Then returns back to state one.
*/
void LexerAnalyzer::stateSeven()
{
	// cout << "'" << ch << "'" << endl;
	ch = getNextCharacter();
	if (ch != '!') {
		section = 1;
	}
	else {
		section = 5;
	}
}

/*
 STATE EIGHT METHOD
 End of integer / float value
*/
void LexerAnalyzer::stateEight()
{
	// cout << "'" << ch << "'" << endl;
	if (isalpha(ch) && ch != '\n') {
		buffer[j++] = ch;
		section = 1;
	}
	else if (isOperator(ch)) {
		tokens.push_back(string(1, ch));
		tokensType.push_back("operator");
		section = 3;
	}
	else if (isSeperator(ch)) {
		tokens.push_back(string(1, ch));
		tokensType.push_back("seperator");
		section = 4;
	}
	else {
		// cout << "Error has occurred\n";
		// cout << "Value causing problems is: " << ch << endl;
		section = 7;
	}
}

/*
 STATE NINE METHOD
 A '.' was found while finding an integer
 Scan for remaining number for float value
*/
void LexerAnalyzer::stateNine()
{
	ch = getNextCharacter();
	// cout << "'" << ch << "'" << endl;
	if (isalpha(ch)) {
		// send float to token
		buffer[j] = '\0';
		j = 0;
		tokens.push_back(buffer);
		tokensType.push_back("float");

		section = 1;
	}
	else if (isdigit(ch)) {
		buffer[j++] = ch;
		section = 2;
	}
	else if (isOperator(ch)) {
		// send float to token
		buffer[j] = '\0';
		j = 0;
		tokens.push_back(buffer);
		tokensType.push_back("float");

		section = 3;
	}
	else if (isSeperator(ch)) {
		// send float to token
		buffer[j] = '\0';
		j = 0;
		tokens.push_back(buffer);
		tokensType.push_back("float");

		section = 4;
	}
	else {
		cout << "Error has occurred\n";
		section = 7;
	}
}

void LexerAnalyzer::stateTen()
{
	// cout << "'" << ch << "'" << endl;
	section = 1;
}

/*
 IS CHARACTER A SEPERATOR METHOD
 checks if the following chracter is part of the seperator list
*/
bool LexerAnalyzer::isSeperator(char ch)
{
	char seperators[12] {
		'(', ')', '\'', '{', '}',
		'[', ']', ',', '.', ':',
		';', '!'
	};
	if (ch == char(32)) return true;

	for (int i = 0; i < 13; i++)
		if (ch == seperators[i]) return true;
	return false;
}

/*
 IS CHARATER A OPERATOR METHOD
 checks if the following character is part of the operator list
*/
bool LexerAnalyzer::isOperator(char ch)
{
	char operators[8]{
		'*', '+', '-', '=', '/',
			'>', '<', '%'
	};
	
	for (int i = 0; i < 8; i++)
		if (ch == operators[i]) return true;
	return false;
}

/*
 IS IDENTIFIER A KEYWORD METHOD
 checks if the following string(buffer) is part of the keyword list.
*/
bool LexerAnalyzer::isKeyword(char buffer[])
{
	char keywords[13][10]{
	"int", "float", "bool", "if", "else",
	"do", "while", "whileend", "doend", "for",
	"and", "or", "function"
	};

	for (int i = 0; i < 13; i++)
		if (strcmp(buffer, keywords[i]) == 0) return true;
	return false;
}

/*
 LOAD TEXT FILE METHOD
 loads a text file to read. If text file doesn't exist, it will display an error.
*/
void LexerAnalyzer::loadTextFile(string textFile)
{
	fin.open(textFile);
	if (!fin.is_open()) printf("Unable to open file: %s \n", textFile.c_str());
	else {
		printf("Successfully opened file: %s \n", textFile.c_str());
		currentFile = textFile;
	}
}

/*
 IS TEXT FILE OPEN? METHOD
 validates if there is a textfile loaded.
*/
void LexerAnalyzer::isTextFileOpen()
{
	if (fin.is_open()) printf("text file %s is currently open", currentFile.c_str());
	else printf("no text file loaded yet");
}

/*
 GET NEXT CHARACTER METHOD
 scans for the the next character of the loaded file.
*/
char LexerAnalyzer::getNextCharacter()
{
	return fin.get();
}

vector<string> LexerAnalyzer::getLexemes() {
	return tokens;
}

vector<string> LexerAnalyzer::getTokens() {
	return tokensType;
}

