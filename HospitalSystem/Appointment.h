#pragma once
#include <string>
#include <vector>
class Appointment
{/*
 appointment_id,resident_number
	employee_number ,date,CC
 
 */
private:
	
	std::string residentNumber;
	std::string employeeNumber;
	std::string date;
	std::string cc;	
public:
	Appointment(std::string& residentNumber, std::string& employeeNumber, std::string& date,std::string& cc );
	std::string getResidentNumber();
	std::string getEmployeeNumber();
	std::string getDate();
	std::string getCC();
};

