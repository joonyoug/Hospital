#pragma once
#include <string>
#include <mysql/jdbc.h>
#include <vector>
#include "Appointment.h"
#include "AppointmentDB.h"
class AppointmentController
{
public:
	std::vector<AppointmentDto> selectAppointment(std::string employeeNumber);
	bool addAppointment(std::string residentNUmber,std::string name, std::string date,
		std::string employeeNumber, std::string CC);
};

