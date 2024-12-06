#pragma once
#include <string>

class Vitalsign_status
{
private:
	int chart_id;
	std::string resident_number;
	int D_BP;
	int S_BP;
	int PR;
	int RR;
	float BT;
	int spO2;
	float height;
	float weight;

public:
	Vitalsign_status(int chart_id, std::string& resident_number,
		int D_BP, int S_BP, int PR, int RR,
		float BT, int spO2, float height, float weight);
	int getChart_id();
	std::string getResidentNumber();
	int getD_BP();
	int getS_BP();
	int getPR();
	int getRR();
	float getBT();
	int getSpO2();
	float Height();
	float Weight();
};

