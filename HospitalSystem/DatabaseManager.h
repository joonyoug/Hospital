#pragma once
#include <mysql/jdbc.h>
#include "Doctor.h";
#include <nlohmann/json.hpp> 
#include <fstream> 
#include "DBconnect.h"

class DatabaseManager :public DBconnect
{

public:
	DatabaseManager();
	~DatabaseManager();

	bool ExecuteInsertQuery(Doctor& member); //회원가입
	bool ExcuteLoginQuery(const std::string id,   //로그인
		const std::string pw);
	bool CheckIdQuery(const std::string id);
};

