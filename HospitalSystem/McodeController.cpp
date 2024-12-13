#include "pch.h"
#include "McodeController.h"


std::vector<Mcode> McodeController::selectMcode() {
	McodeDB db;
	return  db.selectMcode();

}