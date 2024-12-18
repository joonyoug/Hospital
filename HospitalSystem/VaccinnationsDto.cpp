#include "pch.h"
#include "VaccinnationsDto.h"
VaccinnationsDto::VaccinnationsDto(std::string& residentNumber, std::string& date, std::string& v_name, std::string& d_name,int th) :
	residentNumber(residentNumber), date(date), v_name(v_name), d_name(d_name),th(th) {
}