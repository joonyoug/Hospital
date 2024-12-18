#include "pch.h"
#include "WaitPatient.h"
WaitPatient::WaitPatient(std::string name, std::string residentNUmber) {
	
	this->name = name;
	this->residentNumber = residentNUmber;
}

std::string WaitPatient::getName() {
	return name;
}
std::string WaitPatient::getResidentNumber() {
	return residentNumber;
}

