// Addpatients.cpp: 구현 파일
//

#include "pch.h"
#include "HospitalSystem.h"
#include "afxdialogex.h"
#include "Addpatients.h"
#include "PatientController.h"
// Addpatients 대화 상자

IMPLEMENT_DYNAMIC(Addpatients, CDialogEx)

Addpatients::Addpatients(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_AddPatient, pParent)
{

}

Addpatients::~Addpatients()
{
}

void Addpatients::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1_MAN, m_checkbox_man);
	DDX_Control(pDX, IDC_CHECK_WOMAN, m_checkbox_woman);
}


BEGIN_MESSAGE_MAP(Addpatients, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &Addpatients::OnBnClickedButtonAdd)
END_MESSAGE_MAP()


// Addpatients 메시지 처리기

CString Addpatients::getGender() {
	
	if (m_checkbox_man.GetCheck() == BST_CHECKED) {
		m_checkbox_woman.SetCheck(BST_UNCHECKED);
		return _T("남");
	}
	else {
		m_checkbox_man.SetCheck(BST_UNCHECKED);
		return _T("여");
	}

}

void Addpatients::OnBnClickedButtonAdd()
{
    CString phone, addr, name, residentNumber, gender, dosing_list, blood_type, emergencyNumber;

    // 각 입력 필드에서 텍스트 가져오기
    GetDlgItemText(IDC_EDIT_PatientName, name);
    GetDlgItemText(IDC_EDIT_Patient_Phon, phone);
    GetDlgItemText(IDC_EDIT_PatientAddr, addr);
    GetDlgItemText(IDC_EDIT_ResidentNumber, residentNumber);
    GetDlgItemText(IDC_EDIT_dosing_list, dosing_list);
    GetDlgItemText(IDC_EDIT_blood_type, blood_type);
    GetDlgItemText(IDC_EDIT_emergencyNumber, emergencyNumber);
    gender = getGender();  // gender는 이미 CString으로 받았다고 가정

    // emergencyNumber를 std::string으로 변환
    std::string emerStr = std::string(CT2A(emergencyNumber));

    // std::stoi로 emergencyNumber를 int로 변환
    int emerNum = 0;
    try {
        emerNum = std::stoi(emerStr);  // emergencyNumber를 정수로 변환
    }
    catch (const std::invalid_argument& e) {
        AfxMessageBox(_T("등록실패: 잘못된 숫자 형식입니다."));
        return;
    }
    catch (const std::out_of_range& e) {
        AfxMessageBox(_T("등록실패: 숫자가 너무 큽니다."));
        return;
    }

    PatientController patient;

    if (patient.addPatient(
        std::string(CT2A(residentNumber)),
        std::string(CT2A(name)),
        std::string(CT2A(phone)),
        std::string(CT2A(gender)),
        std::string(CT2A(addr)),
        std::string(CT2A(emergencyNumber)),  // 정수형 emergencyNumber 사용
        std::string(CT2A(dosing_list)),
        std::string(CT2A(blood_type))
    )) {
        AfxMessageBox(_T("등록성공"));
        NotifyParent();
        
        this->EndDialog(IDOK);  // 다이얼로그 종료
    }
    else {
        AfxMessageBox(_T("등록 실패"));
    }
}
void Addpatients::setParent(CWnd* pParent) {
    pParnet = pParent;
}
void Addpatients::NotifyParent() {

    if (pParnet != nullptr) {
        CString name;
        GetDlgItemText(IDC_EDIT_PatientName, name);
        HosipitalOffice* pDoctorPage = dynamic_cast<HosipitalOffice*>(pParnet);
        if (pDoctorPage) {
            pDoctorPage->UpdateWait(name);
        }
    }
}
