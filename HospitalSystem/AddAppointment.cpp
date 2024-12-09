#include "pch.h"
#include "HospitalSystem.h"
#include "afxdialogex.h"
#include "AddAppointment.h"
#include "HosipitalOffice.h"


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
	CString phone, doctorId, symptoms, date, name, residentNumber;
	GetDlgItemText(IDC_EDIT_ResidentNumber, residentNumber);
	GetDlgItemText(IDC_EDIT_Phone, name);
	GetDlgItemText(IDC_EDIT_Phone, phone);
	GetDlgItemText(IDC_EDIT_DoctorId, doctorId);
	GetDlgItemText(IDC_EDIT_symptoms, symptoms);
	date = getTime() + " " + getComboBox();
	/*
	appointment_id,resident_number
	employee_number ,date,CC
	std::string doctorId, std::string sympton
	*/
	AppointmentController ap;
	bool check = ap.addAppointment(std::string(CT2A(residentNumber)), std::string(CT2A(name)), std::string(CT2A(date)),
		std::string(CT2A(doctorId)), std::string(CT2A(symptoms)));

	if (check) {
		AfxMessageBox(_T("예약성공"));
		NotifyParent();
		this->EndDialog(IDOK);

	}
	else { AfxMessageBox(_T("예약실패")); }


}
void AddAppointment::drawComboBox() {
	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO1);
	if (pComboBox != nullptr) {

		for (int hour = 10; hour <= 21; ++hour) {
			CString timeString;
			timeString.Format(_T("%d 시"), hour);
			pComboBox->AddString(timeString);
		}

		pComboBox->SetCurSel(0);
	}
}

BOOL AddAppointment::OnInitDialog()
{
	CDialog::OnInitDialog();
	drawComboBox();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
CString AddAppointment::getTime()
{
	CMonthCalCtrl* pMonthCal = (CMonthCalCtrl*)GetDlgItem(IDC_MONTHCALENDAR_Appointment);

	// 선택된 날짜를 저장할 COleDateTime 객체 선언
	COleDateTime selectedDate;

	// 선택된 날짜가 있는지 확인
	if (pMonthCal->GetCurSel(selectedDate))
	{
		// 날짜 선택이 정상적으로 되었을 경우
		CString strDate;
		strDate.Format(_T("%04d-%02d-%02d"), selectedDate.GetYear(), selectedDate.GetMonth(), selectedDate.GetDay());
		return strDate;
	}
	else
	{
		// 날짜가 선택되지 않았을 경우
		AfxMessageBox(_T("날짜를 선택해주세요."));
		return _T(""); // 빈 문자열 반환
	}
}

CString AddAppointment::getComboBox() {

	// 콤보박스에서 현재 선택된 시간 가져오기
	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO1);
	int selectedIndex = pComboBox->GetCurSel();
	CString selectedText;
	pComboBox->GetLBText(selectedIndex, selectedText);  // 선택된 시간 ("10 시"와 같은 형식)

	// 선택된 시간에서 " 시" 부분을 제거하고, "hh:00:00" 형식으로 변환
	CString formattedTime;
	formattedTime.Format(_T("%s:00:00"), selectedText.Left(selectedText.GetLength() - 2));  // "10 시" -> "10:00:00"


	return formattedTime;
}


void AddAppointment::setParent(CWnd* pParent) {
	pParnet = pParent;	
}
void AddAppointment::NotifyParent() {
	if (pParnet != nullptr) {

		HosipitalOffice* pDoctorPage = dynamic_cast<HosipitalOffice*>(pParnet);
		if (pDoctorPage) {
			pDoctorPage->drawAppointment();
		}
	}
}
