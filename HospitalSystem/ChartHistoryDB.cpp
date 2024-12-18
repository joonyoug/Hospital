#include "pch.h"
#include "ChartHistoryDB.h"



ChartHistoryDB::ChartHistoryDB() {}
ChartHistoryDB::~ChartHistoryDB() {}

bool ChartHistoryDB::addChartHistory(std::string residentNumber, 
	std::string employeeNumber, std::string date, std::string cc,
	std::string mani) {

	sql::PreparedStatement *pstmt= nullptr;
	std::string query = "insert into chart_records (resident_number,employee_number,date,CC,manifestation) values(?,?,?,?,?);";
	try {
		pstmt = conn->prepareStatement(query);
		pstmt->setString(1, residentNumber);
		pstmt->setString(2, employeeNumber);
		pstmt->setString(3, date);
		pstmt->setString(4, cc);
		pstmt->setString(5, mani);
		delete pstmt;
		return true;
	}
	catch (sql::SQLException e) {
		delete pstmt;
		std::cout << e.what() << std::endl;
		return false;
	}
}
std::vector<ChatHistoryDto> ChartHistoryDB::selectedChart(std::string residentNumber) {
	std::vector<ChatHistoryDto> dto;

	std::string query = "select * from chart_records where resident_number =?";
	sql::PreparedStatement* pstmt = nullptr;
	try {
		pstmt = conn->prepareStatement(query);
		pstmt->setString(1, residentNumber);
		sql::ResultSet* res = pstmt->executeQuery();
		
		while (res->next()) {
			std::string resiNumber = res->getString("resident_number");
			std::string employee_number = res->getString("employee_number");
			std::string date = res->getString("date");
			std::string cc = res->getString("CC");
			std::string manifestation = res->getString("manifestation");
			dto.push_back(ChatHistoryDto(resiNumber, employee_number, date, cc, manifestation));			
		}
		return dto;	
	
	}
	catch (sql::SQLException e) {
	
		std::cout << e.what() << std::endl;
		delete pstmt;
	}

}
bool ChartHistoryDB::addChart(std::string residentNumber, std::string employeeNumber,
    std::string date, std::string cc, std::string meni, std::vector<std::string> dcode) {

    std::string query = "insert into chart_records (resident_number, employee_number, date, CC, manifestation) values(?,?,?,?,?);";
    sql::PreparedStatement* pstmt = nullptr;

    try {
        // ��Ʈ ��� ����
        pstmt = conn->prepareStatement(query);
        pstmt->setString(1, residentNumber);
        pstmt->setString(2, employeeNumber);
        pstmt->setString(3, date);
        pstmt->setString(4, cc);
        pstmt->setString(5, meni);

        pstmt->executeUpdate(); // executeUpdate�� ����

        // ��Ʈ �ڵ� �ڵ� ������ ID ��������
        sql::PreparedStatement* idStmt = conn->prepareStatement("SELECT LAST_INSERT_ID()");
        sql::ResultSet* res = idStmt->executeQuery();
        int chart_code = 0;

        if (res->next()) {
            chart_code = res->getInt(1);  // ��� ������ ��Ʈ ���̺��� �ڵ� ������ ��Ʈ �ڵ�
            
        }

        // �ǻ���� ���̺� ������ ���� (�� ���� �ڵ忡 ����)
        for (const auto& diseaseCode : dcode) {
            query = "select k_name, k_cost from KCD where k_code = ?";
            pstmt = conn->prepareStatement(query);
            pstmt->setString(1, diseaseCode);
            res = pstmt->executeQuery();

            if (res->next()) {
                int k_cost = res->getInt("k_cost");
                std::string k_name = res->getString("k_name");

                query = "insert into decisions (chart_id, k_code, k_name, k_cost) values(?, ?, ?, ?)";
                sql::PreparedStatement* pstmt2 = conn->prepareStatement(query);
                pstmt2->setInt(1, chart_code);
                pstmt2->setString(2, diseaseCode);
                pstmt2->setString(3, k_name);
                pstmt2->setInt(4, k_cost);

                pstmt2->executeUpdate(); // executeUpdate�� ����
            }
        }

        // ���� �ջ� ���
        query = "SELECT SUM(k_cost) FROM decisions WHERE chart_id = ?";
        pstmt = conn->prepareStatement(query);
        pstmt->setInt(1, chart_code);
        res = pstmt->executeQuery();

        int totalPrice = 0;
        if (res->next()) {
            totalPrice = res->getInt(1);  // �ش� ��Ʈ �ڵ��� ��� ���� �ջ�
        }

        // �ջ� ���̺� �� ���� ���� �Ǵ� ������Ʈ
        query = "INSERT INTO sum (chart_id, resident_number, sum) VALUES (?, ?, ?) ";
        pstmt = conn->prepareStatement(query);
        pstmt->setInt(1, chart_code);
        pstmt->setString(2, residentNumber);
        pstmt->setInt(3, totalPrice);
        pstmt->executeUpdate(); 

        std::cout << "��" << std::endl;
        delete pstmt;
        return true;

    }
    catch (sql::SQLException& e) {
        std::cout << "qweqweqweqweqweq" << std::endl;
        std::cout << "Error: " << e.what() << std::endl;
        return false;
    }
}
