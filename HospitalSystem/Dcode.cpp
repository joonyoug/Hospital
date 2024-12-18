#include "pch.h"
#include "Dcode.h"
/*
	private:
	std::string kcd_code;
	std::string name;
public:
	std::string getKcdcode();
	std::string getName();
	void setKcdCode(std::string kcd_cod);
	void setName(std::string name);
*/

Dcode::Dcode(std::string &kcd, std::string& name) {
	this->kcd_code = kcd;
	this->name = name;
}



std::string Dcode::getKcdcode() {

	return this->kcd_code;
}
std::string Dcode::getName() {
	return this->name;
}
void Dcode::setKcdCode(std::string kcd_cod) {

	this->kcd_code = kcd_cod;

}
void Dcode::setName(std::string name) {
	this->name = name;
}




