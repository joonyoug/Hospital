#pragma once
#include "afxdialogex.h"


// HospitamOffice 대화 상자

class HospitamOffice : public CDialogEx
{
	DECLARE_DYNAMIC(HospitamOffice)

public:
	HospitamOffice(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~HospitamOffice();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HospitamOffice };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
