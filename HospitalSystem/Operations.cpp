#include "pch.h"
#include "Operations.h"
/*
Operations(int appointment_id, std::string& operation_id, std::string& name,
		std::string& operating_room, std::string& status, std::string& employee_number2,
		std::string& s_date, std::string& e_date, std::string& notes
	);
	int getAppointment_id();
	std::string getOperation_id();
	std::string getName();
	std::string Operating_room();
	std::string getStatus();
	std::string getEmployee_number2();
	std::string getS_date();
	std::string getE_date();
	std::string getNotes();
*/
Operations::Operations(int appointment_id, std::string& operation_id, std::string& name,
	std::string& operating_room, std::string& status, std::string& employee_number2,
	std::string& s_date, std::string& e_date, std::string& notes) {
	this->appointment_id = appointment_id;
	this->operation_id = operation_id;
	this->name = name;
	this->operating_room = operating_room;
	this->status = status;
	this->employee_number2 = employee_number2;
	this->s_date = s_date;
	this->e_date = e_date;
	this->notes = notes;
}

int Operations::getAppointment_id() {
	return this->appointment_id;
}
std::string Operations::getOperation_id() {
	return this->operation_id;
}
std::string Operations::getName() {
	return this->name;
}
std::string Operations::Operating_room() {
	return this->operating_room;
}
std::string Operations::getStatus() {
	return this->status;
}
std::string Operations::getEmployee_number2() {
	return this->status;
}
std::string Operations::getS_date() {
	return this->s_date;
}
std::string Operations::getE_date() {
	return this->e_date;
}
std::string Operations::getNotes() {
	return this->notes;
}