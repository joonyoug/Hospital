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
<<<<<<< HEAD
=======
	std::string name;
>>>>>>> upstream/dev
	float daily_dosage;
	int frequency;
	int duration;
	std::string text;

	Prescriptions(std::string& resident_number, std::string& employee_numner, 
<<<<<<< HEAD
		std::string& date, std::string& method, std::string& dosage,
		float daily_dosage, int frequency, int duration,std::string text);
=======
		std::string& date, std::string& method,std::string & name);
>>>>>>> upstream/dev

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

