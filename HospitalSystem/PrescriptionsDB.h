#pragma once
#include "DBconnect.h"
#include <string>
class PrescriptionsDB :public DBconnect
{
public:
	bool addPrescriptions(std::string residentNumber, std::string employee_number
		, std::string date, std::string method,std::string name);



};

