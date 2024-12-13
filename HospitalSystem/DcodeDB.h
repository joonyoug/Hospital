#pragma once
#include "DBconnect.h"
#include <mysql/jdbc.h>
#include <nlohmann/json.hpp> 
#include <fstream>
#include "Dcode.h"
#include "vector"
class DcodeDB: public  DBconnect
{

public:
	DcodeDB();
	~DcodeDB();
	std::vector<Dcode> selectDcode();


};

