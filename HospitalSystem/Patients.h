#pragma once
#include <string>
class Patients
{
private:
	std::string residentNumber;
	std::string name;
	std::string phone;
	std::string address;
public:
	Patients(std::string residentNumber, std::string name, 
		std::string phone, std::string address);
	std::string getName();
	std::string getPhone();
	std::string getAddress();
	std::string getBirthday();


};

