
#pragma once
#include<string>
class Doctor
{
private:
	std::string employeeNumber;
	std::string password;
	std::string name;
	std::string licenseId;
	std::string department;
	std::string departmentCode;
	std::string speicalty;
	std::string role;
	std::string phoneNumber;
public:
	Doctor(std::string &employeeNumber, std::string& password, std::string &name,
		std::string& licenseId, std::string &department, std::string& departmentCode,
		std::string &speicalty,
		std::string& phoneNumber
	);
	std::string getEmployeeNumber();
	std::string getPassword();
	std::string getName();
	std::string getlicenseId();
	std::string getDepatment();
	std::string getDepartmentCode();
	std::string getSpeicalty();
	std::string getPhoneNumber();

	
};

