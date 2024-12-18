#include "pch.h"
#include "PrescriptionsDB.h"
<<<<<<< HEAD


bool PrescriptionsDB::addPrescriptions(std::string residentNumber, std::string employee_number
	, std::string date, std::string method, std::string dosage, float daily_dosage,
	int frequency, int duration, std::string notes) {

	std::string query = "insert into prescriptions (resident_number,employee_number,date,method,dosage,daily_dosage,frequency,duration,notes) values(?,?,?,?,?,?,?,?,?)";
=======
bool PrescriptionsDB::addPrescriptions(std::string residentNumber, std::string employee_number
	, std::string date, std::string method,std::string name) {

	std::string query = "insert into prescriptions (resident_number,employee_number,date,method,drugs_name) values(?,?,?,?,?)";
>>>>>>> upstream/dev
	sql::PreparedStatement* pstmt = nullptr;

	try {
		pstmt = conn->prepareStatement(query);
		pstmt->setString(1, residentNumber);
		pstmt->setString(2, employee_number);
		pstmt->setString(3, date);
		pstmt->setString(4, method);
<<<<<<< HEAD
		pstmt->setString(5, dosage);
		pstmt->setDouble(6, daily_dosage);
		pstmt->setInt(7, frequency);
		pstmt->setInt(8, duration);
		pstmt->setString(9, notes);
=======
		pstmt->setString(5, name);
		
>>>>>>> upstream/dev
		pstmt->executeUpdate();

		delete pstmt;
		return true;
	
	}
	catch (sql::SQLException e) {
	
		std::cout << e.what() << std::endl;
		return false;	
	}


}