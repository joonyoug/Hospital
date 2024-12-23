#include "pch.h"
#include "PatientDto.h"


bool PatientDto::isEmpty() {
	if (this->residentNumber.empty()) {
		return true;
	}
	return false;
}