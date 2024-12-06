#include "pch.h"
#include "Vaccinations.h"
/*
Vaccinations(std::string resident_number, std::string date,
		std::string v_name, std::string d_name, int th,
		std::string status, std::string reason);
	std::string getResidentNumber();
	std::string getDate();
	std::string getvName();
	std::string getdName();
	int getTh();
	std::string getStatus();
	std::string getReason();

*/


Vaccinations::Vaccinations(std::string &resident_number, std::string &date,
	std::string &v_name, std::string &d_name, int th,
	std::string &status, std::string &reason) {

	this->residentNumber = resident_number;
	this->date = date;
	this->vName = v_name;
	this->dName = d_name;
	this->th = th;
	this->status = status;
	this->reason = reason;


}

std::string Vaccinations::getResidentNumber() {
	return this->residentNumber;
}
std::string Vaccinations::getDate() {
	return this->date;
}
std::string Vaccinations::getvName() {
	return this->vName;
}
std::string Vaccinations::getdName() {
	return this->dName;
}
int Vaccinations::getTh() {
	return this->th;
}
std::string Vaccinations::getStatus() {
	return this->status;
}
std::string Vaccinations::getReason() {
	return this->reason;
}