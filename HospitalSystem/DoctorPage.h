#pragma once
#include "afxdialogex.h"
#include "AppointmentDto.h"

// DoctorPage 대화 상자

class DoctorPage : public CDialogEx
{
	DECLARE_DYNAMIC(DoctorPage)

public:
	DoctorPage(CString doctorId,CWnd* pParent = nullptr);   // 표준 생성자입니다.
	BOOL OnInitDialog();
	virtual ~DoctorPage();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Doctor };
#endif
private:
	CString doctorId;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// 리스트컨트롤
	CString getDoctorId();
	//bool DoctorPageInitial();
	CListCtrl m_list;
};
