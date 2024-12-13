#include "pch.h"
#include "DcodeDB.h"
using namespace std;

DcodeDB::DcodeDB() {
}
DcodeDB::~DcodeDB() {}



std::vector<Dcode> DcodeDB::selectDcode() {

	sql::PreparedStatement *pstmt = nullptr;
	std::string sql = "select * from KCD";
	std::vector<Dcode> dc;

	try {
		pstmt = conn->prepareStatement(sql);
		sql::ResultSet* res = pstmt->executeQuery();

		while (res->next()) {
			string kcd_code = res->getString("k_code");
			string name = res->getString("k_name");
			Dcode code(kcd_code, name);	
			dc.push_back(code);
		}
		delete pstmt;
		delete res;
		return dc;
	
	}
	catch (sql::SQLException e) {
		cout << e.what() << endl;
		delete pstmt;
		return dc;  // 
	}

	





}