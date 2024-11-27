#pragma once
#include <string>
#include <vector>
class Appointment
{
private:
	std::string doctorid;
	std::string patientid;
	std::string appointDate;
	std::string symptons;
public:
	Appointment();
	Appointment(std::string doctorid, std::string patientid,
		std::string appointDate,std::string symptons);
	std::string getAppointDate();
	std::string getPatientid();
	std::string getDoctorid();
	std::string getSympthons();
	std::vector<Appointment> todayAppointment(std::string doctorid);


};

