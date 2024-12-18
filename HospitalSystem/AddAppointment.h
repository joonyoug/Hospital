#pragma once
#include "afxdialogex.h"
#include "AppointmentController.h"

// AddAppointment 대화 상자

class AddAppointment : public CDialog
{
	DECLARE_DYNAMIC(AddAppointment)

public:
	AddAppointment(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AddAppointment();
	CWnd* pParnet;

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Add_Appointment };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAppointment();
	void drawComboBox();
	virtual BOOL OnInitDialog();
	CString getTime();
	CString getComboBox();
	void setParent(CWnd* pParent);
	void NotifyParent();
	
	afx_msg void OnMcnSelectMonthcalendardoctorpage(NMHDR* pNMHDR, LRESULT* pResult);
	
};