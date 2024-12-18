#include "pch.h"
#include "Appointment.h"

// ������ ����
Appointment::Appointment(std::string& residentNumber, std::string& employeeNumber,
    std::string& date, std::string& cc)
    : residentNumber(residentNumber), employeeNumber(employeeNumber),
    date(date), cc(cc) {
}

// ��� �Լ� ����
std::string Appointment::getResidentNumber() {
    return residentNumber;
}

std::string Appointment::getEmployeeNumber() {
    return employeeNumber;
}

std::string Appointment::getDate() {
    return date;
}

std::string Appointment::getCC() {
    return cc;
}
