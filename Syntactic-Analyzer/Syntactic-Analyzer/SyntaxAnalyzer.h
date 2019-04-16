#pragma once
#include <stack>
#include <vector>
#include <string>

using namespace std;
class SyntaxAnalyzer {
public:
	SyntaxAnalyzer();
	void loadLexemes(vector<string>);
	void loadTokens(vector<string>);
	void printLexemes();
	void printTokens();
	void lexer();
private:
	vector<string> lexemes;
	vector<string> tokens;
	stack <string> syntaxStack; 
	
};
