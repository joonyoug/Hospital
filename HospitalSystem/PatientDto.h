#pragma once
#include <string>
class PatientDto
{
public:
	std::string residentNumber;
	std::string name;
	std::string phone;
	std::string gender;
	std::string address;
<<<<<<< HEAD
	int emergencyNumber;
=======
	std::string emergencyNumber;
>>>>>>> upstream/dev
	std::string dosingList;
	std::string bloodType;
	PatientDto::PatientDto() {}
};

