#pragma once
#include <mysql/jdbc.h>
#include <vector>
#include "AppointmentDto.h"
#include <nlohmann/json.hpp>
#include "DBconnect.h"
class AppointmentDB :public DBconnect
{

public:
	AppointmentDB();
	~AppointmentDB();
	std::vector<AppointmentDto>todayAppointment(std::string doctorId);
	
	bool addAppointment(
		std::string residentNUmber, std::string name, std::string date,
		std::string employeeNumber, std::string CC);


};

