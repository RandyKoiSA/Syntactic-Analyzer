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
	conversion["E"] = 0;
	conversion["J"] = 1;
	conversion["T"] = 2;
	conversion["U"] = 3;
	conversion["F"] = 4;
	conversion["i"] = 0;
	conversion["+"] = 1;
	conversion["-"] = 2;
	conversion["/"] = 3;
	conversion["*"] = 4;
	conversion["("] = 5;
	conversion[")"] = 6;
	conversion["$"] = 7;
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
		int currentRow = conversion[syntaxStack.top()];
		int currentColumn = conversion[lexemes[index]];
		syntaxStack.pop();
		int state = rules[currentRow][currentColumn];
		
		switch (state){
		case -1:
			break;
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		default:
			cout << "ERROR, UNREACHABLE AREA\n";
		}

	} while (syntaxStack.top() == "$" || lexemes[index] == "$");
}

void SyntaxAnalyzer::ruleOne()
{
	// pushes J then T
}

void SyntaxAnalyzer::ruleTwo()
{
	// push J, T, +
	// check if the top of stack terminal and compares with lexeme index
}

void SyntaxAnalyzer::ruleThree()
{
	// push J, T, -
	// check if the top of stack terminal and compares with lexeme index
}

void SyntaxAnalyzer::ruleFour()
{
	// push U, F
}

void SyntaxAnalyzer::ruleFive()
{
	// push U, F, *
	// check if the top of stack terminal and compares with lexeme index
}

void SyntaxAnalyzer::ruleSix()
{
	// push U, F, /
	// check if the top of stack terminal and compares with lexeme index
}

void SyntaxAnalyzer::ruleSeven()
{
	// push ), E, (
	// check if the top of stack terminal and compares with lexeme index

}

void SyntaxAnalyzer::ruleEight()
{
	// push i
	// check if the top of stack terminal and compares with lexeme index
}

void SyntaxAnalyzer::ruleZero()
{
	// push nothing; continue
}

void SyntaxAnalyzer::ruleError()
{
	// ERROR HAS OCCURED
}
