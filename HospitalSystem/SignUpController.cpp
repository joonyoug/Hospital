#include "pch.h"
#include "SignUpController.h"
#include "Doctor.h"
/*
	회원가입 
	DB의 insertQuery 호출 성공시 true
	실패시 false;
*/
bool SignUpController::SignUP(std::string id,std::string pw,
	std::string name,std::string phoneNumber,std::string employeeNumber) {
	if (id.empty() || pw.empty() || name.empty()||phoneNumber.empty()
		||employeeNumber.empty()) { return false; }
	DatabaseManager db;
	if (db.Connect()) {
		Doctor m(id, pw, name, phoneNumber,employeeNumber);
		return db.ExecuteInsertQuery(m);
	}
	return false;
}
/*
	id 중복확인
*/
bool SignUpController::checkId(std::string id) {
	DatabaseManager db;
	if (db.Connect()) {
		return db.CheckIdQuery(id);
	}
	return false;
}


