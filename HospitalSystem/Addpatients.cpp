﻿// Addpatients.cpp: 구현 파일
//

#include "pch.h"
#include "HospitalSystem.h"
#include "afxdialogex.h"
#include "Addpatients.h"
#include "PatientController.h"
#include "WaitPatientDB.h"
#include "PatientDto.h"
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
    ON_BN_CLICKED(IDC_BUTTON1, &Addpatients::OnBnClickedButton1)
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
    CString phone, addr, gender, dosing_list, blood_type, emergencyNumber;

    // 각 입력 필드에서 텍스트 가져오기
    GetDlgItemText(IDC_EDIT_PatientName, m_name);
    GetDlgItemText(IDC_EDIT_Patient_Phon, phone);
    GetDlgItemText(IDC_EDIT_PatientAddr, addr);
    GetDlgItemText(IDC_EDIT_ResidentNumber, m_resident);
    GetDlgItemText(IDC_EDIT_dosing_list, dosing_list);
    GetDlgItemText(IDC_EDIT_blood_type, blood_type);
    GetDlgItemText(IDC_EDIT_emergencyNumber, emergencyNumber);
    GetDlgItemText(IDC_EDIT_symptoms, m_s);

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
        std::string(CT2A(m_resident)),
        std::string(CT2A(m_name)),
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
        
        HosipitalOffice* pDoctorPage = dynamic_cast<HosipitalOffice*>(pParnet);
        
        if (pDoctorPage) {
            pDoctorPage->UpdateWait(m_name,m_s);
            WaitPatientDB db;
            db.addWait(std::string(CT2A(m_name)), std::string(CT2A(m_resident)),std::string(CT2A(m_s)));
        }
    }
}


void Addpatients::OnBnClickedButton1()
{
   
    CString residentNumber;
    GetDlgItemText(IDC_EDIT_ResidentNumber, residentNumber);

    PatientController cp;
    PatientDto dto = cp.selectPatient(std::string(CT2A(residentNumber)));

    if (dto.name=="-1") {

        std::cout << "111" << std::endl;

        AfxMessageBox(_T("새로 추가해야합니다."));
    }
    else {
        /*
        GetDlgItemText(IDC_EDIT_PatientName, m_name);
    GetDlgItemText(IDC_EDIT_Patient_Phon, phone);
    GetDlgItemText(IDC_EDIT_PatientAddr, addr);
    GetDlgItemText(IDC_EDIT_ResidentNumber, m_resident);
    GetDlgItemText(IDC_EDIT_dosing_list, dosing_list);
    GetDlgItemText(IDC_EDIT_blood_type, blood_type);
    GetDlgItemText(IDC_EDIT_emergencyNumber, emergencyNumber);
        
        */
        SetDlgItemText(IDC_EDIT_PatientName, CString(dto.name.c_str()));
        SetDlgItemText(IDC_EDIT_Patient_Phon, CString(dto.phone.c_str()));
        SetDlgItemText(IDC_EDIT_PatientAddr, CString(dto.address.c_str()));
        SetDlgItemText(IDC_EDIT_ResidentNumber, CString(dto.residentNumber.c_str()));
        SetDlgItemText(IDC_EDIT_dosing_list, CString(dto.dosingList.c_str()));
        SetDlgItemText(IDC_EDIT_blood_type, CString(dto.bloodType.c_str()));
        SetDlgItemText(IDC_EDIT_emergencyNumber, CString(dto.emergencyNumber.c_str()));
        SetDlgItemText(IDC_EDIT_symptoms, CString(m_s));

        if (dto.gender == "F") {
            m_checkbox_man.SetCheck(BST_CHECKED);
        
        }
        else {
            m_checkbox_woman.SetCheck(BST_CHECKED);
        }

    }






}
