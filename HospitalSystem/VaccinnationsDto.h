#pragma once
#include <string>
class VaccinnationsDto
{
public:
	std::string residentNumber; //주민번호 
	std::string date;  //일시
	std::string v_name; //예방 접종명 
	std::string d_name; //약품명
	int th; // 차수

	VaccinnationsDto(std::string& residentNumber, std::string& date, std::string& v_name, std::string& d_name,int th);



};

