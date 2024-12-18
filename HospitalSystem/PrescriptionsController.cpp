#include "pch.h"
#include "PrescriptionsController.h"


bool PrescriptionsController::addPrescriptions(std::string residentNumber, std::string employee_number
	, std::string date, std::string method, std::string dosage, float daily_dosage,
	int frequency, int duration, std::string notes) {
	PrescriptionsDB db;	

	if (db.addPrescriptions(residentNumber, employee_number, date, method, dosage, daily_dosage, frequency, duration, notes)) {
		return true;
	}
	else {
		return false;
	}
	

}