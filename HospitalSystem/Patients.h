#pragma once
#include <string>
class Patients
{
private:
	std::string birthday;
	std::string name;
	std::string phone;
	std::string address;
public:
	Patients(std::string birthday, std::string name, 
		std::string phone, std::string address);
	std::string getName();
	std::string getPhone();
	std::string getAddress();
	std::string getBirthday();


};

