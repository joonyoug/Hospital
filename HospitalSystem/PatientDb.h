#pragma once
#include <mysql/jdbc.h>
#include "Patient.h"
#include <nlohmann/json.hpp> 
#include "DBconnect.h"
#include <fstream>
class PatientDb:public DBconnect
{
public:
	PatientDb();
	~PatientDb();
	bool addPatient(Patient patient);
	Patient selectPatient(std::string residentNumber);
	Patient searchPatient(std::string Name);
};

