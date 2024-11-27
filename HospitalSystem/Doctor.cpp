#include "pch.h"
#include "Doctor.h"
/*

public:
Doctor();
Doctor(const std::string id, const std::string pw, const std::string name);
std::string getId();
std::string getName();
std::string getPassword();
};

*/

Doctor::Doctor() {}
Doctor::Doctor(const std::string id, const std::string pw,
	const std::string name,
	const std::string phoneNumber,std::string employeeNumber) {
	this->id = id;
	this->password = pw;
	this->name = name;
	this->phoneNumber = phoneNumber;
	this->employeeNumber = employeeNumber;
}
std::string Doctor::getName() const{
	return this->name;
}
std::string Doctor::getId() const{
	return this->id;
}
std::string Doctor::getPassword() const{
	return this->password;
}
std::string Doctor::getPhoneNumber() const {
	return this->phoneNumber;
}
std::string Doctor::getEmployeeNumber() const {
	return this->employeeNumber;
}