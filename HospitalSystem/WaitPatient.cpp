#include "pch.h"
#include "WaitPatient.h"
WaitPatient::WaitPatient(std::string name, std::string residentNUmber,std::string symtons) {
	
	this->name = name;
	this->residentNumber = residentNUmber;
	this->symtons = symtons;
}

std::string WaitPatient::getName() {
	return name;
}
std::string WaitPatient::getResidentNumber() {
	return residentNumber;
}
std::string WaitPatient::getSymtones() {
	return symtons;
}

