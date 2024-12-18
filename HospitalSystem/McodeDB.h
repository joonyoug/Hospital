#pragma once
#include "Mcode.h"
#include "DBconnect.h"
#include "Mcode.h"
#include <vector>
class McodeDB : public DBconnect
{
public:
	McodeDB();
	~McodeDB();
	std::vector<Mcode> selectMcode();

};

