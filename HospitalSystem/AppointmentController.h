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
	




};

