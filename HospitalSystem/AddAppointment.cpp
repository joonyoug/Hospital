// AddAppointment.cpp: 구현 파일
//

#include "pch.h"
#include "HospitalSystem.h"
#include "afxdialogex.h"
#include "AddAppointment.h"


// AddAppointment 대화 상자

IMPLEMENT_DYNAMIC(AddAppointment, CDialog)

AddAppointment::AddAppointment(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_Add_Appointment, pParent)
{

}

AddAppointment::~AddAppointment()
{
}

void AddAppointment::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AddAppointment, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_Appointment, &AddAppointment::OnBnClickedButtonAppointment)
END_MESSAGE_MAP()


// AddAppointment 메시지 처리기


void AddAppointment::OnBnClickedButtonAppointment()
{
	CString phone, doctorId, symptoms, date;
	GetDlgItemText(IDC_EDIT_Phone, phone);
	GetDlgItemText(IDC_EDIT_DoctorId, doctorId);
	GetDlgItemText(IDC_EDIT_symptoms, symptoms);
	GetDlgItemText(IDC_EDIT_Date, date);
	/*
	std::string patientPhone,
	std::string appointDate, 
	std::string doctorId, std::string sympton
	*/
	AppointmentController ap;
	bool check=	ap.addAppointment(std::string(CT2A(phone)), std::string(CT2A(date)),
		std::string(CT2A(doctorId)), std::string(CT2A(symptoms)));

	if (check) { AfxMessageBox(_T("예약성공")); }



}
