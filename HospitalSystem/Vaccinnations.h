#pragma once
#include <string>
class Vaccinnations
{
private:
	std::string residentNumber; //주민번호 
	std::string date;  //일시
	std::string v_name; //예방 접종명 
	std::string d_name; //약품명
	int th; // 차수
public:

	std::string getResidentNumner();
	std::string getDate();
	std::string getVname();
	std::string getDname();
	int getTh();


};

