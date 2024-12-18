#include "pch.h"
#include "ChatHistoryDto.h"


ChatHistoryDto::ChatHistoryDto(std::string& residentNumber, std::string& employeeNumber,
	std::string& date,
	std::string& cc, std::string& manifestation) :residentNumber(residentNumber), employeeNumber(employeeNumber),
	date(date), cc(cc), manifestation(manifestation) {
}