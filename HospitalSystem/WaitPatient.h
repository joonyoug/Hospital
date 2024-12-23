#pragma once
#include <string>
class WaitPatient
{
private:
	std::string name;
	std::string residentNumber;
	std::string symtons;


public:
	WaitPatient(std::string name, std::string residentNumber,std::string symtons);
	std::string getName();
	std::string getResidentNumber();
	std::string getSymtones();


};

