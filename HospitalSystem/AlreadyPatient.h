#pragma once
#include "afxdialogex.h"
#include "HosipitalOffice.h"

// AlreadyPatient 대화 상자

class AlreadyPatient : public CDialogEx
{
	DECLARE_DYNAMIC(AlreadyPatient)

public:
	AlreadyPatient(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AlreadyPatient();
	CWnd* pParnet;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AlreadyPatient };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	
	DECLARE_MESSAGE_MAP()
public:
	void setParent(CWnd* p);
	void NotifyParent();
<<<<<<< HEAD
=======
	CString m_name;
	CString m_resident;

>>>>>>> upstream/dev
	afx_msg void OnBnClickedButton1();
};
