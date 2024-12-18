#include "pch.h"
#include "AppointmentController.h"
#include "AppointmentDto.h"
#include "vector"



std::vector<AppointmentDto> AppointmentController:: selectAppointment(std::string doctorId) {
	AppointmentDB db;
	if (db.Connect()) {
		return db.todayAppointment(doctorId);
	}
}
bool AppointmentController::addAppointment(std::string residentNUmber, std::string name, std::string date,
	std::string employeeNumber, std::string CC) {
	AppointmentDB db;
	if (db.Connect()) {
		return db.addAppointment(residentNUmber, name,date, employeeNumber, CC);
	}
	return false;
}
std::vector<AppointmentDto> AppointmentController::dayAppointment(std::string doctorId, std::string date) {
	AppointmentDB db;

	if (db.Connect()) {
		return db.DayAppointment(doctorId, date);
	}
}