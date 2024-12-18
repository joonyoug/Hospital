#include "pch.h"
#include "PrescriptionsController.h"


bool PrescriptionsController::addPrescriptions(std::string residentNumber, std::string employee_number
	, std::string date, std::string method,std::string name) {
	PrescriptionsDB db;	

	if (db.addPrescriptions(residentNumber, employee_number, date, method,name)) {
		return true;
	}
	else {
		return false;
	}
	

}