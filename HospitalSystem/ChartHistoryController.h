#pragma once
#include "ChartHistoryDB.h"
#include <string>
#include <vector>
class ChartHistoryController
{

	/*
	bool addChart(std::string residentNumber, std::string employeeNumber, 
		std::string date, std::string cc, std::string meni, std::vector<std::string> dcode);
	
	*/
public:
	bool addChart(std::string residentNumber, std::string employeeNumber,
		std::string date, std::string cc, std::string meni, std::vector<std::string> dcode);




};

