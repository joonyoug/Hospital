﻿
// HospitalSystemDlg.h: 헤더 파일
//

#pragma once


// CHospitalSystemDlg 대화 상자
class CHospitalSystemDlg : public CDialogEx
{
// 생성입니다.
public:
	CHospitalSystemDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOSPITALSYSTEM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonlogin();
	afx_msg void OnBnClickedRegister();
	void onDrawItem();
	afx_msg void OnMenuBilling(); // 메뉴 이벤트 처리 핸들러
	
	CMFCButton m_loginBtn;
	CMFCButton m_signBtn;
	CMFCButton signBtn;
};
