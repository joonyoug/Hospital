// DoctorPage1.cpp: 구현 파일
//

#include "pch.h"
#include "afxdialogex.h"
#include "DoctorPage1.h"
#include "AppointmentDto.h"
#include "AppointmentController.h"
#include "DcodeController.h"
#include "McodeController.h"
#include "Mcode.h"
#include "ChartHistoryDB.h"
#include "PatientController.h"
#include "PatientDto.h"
#include "HosipitalOffice.h"
#include "VaccinnationsDB.h"
#include "VaccinnationsDto.h"
#include "HospitalSystem.h"
#include "Dcode.h"
#include <iostream>
#include <sstream>
#include <string>
#include "ChartHistoryController.h"
#include "PrescriptionsController.h"
#include <chrono>
#include <iomanip>
#include <ctime>
#include "WaitPatientDB.h"

// DoctorPage1 대화 상자
using namespace std;
IMPLEMENT_DYNAMIC(DoctorPage1, CDialogEx)

DoctorPage1::DoctorPage1(CString doctorId,CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DoctorPage1, pParent)
{
	this->doctorId = doctorId;
}

DoctorPage1::~DoctorPage1()
{
}

void DoctorPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PatientInformation, m_patientInfo);
	DDX_Control(pDX, IDC_LIST_ChartHistory, m_ChartHistroy);
	DDX_Control(pDX, IDC_LIST_DCode, m_listDcode);
	DDX_Control(pDX, IDC_LIST_MCode, m_listMcode);
	DDX_Control(pDX, IDC_LIST_appointment, m_listAppointment);
	DDX_Control(pDX, IDC_LIST_MedicineHistroy, m_listVaccin);
	DDX_Control(pDX, IDC_MONTHCALENDAR_doctorPage, m_doctorPageCal);
	DDX_Control(pDX, IDC_BUTTON1, m_static);

	DDX_Control(pDX, IDC_LIST2, m_listWait);
}

BOOL DoctorPage1::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CFont font;
	font.CreatePointFont(120, _T("MS Shell Dlg"));  

	
	setFont(&font);
	

	drawDcode();
	drawMcode();
	DrawAppointment();
	DrawPatient();
	drawInitialChart();
	drawWait();
	return TRUE;
}

BEGIN_MESSAGE_MAP(DoctorPage1, CDialogEx)
	ON_COMMAND(ID_32773, &DoctorPage1::OnMenuOffice)
	
	ON_NOTIFY(NM_CLICK, IDC_LIST_DCode, &DoctorPage1::OnNMClickListDcode)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MCode, &DoctorPage1::OnNMClickListMcode)
	ON_NOTIFY(NM_CLICK, IDC_LIST_appointment, &DoctorPage1::OnNMClickListappointment)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PatientInformation, &DoctorPage1::OnNMClickListPatientinformation)
	ON_NOTIFY(MCN_SELECT, IDC_MONTHCALENDAR_doctorPage, &DoctorPage1::OnMcnSelectMonthcalendardoctorpage)
	
	ON_BN_CLICKED(IDC_BUTTON_OKD, &DoctorPage1::OnBnClickedButtonOkd)
	ON_BN_CLICKED(IDC_BUTTON_OKM, &DoctorPage1::OnBnClickedButtonOkm)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &DoctorPage1::OnNMClickListWait)
END_MESSAGE_MAP()


// DoctorPage1 메시지 처리기

