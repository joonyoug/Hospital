#include "pch.h"
#include "MedicalHistory.h"
/*
MedicalHistory(std::string diagnois, std::string treatment,
		std::string prescription, std::string visitDay);

	std::string getDiagnois();
	std::string getTreatment();
	std::string getPrescription();
	std::string getVisitDay();
*/
MedicalHistory::MedicalHistory(std::string diagnois, std::string treatment,
	std::string prescription, std::string visitDay) {
	this->diagnois = diagnois;
	this->treatment = treatment;
	this->prescription = prescription;
	this->visitDay = visitDay;
}
std::string MedicalHistory::getDiagnois() {
	return this->diagnois;
}
std::string MedicalHistory::getTreatment() {
	return this->treatment;
}
std::string MedicalHistory::getPrescription() {
	return this->prescription;
}
std::string MedicalHistory::getVisitDay() {
	return this->visitDay;
}

