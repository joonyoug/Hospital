#pragma once
#include "afxdialogex.h"
#include "SignUpController.h"

// SignUP 대화 상자

class SignUP : public CDialog
{
	DECLARE_DYNAMIC(SignUP)

public:
	SignUP(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SignUP();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SignUP };
#endif
private:
	bool checkId = false;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonCheckid();
};
