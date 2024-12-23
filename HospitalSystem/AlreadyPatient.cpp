// AlreadyPatient.cpp: 구현 파일
//

#include "pch.h"
#include "HospitalSystem.h"
#include "afxdialogex.h"
#include "AlreadyPatient.h"
#include "PatientController.h"
#include "WaitPatientDB.h"


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
        
        HosipitalOffice* pDoctorPage = dynamic_cast<HosipitalOffice*>(pParnet);
        if (pDoctorPage) {
            pDoctorPage->UpdateWait(m_name,m_s);
            WaitPatientDB db;
            db.addWait(std::string(CT2A(m_name)), std::string(CT2A(m_resident)),std::string(CT2A(m_s)));
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
    GetDlgItemText(IDC_EDIT_PatientName, m_name);
    GetDlgItemText(IDC_EDIT_ResidentNumber, m_resident);
    GetDlgItemText(IDC_EDIT_S, m_s);

    PatientDto dto=p.selectPatient(std::string(CT2A(m_resident)));
    if (dto.name!="-1") {
        NotifyParent();
        this->EndDialog(IDOK);
    }
    else {
        AfxMessageBox(_T("없는 환자"));
    
    }


   
}
