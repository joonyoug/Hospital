#pragma once
#include "PatientDb.h"
#include "Patient.h"
#include "PatientDto.h"
class PatientController
{
public:
	bool addPatient(const std::string& residentNumber, const std::string& name, const std::string& phone,
        const std::string& gender, const std::string& address, std::string& emergencyNumber, const std::string& dosingList,
        const std::string& bloodType);
    PatientDto searchPatient(std::string name);
    PatientDto selectPatient(std::string residentNumber);


};

