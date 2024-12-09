// AddPatient.cpp: 구현 파일
//

#include "pch.h"
#include "HospitalSystem.h"
#include "afxdialogex.h"
#include "AddPatient.h"


// AddPatient 대화 상자

IMPLEMENT_DYNAMIC(AddPatient, CDialogEx)

AddPatient::AddPatient(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Doctor, pParent)
{

}

AddPatient::~AddPatient()
{
}

void AddPatient::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AddPatient, CDialogEx)
END_MESSAGE_MAP()


// AddPatient 메시지 처리기
