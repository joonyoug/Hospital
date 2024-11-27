#include "pch.h"
#include "AppointmentDto.h"

AppointmentDto::AppointmentDto(std::string doctorid, std::string patientid,
	std::string appointDate, std::string symptons) {
	this->doctorid = doctorid;
	this->appointDate = appointDate;
	this->patientid = patientid;
	this->symptons = symptons;

}