/*
	CPSC 323 Compilers and Languages

	@Author Randy Le, Alex Ma, Sami Halwani
	@Version 1.2 04/22/2019
*/

#include <stack>
#include <string>
#include <vector>
#include <iostream>
#include "SyntaxAnalyzer.h"

using namespace std;

/*
	Syntax Analyzer Constructor
	initializes emmpty variables and set the T and NT conversions
*/
SyntaxAnalyzer::SyntaxAnalyzer() {
	index = 0;
	syntaxStack = stack<string>();
	lexemes = vector<string>();
	tokens = vector<string>();
	makeConversions();
}

/*
	Make Conversion Method
	Converts terminals and non-terminals to there corresponding
	row or column in order use the 2D array rules
*/
void SyntaxAnalyzer::makeConversions() {
	conversionNonTerminals.insert(pair<string, int>("S", 0));
	conversionNonTerminals.insert(pair<string, int>("E", 1));
	conversionNonTerminals.insert(pair<string, int>("Q", 2));
	conversionNonTerminals.insert(pair<string, int>("T", 3));
	conversionNonTerminals.insert(pair<string, int>("R", 4));
	conversionNonTerminals.insert(pair<string, int>("F", 5));
	conversionTerminals.insert(pair<string, int>("i", 0));
	conversionTerminals.insert(pair<string, int>("+", 1));
	conversionTerminals.insert(pair<string, int>("-", 2));
	conversionTerminals.insert(pair<string, int>("*", 3));
	conversionTerminals.insert(pair<string, int>("/", 4));
	conversionTerminals.insert(pair<string, int>("(", 5));
	conversionTerminals.insert(pair<string, int>(")", 6));
	conversionTerminals.insert(pair<string, int>("$", 7));
	conversionTerminals.insert(pair<string, int>("=", 8));
}

/*
	Load Lexemes Method
	Load the lexemes that was read from the Lexical Analyzer
	to Syntax Analyzer
*/
void SyntaxAnalyzer::loadLexemes(vector<string> lexemes) {
	this->lexemes = lexemes;
}

/*
	Load Tokens Method
	Loads the tokens that was read from the Lexical Anaylzer
	to the Syntax Analyzer.
*/
void SyntaxAnalyzer::loadTokens(vector<string> tokens) {
	this->tokens = tokens;
}

/*
	Print Lexemes Method
	Prints out the lexemes that was loaded onto the
	Syntax Analyzer. This method is mostly used to test if the
	Lexemes were loaded correctly.
*/
void SyntaxAnalyzer::printLexemes() {
	for (int i = 0; i < lexemes.size(); i++) {
		cout << lexemes[i] << endl;
	}
}

/*
	Print Tokens Method
	Prints out the tokens that was loaded onto the
	Syntax Analyzer. Method is mostly used to test if the Tokens
	were loaded correctly onto the Syntax Analyzer.
*/
void SyntaxAnalyzer::printTokens() {
	for (int i = 0; i < tokens.size(); i++) {
		cout << tokens[i] << endl;
	}
}

/*
	Print Stack Method
	Prints out the what is in the current stack.
	Used to keep track of whats being pushed and popped.
*/
void SyntaxAnalyzer::printStack() {
	stack<string> displayStack = syntaxStack;
	while (displayStack.size() < 0) {
		cout << "stack: " << displayStack.top();
		displayStack.pop();
	}
}

/*
	Lexer Method
	increases the index to read the next lexemes / tokens
*/
void SyntaxAnalyzer::lexer() {
	index++;
}

/*
	Analyze Syntax Method
	Main Function of Syntax Analyze
	Checks if the given tokens / lexemes are grammarly correctly
	with the given production rules.
*/
void SyntaxAnalyzer::analyzeSyntax() {
	if (lexemes.size() < 1 || tokens.size() < 1) {
		cout << "ERROR: NO FILE WAS FOUND TO ANALYZE SYNTAX\n";
		return;
	}
	// add $ to the back
	lexemes.push_back("$");
	tokens.push_back("$");
	syntaxStack.push("$");

	// adding first state in stack
	syntaxStack.push("S");

	do {
		cout << "\ntop stack: " << syntaxStack.top() << endl;
		// check if the top of the stack is a terminal, if so check if lexeme matches
		if (isTerminal(syntaxStack.top())) {
			// check if it is an identifier
			handleTerminal();
		}
		else if (isNonterminal(syntaxStack.top())) {
			cout << "nonterminal: " << syntaxStack.top() << "\trow: " << conversionNonTerminals[syntaxStack.top()] << endl;
			int currentRow = conversionNonTerminals[syntaxStack.top()];
			int currentColumn;

			// check the types of tokens before processing into the column
			if (tokens[index] == "identifier") {
				currentColumn = conversionTerminals["i"];
				cout << "terminal: " << lexemes[index] << " \tcolumn: " << currentColumn << endl;
			}
			else {
				currentColumn = conversionTerminals[lexemes[index]];
				cout << "terminal: " << lexemes[index] << " \tcolumn: " << currentColumn << endl;
			}

			syntaxStack.pop();
			int state = rules[currentRow][currentColumn];
			cout << "state:\t " << state << endl;

			switch (state) {
			case -1:
				ruleErrorTriggered();
				break;
			case 0:
				ruleZeroTriggered();
				break;
			case 1:
				ruleOneTriggered();
				break;
			case 2:
				ruleTwoTriggered();
				break;
			case 3:
				ruleThreeTriggered();
				break;
			case 4:
				ruleFourTriggered();
				break;
			case 5:
				ruleFiveTriggered();
				break;
			case 6:
				ruleSixTriggered();
				break;
			case 7:
				ruleSevenTriggered();
				break;
			case 8:
				ruleEightTriggered();
				break;
			case 9:
				ruleNineTriggered();
				break;
			default:
				printf("ERROR on %d \n", __LINE__);
				printf("Prease enter to exit program\n");
				cin.get();
				exit(0);
			}
		}
		else {
			cerr << "ERROR HAS OCCURED (80)\n";
		}
	} while (syntaxStack.top() != "$" || lexemes[index] != "$");
	cout << "SYNTAX IS CORRECT!\n";
}

