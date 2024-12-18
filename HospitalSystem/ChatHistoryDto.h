#pragma once
#include <string>
#include <vector>
class ChatHistoryDto
{
public:
	
	std::string residentNumber;
	std::string employeeNumber;
	std::string date;
	std::string cc;
	std::string manifestation;
	ChatHistoryDto(std::string& residentNumber, std::string& employeeNumber,
		std::string& date,
		std::string& cc, std::string& manifestation);



};

