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
bool AppointmentController::addAppointment(std::string patientPhone,
	std::string appointDate, std::string doctorId, std::string sympton) {
	AppointmentDB db;
	if (db.Connect()) {
		return db.addAppointment(patientPhone, appointDate,doctorId, sympton);
	}
	return false;
}