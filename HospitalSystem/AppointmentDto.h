#pragma once
#include <string>
class AppointmentDto
{
public:
	AppointmentDto(std::string doctorid,
        std::string appointDate, std::string symptons, std::string phone_number);
    std::string patientName;  // ȯ�� �̸�
    std::string doctorid;     // �ǻ� ���̵�
    std::string appointDate;  // ���� ��¥
    std::string symptons;     // ����
    std::string patientPhone; // ȯ�� ��ȭ��ȣ
};

