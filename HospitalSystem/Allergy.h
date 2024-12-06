#pragma once
#include <string>

class Allergy
{
private:
	std::string residentNumber;
	std::string category;
	std::string allergen;
	std::string reaction;
	int severity;
	std::string record_date;

public:
	Allergy(std::string& resident_number, std::string& category,
		std::string& allergen, std::string& reaction, int severity,
		std::string& record_date);
	std::string getResidentNumber();
	std::string getCategory();
	std::string getAllergen();
	std::string getRecation();
	int getSeverity();
	std::string getRocordDate();
};
