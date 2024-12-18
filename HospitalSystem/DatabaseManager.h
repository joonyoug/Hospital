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

	bool ExecuteInsertQuery(Doctor& member); //ȸ������
	bool ExcuteLoginQuery(const std::string id,   //�α���
		const std::string pw);
	bool CheckIdQuery(const std::string id);
};

