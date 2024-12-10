// DoctorPage1.cpp: 구현 파일
//

#include "pch.h"
#include "HospitalSystem.h"
#include "afxdialogex.h"
#include "DoctorPage1.h"


// DoctorPage1 대화 상자

IMPLEMENT_DYNAMIC(DoctorPage1, CDialogEx)

DoctorPage1::DoctorPage1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DoctorPage1, pParent)
{

}

DoctorPage1::~DoctorPage1()
{
}

void DoctorPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DoctorPage1, CDialogEx)
END_MESSAGE_MAP()


// DoctorPage1 메시지 처리기
