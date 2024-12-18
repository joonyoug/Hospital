#include "pch.h"
#include "McodeDB.h"
McodeDB::McodeDB() {}
McodeDB::~McodeDB() {}
std::vector<Mcode> McodeDB::selectMcode() {
	std::string query = "select * from drugs_list";
	std::vector<Mcode> db;
	sql::PreparedStatement * pstmt = nullptr;
	try {	
		pstmt = conn->prepareStatement(query);
		sql::ResultSet* res = pstmt->executeQuery();

		while (res->next()) {
			std::string name = res->getString("drugs_name");
			std::string code = res->getString("drugs_code");
			db.push_back(Mcode(code, name));
		}
		delete pstmt;
		delete res;
		return db;
	}
	catch (sql::SQLException e) {
		std::cout << e.what() << std::endl;
		delete pstmt;
	}
}

