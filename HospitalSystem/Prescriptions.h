#pragma once
#include <string>
class Prescriptions
{
private :
	std::string resident_number;
	std::string employee_number;
	std::string date;
	std::string method;
	std::string dosage;
	std::string name;
	float daily_dosage;
	int frequency;
	int duration;
	std::string text;

	Prescriptions(std::string& resident_number, std::string& employee_numner, 
		std::string& date, std::string& method,std::string & name);

	std::string getResidentNumber();
	std::string getEmployeeNumber();
	std::string getDate();
	std::string getMethod();
	std::string getDosage();
	float getDailyDosage();
	int getFrequency();
	int getDuration();
	std::string getText();





};

