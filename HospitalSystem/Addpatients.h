#pragma once
#include "afxdialogex.h"
#include "Addpatients.h"
#include "PatientController.h"
#include "HosipitalOffice.h"

// Addpatients 대화 상자

class Addpatients : public CDialogEx
{
	DECLARE_DYNAMIC(Addpatients)

public:
	Addpatients(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Addpatients();
	CWnd* pParnet;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_AddPatient };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdd();
	CString getGender();
	CButton m_checkbox_man;
	CButton m_checkbox_woman;
<<<<<<< HEAD
=======
	CString m_name;
	CString m_resident;

>>>>>>> upstream/dev
	void setParent(CWnd* p);
	void NotifyParent();

};
