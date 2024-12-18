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
	CString pw,name,phoneNumber,employeeNumber,licenseId, department, departmentCode, speicalty;

	SignUpController sign;
	/*
	
	std::string &employeeNumber, std::string& password, std::string &name,
	std::string& licenseId, std::string &department, std::string& departmentCode,
	std::string &speicalty, std::string& employeeDate, std::string &role, std::string &status,
	std::string& phoneNumber
	
	*/
	GetDlgItemText(IDC_EDIT_SignUp_pw, pw);
	GetDlgItemText(IDC_EDIT_SignUp_Name, name);
	GetDlgItemText(IDC_EDIT_SignUp_Employee, employeeNumber);
	GetDlgItemText(IDC_EDIT_SignUp_Phone, phoneNumber);
	GetDlgItemText(IDC_EDIT_SignUp_license_id, licenseId);
	GetDlgItemText(IDC_EDIT_SignUp_department, department);
	GetDlgItemText(IDC_EDIT_SignUp_departmentCode, departmentCode);
	GetDlgItemText(IDC_EDIT_SignUP_specialty, speicalty);
	// 중복확인
	if (!(this->checkId)) {
		AfxMessageBox(_T("중복확인 하세요."));
		return;
	}
	/*
	std::string& employeeNumber, std::string& password, std::string& name,
	std::string& licenseId, std::string& department, std::string& departmentCode,
	std::string& speicalty,
	std::string& phoneNumber
	"insert into doctors (employee_number,password,name,license_id,department,department_code,specialty,phone_number) values(?,?,?,?,?,?,?,?,?)";
	*/
	//가입

	std::string strPw = std::string(CT2A(pw));            // CString -> std::string
	std::string strName = std::string(CT2A(name));        // CString -> std::string
	std::string strEmployeeNumber = std::string(CT2A(employeeNumber)); // CString -> std::string
	std::string strPhoneNumber = std::string(CT2A(phoneNumber)); // CString -> std::string
	std::string strLicenseId = std::string(CT2A(licenseId)); // CString -> std::string
	std::string strDepartment = std::string(CT2A(department)); // CString -> std::string
	std::string strDepartmentCode = std::string(CT2A(departmentCode)); // CString -> std::string
	std::string strSpecialty = std::string(CT2A(speicalty)); // CString -> std::string

	// SignUP 함수 호출 (std::string 참조로 넘겨줌)
	try {
		if (sign.SignUP(strEmployeeNumber,strPw,strName,strLicenseId,strDepartment
			,strDepartmentCode,strSpecialty,strPhoneNumber)) {
			// 회원가입 성공 처리
			AfxMessageBox(_T("회원가입 성공!"));
			this->EndDialog(IDOK);
		}
		else {
			// 회원가입 실패 처리
			AfxMessageBox(_T("회원가입 실패!"));
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
	GetDlgItemText(IDC_EDIT_SignUp_Employee,id);
	if (id.IsEmpty()) { 
		AfxMessageBox(_T("값을 입력하세요"));
		return;
	} //빈값
	SignUpController sign;
	this->checkId = sign.checkId(std::string(CT2A(id)));
	if (this->checkId) { AfxMessageBox(_T("사용가능한 아이디 ")); }
	else { AfxMessageBox(_T("이미 존재하는 아이디")); }

}
