#pragma once
#include <string>
class AppointmentDto
{
public:
	AppointmentDto(std::string doctorid, std::string patientid,
		std::string appointDate, std::string symptons);
	
	std::string doctorid;
	std::string patientid;
	std::string appointDate;
	std::string symptons;
};

