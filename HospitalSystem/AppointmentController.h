#pragma once
#include <string>
#include <mysql/jdbc.h>
#include <vector>
#include "Appointment.h"
#include "AppointmentDB.h"
class AppointmentController
{
public:
	std::vector<AppointmentDto> selectAppointment(std::string doctorId);
	bool addAppointment(std::string patientPhone, std::string appointDate, std::string time,
		std::string doctorId, std::string sympton);
};

