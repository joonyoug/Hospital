#include "pch.h"
#include "Patient.h"

Patient::Patient() {}
// 생성자 정의 (참조 매개변수 사용)
Patient::Patient(const std::string& residentNumber, const std::string& name, const std::string& phone,
    const std::string& gender, const std::string& address,const std::string &emergencyNumber, const std::string& dosingList,
    const std::string& bloodType)
    : residentNumber(residentNumber), name(name), phone(phone),
    gender(gender), address(address), dosingList(dosingList),
    bloodType(bloodType), emergencyNumber(emergencyNumber) {
}


// 멤버 함수 정의
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
std::string Patient::getEmergencyNumber() {
    return emergencyNumber;
}