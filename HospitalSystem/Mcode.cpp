#include "pch.h"
#include "Mcode.h"
Mcode::Mcode(std::string& code, std::string &name) :code(code), name(name) {};

std::string Mcode::getCode() {
	return code;
}
std::string Mcode::getName() {
	return name;
}