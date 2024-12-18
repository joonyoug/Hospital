#pragma once
#include "DBconnect.h"
#include <string>
class PrescriptionsDB :public DBconnect
{
public:
	bool addPrescriptions(std::string residentNumber, std::string employee_number
<<<<<<< HEAD
		, std::string date, std::string method, std::string dosage, float daily_dosage,
		int frequency, int duration, std::string notes);
=======
		, std::string date, std::string method,std::string name);
>>>>>>> upstream/dev



};

