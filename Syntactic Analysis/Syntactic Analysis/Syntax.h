#pragma once
#include <stack>
#include <string>
class Syntax {
public:
	Syntax();
	
private:
	std::stack <std::string> syntaxStack;
};