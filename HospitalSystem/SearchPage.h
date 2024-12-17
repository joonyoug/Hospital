#pragma once
#include "afxdialogex.h"


// SearchPage 대화 상자

class SearchPage : public CDialogEx
{
	DECLARE_DYNAMIC(SearchPage)

public:
	SearchPage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SearchPage();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SearchPage };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSearch();
};
