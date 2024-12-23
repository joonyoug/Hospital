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
#include "DoctorPage1.h"
#include "DetailPage.h"
#include "WaitPatient.h"
#include "WaitPatientDB.h"
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
	SetDlgItemText(IDC_STATIC_ID, doctorId);
	drawPatient();
	drawAppointment();
	drawWait();
	CFont font;
	font.CreatePointFont(120, _T("맑은 고딕"));
	drawfont(&font);
	drawItem();
	m_toolTip.Create(this);
	m_toolTip.AddTool(&m_list, _T("왼쪽 버튼 클릭시 환자 정보 보기 오른쪽 클릭시 대기열 추가"));
	m_toolTip.Activate(TRUE);

	
	DWORD dwStyle = m_list.GetExtendedStyle();
	dwStyle &= ~LVS_EX_TRACKSELECT;  // LVS_EX_TRACKSELECT 스타일 제거
	m_list.SetExtendedStyle(dwStyle);


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
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_officePageCal);
	
}
BEGIN_MESSAGE_MAP(HosipitalOffice, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_addAppointment, &HosipitalOffice::OnBnClickedButtonaddappointment)
	ON_BN_CLICKED(IDC_BUTTON_AddPatient, &HosipitalOffice::OnBnClickedButtonAddpatient)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &HosipitalOffice::OnNMClickListAppointment)
	ON_NOTIFY(NM_CLICK, IDC_LIST3, &HosipitalOffice::OnNMClickListPatientInfo)
	ON_BN_CLICKED(IDC_BTN_alreadyPatient, &HosipitalOffice::OnBnClickedBtnalreadypatient)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_32771, &HosipitalOffice::OnMenuDoctor)
	ON_NOTIFY(MCN_SELECT, IDC_MONTHCALENDAR1, &HosipitalOffice::OnMcnSelectMonthcalendar1)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_SearchPatient, &HosipitalOffice::OnBnClickedButtonSearchpatient)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &HosipitalOffice::OnNMRClicAppointment)
END_MESSAGE_MAP()

void HosipitalOffice::drawfont(CFont* font) {

	//CButton* pbutton;
	

	//pbutton = (CButton*)GetDlgItem(IDC_BTN_1);
//	pbutton->SetFont(font);

	//pbutton = (CButton*)GetDlgItem(IDC_BUTTON2);
	//pbutton->SetFont(font);

	//pbutton = (CButton*)GetDlgItem(IDC_BTN_1);
	//pbutton->SetFont(font);
	//CRect rect;
	//pbutton->GetClientRect(&rect);
	//std::cout << rect.Width() << std::endl;
	//std::cout << rect.Height() << std::endl;



	m_list.SetFont(font);
	m_list_wait.SetFont(font);
	m_patientInfoList.SetFont(font);
	

}
void HosipitalOffice::drawItem() {
	
}

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
	m_list_wait.InsertColumn(1, _T("증상"), LVCFMT_CENTER, 100);
	WaitPatientDB db;
	std::vector<WaitPatient> dto = db.selectWait();
	std::cout << dto.size() << std::endl;
	for (int i = 0;i < dto.size();i++) {
		m_list_wait.InsertItem(i, CString(dto[i].getName().c_str()));
		m_list_wait.SetItemText(i, 1, CString(dto[i].getSymtones().c_str()));

	}
}
void HosipitalOffice::drawAppointment() {

	m_list.DeleteAllItems();

	m_list.ModifyStyle(0, LVS_REPORT);
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EDITLABELS);

	
	if (m_list.GetHeaderCtrl()->GetItemCount()==0) {
		m_list.InsertColumn(0, _T("이름"), LVCFMT_CENTER, 100);
		m_list.InsertColumn(1, _T("전화번호"), LVCFMT_CENTER, 100);
		m_list.InsertColumn(2, _T("증상"), LVCFMT_CENTER, 100);
		m_list.InsertColumn(3, _T("예약일"), LVCFMT_CENTER, 100);

		
	}
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
void HosipitalOffice::UpdateWait(CString name,CString symtons) {

     int cnt=m_list_wait.InsertItem(m_list_wait.GetItemCount(), name);
	 m_list_wait.SetItemText(cnt,1,symtons);
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
	m_resident = dto.residentNumber.c_str();
	
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
	detailPatient();
	
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

	pDC->FillSolidRect(rect, RGB(255, 255, 255));	
	return TRUE;

	return CDialogEx::OnEraseBkgnd(pDC);
}


