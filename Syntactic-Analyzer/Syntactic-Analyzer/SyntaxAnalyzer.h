/*
	CPSC 323 Compilers and Languages
	
	@Project 2
	@Author Randy Le, Alex Ma, Sami Halwani
	@Version 1.2 04/22/2019s
*/

#pragma once
#include <stack>
#include <vector>
#include <string>
#include <map>

using namespace std;

class SyntaxAnalyzer {
public:
	SyntaxAnalyzer();
	// main method of running syntax analyzer
	void analyzeSyntax();

	// load lexemes / tokens for the lexeranalyzer
	void loadLexemes(vector<string>);
	void loadTokens(vector<string>);

	// testable methods
	void printLexemes();
	void printTokens();
	void printStack();
private:
	void makeConversions();
	bool isTerminal(string);
	bool isNonterminal(string);
	void handleTerminal();

	void ruleOneTriggered();   // i = E
	void ruleTwoTriggered();   // TQ
	void ruleThreeTriggered(); // +TQ
	void ruleFourTriggered();  // -TQ
	void ruleFiveTriggered();  // FR
	void ruleSixTriggered();   // *FR
	void ruleSevenTriggered(); // /FR
	void ruleEightTriggered(); // (E)
	void ruleNineTriggered();  // i
	void ruleZeroTriggered();  // EPSILON
	void ruleErrorTriggered(); // ERROR

	// get next lexeme / token
	void lexer();

private:
	vector<string> lexemes;
	vector<string> tokens;
	stack <string> syntaxStack; 
	map<string, int> conversionTerminals;
	map<string, int> conversionNonTerminals;

	vector<string> terminals= { "i", "+", "-", "/", "*", "(", ")", "$", "="};
	vector<string> nonterminals = { "S", "E", "Q", "T", "R", "F" };

	int rules[6][9] = {
		 1, -1, -1, -1, -1, -1, -1, -1, -1,
		 2, -1, -1, -1, -1,  2, -1, -1, -1,
		-1,  3,  4, -1, -1, -1,  0,  0, -1,
		 5, -1, -1, -1, -1,  5,  0,  0, -1,
		-1,  0,  0,  6,  7, -1,  0,  0, -1,
		 9, -1, -1, -1, -1,  8, -1, -1, -1
	};
	int index;	// index will keep track of where you are in the lexemes/tokens
};
