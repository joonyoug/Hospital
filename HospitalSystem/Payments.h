#pragma once
#include <string>

class Payments
{
private:
	std::string payment_id;
	std::string custodian_id;
	std::string resident_number;
	std::string p_date;
	std::string date;
	int total;
	std::string status;

public:
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
};