void HosipitalOffice::OnMenuDoctor()
{
	DoctorPage1 doc(doctorId);
	this->EndDialog(IDOK);

	// 새로운 다이얼로그 모달로 띄우기
	doc.DoModal();
}

void HosipitalOffice::drawDayAppointment(std::vector<AppointmentDto> dto) {	
	m_list.DeleteAllItems();
	if (dto.empty()) {
			m_list.InsertItem(0, _T("예약 없음"));
			m_list.SetItemText(0, 1, _T(""));
			return;
	}

	for (int i = 0;i < dto.size();i++) {
		m_list.InsertItem(i, CString(dto[i].patientName.c_str()));
		m_list.SetItemText(i, 1, CString(dto[i].patientPhone.c_str()));
		m_list.SetItemText(i, 2, CString(dto[i].symptons.c_str()));
		m_list.SetItemText(i, 3, CString(dto[i].appointDate.c_str()));
	}

	}

void HosipitalOffice::detailPatient() {

	//AfxMessageBox(_T("dddd"));
	m_detail = new DetailPage();
	m_detail->setResident(m_resident);
	m_detail->Create(IDD_DetailPage);
	m_detail->ShowWindow(SW_SHOW);

	
}

void HosipitalOffice::OnMcnSelectMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = getTime();

	// 예약 목록 불러오기
	AppointmentController ap;
	std::vector<AppointmentDto> dto = ap.dayAppointment(std::string(CT2A(doctorId)), std::string(CT2A(str)));
	std::cout << std::string(CT2A(str));
	// 예약 목록을 리스트에 표시
	drawDayAppointment(dto);

	*pResult = 0;
}
CString HosipitalOffice::getTime() {
	COleDateTime selectedDate;

	// 선택된 날짜가 있는지 확인
	if (m_officePageCal.GetCurSel(selectedDate)) {
		// 선택된 날짜가 있다면, "YYYY-MM-DD" 형식으로 포맷
		CString strDate;
		strDate.Format(_T("%04d-%02d-%02d"), selectedDate.GetYear(), selectedDate.GetMonth(), selectedDate.GetDay());

		// 날짜 출력 (디버깅용)
		std::cout << CT2A(strDate.GetString()) << std::endl;

		return strDate;
	}

	// 날짜가 선택되지 않았을 경우 빈 문자열 반환
	return _T("");
}


void HosipitalOffice::OnDestroy()
{
	CDialogEx::OnDestroy();
	delete m_detail;
	delete this->m_search;
}


void HosipitalOffice::OnBnClickedButtonSearchpatient()
{
	m_search = new SearchPage();
	m_search->Create(IDD_SearchPage);
	m_search->ShowWindow(SW_SHOW);

}


void HosipitalOffice::OnNMRClicAppointment(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString name,symtons;

	int selected = pNMItemActivate->iItem;
	if (selected != -1) {
		name=m_list.GetItemText(selected, 0);
		symtons = m_list.GetItemText(selected, 1);
		PatientController db;
		PatientDto dto=db.searchPatient(std::string(CT2A(name)));
		UpdateWait(CString(dto.name.c_str()),symtons);
		WaitPatientDB pdb;
		pdb.addWait(dto.name.c_str(), dto.residentNumber.c_str(),std::string(CT2A(symtons)));
	}
	*pResult = 0;
}


BOOL HosipitalOffice::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (m_toolTip.GetSafeHwnd())
	{
		m_toolTip.RelayEvent(pMsg);  // 툴팁 이벤트 전달
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