void DoctorPage1::setFont(CFont* font) {
	m_patientInfo.SetFont(font);      // CListCtrl
	m_ChartHistroy.SetFont(font);     // CListCtrl
	m_listDcode.SetFont(font);        // CListCtrl
	m_listMcode.SetFont(font);        // CListCtrl
	m_listVaccin.SetFont(font);       // CComboBox
	m_listAppointment.SetFont(font);  // CComboBox
	m_doctorPageCal.SetFont(font);    // CMonthCalCtrl
	m_listWait.SetFont(font);
	drawFont(font);
	//m_static.SetFont(font);
	//m_static.Invalidate();  // 다시 그리기
	//m_static.UpdateWindow(); // 즉시 업데이트
}
void DoctorPage1::drawFont(CFont *font) {
	CButton* pbutton = (CButton*)GetDlgItem(IDC_BUTTON1);
	pbutton->SetFont(font);

	pbutton = (CButton*)GetDlgItem(IDC_BUTTON2);
	pbutton->SetFont(font);

	pbutton = (CButton*)GetDlgItem(IDC_BUTTON7);
	pbutton->SetFont(font);

	pbutton = (CButton*)GetDlgItem(IDC_BUTTON4);
	pbutton->SetFont(font);

	pbutton = (CButton*)GetDlgItem(IDC_BUTTON5);
	pbutton->SetFont(font);


	pbutton = (CButton*)GetDlgItem(IDC_BUTTON6);
	pbutton->SetFont(font);

	pbutton = (CButton*)GetDlgItem(IDC_BUTTON8);
	pbutton->SetFont(font);

	pbutton = (CButton*)GetDlgItem(IDC_BUTTON9);
	pbutton->SetFont(font);

	pbutton = (CButton*)GetDlgItem(IDC_BUTTON3);
	pbutton->SetFont(font);


	pbutton = (CButton*)GetDlgItem(IDC_BUTTON_OKD);
	pbutton->SetFont(font);

	pbutton = (CButton*)GetDlgItem(IDC_BUTTON_OKM);
	pbutton->SetFont(font);


	CStatic *pstatic = (CStatic*)GetDlgItem(IDC_doc_text1);
	pstatic->SetFont(font);


	pstatic = (CStatic*)GetDlgItem(IDC_doc_text2);
	pstatic->SetFont(font);

	pstatic = (CStatic*)GetDlgItem(IDC_doc_text3);
	pstatic->SetFont(font);

	pstatic = (CStatic*)GetDlgItem(IDC_doc_text4);
	pstatic->SetFont(font);

	pstatic = (CStatic*)GetDlgItem(IDC_doc_text5);
	pstatic->SetFont(font);

	pstatic = (CStatic*)GetDlgItem(IDC_doc_text6);
	pstatic->SetFont(font);

	pstatic = (CStatic*)GetDlgItem(IDC_doc_text7);
	pstatic->SetFont(font);

	pstatic = (CStatic*)GetDlgItem(IDC_doc_text8);
	pstatic->SetFont(font);

	pstatic = (CStatic*)GetDlgItem(IDC_doc_text9);
	pstatic->SetFont(font);

	pstatic = (CStatic*)GetDlgItem(IDC_doc_text10);
	pstatic->SetFont(font);

	//font->CreatePointFont(90, _T("MS Shell Dlg"));

	CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT_Name1);
	edit->SetFont(font);


	edit = (CEdit*)GetDlgItem(IDC_EDIT_ResidentNumber1);
	edit->SetFont(font);

	edit = (CEdit*)GetDlgItem(IDC_EDIT_CC);
	edit->SetFont(font);

	edit = (CEdit*)GetDlgItem(IDC_EDIT_DCode);
	edit->SetFont(font);


	edit = (CEdit*)GetDlgItem(IDC_EDIT_Diagnoisis);
	edit->SetFont(font);

	edit = (CEdit*)GetDlgItem(IDC_EDIT_Menifestitation);
	edit->SetFont(font);

	edit = (CEdit*)GetDlgItem(IDC_EDIT_Name);
	edit->SetFont(font);

	
	edit = (CEdit*)GetDlgItem(IDC_EDIT_ResidentNumber);
	edit->SetFont(font);
	

	edit = (CEdit*)GetDlgItem(IDC_EDIT_Mcode);
	edit->SetFont(font);

	edit = (CEdit*)GetDlgItem(IDC_EDIT_Method);
	edit->SetFont(font);




}
void DoctorPage1::drawMcode() {
	m_listMcode.ModifyStyle(0, LVS_REPORT);
	m_listMcode.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT); // 확장 스타일 설정


	m_listMcode.InsertColumn(0, _T("코드"), LVCFMT_CENTER, 100);
	m_listMcode.InsertColumn(1, _T("이름"), LVCFMT_CENTER, 100);
	

	CRect rect;
	m_listMcode.GetClientRect(&rect);
	int width = rect.Width();
	int otherColumnsWidth = 100 * 1;
	m_listMcode.SetColumnWidth(1, width - otherColumnsWidth);

	McodeController dc;
	std::vector<Mcode> mcode = dc.selectMcode();

	for (size_t i = 0; i < mcode.size(); ++i)
	{
		m_listMcode.InsertItem(i, CString(mcode[i].getCode().c_str()));
		m_listMcode.SetItemText(i, 1, CString(mcode[i].getName().c_str()));
	}

}
void DoctorPage1::setResidentNumber(std::string residentNumber) {
	m_residentNumber = residentNumber;
}
void DoctorPage1::drawPatientInfo(CString name) {
	PatientController pt;
	PatientDto dto = pt.searchPatient(std::string(CT2A(name)));
	m_patientInfo.DeleteAllItems();
	// 환자 정보를 조회할 수 없을 때
	if (dto.residentNumber.empty()) {
		// 예외 처리: 환자 정보가 없을 경우 사용자에게 알림
		AfxMessageBox(_T("환자 정보를 찾을 수 없습니다."));
		return;
	}

	
	m_residentNumber = dto.residentNumber;
	m_name = dto.name;


	// 각 항목의 텍스트 설정
	m_patientInfo.InsertItem(0, CString(dto.name.c_str()));
	m_patientInfo.SetItemText(0, 1, CString(dto.residentNumber.c_str()));  // 주민등록번호
	m_patientInfo.SetItemText(0, 2, CString(dto.gender.c_str()));        // 성별
	m_patientInfo.SetItemText(0, 3, CString(dto.phone.c_str()));         // 전화번호
	for (int col = 0; col < m_patientInfo.GetHeaderCtrl()->GetItemCount(); col++) {
		m_patientInfo.SetColumnWidth(col, LVSCW_AUTOSIZE_USEHEADER);
	}
}

