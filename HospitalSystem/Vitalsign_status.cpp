#include "pch.h"
#include "Vitalsign_status.h"
/*
Vitalsign_status(int chart_id, std::string& resident_number,
		int D_BP, int S_BP, int PR, int RR,
		float BT, int spO2, float height, float weight);
	int getChart_id();
	std::string getResidentNumber();
	int getD_BP();
	int getS_BP();
	int getPR();
	int getRR();
	int getBT();
	int getSpO2();
	float Height();
	float Weight();
*/

Vitalsign_status::Vitalsign_status(int chart_id, std::string& resident_number,
	int D_BP, int S_BP, int PR, int RR,
	float BT, int spO2, float height, float weight) {
	this->chart_id = chart_id;
	this->resident_number = resident_number;
	this->D_BP = D_BP;
	this->S_BP = S_BP;
	this->PR = PR;
	this->RR = RR;
	this->BT = BT;
	this->spO2 = spO2;
	this->height = height;
	this->weight = weight;
}

int Vitalsign_status::getChart_id() {
	return this->chart_id;
}
std::string Vitalsign_status::getResidentNumber() {
	return this->resident_number;
}
int Vitalsign_status::getD_BP() {
	return this->D_BP;
}
int Vitalsign_status::getS_BP() {
	return this->S_BP;
}
int Vitalsign_status::getPR() {
	return this->PR;
}
int Vitalsign_status::getRR() {
	return this->RR;
}
float Vitalsign_status::getBT() {
	return this->BT;
}
int Vitalsign_status::getSpO2() {
	return this->spO2;
}
float Vitalsign_status::Height() {
	return this->height;
}
float Vitalsign_status::Weight() {
	return this->weight;
}
