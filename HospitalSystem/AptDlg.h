#pragma once
#include "afxdialogex.h"


// AptDlg 대화 상자

class AptDlg : public CDialog
{
	DECLARE_DYNAMIC(AptDlg)

public:
	AptDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AptDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Add_Appointment };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
