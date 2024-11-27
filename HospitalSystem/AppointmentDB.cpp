#include "pch.h"
#include "AppointmentDB.h"
#include <nlohmann/json.hpp> 
#include <fstream> 

using json = nlohmann::json;

AppointmentDB::AppointmentDB() {
    this->con = nullptr;
}

AppointmentDB::~AppointmentDB() {
    delete this->con;
}

bool AppointmentDB::Connect() {
    try {
        
        std::ifstream inputFile("config.json");
        if (!inputFile.is_open()) {
            std::cerr << "파일을 열 수 없습니다!" << std::endl;
            return false;
        }

        
        json config;
        inputFile >> config;

        
        std::string host = config["database"]["host"];
        std::string username = config["database"]["username"];
        std::string password = config["database"]["password"];
        std::string schema = config["database"]["schema"];
        std::string charset = config["database"]["charset"];

        // MySQL 연결
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_driver_instance();
        con = driver->connect(host, username, password);
        con->setSchema(schema);

        
        stmt = con->createStatement();
        stmt->execute("set names " + charset);
        if (stmt) { delete stmt; stmt = nullptr; }

        return true;
    }
    catch (sql::SQLException& e) {
        std::cout << "SQL 오류: " << e.what() << std::endl;
        return false;
    }
    catch (const std::exception& e) {
        std::cout << "일반 오류: " << e.what() << std::endl;
        return false;
    }
}

std::vector<AppointmentDto> AppointmentDB::todayAppointment(std::string doctorId) {
    sql::PreparedStatement* pstmt = nullptr;
    std::vector<AppointmentDto> appointments;
    try {
        std::string query =
            "SELECT a.patient_phone_number, a.appointment_date, a.symptoms, p.name FROM appointment a JOIN patient p ON a.patient_phone_number = p.phone_number WHERE a.doctor_id = ? AND DATE(a.appointment_date) = CURDATE();";
        pstmt = con->prepareStatement(query);
        pstmt->setString(1, doctorId);
        sql::ResultSet* res = pstmt->executeQuery();
        while (res->next()) {
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
    sql::PreparedStatement* pstmt = nullptr;
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
