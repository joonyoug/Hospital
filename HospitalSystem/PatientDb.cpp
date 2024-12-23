#include "pch.h"
#include "PatientDb.h"


/*
	PatientDb();
	~PatientDb();
	bool Connect();
	bool addPatient(Patient patient);
*/
using json = nlohmann::json;
PatientDb::PatientDb() {
	
}
PatientDb::~PatientDb() {
	
}

bool PatientDb::addPatient(Patient patient) {
	sql::PreparedStatement *ptsmt = nullptr;
	try {
		string query = "insert into patients (resident_number,name,gender,address,phone_number,emergency_number,dosing_list,blood_type) values(?,?,?,?,?,?,?,?);";
		ptsmt = conn->prepareStatement(query);
		ptsmt->setString(1, patient.getResidentNumber());
		ptsmt->setString(2, patient.getName());
		ptsmt->setString(3, patient.getGender());
		ptsmt->setString(4, patient.getAddress());
		ptsmt->setString(5, patient.getPhone());
		ptsmt->setString(6, patient.getEmergencyNumber());
		ptsmt->setString(7, patient.getDosingList());
		ptsmt->setString(8, patient.getBloodType());

		ptsmt->executeQuery();
		delete ptsmt;
		return true;
	
	}
	catch (sql::SQLException e) {
		cout << e.what();
		return false;	
	}

}

/*
Patient(std::string &residentNumber, std::string &name, std::string& phone,
		std::string& gender,std::string &address, int emergencyNumber, std::string &dosingList,
		std::string &bloodType);

*/

Patient PatientDb::searchPatient(std::string name) {

	sql::PreparedStatement* pstmt = nullptr;

	try {
		string query = "select * from patients where name = ? ";
		pstmt = conn->prepareStatement(query);
		pstmt->setString(1, name);
		sql::ResultSet* res = pstmt->executeQuery();

		while (res->next()) {

			Patient patient(
				res->getString("resident_number").asStdString(),
				res->getString("name").asStdString(),
				res->getString("phone_number").asStdString(),
				res->getString("gender").asStdString(),
				res->getString("address").asStdString(),
				res->getString("emergency_number").asStdString(),  
				res->getString("dosing_list").asStdString(),
				res->getString("blood_type").asStdString()
			);
			delete res;
			delete pstmt;
			return patient;

		}
	}
	catch (sql::SQLException e) {

		cout << e.what();
		delete pstmt;

	}
}
Patient PatientDb::selectPatient(std::string residentNumber) {
	sql::PreparedStatement* pstmt = nullptr;

	try {
		string query = "select * from patients where resident_number = ? ";
		pstmt = conn->prepareStatement(query);
		pstmt->setString(1,residentNumber);
		sql::ResultSet* res = pstmt->executeQuery();
		Patient pt; 
		
		while (res->next()) {			

			Patient patient(
				res->getString("resident_number").asStdString(),
				res->getString("name").asStdString(),
				res->getString("phone_number").asStdString(),
				res->getString("gender").asStdString(),
				res->getString("address").asStdString(),
				res->getString("emergency_number").asStdString(), 
				res->getString("dosing_list").asStdString(),
				res->getString("blood_type").asStdString()
			);
			delete res;
			delete pstmt;
			return patient;
		}
		return pt;

	}
	catch (sql::SQLException e) {
	
		cout << e.what();
		delete pstmt;
	
	}

}