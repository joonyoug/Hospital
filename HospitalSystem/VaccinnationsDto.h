#pragma once
#include <string>
class VaccinnationsDto
{
public:
	std::string residentNumber; //�ֹι�ȣ 
	std::string date;  //�Ͻ�
	std::string v_name; //���� ������ 
	std::string d_name; //��ǰ��
	int th; // ����

	VaccinnationsDto(std::string& residentNumber, std::string& date, std::string& v_name, std::string& d_name,int th);



};

