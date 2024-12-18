#include "pch.h"
#include "Prescriptions.h"
/*
Prescriptions(std::string& resident_number, std::string& employee_numner,
		std::string& date, std::string& method, std::string& dosage,
		float daily_dosage, int frequency, int duration);

	std::string getResidentNumber();
	std::string getEmployeeNumber();
	std::string getDate();
	std::string getMethod();
	std::string getDosage();
	float getDailyDosage();
	int getFrequency();
	int getDuration();
*/
Prescriptions::Prescriptions(std::string& resident_number, std::string& employee_numner,
<<<<<<< HEAD
	std::string& date, std::string& method, std::string& dosage,
	float daily_dosage, int frequency, int duration,std::string text) :resident_number(resident_number), employee_number(employee_numner),
	date(date), method(method), dosage(dosage), daily_dosage(daily_dosage), frequency(frequency), duration(duration) ,text(text){
}
=======
	std::string& date, std::string& method,std::string&name) :resident_number(resident_number), employee_number(employee_numner),
	date(date), method(method) ,name(name){
};

>>>>>>> upstream/dev

std::string Prescriptions::getResidentNumber() {
	return this->resident_number;
}
std::string Prescriptions::getEmployeeNumber() {
	return this->employee_number;
}
std::string Prescriptions::getDate() {
	return this->date;
}

/*
	std::string getMethod();
	std::string getDosage();
	float getDailyDosage();
	int getFrequency();
	int getDuration();
*/
std::string Prescriptions::getMethod() {
	return this->method;
}
std::string Prescriptions::getDosage() {
	return this->dosage;
}
int Prescriptions::getFrequency() {
	return this->frequency;
}
float Prescriptions::getDailyDosage() {
	return this->daily_dosage;
}
int Prescriptions::getDuration() {
	return this->duration;
}
std::string Prescriptions::getText() {
	return text;
}








