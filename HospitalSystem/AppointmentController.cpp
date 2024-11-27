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