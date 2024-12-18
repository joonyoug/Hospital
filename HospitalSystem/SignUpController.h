#pragma once
#include "DatabaseManager.h"

class SignUpController
{
public:
	bool SignUP(
		std::string& employeeNumber, std::string& password, std::string& name,
		std::string& licenseId, std::string& department, std::string& departmentCode,
		std::string& speicalty,
		std::string& phoneNumber
		);
	bool checkId(std::string& employeeNumber);

};

