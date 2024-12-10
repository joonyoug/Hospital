// HosipitalOffice.cpp: 구현 파일
//

#include "pch.h"
#include "HospitalSystem.h"
#include "afxdialogex.h"
#include "HosipitalOffice.h"
#include "AppointmentController.h"
#include "AddAppointment.h"
#include "Addpatients.h"
#include "AlreadyPatient.h"
#include <vector>

// HosipitalOffice 대화 상자

IMPLEMENT_DYNAMIC(HosipitalOffice, CDialogEx)

HosipitalOffice::HosipitalOffice(CString doctorId, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Doctor, pParent)
{
	this->doctorId = doctorId;
}
CString HosipitalOffice::getDoctorId() {
	return this->doctorId;
}
BOOL HosipitalOffice::OnInitDialog()
{	
	CDialogEx::OnInitDialog();  // 기본 초기화
	
	drawPatient();
	drawAppointment();
	drawWait();
	return TRUE;  // 초기화 완료 후 TRUE 반환
}

HosipitalOffice::~HosipitalOffice()                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
{
}
void HosipitalOffice::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_LIST3, m_patientInfoList);
	DDX_Control(pDX, IDC_LIST_wait, m_list_wait);
}
BEGIN_MESSAGE_MAP(HosipitalOffice, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_addAppointment, &HosipitalOffice::OnBnClickedButtonaddappointment)
	ON_BN_CLICKED(IDC_BUTTON_AddPatient, &HosipitalOffice::OnBnClickedButtonAddpatient)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &HosipitalOffice::OnNMClickListAppointment)
	ON_NOTIFY(NM_CLICK, IDC_LIST3, &HosipitalOffice::OnNMClickListPatientInfo)
	ON_BN_CLICKED(IDC_BTN_alreadyPatient, &HosipitalOffice::OnBnClickedBtnalreadypatient)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// HosipitalOffice 메시지 처리기
void HosipitalOffice::OnBnClickedButtonaddappointment()
{
	AddAppointment ap;
	ap.setParent(this);
	ap.DoModal();

}

void HosipitalOffice::drawPatient() {
	m_patientInfoList.ModifyStyle(0, LVS_REPORT); // 리포트 뷰 스타일 설정
	m_patientInfoList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT); // 확장 스타일 설정


	m_patientInfoList.InsertColumn(0, _T("이름"), LVCFMT_CENTER, 100);
	m_patientInfoList.InsertColumn(1, _T("주민번호"), LVCFMT_CENTER, 100);
	m_patientInfoList.InsertColumn(2, _T("성"), LVCFMT_CENTER, 50);
	m_patientInfoList.InsertColumn(3, _T("전화번호"), LVCFMT_CENTER, 100);
	
	CRect rect;
	m_patientInfoList.GetClientRect(&rect);
	int width = rect.Width(); 
	int otherColumnsWidth = 100 * 3; 
	m_patientInfoList.SetColumnWidth(3, width - otherColumnsWidth); // 예약시간 열 확장
}
void HosipitalOffice::drawWait() {

	m_list_wait.ModifyStyle(0, LVS_REPORT); // 리포트 뷰 스타일 설정
	m_list_wait.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT); // 확장 스타일 설정

	m_list_wait.InsertColumn(0, _T("이름"), LVCFMT_CENTER, 100);
}




