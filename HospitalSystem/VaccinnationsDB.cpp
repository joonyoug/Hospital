#include "pch.h"
#include "VaccinnationsDB.h"


std::vector<VaccinnationsDto> VaccinnationsDB::selectVaccin(std::string residentNumber) {
	std::vector<VaccinnationsDto> dto;
	std::string query = "select * from vaccinations where resident_number =?";
	sql::PreparedStatement* pstmt = nullptr;
	try {
	
		pstmt = conn->prepareStatement(query);
		pstmt->setString(1, residentNumber);

		sql::ResultSet* res = pstmt->executeQuery();

		while (res->next()) {
			
			std::string resident_number = res->getString("resident_number");
			std::string date = res->getString("date");
			std::string v_name = res->getString("v_name");
			std::string d_name = res->getString("d_name");
			int th = res->getInt("th");
<<<<<<< HEAD
=======
			//std::cout << th << std::endl;
>>>>>>> upstream/dev
			VaccinnationsDto va(resident_number, date, v_name, d_name, th);
			dto.push_back(va);
		}
		delete pstmt;
		return dto;
	
	}
	catch (sql::SQLException e) {
		delete pstmt;
		std::cout << e.what() << std::endl;
	
	}


}