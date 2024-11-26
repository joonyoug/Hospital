#include "pch.h"
#include "Member.h"
/*

public:
Member();
Member(const std::string id, const std::string pw, const std::string name);
std::string getId();
std::string getName();
std::string getPassword();
};

*/

Member::Member() {}
Member::Member(const std::string id, const std::string pw,
	const std::string name,
	const std::string phoneNumber,std::string employeeNumber) {
	this->id = id;
	this->password = pw;
	this->name = name;
	this->phoneNumber = phoneNumber;
	this->employeeNumber = employeeNumber;
}
std::string Member::getName() const{
	return this->name;
}
std::string Member::getId() const{
	return this->id;
}
std::string Member::getPassword() const{
	return this->password;
}
std::string Member::getPhoneNumber() const {
	return this->phoneNumber;
}
std::string Member::getEmployeeNumber() const {
	return this->employeeNumber;
}