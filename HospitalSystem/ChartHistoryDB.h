#pragma once
#include "DBconnect.h"
#include "ChatHistoryDto.h"
#include <string>
#include <vector>
class ChartHistoryDB : public DBconnect
{

public:
	ChartHistoryDB();
	~ChartHistoryDB();

	bool addChartHistory(std::string residentNumber, std::string employeeNumber, std::string date, std::string cc,
		std::string mani
	);
	std::vector<ChatHistoryDto> selectedChart(std::string residentNumber);
	bool addChart(std::string residentNumber, std::string employeeNumber, 
		std::string date, std::string cc, std::string meni, std::vector<std::string> dcode);
	



	

	
};

