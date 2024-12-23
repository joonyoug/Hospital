// DetailPage.cpp: 구현 파일
//

#include "pch.h"
#include "HospitalSystem.h"
#include "afxdialogex.h"
#include "DetailPage.h"
#include "PatientController.h"
#include "PatientDto.h"

// DetailPage 대화 상자

IMPLEMENT_DYNAMIC(DetailPage, CDialogEx)

DetailPage::DetailPage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DetailPage, pParent)
{

}

DetailPage::~DetailPage()
{
}

void DetailPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(DetailPage, CDialogEx)
END_MESSAGE_MAP()
// DetailPage 메시지 처리기
void DetailPage::setResident(CString residentNumber) {
	
	this->residentNumber = residentNumber;
}
void DetailPage::drawDetail() {
	
	PatientController pc;
	PatientDto dt = pc.selectPatient(std::string(CT2A(residentNumber)));
	
	if (dt.name == "-1") {
		std::cout << "asd";
		AfxMessageBox(_T("없는 환자입니다."));
	}
	else {
		SetDlgItemText(IDC_EDIT_detaiName, CString(dt.name.c_str()));
		SetDlgItemText(IDC_EDIT_blood_type, CString(dt.bloodType.c_str()));
		SetDlgItemText(IDC_EDIT_detailResidentNumber, CString(dt.residentNumber.c_str()));
		SetDlgItemText(IDC_EDIT_detailAddr, CString(dt.address.c_str()));
		SetDlgItemText(IDC_EDIT_detailDosing, CString(dt.dosingList.c_str()));
		SetDlgItemText(IDC_EDIT_detailEmer, CString(dt.emergencyNumber.c_str()));
		SetDlgItemText(IDC_EDIT_detailGender, CString(dt.gender.c_str()));
		SetDlgItemText(IDC_EDIT_detailBloody, CString(dt.bloodType.c_str()));
		SetDlgItemText(IDC_EDIT_detailPhone, CString(dt.phone.c_str()));
	}
}
BOOL DetailPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	drawDetail();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
