#include "pch.h"
#include "ChartRecords.h"

// ������ ���� (���� �Ű����� ���)
ChartRecords::ChartRecords(std::string& residentNumber, std::string& employeeNumber,
    std::string& date, std::string& KdcCode, std::string& diagnose,
    std::string& cc, std::string& manifestation)
    : residentNumber(residentNumber), employeeNumber(employeeNumber),
    date(date), KdcCode(KdcCode), diagnose(diagnose), cc(cc),
    manifestation(manifestation) {
}

// ��� �Լ� ����
std::string ChartRecords::getResidentNumber() {
    return residentNumber;
}

std::string ChartRecords::getEmployeeNumber() {
    return employeeNumber;
}

std::string ChartRecords::getDate() {
    return date;
}

std::string ChartRecords::getKdcCOde() {
    return KdcCode;
}

std::string ChartRecords::getDiagnose() {
    return diagnose;
}

std::string ChartRecords::getCC() {
    return cc;
}

std::string ChartRecords::getManifestation() {
    return manifestation;
}

