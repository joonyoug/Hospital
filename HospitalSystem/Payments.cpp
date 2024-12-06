#include "pch.h"
#include "Payments.h"
/*
Payments(std::string& payment_id, std::string& custodian_id,
		std::string& resident_number, std::string& p_date, std::string& date,
		int total, std::string& status);
	std::string getPayment_id();
	std::string getCustodian_id();
	std::string getResidentNumber();
	std::string getP_date();
	std::string getDate();
	int getTotal();
	std::string getStatus();
*/

Payments::Payments(std::string& payment_id, std::string& custodian_id,
	std::string& resident_number, std::string& p_date, std::string& date,
	int total, std::string& status) {
	this->payment_id = payment_id;
	this->custodian_id = custodian_id;
	this->resident_number = resident_number;
	this->p_date = p_date;
	this->date = date;
	this->total = total;
	this->status = status;

}

std::string Payments::getPayment_id() {
	return this->payment_id;
}
std::string Payments::getCustodian_id() {
	return this->custodian_id;
}
std::string Payments::getResidentNumber() {
	return this->resident_number;
}
std::string Payments::getP_date() {
	return this->p_date;
}
std::string Payments::getDate() {
	return this->date;
}
int Payments::getTotal() {
	return this->total;
}
std::string Payments::getStatus() {
	return this->status;
}
