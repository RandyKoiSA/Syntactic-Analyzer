#include <stack>
#include <string>
#include <vector>
#include <iostream>
#include "SyntaxAnalyzer.h"

using namespace std;

SyntaxAnalyzer::SyntaxAnalyzer() {
	index = 0;
	syntaxStack = stack<string>();
	lexemes = vector<string>();
	tokens = vector<string>();
	makeConversions();
}

void SyntaxAnalyzer::makeConversions() {
	conversionNonTerminals["E"] = 0;
	conversionNonTerminals["J"] = 1;
	conversionNonTerminals["T"] = 2;
	conversionNonTerminals["U"] = 3;
	conversionNonTerminals["F"] = 4;
	conversionTerminals["i"] = 0;
	conversionTerminals["+"] = 1;
	conversionTerminals["-"] = 2;
	conversionTerminals["/"] = 3;
	conversionTerminals["*"] = 4;
	conversionTerminals["("] = 5;
	conversionTerminals[")"] = 6;
	conversionTerminals["$"] = 7;
}

void SyntaxAnalyzer::loadLexemes(vector<string> lexemes) {
	this->lexemes = lexemes;
}

void SyntaxAnalyzer::loadTokens(vector<string> tokens) {
	this->tokens = tokens;
}

void SyntaxAnalyzer::printLexemes() {
	for (int i = 0; i < lexemes.size(); i++) {
		cout << lexemes[i] << endl;
	}
}

void SyntaxAnalyzer::printTokens() {
	for (int i = 0; i < tokens.size(); i++) {
		cout << tokens[i] << endl;
	}
}

void SyntaxAnalyzer::printStack() {
	stack<string> displayStack = syntaxStack;
	while (displayStack.size() < 0) {
		cout << "stack: " << displayStack.top();
		displayStack.pop();
	}
}

void SyntaxAnalyzer::lexer() {
	index++;
}

void SyntaxAnalyzer::analyzeSyntax() {
	if (lexemes.size() < 0 || tokens.size() < 0) {
		cout << "ERROR: NO FILE WAS FOUND TO ANALYZE SYNTAX\n";
		return;
	}
	// add $ to the back
	lexemes.push_back("$");
	tokens.push_back("$");
	syntaxStack.push("$");

	// adding first state in stack
	syntaxStack.push("E");

	do {
		cout << "top stack: " << syntaxStack.top() << endl;
		// check if the top of the stack is a terminal, if so check if lexeme matches
		if (isTerminal(syntaxStack.top())) {
			// check if it is an identifier
			handleTerminal();
		}
		else if (isNonterminal(syntaxStack.top())) {
			cout << "nonterminal: " << syntaxStack.top() << " row: " << conversionNonTerminals[syntaxStack.top()] << endl;
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
			cout << "state: " << state << endl;

			switch (state) {
			case -1:
				ruleError();
				break;
			case 0:
				ruleZero();
				break;
			case 1:
				ruleOne();
				break;
			case 2:
				ruleTwo();
				break;
			case 3:
				ruleThree();
				break;
			case 4:
				ruleFour();
				break;
			case 5:
				ruleFive();
				break;
			case 6:
				ruleSix();
				break;
			case 7:
				ruleSeven();
				break;
			case 8:
				ruleEight();
				break;
			default:
				cout << "ERROR, UNREACHABLE AREA\n";
			}
		}
		else {
			cout << "ERROR HAS OCCURED (80)\n";
		}
	} while (syntaxStack.top() != "$" || lexemes[index] != "$");
	cout << "stack: " << syntaxStack.top() << endl;
	cout << "last lexeme: " << lexemes[index] << endl;
	cout << "SYNTAX IS CORRECT!\n";
}

bool SyntaxAnalyzer::isTerminal(string value) {
	for (int i = 0; i < terminals.size(); i++) {
		if (terminals[i] == value) return true;
	}
	return false;
}

bool SyntaxAnalyzer::isNonterminal(string value) {
	for (int i = 0; i < nonterminals.size(); i++) {
		// cout << value << " equals to " << nonterminals[i] << "?";
		if (nonterminals[i] == value) {
			// cout << " true \n";
			return true;
		}
		else {
			// cout << " false \n";
		}
	}
	return false;
}

void SyntaxAnalyzer::handleTerminal() {
	if (syntaxStack.top() == "i") {
		if (tokens[index] == "identifier") {
			lexer();
			syntaxStack.pop();
		}
		else {
			cout << "ERORR (146)\n";
		}
	}
	else {
		if (syntaxStack.top() == lexemes[index]) {
			lexer();
			syntaxStack.pop();
		}
		else {
			cout << "ERROR (155)\n";
		}	
	}
}

void SyntaxAnalyzer::ruleOne()
{
	cout << "ruleONE\n";
	// pushes J then T
	syntaxStack.push("J");
	syntaxStack.push("T");
}

void SyntaxAnalyzer::ruleTwo()
{
	cout << "ruleTwo\n";
	// push J, T, +
	// check if the top of stack terminal and compares with lexeme index
	syntaxStack.push("J");
	syntaxStack.push("T");
	syntaxStack.push("+");
}

void SyntaxAnalyzer::ruleThree()
{
	cout << "ruleThree\n";
	// push J, T, -
	// check if the top of stack terminal and compares with lexeme index
	syntaxStack.push("J");
	syntaxStack.push("T");
	syntaxStack.push("-");
}

void SyntaxAnalyzer::ruleFour()
{
	cout << "ruleFour\n";
	// push U, F
	syntaxStack.push("U");
	syntaxStack.push("F");
}

void SyntaxAnalyzer::ruleFive()
{
	cout << "ruleFive\n";
	// push U, F, *
	// check if the top of stack terminal and compares with lexeme index
	syntaxStack.push("U");
	syntaxStack.push("F");
	syntaxStack.push("*");
}

void SyntaxAnalyzer::ruleSix()
{
	cout << "ruleSix\n";
	// push U, F, /
	// check if the top of stack terminal and compares with lexeme index
	syntaxStack.push("U");
	syntaxStack.push("F");
	syntaxStack.push("/");
}

void SyntaxAnalyzer::ruleSeven()
{
	cout << "ruleSeven\n";
	// push ), E, (
	// check if the top of stack terminal and compares with lexeme index
	syntaxStack.push(")");
	syntaxStack.push("E");
	syntaxStack.push("(");
}

void SyntaxAnalyzer::ruleEight()
{
	cout << "ruleEight\n";
	// push i
	// check if the top of stack terminal and compares with lexeme index
	syntaxStack.push("i");
}

void SyntaxAnalyzer::ruleZero()
{
	cout << "ruleZero\n";
	// push nothing; continue
}

void SyntaxAnalyzer::ruleError()
{
	cout << "ruleError\n";
	// ERROR HAS OCCURED
}
