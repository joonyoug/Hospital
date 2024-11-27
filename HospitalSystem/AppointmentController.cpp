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
	std::string appointDate, std::string time,
	std::string doctorId, std::string sympton) {
	AppointmentDB db;
	if (db.Connect()) {
		db.addAppointment(patientPhone, appointDate, time, doctorId, sympton);
	}	
}