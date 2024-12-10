#include "pch.h"
#include "Patient.h"

Patient::Patient() {}
// ������ ���� (���� �Ű����� ���)
Patient::Patient(const std::string& residentNumber, const std::string& name, const std::string& phone,
    const std::string& gender, const std::string& address, int emergencyNumber, const std::string& dosingList,
    const std::string& bloodType)
    : residentNumber(residentNumber), name(name), phone(phone),
    gender(gender), address(address), dosingList(dosingList),
    bloodType(bloodType), emergencyNumber(emergencyNumber) {
}


// ��� �Լ� ����
std::string Patient::getName() {
    return name;
}

std::string Patient::getPhone() {
    return phone;
}

std::string Patient::getAddress() {
    return address;
}

std::string Patient::getResidentNumber() {
    return residentNumber;
}

std::string Patient::getDosingList() {
    return dosingList;
}

std::string Patient::getBloodType() {
    return bloodType;
}
std::string Patient::getGender() {
    return gender;
}
int Patient::getEmergencyNumber() {
    return emergencyNumber;
}