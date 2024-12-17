#pragma once
#include "afxdialogex.h"


// DetailPage 대화 상자

class DetailPage : public CDialogEx
{
	DECLARE_DYNAMIC(DetailPage)

public:
	DetailPage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DetailPage();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DetailPage };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
public:
	CString residentNumber;
	void drawDetail();
	void setResident(CString residentNumber);

	virtual BOOL OnInitDialog();
};
