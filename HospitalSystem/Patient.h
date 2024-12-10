#pragma once
#include <string>
using namespace std;
class Patient
{
private:
	std::string residentNumber;
	std::string name;
	std::string phone;
	std::string gender;
	std::string address;
	int emergencyNumber;
	std::string dosingList;
	std::string bloodType;
public:
	Patient::Patient();
	Patient::Patient(const std::string& residentNumber, const std::string& name, const std::string& phone,
		const std::string& gender, const std::string& address, int emergencyNumber, const std::string& dosingList,
		const std::string& bloodType);
	std::string getName();
	std::string getPhone();
	std::string getAddress();
	std::string getResidentNumber();
	std::string getDosingList();
	std::string getBloodType();
	std::string getGender();
	int getEmergencyNumber();

};

