#include "pch.h"
#include "Appointment.h"
#include <mysql/jdbc.h>
/*
	Appointment(std::string doctorid, std::string patientid,
	std::string appointDate, std::string visitedDate,std::string symptons);
	std::string getVisitDate();
	std::string getAppointDate();
	std::string getPatientid();
	std::string getDoctorid();
	std::string getSympthons();
	std::vector<Appointment> todayAppointment(std::string doctorid);
*/

Appointment::Appointment(std::string doctorid, std::string patientid,
	std::string appointDate, std::string symptons) {
	this->doctorid = doctorid;
	this->appointDate = appointDate;
	this->patientid = patientid;
	this->symptons = symptons;

}
std::string Appointment::getDoctorid() {
	return this->doctorid;
}
std::string Appointment::getSympthons() {
	return this->symptons;
}
std::string Appointment::getPatientid() {
	return this->patientid;
}
std::string Appointment::getAppointDate() {
	return this->appointDate;
}
Appointment::Appointment() {
}


