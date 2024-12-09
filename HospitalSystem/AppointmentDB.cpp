#include "pch.h"
#include "AppointmentDB.h"
#include <nlohmann/json.hpp> 
#include <fstream> 

using json = nlohmann::json;

AppointmentDB::AppointmentDB() {
    
}

AppointmentDB::~AppointmentDB() {
   
}
std::vector<AppointmentDto> AppointmentDB::todayAppointment(std::string doctorId) {
    sql::PreparedStatement* pstmt = nullptr;
    std::vector<AppointmentDto> appointments;
    try {
        // 쿼리 수정: 'phone_number'를 SELECT에 포함
        std::string query =
            "SELECT a.resident_number, a.date, a.cc, p.name, p.phone_number "
            "FROM appointments a "
            "JOIN patients p ON a.resident_number = p.resident_number "
            "WHERE a.employee_number = ? "
            "AND DATE(a.date) = CURDATE();";

        pstmt = conn->prepareStatement(query);
        pstmt->setString(1, doctorId);

        sql::ResultSet* res = pstmt->executeQuery();

        while (res->next()) {
            // AppointmentDto 객체 생성
            AppointmentDto app(
                doctorId,                          // 의사 아이디
                res->getString("date"),             // 예약 날짜
                res->getString("cc"),               // 증상
                res->getString("phone_number")      // 환자 전화번호
            );
            app.patientName = res->getString("name");  // 환자 이름 설정
            appointments.push_back(app);  // 벡터에 추가
        }

        // ResultSet 메모리 해제
        delete res;

        return appointments;
    }
    catch (sql::SQLException& e) {
        std::cout << "SQL 오류: " << e.what() << std::endl;

        // 예외 발생 시 PreparedStatement 객체 삭제
        if (pstmt) {
            delete pstmt;
        }

        return appointments;  // 빈 벡터를 반환
    }
    catch (std::exception& e) {
        std::cout << "일반 오류: " << e.what() << std::endl;

        // 예외 발생 시 PreparedStatement 객체 삭제
        if (pstmt) {
            delete pstmt;
        }

        return appointments;  // 빈 벡터를 반환
    }
}



bool AppointmentDB::addAppointment(
    std::string residentNUmber, std::string name, std::string date,
    std::string employeeNumber, std::string CC) {
    sql::PreparedStatement* pstmt = nullptr;
    try {
        std::string query = "INSERT INTO appointments (resident_number, employee_number, date, CC) VALUES(?,?,?,?);";
        pstmt = conn->prepareStatement(query);
        pstmt->setString(1, residentNUmber);
        pstmt->setString(2, employeeNumber);
        pstmt->setString(3, date);
        pstmt->setString(4, CC);

        pstmt->executeUpdate();  

        delete pstmt;  // 
        return true;
    }
    catch (sql::SQLException& e) {
        if (pstmt) {
            delete pstmt;  
        }
        std::cout << "SQL 오류: " << e.what() << std::endl;
        return false;
    }
}
