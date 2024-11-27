#include "pch.h"
#include "AppointmentDB.h"
/*
	AppointmentDB();
	~AppointmentDB();
	std::vector<Appointment> todayAppointment(std::string doctorId);
*/

AppointmentDB::AppointmentDB() {
	this->con = nullptr;
}
AppointmentDB::~AppointmentDB() {
	delete this->con;
}
bool AppointmentDB::Connect() {
	try {
		sql::mysql::MySQL_Driver* driver = sql::mysql::get_driver_instance();
		con = driver->connect("tcp://database-1.ct8gi4ac6qk6.ap-southeast-2.rds.amazonaws.com:3306", "admin", "qkralsdn!!");
		con->setSchema("hospital");

		// db 한글 저장을 위한 셋팅 
		stmt = con->createStatement();
		stmt->execute("set names euckr");
		if (stmt) { delete stmt; stmt = nullptr; }
		return true;
	}
	catch (sql::SQLException e) {
		std::cout << e.what() << std::endl;
		return false;
	}
}
std::vector<AppointmentDto> AppointmentDB::todayAppointment(std::string doctorId) {
	sql::PreparedStatement *pstmt = nullptr;
	std::vector<AppointmentDto> appointments;
	try {
		std::string query = 
			"SELECT a.patient_phone_number, a.appointment_date, a.symptoms, p.name FROM appointment a JOIN patient p ON a.patient_phone_number = p.phone_number WHERE a.doctor_id = ? AND DATE(a.appointment_date) = CURDATE();";
		pstmt = con->prepareStatement(query);
		pstmt->setString(1, doctorId);
		sql::ResultSet* res = pstmt->executeQuery();
		while (res->next()) {
			/*(std::string doctorid, std::string patientid,
		std::string appointDate,std::string symptons);
			*/
			AppointmentDto app(
				doctorId, 
				res->getString("patient_phone_number"),
				res->getString("appointment_date"),
				res->getString("symptoms"));
			app.patientName = res->getString("name");


			appointments.push_back(app);
		}
		return appointments;
	}
	catch (sql::SQLException e) {
		std::cout << e.what() << std::endl;
		delete pstmt;
	}
}
bool AppointmentDB::addAppointment(
	std::string patientPhone, std::string appointDate, std::string time,
	std::string doctorId, std::string sympton) {
	sql::PreparedStatement * pstmt = nullptr;
	try {
		std::string query = "INSERT INTO appointment (patient_phone_number, doctor_id, appointment_date, symptoms) VALUES(?,?,?,?);";
		pstmt = con->prepareStatement(query);
		pstmt->setString(1, patientPhone);
		pstmt->setString(2, doctorId);
		pstmt->setString(3, appointDate);
		pstmt->setString(4, sympton);
		pstmt->executeQuery();
	}
	catch (sql::SQLException e) {
		delete pstmt;
		return false;
	}
}



