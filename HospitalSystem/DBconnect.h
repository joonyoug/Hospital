#include <nlohmann/json.hpp> 
#include <fstream>
#include <mysql/jdbc.h>
#pragma once

class DBconnect
{
public:
	sql::Connection* conn;
	sql::Statement* stmt;
	DBconnect();
	~DBconnect();
	bool Connect();
	
};