/*
	Is Terminal Method
	returns true if the given string is a terminal
*/
bool SyntaxAnalyzer::isTerminal(string value) {
	for (int i = 0; i < terminals.size(); i++) {
		if (terminals[i] == value) return true;
	}
	return false;
}

/*
	Is Non-Terminal Method
	returns true if the given string is a non-terminal
*/
bool SyntaxAnalyzer::isNonterminal(string value) {
	for (int i = 0; i < nonterminals.size(); i++) {
		if (nonterminals[i] == value) {
			return true;
		}
	}
	return false;
}

/*
	handle Terminal method
	this handles if the given top of the stack matches with the
	current lexemes being read. This will produce an error if the
	current lexemes does not match with the top of the stack terminal.
*/
void SyntaxAnalyzer::handleTerminal() {
	if (syntaxStack.top() == "i") {
		if (tokens[index] == "identifier") {
			lexer();
			syntaxStack.pop();
		}
		else {
			printf("ERROR on %d \n", __LINE__);
			printf("Prease enter to exit program\n");
			cin.get();
			exit(0);
		}
	}
	else {
		if (syntaxStack.top() == lexemes[index]) {
			lexer();
			syntaxStack.pop();
		}
		else {
			printf("ERROR on %d \n", __LINE__);
			printf("Prease enter to exit program\n");
			cin.get();
			exit(0);
		}	
	}
}

/*
	Rule One Triggered Method
	Production rule one has been triggered.
	This will push i, = , then E to the stack
*/
void SyntaxAnalyzer::ruleOneTriggered()
{
	// cout << "ruleONE\n";
	syntaxStack.push("E");
	syntaxStack.push("=");
	syntaxStack.push("i");
}

/*
	Rule Two Triggered Method
	Product rule two has been triggered.
	This will push T then Q
*/
void SyntaxAnalyzer::ruleTwoTriggered()
{
	cout << "ruleTwo\n";
	syntaxStack.push("Q");
	syntaxStack.push("T");
}

/*
	Rule Three Triggered Method
	Production rule three has been triggered.
*/
void SyntaxAnalyzer::ruleThreeTriggered()
{
	cout << "ruleThree\n";
	syntaxStack.push("Q");
	syntaxStack.push("T");
	syntaxStack.push("+");
}

/*
	Rule Four Triggered Method
	Production rule four has been triggered.
*/
void SyntaxAnalyzer::ruleFourTriggered()
{
	cout << "ruleFour\n";
	syntaxStack.push("Q");
	syntaxStack.push("T");
	syntaxStack.push("-");
}

/*
	Rule Five Triggered Method
	Production rule five has been triggered.
*/
void SyntaxAnalyzer::ruleFiveTriggered()
{
	cout << "ruleFive\n";
	syntaxStack.push("R");
	syntaxStack.push("F");
}

/*
	Rule Six Triggered Method
	Production rule six has been triggered.
*/
void SyntaxAnalyzer::ruleSixTriggered()
{
	cout << "ruleSix\n";
	syntaxStack.push("R");
	syntaxStack.push("F");
	syntaxStack.push("*");
}

/*
	Rule Seven Triggered Method
	Production rule seven has been triggered.
*/
void SyntaxAnalyzer::ruleSevenTriggered()
{
	cout << "ruleSeven\n";
	syntaxStack.push("R");
	syntaxStack.push("F");
	syntaxStack.push("/");
}

/*
	Rule Eight Triggered Method
	Production rule eight has been triggered.
*/
void SyntaxAnalyzer::ruleEightTriggered()
{
	cout << "ruleEight\n";
	syntaxStack.push(")");
	syntaxStack.push("E");
	syntaxStack.push("(");
}

/*
	Rule Nine Triggered Method
*/
void SyntaxAnalyzer::ruleNineTriggered()
{
	syntaxStack.push("i");
}

/*
	Rule Zero Triggered Method
	Production rule zero has been triggered.
	This means that there is no error so just continute.
*/
void SyntaxAnalyzer::ruleZeroTriggered()
{
	cout << "ruleZero\n";
}

/*
	Rule Error Triggered Method
	An error had occured in the process.
	This means that the lexemes and tokens are not
	syntactically correct.
*/
void SyntaxAnalyzer::ruleErrorTriggered()
{
	cout << "ruleError\n";
}