void HosipitalOffice::drawAppointment() {
	m_list.DeleteAllItems();
	m_list.ModifyStyle(0, LVS_REPORT);
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EDITLABELS);

	// 컬럼 추가
	m_list.InsertColumn(0, _T("이름"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(1, _T("전화번호"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(2, _T("증상"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(3, _T("예약일"), LVCFMT_CENTER, 100);

	CRect rect;
	m_list.GetClientRect(&rect);
	int width = rect.Width(); // 올바른 사용
	int otherColumnsWidth = 100 * 3; // tRect().Width();다른 열의 총 너비 (100 * 3)
	m_list.SetColumnWidth(3, width - otherColumnsWidth); // 예약시간 열 확장
	
	AppointmentController apc;
	std::vector<AppointmentDto> apdto = apc.selectAppointment(std::string
	(CT2A(this->getDoctorId())));

	for (size_t i = 0; i < apdto.size(); ++i) 
	{
		// AppointmentDto 객체를 사용하여 리스트 뷰에 항목 추가
		const AppointmentDto& appointment = apdto[i];
		m_list.InsertItem(i, CString(appointment.patientName.c_str()));
		m_list.SetItemText(i, 1, CString(appointment.patientPhone.c_str()));
		m_list.SetItemText(i, 2, CString(appointment.symptons.c_str()));
		m_list.SetItemText(i, 3, CString(appointment.appointDate.c_str()));
	}
	
}

void HosipitalOffice::OnBnClickedButtonAddpatient()
{
	Addpatients patient;
	patient.setParent(this);
	patient.DoModal();

}


void HosipitalOffice::OnNMClickListAppointment(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pItemActivate = (LPNMITEMACTIVATE)pNMHDR;
	int selected = pItemActivate->iItem;

	if (selected != -1) {
		CString patientName = m_list.GetItemText(selected, 0);  // 이름
		CString patientPhone = m_list.GetItemText(selected, 1); // 전화번호
		CString patientSymptoms = m_list.GetItemText(selected, 2); // 증상
		CString appointmentDate = m_list.GetItemText(selected, 3); // 예약시간

		
		// 환자 정보 업데이트
		UpdatePatientInfo(std::string(CT2A(patientName)));
	}

	*pResult = 0;
}
void HosipitalOffice::UpdateWait(CString name) {
   
    int index = m_list_wait.InsertItem(m_list_wait.GetItemCount(), name);
  
}

void HosipitalOffice::UpdatePatientInfo(std::string name)
{	

	/*
	m_patientInfoList.InsertColumn(0, _T("이름"), LVCFMT_CENTER, 50);
	m_patientInfoList.InsertColumn(1, _T("주민번호"), LVCFMT_CENTER, 50);
	m_patientInfoList.InsertColumn(2, _T("전화번호"), LVCFMT_CENTER, 50);
	m_patientInfoList.InsertColumn(3, _T("성"), LVCFMT_CENTER, 50);
	
	
	*/
	PatientController pt;
	PatientDto dto = pt.searchPatient(name);

	
	// 첫 번째 항목이 없다면 새 항목을 추가하고, 있다면 기존 항목을 갱신
	if (m_patientInfoList.GetItemCount() > 0) {
		// 기존 항목 갱신
		m_patientInfoList.SetItemText(0, 0,CString( dto.name.c_str()));
		m_patientInfoList.SetItemText(0,1, CString(dto.residentNumber.c_str()));      // 전화번호 설정
		m_patientInfoList.SetItemText(0,3, CString(dto.phone.c_str()));   // 증상 설정
		m_patientInfoList.SetItemText(0,2, CString(dto.gender.c_str()));       // 예약시간 설정
	}
	else {
		// 첫 번째 항목 추가
		int index = m_patientInfoList.InsertItem(0, CString(name.c_str()));  // 첫 번째 행에 환자 이름 추가
		m_patientInfoList.SetItemText(index, 1,CString(dto.residentNumber.c_str()));      // 전화번호 설정
		m_patientInfoList.SetItemText(index, 3,CString(dto.phone.c_str()));   // 증상 설정
		m_patientInfoList.SetItemText(index, 2,CString(dto.gender.c_str()));       // 예약시간 설정
	
	}
}

void HosipitalOffice::OnNMClickListPatientInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int selected = pNMItemActivate->iItem;

	AfxMessageBox(_T("asd"));
	CString name;
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void HosipitalOffice::OnBnClickedBtnalreadypatient()
{
	AlreadyPatient ap;
	ap.setParent(this);
	ap.DoModal();

}


BOOL HosipitalOffice::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);

	pDC->FillSolidRect(rect, RGB(255, 255, 255));	// 변경하고 싶은 색상 RGB색
	return TRUE;

	return CDialogEx::OnEraseBkgnd(pDC);
}
