#pragma once
#include <string>
class Dcode
{
private:
	std::string kcd_code;
	std::string name;
public:
	Dcode(std::string& kcd, std::string& name);
	std::string getKcdcode();
	std::string getName();
	void setKcdCode(std::string kcd_cod);
	void setName(std::string name);


};

