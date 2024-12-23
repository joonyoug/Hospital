#include "pch.h"
#include "WaitPatientDB.h"

bool WaitPatientDB::deleteWait(std::string residentNumber) {
	std::string query = "delete from a_list where resident_number =?";
	sql::PreparedStatement* pstmt = nullptr;
	try {
		pstmt = conn->prepareStatement(query);
		pstmt->setString(1,residentNumber);
		pstmt->executeUpdate();
		delete pstmt;
		return true;	
	}
	catch (sql::SQLException e) {		
		std::cout << e.what() << std::endl;
		delete pstmt;
		return false;
	}
}
std::vector<WaitPatient> WaitPatientDB:: selectWait() {
	std::string query = "select * from a_list";
	sql::PreparedStatement* pstmt = nullptr;
	std::vector<WaitPatient> dto;

	try {
		pstmt = conn->prepareStatement(query);
		sql::ResultSet* res = pstmt->executeQuery();

		while (res->next()) {
			dto.push_back(WaitPatient(
				res->getString("name").asStdString(),
				res->getString("resident_number").asStdString(),
				res->getString("symptoms").asStdString()
			));
		}
		delete pstmt;
		delete res;
		return dto;
	}
	catch (sql::SQLException e) {

		std::cout << e.what() << std::endl;
	}
}
bool WaitPatientDB::addWait(std::string name, std::string resident,std::string s) {

	std::string query = "insert into a_list (name,resident_number,symptoms) values(?,?,?)";
	sql::PreparedStatement* pstmt = nullptr;
	try {
		pstmt = conn->prepareStatement(query);
		pstmt->setString(1, name);
		pstmt->setString(2, resident);
		pstmt->setString(3, s);

		pstmt->executeQuery();
		delete pstmt;
		
		return true;
	
	}
	catch (sql::SQLException e) {
		std::cout << e.what() << std::endl;
		delete pstmt;
		return false;
	}

}
