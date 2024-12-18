#include "pch.h"
#include "DcodeController.h"


std::vector<Dcode> DcodeController::selectDcode() {
	DcodeDB db;
	return db.selectDcode();
}