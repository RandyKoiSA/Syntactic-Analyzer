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

enum productionRule {
	ruleNeg, ruleZero, ruleOne, ruleTwo, ruleThree, ruleFour,
	ruleFive, ruleSix, ruleSeven, ruleEight, ruleNine
};

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

	productionRule rules[6][9] = {
		  ruleOne,   ruleNeg,  ruleNeg, ruleNeg, ruleNeg,   ruleNeg,  ruleNeg,  ruleNeg, ruleNeg,
		  ruleTwo,   ruleNeg,  ruleNeg, ruleNeg, ruleNeg,   ruleTwo,  ruleNeg,  ruleNeg, ruleNeg,
		  ruleNeg, ruleThree, ruleFour, ruleNeg, ruleNeg,   ruleNeg, ruleZero, ruleZero, ruleNeg,
		 ruleFive,   ruleNeg,  ruleNeg, ruleNeg, ruleNeg,  ruleFive, ruleZero, ruleZero, ruleNeg,
		  ruleNeg,  ruleZero, ruleZero, ruleSix, ruleSeven, ruleNeg, ruleZero, ruleZero, ruleNeg,
		 ruleNine,   ruleNeg,  ruleNeg, ruleNeg, ruleNeg, ruleEight,  ruleNeg,  ruleNeg, ruleNeg
	};
	int index;	// index will keep track of where you are in the lexemes/tokens
};
