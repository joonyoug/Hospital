#include "pch.h"
#include "SignUpController.h"
#include "Doctor.h"
/*
	ȸ������ 
	DB�� insertQuery ȣ�� ������ true
	���н� false;
	Doctor(std::string &employeeNumber, std::string& password, std::string &name,
		std::string& licenseId, std::string &department, std::string& departmentCode,
		std::string &speicalty,
		std::string& phoneNumber
	);
*/





bool SignUpController::SignUP(std::string& employeeNumber, std::string& password, std::string& name,
	std::string& licenseId, std::string& department, std::string& departmentCode,
	std::string& speicalty,
	std::string& phoneNumber) {
	if (employeeNumber.empty() || password.empty() || name.empty()||phoneNumber.empty()
		||employeeNumber.empty()) { return false; }
	DatabaseManager db;
	if (db.Connect()) {
		Doctor m(employeeNumber, password, name, licenseId, department, departmentCode,
			speicalty, phoneNumber
			);
		return db.ExecuteInsertQuery(m);
	}
	return false;
}
/*
	id �ߺ�Ȯ��
*/
bool SignUpController::checkId(std::string& employeeNumber) {
	DatabaseManager db;
	if (db.Connect()) {
		return db.CheckIdQuery(employeeNumber);
	}
	return false;
}


