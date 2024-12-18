#include "pch.h"
#include "DBconnect.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp> // JSON�� �б� ���� ���

using json = nlohmann::json;

DBconnect::DBconnect() : conn(nullptr), stmt(nullptr) {
    if (!Connect()) {
        std::cerr << "�����ͺ��̽� ���� ����!" << std::endl;
    }
}

DBconnect::~DBconnect() {
    // stmt�� conn�� nullptr�� �ƴ� ��쿡�� ����
    if (stmt) {
        delete stmt;
    }
    if (conn) {
        delete conn;
    }
}

bool DBconnect::Connect() {
    try {
        // config.json ���� ����
        std::ifstream inputFile("config.json");
        if (!inputFile.is_open()) {
            std::cerr << "config.json ������ �� �� �����ϴ�!" << std::endl;
            return false;
        }

        // JSON �Ľ�
        json config;
        inputFile >> config;

        std::string host = config["database"]["host"];
        std::string username = config["database"]["username"];
        std::string password = config["database"]["password"];
        std::string schema = config["database"]["schema"];
        std::string charset = config["database"]["charset"];

        // MySQL ����̹� �ν��Ͻ� ���
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_driver_instance();
        conn = driver->connect(host, username, password);
        conn->setSchema(schema); // �����ͺ��̽� ����

        // SQL �� ���� (Ÿ���� �� ���ڼ� ����)
        stmt = conn->createStatement();
        stmt->execute("SET time_zone = '+09:00';");
        stmt->execute("SET NAMES " + charset); // ���ڼ� ���� (��: utf8)

        // stmt ����
        if (stmt) {
            delete stmt;
            stmt = nullptr;
        }

        return true;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL ���� �߻�: " << e.what() << std::endl;
        return false;
    }
    catch (const std::exception& e) {
        std::cerr << "�Ϲ� ���� �߻�: " << e.what() << std::endl;
        return false;
    }
}