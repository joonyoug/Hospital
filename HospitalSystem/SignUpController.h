#pragma once
#include "DatabaseManager.h"
class SignUpController
{
public:
	bool SignUP(std::string id, std::string pw,
		std::string name,std::string phoneNumber,std::string employeeNumber);
	bool checkId(std::string id);

};

