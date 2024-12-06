#pragma once
#include <string>
class Vaccinations
{
private:
	std::string residentNumber;
	std::string date;
	std::string vName;
	std::string dName;
	int th;
	std::string status;
	std::string reason;

public:
	Vaccinations(std::string &resident_number, std::string& date,
		std::string &v_name, std::string& d_name, int th,
		std::string &status, std::string &reason);
	std::string getResidentNumber();
	std::string getDate();
	std::string getvName();
	std::string getdName();
	int getTh();
	std::string getStatus();
	std::string getReason();



};

