#include "pch.h"
#include "Patients.h"
/*

Patients(std::string birthday, std::string name,
std::string phone, std::string address);
std::string getName();
std::string getPhone();
std::string getAddress();
std::string getBirthday();
*/

Patients::Patients(std::string birthday, std::string name,
	std::string phone, std::string address) {
	this->birthday = birthday;
	this->name = name;
	this->phone = phone;
	this->address = address;
}
std::string Patients::getName() {
	return this->name;
}
std::string Patients::getPhone() {
	return this->phone;
}
std::string Patients::getAddress() {
	return this->address;
}
std::string Patients::getBirthday() {
	return this->birthday;
}




