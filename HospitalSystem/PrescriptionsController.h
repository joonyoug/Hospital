#pragma once
#include "PrescriptionsDB.h"
#include <string>
class PrescriptionsController
{

public:
	bool addPrescriptions(std::string residentNumber, std::string employee_number
		, std::string date, std::string method,std::string name);







};

