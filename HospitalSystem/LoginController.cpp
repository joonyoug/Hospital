#include "pch.h"
#include "LoginController.h"
//로그인
/*
	db.connect() 의 로그인 커리 실행 성공시 true 실패시 false
*/

bool LoginController::Login(const std::string id, const std::string pw) {
	DatabaseManager db;
	if (db.Connect()) {
		return db.ExcuteLoginQuery(id, pw);
	}
	else {
		return false;
	}
}