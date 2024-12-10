#include "pch.h"
#include "Doctor.h"

// 생성자 정의 (참조 매개변수 사용)
Doctor::Doctor(std::string& employeeNumber, std::string& password, std::string& name,
    std::string& licenseId, std::string& department, std::string& departmentCode,
    std::string& speicalty, std::string& phoneNumber)
    : employeeNumber(employeeNumber), password(password), name(name),
    licenseId(licenseId), department(department), departmentCode(departmentCode),
    speicalty(speicalty), phoneNumber(phoneNumber) {
}

// 멤버 함수 정의
std::string Doctor::getEmployeeNumber() {
    return employeeNumber;
}

std::string Doctor::getPassword() {
    return password;
}

std::string Doctor::getName() {
    return name;
}

std::string Doctor::getlicenseId() {
    return licenseId;
}

std::string Doctor::getDepatment() {
    return department;
}

std::string Doctor::getDepartmentCode() {
    return departmentCode;
}

std::string Doctor::getSpeicalty() {
    return speicalty;
}

std::string Doctor::getPhoneNumber() {
    return phoneNumber;
}
