#pragma once
#include "WaitPatient.h"
#include "DBconnect.h"
#include <vector>
class WaitPatientDB: public DBconnect
{
public:
	std::vector<WaitPatient> selectWait();
	bool deleteWait(std::string residentNumber);
	bool addWait(std::string name, std::string residentNumber,std::string s);
	
	
	
	
	
};

