#pragma once
#include <string>
class WaitPatient
{
private:
	std::string name;
	std::string residentNumber;
	

public:
	WaitPatient(std::string name, std::string residentNumber);
	std::string getName();
	std::string getResidentNumber();

};

