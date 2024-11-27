// DoctorPage.cpp: 구현 파일
//

#include "pch.h"
#include "HospitalSystem.h"
#include "afxdialogex.h"
#include "DoctorPage.h"
#include "AppointmentController.h"
#include <vector>

// DoctorPage 대화 상자

IMPLEMENT_DYNAMIC(DoctorPage, CDialogEx)

DoctorPage::DoctorPage(CString doctorId, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Doctor, pParent)
{
	this->doctorId = doctorId;
}
CString DoctorPage::getDoctorId() {
	return this->doctorId;
}
BOOL DoctorPage::OnInitDialog()
{
	
	CDialogEx::OnInitDialog();  // 기본 초기화
	m_list.ModifyStyle(0, LVS_REPORT);
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EDITLABELS);

	// 컬럼 추가
	m_list.InsertColumn(0, _T("이름"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(1, _T("증상"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(2, _T("예약시간"), LVCFMT_CENTER, 100);
	AppointmentController apc;
	std::vector<AppointmentDto> apdto = apc.selectAppointment(std::string
		(CT2A(this->getDoctorId())));


	for (size_t i = 0; i < apdto.size(); ++i)
	{
		// AppointmentDto 객체를 사용하여 리스트 뷰에 항목 추가
		const AppointmentDto& appointment = apdto[i];
		m_list.InsertItem(i,CString(appointment.patientName.c_str()));
		m_list.SetItemText(i, 1, CString(appointment.symptons.c_str()));
		m_list.SetItemText(i, 2, CString(appointment.appointDate.c_str()));
	}
	


	
	return TRUE;  // 초기화 완료 후 TRUE 반환
}

DoctorPage::~DoctorPage()
{
}
void DoctorPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}
BEGIN_MESSAGE_MAP(DoctorPage, CDialogEx)
END_MESSAGE_MAP()

// DoctorPage 메시지 처리기
