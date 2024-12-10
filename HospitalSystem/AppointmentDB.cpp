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
        // ���� ����: 'phone_number'�� SELECT�� ����
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
            // AppointmentDto ��ü ����
            AppointmentDto app(
                doctorId,                          // �ǻ� ���̵�
                res->getString("date"),             // ���� ��¥
                res->getString("cc"),               // ����
                res->getString("phone_number")      // ȯ�� ��ȭ��ȣ
            );
            app.patientName = res->getString("name");  // ȯ�� �̸� ����
            appointments.push_back(app);  // ���Ϳ� �߰�
        }

        // ResultSet �޸� ����
        delete res;

        return appointments;
    }
    catch (sql::SQLException& e) {
        std::cout << "SQL ����: " << e.what() << std::endl;

        // ���� �߻� �� PreparedStatement ��ü ����
        if (pstmt) {
            delete pstmt;
        }

        return appointments;  // �� ���͸� ��ȯ
    }
    catch (std::exception& e) {
        std::cout << "�Ϲ� ����: " << e.what() << std::endl;

        // ���� �߻� �� PreparedStatement ��ü ����
        if (pstmt) {
            delete pstmt;
        }

        return appointments;  // �� ���͸� ��ȯ
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
        std::cout << "SQL ����: " << e.what() << std::endl;
        return false;
    }
}
