#pragma once
#include "afxdialogex.h"
#include <vector>
#include "AppointmentDto.h"
#include <iostream>
#include <sstream>
#include <string>
// DoctorPage1 대화 상자
using namespace std;

class DoctorPage1 : public CDialogEx
{
	DECLARE_DYNAMIC(DoctorPage1)

public:
	DoctorPage1(CString doctorId,CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DoctorPage1();
	CString doctorId;
	std::string m_residentNumber;
	std::string m_name;
	std::string m_cc;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DoctorPage1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_patientInfo;
	CListCtrl m_ChartHistroy;
	CListCtrl m_listDcode;
	CListCtrl m_listMcode;
	
	void drawPatientInfo(CString name);
	void setResidentNumber(std::string residentNumber);
	void drawDcode();
	void drawMcode();
	virtual BOOL OnInitDialog();
	afx_msg void OnMenuOffice();
	void DrawPatient();
	void setFont(CFont *font);
	void drawDayAppointment(std::vector<AppointmentDto> dto);
	void drawChartHistory();
	void drawVaccinations();
	void DrawAppointment();
	afx_msg void OnNMClickListDcode(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMClickListMcode(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_listAppointment;
	afx_msg void OnNMClickListappointment(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMClickListPatientinformation(NMHDR* pNMHDR, LRESULT* pResult);
	void drawInitialChart();
	CListCtrl m_listVaccin;
	CMonthCalCtrl m_doctorPageCal;
	CString getTime();
	afx_msg void OnMcnSelectMonthcalendardoctorpage(NMHDR* pNMHDR, LRESULT* pResult);
	CButton m_static;
	
	std::vector<std::string> split(std::string dcode,std::string delimeter);
	afx_msg void OnBnClickedButtonOkd();
	afx_msg void OnBnClickedButtonOkm();
};
