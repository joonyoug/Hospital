#pragma once
#include "DBconnect.h"
#include "VaccinnationsDto.h"
#include <vector>
class VaccinnationsDB :public DBconnect
{

public:
	std::vector<VaccinnationsDto> selectVaccin(std::string residentNumber);


};

