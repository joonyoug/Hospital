#pragma once
#include <string>
class ChartRecords
{
private:
	int chart_id;
	std::string residentNumber;
	std::string employeeNumber;
	std::string date;
	std::string KdcCode;
	std::string diagnose;
	std::string cc;
	std::string manifestation;
public:
	ChartRecords(std::string &residentNumber, std::string& employeeNumber,
		std::string& date, std::string& KdcCode, std::string& diagnose, std::string& cc,
		std::string &manifestation);
	std::string getResidentNumber();
	std::string getEmployeeNumber();
	std::string getDate();
	std::string getKdcCOde();
	std::string getDiagnose();
	std::string getCC();
	std::string getManifestation();
};



