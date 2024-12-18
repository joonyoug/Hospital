#include "pch.h"
#include "AppointmentDto.h"

AppointmentDto::AppointmentDto(std::string doctorid,std::string appointDate, 
    std::string symptons, std::string phone_number)
    : doctorid(doctorid), appointDate(appointDate), symptons(symptons), patientPhone(phone_number) {
}
