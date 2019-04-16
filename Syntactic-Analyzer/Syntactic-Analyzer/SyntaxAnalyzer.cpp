#include <stack>
#include <string>
#include <vector>
#include <iostream>
#include "SyntaxAnalyzer.h"

SyntaxAnalyzer::SyntaxAnalyzer() {
	syntaxStack = std::stack<std::string>();
	syntaxStack.push("$");
	lexemes = std::vector<std::string>();
	tokens = std::vector<std::string>();
}

void SyntaxAnalyzer::loadLexemes(std::vector<std::string> lexemes) {
	this->lexemes = lexemes;
}

void SyntaxAnalyzer::loadTokens(std::vector < std::string> tokens) {
	this->tokens = tokens;
}

void SyntaxAnalyzer::printLexemes() {
	for (int i = 0; i < lexemes.size(); i++) {
		std::cout << lexemes[i] << std::endl;
	}
}

void SyntaxAnalyzer::printTokens() {
	for (int i = 0; i < tokens.size(); i++) {
		std::cout << tokens[i] << std::endl;
	}
}

void SyntaxAnalyzer::lexer() {

}