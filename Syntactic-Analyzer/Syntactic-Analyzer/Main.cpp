#include <stack>
#include <string>
#include <iostream>
#include <sstream>
#include "SyntaxAnalyzer.h"
#include "LexerAnalyzer.h"

void helpDisplay();

int main(int argc, char* arg[]) {
	std::string input;
	while (input != "quit") {
		std::cout << ">> Enter File Name: ";
		std::getline(std::cin, input);

		if (input == "help") helpDisplay();
		else {
			LexerAnalyzer la;
			la.loadTextFile(input);
			la.analyzeLexeme();

			SyntaxAnalyzer sa;
			sa.loadLexemes(la.getLexemes());
			sa.loadTokens(la.getTokens());

			sa.printLexemes();
			sa.printTokens();
		}
	}
	return 0;
}

void helpDisplay() {
	std::cout << "*****HELP*****" << std::endl;
	std::cout << "enter a text file with the extension to read";
}