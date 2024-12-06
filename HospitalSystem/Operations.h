#pragma once
#include <string>

class Operations
{
private:
	int appointment_id;
	std::string operation_id;
	std::string name;
	std::string operating_room;
	std::string status;
	std::string employee_number2;
	std::string s_date;
	std::string e_date;
	std::string notes;

public:
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
};

