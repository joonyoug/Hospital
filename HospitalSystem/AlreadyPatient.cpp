// AlreadyPatient.cpp: 구현 파일
//

#include "pch.h"
#include "HospitalSystem.h"
#include "afxdialogex.h"
#include "AlreadyPatient.h"
#include "PatientController.h"


// AlreadyPatient 대화 상자

IMPLEMENT_DYNAMIC(AlreadyPatient, CDialogEx)

AlreadyPatient::AlreadyPatient(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AlreadyPatient, pParent)
{

}

AlreadyPatient::~AlreadyPatient()
{
}

void AlreadyPatient::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
void AlreadyPatient::setParent(CWnd* p) {
    pParnet = p;   
}
void AlreadyPatient::NotifyParent() {
  
    if (pParnet != nullptr) {
        CString name;
        GetDlgItemText(IDC_EDIT_PatientName, name);
        HosipitalOffice* pDoctorPage = dynamic_cast<HosipitalOffice*>(pParnet);
        if (pDoctorPage) {
            pDoctorPage->UpdateWait(name);
        }
    }



}

BEGIN_MESSAGE_MAP(AlreadyPatient, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON1, &AlreadyPatient::OnBnClickedButton1)
END_MESSAGE_MAP()


// AlreadyPatient 메시지 처리기


void AlreadyPatient::OnBnClickedButton1()
{
    PatientController p;
    CString residentnumber;
    GetDlgItemText(IDC_EDIT_ResidentNumber, residentnumber);
    PatientDto dto=p.selectPatient(std::string(CT2A(residentnumber)));
    if (dto.name != "") {

        NotifyParent();
        this->EndDialog(IDOK);
    }
    else {
        AfxMessageBox(_T("없는 환자"));
    
    }


   
}
