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
	void ruleOneTriggered();   // TJ
	void ruleTwoTriggered();   // +TJ
	void ruleThreeTriggered(); // -TJ
	void ruleFourTriggered();  // FU
	void ruleFiveTriggered();  // *FU
	void ruleSixTriggered();   // /FU
	void ruleSevenTriggered(); // (E)
	void ruleEightTriggered(); // i
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

	vector<string> terminals= { "i", "+", "-", "/", "*", "(", ")", "$" };
	vector<string> nonterminals = { "E", "J", "T", "U", "F" };

	int rules[5][8] = {
		 1, -1, -1, -1, -1,  1, 0, 0,
		-1,  2,  3, -1, -1, -1, 0, 0,
		 4,  0,  0, -1, -1,  4, 0, 0,
		-1,  0,  0,  6,  5, -1, 0, 0,
		 8,  0,  0,  0,  0,  7, 0, 0
	};
	int index;	// index will keep track of where you are in the lexemes/tokens
};
