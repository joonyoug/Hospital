#pragma once
#include <string>
#include <vector>

class Mcode
{
private:
	std::string code;
	std::string name;

public:
	Mcode(std::string &code, std::string& name);
	std::string getCode();
	std::string getName();






};