void DoctorPage1::drawDcode() {
	m_listDcode.ModifyStyle(0, LVS_REPORT); // 리포트 뷰 스타일 설정
	m_listDcode.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT); // 확장 스타일 설정


	m_listDcode.InsertColumn(0, _T("코드"), LVCFMT_CENTER, 100);
	m_listDcode.InsertColumn(1, _T("이름"), LVCFMT_CENTER, 100);
;

	CRect rect;
	m_listDcode.GetClientRect(&rect);
	int width = rect.Width();
	int otherColumnsWidth = 100 * 1;
	m_listDcode.SetColumnWidth(1, width - otherColumnsWidth); 

	DcodeController dc;
	std::vector<Dcode> dcode = dc.selectDcode();

	for (size_t i = 0; i < dcode.size(); ++i)
	{
		m_listDcode.InsertItem(i, CString(dcode[i].getKcdcode().c_str()));
		m_listDcode.SetItemText(i, 1, CString(dcode[i].getName().c_str()));
	}


}
void DoctorPage1::DrawPatient() {
	m_patientInfo.InsertColumn(0, _T("이름"),LVCFMT_CENTER, 100);
	m_patientInfo.InsertColumn(1, _T("주민번호"), LVCFMT_CENTER, 100);
	m_patientInfo.InsertColumn(2, _T("성"), LVCFMT_CENTER, 100);
	m_patientInfo.InsertColumn(3, _T("번호"), LVCFMT_CENTER, 100);
	m_listVaccin.InsertColumn(0, _T("예방접종명"), LVCFMT_CENTER, 100);
	m_listVaccin.InsertColumn(1, _T("약품명"), LVCFMT_CENTER, 100);
	m_listVaccin.InsertColumn(2, _T("차수"), LVCFMT_CENTER, 100);
	m_listVaccin.InsertColumn(3, _T("일자"), LVCFMT_CENTER, 100);

	
}
void DoctorPage1::DrawAppointment() {

	AppointmentController ap;
	std::vector<AppointmentDto> dto = ap.selectAppointment(std::string(CT2A(doctorId)));
	m_listAppointment.ModifyStyle(0, LVS_REPORT);
	m_listAppointment.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);


	m_listAppointment.InsertColumn(0, _T("이름"), LVCFMT_CENTER, 100);
	m_listAppointment.InsertColumn(1, _T("증상"), LVCFMT_CENTER, 100);

	
	CRect rect;
	m_listAppointment.GetClientRect(&rect);
	int width = rect.Width();
	int otherColumnsWidth = 100 * 1;
	m_listAppointment.SetColumnWidth(1, width - otherColumnsWidth);

	for (int i = 0;i < dto.size();i++) {
		m_listAppointment.InsertItem(i, CString(dto[i].patientName.c_str()));
		m_listAppointment.SetItemText(i,1, CString(dto[i].symptons.c_str()));
		
	}
}
CString DoctorPage1::getTime() {
	// 선택된 날짜를 저장할 COleDateTime 객체 선언
	COleDateTime selectedDate;

	// 선택된 날짜가 있는지 확인
	if (m_doctorPageCal.GetCurSel(selectedDate)) {
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


void DoctorPage1::OnMenuOffice()
{
	HosipitalOffice off(doctorId);
	this->EndDialog(IDOK);
	off.DoModal();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void DoctorPage1::OnNMClickListDcode(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pItemActivate = (LPNMITEMACTIVATE)pNMHDR;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString kode, now;

	GetDlgItemText(IDC_EDIT_DCode,now);

	CString comma = _T(",");

	int selected = pItemActivate->iItem;
	if (selected != -1) {
		
		kode = m_listDcode.GetItemText(selected, 0);	
		if (now.IsEmpty()) {
			SetDlgItemText(IDC_EDIT_DCode, kode);
		}
		else {
			SetDlgItemText(IDC_EDIT_DCode, now + comma + kode);
		}
	}
	*pResult = 0;
}
void DoctorPage1::drawVaccinations() {

	VaccinnationsDB db;
	std::vector<VaccinnationsDto> dto = db.selectVaccin(m_residentNumber);
	m_listVaccin.DeleteAllItems();

	CRect rect;
	m_listVaccin.GetClientRect(&rect);
	int width = rect.Width();
	int otherColumnsWidth = 100 * 3;
	m_listVaccin.SetColumnWidth(1, width - otherColumnsWidth);
	CString th;

	for (int i = 0;i< dto.size(); i++) 
	{
		m_listVaccin.InsertItem(i, CString(dto[i].v_name.c_str()));
		m_listVaccin.SetItemText(i, 1, CString(dto[i].d_name.c_str()));
		th.Format(_T("%d"), dto[i].th);
		m_listVaccin.SetItemText(i, 2, th);
		m_listVaccin.SetItemText(i, 3, CString(dto[i].date.c_str()));
	}
}
void DoctorPage1::OnNMClickListMcode(NMHDR* pNMHDR, LRESULT* pResult)
{

	LPNMITEMACTIVATE pItemActivate = (LPNMITEMACTIVATE)pNMHDR;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString kode, now;

	GetDlgItemText(IDC_EDIT_Mcode, now);

	CString comma = _T(",");

	int selected = pItemActivate->iItem;
	if (selected != -1) {

		kode = m_listMcode.GetItemText(selected, 0);
		if (now.IsEmpty()) {
			SetDlgItemText(IDC_EDIT_Mcode, kode);
		}
		else {
			SetDlgItemText(IDC_EDIT_Mcode, now + comma + kode);
		}
	}
}


void DoctorPage1::OnNMClickListappointment(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pItemActivate = (LPNMITEMACTIVATE)pNMHDR;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int selected = pItemActivate->iItem;
	if (selected != -1) {
		drawPatientInfo(m_listAppointment.GetItemText(selected,0));
		drawChartHistory();
		drawVaccinations();
		m_cc = std::string(CT2A(m_listAppointment.GetItemText(selected, 1)));
	}
	*pResult = 0;
}
void DoctorPage1::drawInitialChart() {
	m_ChartHistroy.InsertColumn(0, _T("주민번호"), LVCFMT_CENTER, 100);
	m_ChartHistroy.InsertColumn(1, _T("내원일"), LVCFMT_CENTER, 100);
	m_ChartHistroy.InsertColumn(2, _T("증상"), LVCFMT_CENTER, 100);
	m_ChartHistroy.InsertColumn(3, _T("진단"), LVCFMT_CENTER, 100);
	CRect rect;
	m_ChartHistroy.GetClientRect(&rect);
	int width = rect.Width();
	int otherColumnsWidth = 100 * 3;
	m_ChartHistroy.SetColumnWidth(3, width - otherColumnsWidth);

}

void DoctorPage1::drawChartHistory() {

	m_ChartHistroy.DeleteAllItems();
	

	ChartHistoryDB db;
	vector<ChatHistoryDto> dto = db.selectedChart(m_residentNumber);



	for (int i = 0;i < dto.size();i++) {
		m_ChartHistroy.InsertItem(i, CString(dto[i].residentNumber.c_str()));
		m_ChartHistroy.SetItemText(i,1 ,CString(dto[i].date.c_str()));
		m_ChartHistroy.SetItemText(i, 2, CString(dto[i].cc.c_str()));
		m_ChartHistroy.SetItemText(i, 3, CString(dto[i].manifestation.c_str()));
	}
	for (int col = 0; col < m_ChartHistroy.GetHeaderCtrl()->GetItemCount(); col++) {
		m_ChartHistroy.SetColumnWidth(col, LVSCW_AUTOSIZE_USEHEADER);
	}

}

void DoctorPage1::OnNMClickListPatientinformation(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	SetDlgItemText(IDC_EDIT_Name1, CString(m_name.c_str()));
	SetDlgItemText(IDC_EDIT_Name, CString(m_name.c_str()));

	SetDlgItemText(IDC_EDIT_ResidentNumber1, CString(m_residentNumber.c_str()));
	SetDlgItemText(IDC_EDIT_ResidentNumber, CString(m_residentNumber.c_str()));

	SetDlgItemText(IDC_EDIT_CC, CString(m_cc.c_str()));


	*pResult = 0;
}


void DoctorPage1::OnMcnSelectMonthcalendardoctorpage(NMHDR* pNMHDR, LRESULT* pResult)
{
	
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);

	
	CString str = getTime();

	// 예약 목록 불러오기
	AppointmentController ap;
	std::vector<AppointmentDto> dto = ap.dayAppointment(std::string(CT2A(doctorId)), std::string(CT2A(str)));
	std::cout <<std::string(CT2A(str));
	// 예약 목록을 리스트에 표시
	drawDayAppointment(dto);

	*pResult = 0;
}

void DoctorPage1::drawDayAppointment(std::vector<AppointmentDto> dto) {
	// 리스트 컨트롤 설정
	m_listAppointment.ModifyStyle(0, LVS_REPORT);
	m_listAppointment.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	// 기존의 모든 항목을 삭제
	m_listAppointment.DeleteAllItems();

	// 컬럼 설정
	m_listAppointment.InsertColumn(0, _T("이름"), LVCFMT_CENTER, 100);
	m_listAppointment.InsertColumn(1, _T("증상"), LVCFMT_CENTER, 100);

	// 열 너비 설정
	CRect rect;
	m_listAppointment.GetClientRect(&rect);
	int width = rect.Width();
	int otherColumnsWidth = 100 * 1;
	m_listAppointment.SetColumnWidth(1, width - otherColumnsWidth);
	
	if (dto.empty()) {
		m_listAppointment.InsertItem(0, _T("예약 없음"));
		m_listAppointment.SetItemText(0, 1, _T(""));
		return;
	}

	for (int i = 0;i < dto.size();i++) {
		m_listAppointment.InsertItem(i, CString(dto[i].patientName.c_str()));
		m_listAppointment.SetItemText(i, 1, CString(dto[i].symptons.c_str()));
		
	}
}
vector<string> DoctorPage1::split(string dcode, string Delimiter) {

	vector<string> answer;
	stringstream ss(dcode);
	string temp;
	char deli = Delimiter[0];
	while (getline(ss, temp, deli)) {
		answer.push_back(temp);
	}

	return answer;
}

void DoctorPage1::OnBnClickedButtonOkd()
{
	
	CString resident, cc, dcode, meni;
	GetDlgItemText(IDC_EDIT_ResidentNumber1, resident);
	GetDlgItemText(IDC_EDIT_CC, cc);
	GetDlgItemText(IDC_EDIT_DCode, dcode);
	GetDlgItemText(IDC_EDIT_Menifestitation, meni);

	std::vector<std::string> dcodeVector = split(std::string(CT2A(dcode)),",");

	ChartHistoryController chc;
	// 현재 시간 구하기
	auto now = chrono::system_clock::now();
	time_t now_c = chrono::system_clock::to_time_t(now);

	tm now_tm;
	localtime_s(&now_tm, &now_c);  

	stringstream ss;
	ss << put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
	bool check = chc.addChart(std::string(CT2A(resident)),std::string(CT2A(doctorId)),ss.str(), 
		std::string(CT2A(cc)),std::string(CT2A(meni)), dcodeVector);

	if (!check) {
		AfxMessageBox(_T("추가실패."));
	}
	else {
		deleteWait(resident);
		AfxMessageBox(_T("추가"));
		SetDlgItemText(IDC_EDIT_ResidentNumber1, _T(""));
		SetDlgItemText(IDC_EDIT_CC, _T(""));
		SetDlgItemText(IDC_EDIT_DCode, _T(""));
		SetDlgItemText(IDC_EDIT_Menifestitation, _T(""));
		SetDlgItemText(IDC_EDIT_Name1, _T(""));
		SetDlgItemText(IDC_EDIT_DCode, _T(""));
		SetDlgItemText(IDC_EDIT_Diagnoisis, _T(""));	
	}

	/*
	GetDlgItemText(IDC_EDIT_ResidentNumber1, resident);
	GetDlgItemText(IDC_EDIT_CC, cc);
	GetDlgItemText(IDC_EDIT_DCode, dcode);
	GetDlgItemText(IDC_EDIT_Menifestitation, meni);
	*/

}
void DoctorPage1::drawWait() {
	m_listWait.ModifyStyle(0, LVS_REPORT); // 리포트 뷰 스타일 설정
	m_listWait.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT); // 확장 스타일 설정
	m_listWait.InsertColumn(0, _T("이름"), LVCFMT_CENTER, 100);

	WaitPatientDB db;
	std::vector<WaitPatient> dto = db.selectWait();
	std::cout << dto.size() << std::endl;
	for (int i = 0;i < dto.size();i++) {
		m_listWait.InsertItem(i, CString(dto[i].getName().c_str()));
	}
}
void DoctorPage1::OnBnClickedButtonOkm()
{
	/*std::string residentNumber, std::string employee_number
		, std::string date, std::string method, std::string dosage, float daily_dosage,
		int frequency, int duration, std::string notes
*/
	CString residentNumber, employee_number, date, method, mcode;

	GetDlgItemText(IDC_EDIT_ResidentNumber, residentNumber);
	GetDlgItemText(IDC_EDIT_Method, method);
	GetDlgItemText(IDC_EDIT_Mcode, mcode);
////	GetDlgItemText(IDC_EDIT_daily_dosage,daily_dosage);
//	GetDlgItemText(IDC_EDIT_frequency, frequency);
	//GetDlgItemText(IDC_EDIT_duration, duration);
//	GetDlgItemText(IDC_EDIT_note, notes);
	PrescriptionsController ppc;
	auto now = chrono::system_clock::now();
	time_t now_c = chrono::system_clock::to_time_t(now);
	tm now_tm;
	localtime_s(&now_tm, &now_c);
	stringstream ss;
	ss << put_time(&now_tm, "%Y-%m-%d %H:%M:%S");

	bool check = ppc.addPrescriptions(std::string(CT2A(residentNumber)), std::string(CT2A(doctorId)), ss.str(),
		std::string(CT2A(method)),std::string(CT2A(mcode)));
	if (check) {
		AfxMessageBox(_T("등록"));
		SetDlgItemText(IDC_EDIT_Name, _T(""));
		SetDlgItemText(IDC_EDIT_ResidentNumber, _T(""));
		SetDlgItemText(IDC_EDIT_Mcode, _T(""));
		SetDlgItemText(IDC_EDIT_Method, _T(""));

	}
	else {
		AfxMessageBox(_T("실패"));
	}	
}
bool DoctorPage1::deleteWait(CString residentNumber) {
	
	WaitPatientDB db;
	bool check=db.deleteWait(std::string(CT2A(residentNumber)));
	m_listWait.DeleteAllItems();

	std::vector<WaitPatient> dto = db.selectWait();

	for (int i = 0;i < dto.size();i++) {
		m_listWait.InsertItem(i, CString(dto[i].getName().c_str()));
	}
}

void DoctorPage1::OnNMClickListWait(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int selected = pNMItemActivate->iItem;
	if (selected != -1) {
		drawPatientInfo(m_listWait.GetItemText(selected, 0));
		drawChartHistory();
		drawVaccinations();
		
	}
	*pResult = 0;
}



