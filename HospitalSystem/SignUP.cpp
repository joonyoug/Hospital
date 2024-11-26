// SignUP.cpp: 구현 파일
//
#include "SignUpController.h"
#include "pch.h"
#include "HospitalSystemDlg.h"
#include "HospitalSystem.h"
#include "afxdialogex.h"
#include "SignUP.h"
#include <string>


// SignUP 대화 상자

IMPLEMENT_DYNAMIC(SignUP, CDialog)

SignUP::SignUP(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_SignUP, pParent)
{

}

SignUP::~SignUP()
{
}

void SignUP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SignUP, CDialog)
	ON_BN_CLICKED(IDOK, &SignUP::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_CheckID, &SignUP::OnBnClickedButtonCheckid)
END_MESSAGE_MAP()


// SignUP 메시지 처리기


void SignUP::OnBnClickedOk()
{
	CString id,pw,name,phoneNumber,employeeNumber;

	SignUpController sign;

	GetDlgItemText(IDC_EDIT_SIgnUp_ID, id);
	GetDlgItemText(IDC_EDIT_SignUp_pw, pw);
	GetDlgItemText(IDC_EDIT_SignUp_Name, name);
	GetDlgItemText(IDC_EDIT_SignUp_Employee, employeeNumber);
	GetDlgItemText(IDC_EDIT_SignUp_Phone, phoneNumber);
	// 중복확인
	if (!(this->checkId)) {
		AfxMessageBox(_T("중복확인 하세요."));
		return;
	}
	//가입
	try {
		if (sign.SignUP(std::string(CT2A(id)), std::string(CT2A(pw)),
			std::string(CT2A(name)),
			std::string(CT2A(phoneNumber)),std::string(CT2A(employeeNumber))))
		{
			AfxMessageBox(_T("회원가입 성공"));
			this->EndDialog(IDOK);		
		}
		else {
			AfxMessageBox(_T("회원가입 실패"));
		}
	}
	catch (const std::exception& e) {
		AfxMessageBox(_T("회원가입 중 오류가 발생했습니다."));
		std::cout << e.what() << std::endl;  
	}
}
void SignUP::OnBnClickedButtonCheckid()
{
	CString id;
	GetDlgItemText(IDC_EDIT_SIgnUp_ID, id);
	if (id.IsEmpty()) { 
		AfxMessageBox(_T("값을 입력하세요"));
		return;
	} //빈값
	SignUpController sign;
	this->checkId = sign.checkId(std::string(CT2A(id)));
	if (this->checkId) { AfxMessageBox(_T("사용가능한 아이디 ")); }
	else { AfxMessageBox(_T("이미 존재하는 아이디")); }

}
