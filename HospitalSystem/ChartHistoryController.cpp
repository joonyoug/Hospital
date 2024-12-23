#include "pch.h"
#include "ChartHistoryController.h"
#include "ChartHistoryDB.h"

bool ChartHistoryController::addChart(std::string residentNumber, std::string employeeNumber,
	std::string date, std::string cc, std::string meni, std::vector<std::string> dcode) {	
	ChartHistoryDB db;
	if (db.addChart(residentNumber, employeeNumber, date, cc, meni, dcode)) {
		return true;
	}
	else {
		return false;
	}
}
