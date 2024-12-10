#include "pch.h"
#include "DatabaseManager.h"
#include <nlohmann/json.hpp> 
#include <fstream> 

using json = nlohmann::json;

DatabaseManager::DatabaseManager() {
   
}

DatabaseManager::~DatabaseManager() {   
   
}
bool DatabaseManager::ExecuteInsertQuery(Doctor& member) {
    sql::PreparedStatement* pstmt = nullptr;
    try {
        std::string query = "insert into doctors (employee_number,password,name,license_id,department,department_code,specialty,phone_number) values(?,?,?,?,?,?,?,?)";
        pstmt = this->conn->prepareStatement(query);
        pstmt->setString(1, member.getEmployeeNumber());
        pstmt->setString(2, member.getPassword());
        pstmt->setString(3, member.getName());
        pstmt->setString(4, member.getlicenseId());
        pstmt->setString(5, member.getDepatment());   // 수정: getDepartment()
        pstmt->setString(6, member.getDepartmentCode());
        pstmt->setString(7, member.getSpeicalty());    // 수정: getSpecialty()
        pstmt->setString(8, member.getPhoneNumber());
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


bool DatabaseManager::ExcuteLoginQuery(const std::string id, const std::string pw) {
    sql::PreparedStatement* pstmt = nullptr;
    try {
        std::string query = "select * from doctors where employee_number = ? and password =?";
        pstmt = this->conn->prepareStatement(query);
        pstmt->setString(1, id);
        pstmt->setString(2, pw);
        sql::ResultSet* res = pstmt->executeQuery();
        int count = 0;
        while (res->next()) {
            count++;
        }
        if (count == 1) {
            delete pstmt;
            delete res;
            return true;
        }
        delete pstmt;
        delete res;
        return false;
    }
    catch (sql::SQLException e) {
      
    }
}

bool DatabaseManager::CheckIdQuery(const std::string id) {
    std::string query = "select * from doctors where employee_number =?";
    sql::PreparedStatement* pstmt = nullptr;
    try {
        pstmt = conn->prepareStatement(query);
        pstmt->setString(1, id);
        sql::ResultSet* res = pstmt->executeQuery();
        while (res->next()) {
            delete pstmt;
            delete res;
            return false;
        }
        delete pstmt;
        delete res;
        return true;
    }
    catch (sql::SQLException e) {
        std::cout << e.what() << std::endl;
        delete pstmt;
        return false;
    }
}
