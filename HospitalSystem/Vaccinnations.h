#pragma once
#include <string>
class Vaccinnations
{
private:
	std::string residentNumber; //�ֹι�ȣ 
	std::string date;  //�Ͻ�
	std::string v_name; //���� ������ 
	std::string d_name; //��ǰ��
	int th; // ����
public:

	std::string getResidentNumner();
	std::string getDate();
	std::string getVname();
	std::string getDname();
	int getTh();


};

