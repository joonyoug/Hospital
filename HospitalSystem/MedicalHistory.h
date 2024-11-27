#pragma once
#include <string>
class MedicalHistory
{
private:
	std::string diagnois;
	std::string treatment;
	std::string prescription;
	std::string visitDay;

public:
	MedicalHistory(std::string diagnois, std::string treatment,
		std::string prescription, std::string visitDay);
	
	std::string getDiagnois();
	std::string getTreatment();
	std::string getPrescription();
	std::string getVisitDay();
};

