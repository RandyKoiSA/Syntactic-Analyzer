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
	void ruleOne();   // TJ
	void ruleTwo();   // +TJ
	void ruleThree(); // -TJ
	void ruleFour();  // FU
	void ruleFive();  // *FU
	void ruleSix();   // /FU
	void ruleSeven(); // (E)
	void ruleEight(); // i
	void ruleZero();  // EPSILON
	void ruleError(); // ERROR

	// load lexemes / tokens for the lexeranalyzer
	void loadLexemes(vector<string>);
	void loadTokens(vector<string>);
	// get next lexeme / token
	void lexer();
	// testable methods
	void printLexemes();
	void printTokens();

private:
	vector<string> lexemes;
	vector<string> tokens;
	stack <string> syntaxStack; 
	map<string, int> conversionTerminals;
	map<string, int> conversionNonTerminals;
	int rules[5][8] = {
		 1, -1, -1, -1, -1,  1, 0, 0,
		-1,  2,  3, -1, -1, -1, 0, 0,
		 4,  0,  0, -1, -1,  4, 0, 0,
		-1,  0,  0,  6,  5, -1, 0, 0,
		 8,  0,  0,  0,  0,  7, 0, 0
	};
	int index;	// index will keep track of where you are in the lexeme/token

	void makeConversions();
};
