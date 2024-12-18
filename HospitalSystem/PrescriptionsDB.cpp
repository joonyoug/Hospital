#include "pch.h"
#include "PrescriptionsDB.h"
bool PrescriptionsDB::addPrescriptions(std::string residentNumber, std::string employee_number
	, std::string date, std::string method,std::string name) {

	std::string query = "insert into prescriptions (resident_number,employee_number,date,method,drugs_name) values(?,?,?,?,?)";
	sql::PreparedStatement* pstmt = nullptr;

	try {
		pstmt = conn->prepareStatement(query);
		pstmt->setString(1, residentNumber);
		pstmt->setString(2, employee_number);
		pstmt->setString(3, date);
		pstmt->setString(4, method);
		pstmt->setString(5, name);
		
		pstmt->executeUpdate();

		delete pstmt;
		return true;
	
	}
	catch (sql::SQLException e) {
	
		std::cout << e.what() << std::endl;
		return false;	
	}


}