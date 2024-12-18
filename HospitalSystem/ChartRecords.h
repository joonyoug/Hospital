#pragma once
#include <string>
class ChartRecords
{
private:
	std::string residentNumber;
	std::string employeeNumber;
	std::string date;
	std::string cc;
	std::string manifestation;
public:
	ChartRecords(std::string &residentNumber, std::string& employeeNumber,
		std::string& date, std::string& cc,
		std::string &manifestation);
	std::string getResidentNumber();
	std::string getEmployeeNumber();
	std::string getDate();
	std::string getCC();
	std::string getManifestation();
};



