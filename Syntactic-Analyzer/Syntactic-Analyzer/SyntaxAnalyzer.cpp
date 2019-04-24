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
	conversionNonTerminals = {
		{"S", 0}, {"E", 1}, {"Q", 2}, {"T", 3}, {"R", 4}, {"F", 5},
	};
	conversionTerminals = {
		{"i", 0}, {"+", 1}, {"-", 2}, {"*", 3}, {"/", 4}, {"(", 5},
		{")", 6}, {"$", 7}, {"=", 8}
	};
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
		printf("\ntop stack: %s\n", syntaxStack.top().c_str());
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

			productionRule state = rules[currentRow][currentColumn];
			cout << "state:\t " << state << endl;

			switch (state) {
			case ruleNeg:
				ruleErrorTriggered();
				break;
			case ruleZero:
				ruleZeroTriggered();
				break;
			case ruleOne:
				ruleOneTriggered();
				break;
			case ruleTwo:
				ruleTwoTriggered();
				break;
			case ruleThree:
				ruleThreeTriggered();
				break;
			case ruleFour:
				ruleFourTriggered();
				break;
			case ruleFive:
				ruleFiveTriggered();
				break;
			case ruleSix:
				ruleSixTriggered();
				break;
			case ruleSeven:
				ruleSevenTriggered();
				break;
			case ruleEight:
				ruleEightTriggered();
				break;
			case ruleNine:
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
	printf("\nSytax is correct!\n");
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
			printf("identifier found: %s\n", lexemes[index].c_str());
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
			printf("terminal matched with stack: %s\n", lexemes[index].c_str());
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
	This will push T then Q.
*/
void SyntaxAnalyzer::ruleTwoTriggered()
{
	//cout << "ruleTwo\n";
	syntaxStack.push("Q");
	syntaxStack.push("T");
}

/*
	Rule Three Triggered Method
	Production rule three has been triggered.
	Pushing Q, T, then + onto the stack.
*/
void SyntaxAnalyzer::ruleThreeTriggered()
{
	//cout << "ruleThree\n";
	syntaxStack.push("Q");
	syntaxStack.push("T");
	syntaxStack.push("+");
}

/*
	Rule Four Triggered Method
	Production rule four has been triggered.
	Pushing Q, T, then - onto the stack.
*/
void SyntaxAnalyzer::ruleFourTriggered()
{
	//cout << "ruleFour\n";
	syntaxStack.push("Q");
	syntaxStack.push("T");
	syntaxStack.push("-");
}

/*
	Rule Five Triggered Method
	Production rule five has been triggered
	Pushing R then F onto the stack.
*/
void SyntaxAnalyzer::ruleFiveTriggered()
{
	//cout << "ruleFive\n";
	syntaxStack.push("R");
	syntaxStack.push("F");
}

/*
	Rule Six Triggered Method
	Production rule six has been triggered.
	Pushing R, F, then * onto the stack.
*/
void SyntaxAnalyzer::ruleSixTriggered()
{
	//cout << "ruleSix\n";
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
	//cout << "ruleSeven\n";
	syntaxStack.push("R");
	syntaxStack.push("F");
	syntaxStack.push("/");
}

/*
	Rule Eight Triggered Method
	Production rule eight has been triggered.
	Pushing ), E, then ( onto the stack.
*/
void SyntaxAnalyzer::ruleEightTriggered()
{
	//cout << "ruleEight\n";
	syntaxStack.push(")");
	syntaxStack.push("E");
	syntaxStack.push("(");
}

/*
	Rule Nine Triggered Method
	Pushing i onto the stack.
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
	//cout << "ruleZero\n";
}

/*
	Rule Error Triggered Method
	An error had occured in the process.
	This means that the lexemes and tokens are not
	syntactically correct.
*/
void SyntaxAnalyzer::ruleErrorTriggered()
{
	//cout << "ruleError\n";
}
