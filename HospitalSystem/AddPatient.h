#pragma once
#include "afxdialogex.h"


// AddPatient 대화 상자

class AddPatient : public CDialogEx
{
	DECLARE_DYNAMIC(AddPatient)

public:
	AddPatient(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AddPatient();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Doctor };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
