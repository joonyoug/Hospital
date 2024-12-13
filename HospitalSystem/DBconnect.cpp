#include "pch.h"
#include "DBconnect.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp> // JSON을 읽기 위해 사용

using json = nlohmann::json;

DBconnect::DBconnect() : conn(nullptr), stmt(nullptr) {
    if (!Connect()) {
        std::cerr << "데이터베이스 연결 실패!" << std::endl;
    }
}

DBconnect::~DBconnect() {
    // stmt와 conn이 nullptr이 아닐 경우에만 삭제
    if (stmt) {
        delete stmt;
    }
    if (conn) {
        delete conn;
    }
}

bool DBconnect::Connect() {
    try {
        // config.json 파일 열기
        std::ifstream inputFile("config.json");
        if (!inputFile.is_open()) {
            std::cerr << "config.json 파일을 열 수 없습니다!" << std::endl;
            return false;
        }

        // JSON 파싱
        json config;
        inputFile >> config;

        std::string host = config["database"]["host"];
        std::string username = config["database"]["username"];
        std::string password = config["database"]["password"];
        std::string schema = config["database"]["schema"];
        std::string charset = config["database"]["charset"];

        // MySQL 드라이버 인스턴스 얻기
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_driver_instance();
        conn = driver->connect(host, username, password);
        conn->setSchema(schema); // 데이터베이스 선택

        // SQL 문 실행 (타임존 및 문자셋 설정)
        stmt = conn->createStatement();
        stmt->execute("SET time_zone = '+09:00';");
        stmt->execute("SET NAMES " + charset); // 문자셋 설정 (예: utf8)

        // stmt 삭제
        if (stmt) {
            delete stmt;
            stmt = nullptr;
        }

        return true;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL 오류 발생: " << e.what() << std::endl;
        return false;
    }
    catch (const std::exception& e) {
        std::cerr << "일반 오류 발생: " << e.what() << std::endl;
        return false;
    }
}