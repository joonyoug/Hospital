#pragma once
#include "afxdialogex.h"


// DoctorPage1 대화 상자

class DoctorPage1 : public CDialogEx
{
	DECLARE_DYNAMIC(DoctorPage1)

public:
	DoctorPage1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DoctorPage1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DoctorPage1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
