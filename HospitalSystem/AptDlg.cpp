// AptDlg.cpp: 구현 파일
//

#include "pch.h"
#include "HospitalSystem.h"
#include "afxdialogex.h"
#include "AptDlg.h"


// AptDlg 대화 상자

IMPLEMENT_DYNAMIC(AptDlg, CDialog)

AptDlg::AptDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_Add_Appointment, pParent)
{

}

AptDlg::~AptDlg()
{
}

void AptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AptDlg, CDialog)
END_MESSAGE_MAP()


// AptDlg 메시지 처리기
