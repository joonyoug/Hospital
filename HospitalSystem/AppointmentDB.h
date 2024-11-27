#pragma once
#include <mysql/jdbc.h>
#include <vector>
#include "AppointmentDto.h"
class AppointmentDB
{
private:
	sql::Connection *con;
	sql::Statement* stmt;
public:
	AppointmentDB();
	~AppointmentDB();
	std::vector<AppointmentDto>todayAppointment(std::string doctorId);
	bool Connect();

};

