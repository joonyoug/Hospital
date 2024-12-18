// HospitamOffice.cpp: 구현 파일
//

#include "pch.h"
#include "HospitalSystem.h"
#include "afxdialogex.h"
#include "HospitamOffice.h"


// HospitamOffice 대화 상자

IMPLEMENT_DYNAMIC(HospitamOffice, CDialogEx)

HospitamOffice::HospitamOffice(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_HospitamOffice, pParent)
{

}

HospitamOffice::~HospitamOffice()
{
}

void HospitamOffice::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HospitamOffice, CDialogEx)
END_MESSAGE_MAP()


// HospitamOffice 메시지 처리기
