#include "pch.h"
#include "LoginController.h"
//�α���
/*
	db.connect() �� �α��� Ŀ�� ���� ������ true ���н� false
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