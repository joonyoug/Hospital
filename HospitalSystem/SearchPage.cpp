// SearchPage.cpp: 구현 파일
//

#include "pch.h"
#include "HospitalSystem.h"
#include "afxdialogex.h"
#include "SearchPage.h"
#include "PatientController.h"
#include "PatientDto.h"

// SearchPage 대화 상자

IMPLEMENT_DYNAMIC(SearchPage, CDialogEx)

SearchPage::SearchPage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SearchPage, pParent)
{

}

SearchPage::~SearchPage()
{
}

void SearchPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SearchPage, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Search, &SearchPage::OnBnClickedButtonSearch)
END_MESSAGE_MAP()


// SearchPage 메시지 처리기


void SearchPage::OnBnClickedButtonSearch()
{
	CString residentNum;
	GetDlgItemText(IDC_EDIT_srn, residentNum);

	PatientController pt;
	PatientDto dto = pt.selectPatient(std::string(CT2A(residentNum)));
	if (dto.name == "-1") {
		AfxMessageBox(_T("없는환자입니다."));
	}
	else {
		SetDlgItemText(IDC_EDIT_searchAddr, CString(dto.address.c_str()));
		SetDlgItemText(IDC_EDIT_searchBloody, CString(dto.bloodType.c_str()));
		SetDlgItemText(IDC_EDIT_searchDosing, CString(dto.dosingList.c_str()));
		SetDlgItemText(IDC_EDIT_searchGender, CString(dto.gender.c_str()));
		SetDlgItemText(IDC_EDIT_searchlEmer, CString(dto.emergencyNumber.c_str()));
		SetDlgItemText(IDC_EDIT_searchlResidentNumber, CString(dto.residentNumber.c_str()));
		SetDlgItemText(IDC_EDIT_SearchName, CString(dto.name.c_str()));
		SetDlgItemText(IDC_EDIT_searchPhone, CString(dto.phone.c_str()));

	}


}
