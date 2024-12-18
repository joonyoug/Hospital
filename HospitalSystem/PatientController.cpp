#include "pch.h"
#include "PatientController.h"
#include "Patient.h"



PatientDto PatientController::searchPatient(std::string name) {
    PatientDb db;

    Patient patient = db.searchPatient(name);


    PatientDto dto;

    dto.address = patient.getAddress();
    dto.bloodType = patient.getBloodType();
    dto.dosingList = patient.getBloodType();
    dto.gender = patient.getGender();
    dto.name = patient.getName();
    dto.phone = patient.getPhone();
    dto.residentNumber = patient.getResidentNumber();
    return dto;

}
PatientDto PatientController::selectPatient(std::string residentNumber) {
    PatientDb db;

    Patient patient = db.selectPatient(residentNumber);


    PatientDto dto;

    dto.address = patient.getAddress();
    dto.bloodType = patient.getBloodType();
    dto.dosingList = patient.getBloodType();
    dto.gender = patient.getGender();
    dto.name = patient.getName();
    dto.phone = patient.getPhone();
    dto.residentNumber = patient.getResidentNumber();
    return dto;

}

bool PatientController::addPatient(const std::string& residentNumber, const std::string& name, const std::string& phone,
    const std::string& gender, const std::string& address, int emergencyNumber, const std::string& dosingList,
    const std::string& bloodType) {

  
    PatientDb db; 
  
    Patient patient(residentNumber, name, phone, gender, address, emergencyNumber, dosingList, bloodType);

    // ȯ�� ������ �����ͺ��̽��� �߰�
    if (db.addPatient(patient)) {
        return true;  // ȯ�� ��� ����
    }
    else {
        return false;  // ȯ�� ��� ����
    }
}
