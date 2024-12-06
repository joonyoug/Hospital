#include "pch.h"
#include "allergy.h"
/*
Allergy(std::string& resident_number, std::string& category,
		std::string& allergen, std::string& reaction, int severity,
		std::string& record_date);
	std::string getResidentNumber();
	std::string getCategory();
	std::string getAllergen();
	std::string getRecation();
	int getSeverity();
	std::string getRocordDate();
*/

Allergy::Allergy(std::string& resident_number, std::string& category,
	std::string& allergen, std::string& reaction, int severity,
	std::string& record_date) {
	this->residentNumber = resident_number;
	this->category = category;
	this->allergen = allergen;
	this->reaction = reaction;
	this->severity = severity;
	this->record_date = record_date;
}

std::string Allergy::getResidentNumber() {
	return this->residentNumber;
}
std::string Allergy::getCategory() {
	return this->category;
}
std::string Allergy::getAllergen() {
	return this->allergen;
}
std::string Allergy::getRecation() {
	return this->reaction;
}
int Allergy::getSeverity() {
	return this->severity;
}
std::string Allergy::getRocordDate() {
	return this->record_date;
}