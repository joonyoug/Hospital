#include "pch.h"
#include "ChartRecords.h"

// 생성자 정의 (참조 매개변수 사용)
ChartRecords::ChartRecords(std::string& residentNumber, std::string& employeeNumber,
    std::string& date,
    std::string& cc, std::string& manifestation)
    : residentNumber(residentNumber), employeeNumber(employeeNumber),
    date(date), cc(cc),
    manifestation(manifestation) {
}

// 멤버 함수 정의
std::string ChartRecords::getResidentNumber() {
    return residentNumber;
}

std::string ChartRecords::getEmployeeNumber() {
    return employeeNumber;
}

std::string ChartRecords::getDate() {
    return date;
}


std::string ChartRecords::getCC() {
    return cc;
}

std::string ChartRecords::getManifestation() {
    return manifestation;
}

