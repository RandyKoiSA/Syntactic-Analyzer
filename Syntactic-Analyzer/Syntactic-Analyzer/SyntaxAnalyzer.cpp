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
		// check if the top of the stack is a terminal, if so check if lexeme matches
		if (isTerminal(syntaxStack.top())) {
			// check if it is an identifier
			handleTerminal();
		}
		else if (isNonterminal(syntaxStack.top())) {
			int currentRow = conversionNonTerminals[syntaxStack.top()];
			int currentColumn = conversionTerminals[lexemes[index]];

			syntaxStack.pop();
			int state = rules[currentRow][currentColumn];


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
	} while (syntaxStack.top() == "$" || lexemes[index] == "$");
}

bool SyntaxAnalyzer::isTerminal(string value) {
	for (int i = 0; i < terminals->size(); i++) {
		if (terminals[i] == value) return true;
	}
	return false;
}

bool SyntaxAnalyzer::isNonterminal(string value) {
	for (int i = 0; i < nonterminals->size(); i++) {
		if (nonterminals[i] == value) return true;
	}
	return false;
}

void SyntaxAnalyzer::handleTerminal() {

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
	if (syntaxStack.top() == lexemes[index]) {
		lexer();
	}
}

void SyntaxAnalyzer::ruleThree()
{
	cout << "ruleThree\n";
	// push J, T, -
	// check if the top of stack terminal and compares with lexeme index
}

void SyntaxAnalyzer::ruleFour()
{
	cout << "ruleFour\n";
	// push U, F
}

void SyntaxAnalyzer::ruleFive()
{
	cout << "ruleFive\n";
	// push U, F, *
	// check if the top of stack terminal and compares with lexeme index
}

void SyntaxAnalyzer::ruleSix()
{
	cout << "ruleSix\n";
	// push U, F, /
	// check if the top of stack terminal and compares with lexeme index
}

void SyntaxAnalyzer::ruleSeven()
{
	cout << "ruleSeven\n";
	// push ), E, (
	// check if the top of stack terminal and compares with lexeme index

}

void SyntaxAnalyzer::ruleEight()
{
	cout << "ruleEight\n";
	// push i
	// check if the top of stack terminal and compares with lexeme index
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
