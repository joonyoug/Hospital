#pragma once
#include <string>
class AppointmentDto
{
public:
	AppointmentDto(std::string doctorid,
        std::string appointDate, std::string symptons, std::string phone_number);
    std::string patientName;  // 환자 이름
    std::string doctorid;     // 의사 아이디
    std::string appointDate;  // 예약 날짜
    std::string symptons;     // 증상
    std::string patientPhone; // 환자 전화번호
};

