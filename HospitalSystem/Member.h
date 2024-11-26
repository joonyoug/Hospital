
#pragma once
#include<string>
class Member
{
private:
	std::string id;
	std::string name;
	std::string password;
	std::string phoneNumber;
	std::string employeeNumber;
public:
	Member();
	Member(const std::string id, const std::string pw,
		const std::string name, std::string phoneNumber, std::string employeeNumber);
	std::string getId() const;
	std::string getName() const;
	std::string getPassword() const;
	std::string getEmployeeNumber() const;
	std::string getPhoneNumber() const;
};

