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
END_MESSAGE_MAP()


// AddAppointment 메시지 처리기
