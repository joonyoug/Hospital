#pragma once
#include "afxdialogex.h"
#include "AppointmentDto.h"
#include <vector>
#include "AppointmentDto.h"
#include "DetailPage.h"
#include "SearchPage.h"
// HosipitalOffice 대화 상자

class HosipitalOffice : public CDialogEx
{
	DECLARE_DYNAMIC(HosipitalOffice)

public:
	HosipitalOffice(CString doctorId, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	
	BOOL OnInitDialog();
	virtual ~HosipitalOffice();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HospitamOffice};
#endif
private:
	CString doctorId;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// 리스트컨트롤
	CString getDoctorId();
	CListCtrl m_list;
	void drawfont(CFont * font);
	afx_msg void OnBnClickedButtonaddappointment();
	afx_msg void OnBnClickedButtonAddpatient();
	void drawAppointment();
	void drawPatient();
	void drawDayAppointment(std::vector<AppointmentDto> dto);
	void UpdatePatientInfo(std::string name);
	afx_msg void OnNMClickListAppointment(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_patientInfoList;
	afx_msg void OnNMClickListPatientInfo(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_list_wait;
	void drawWait();
	void UpdateWait(CString name,CString symtons);
	afx_msg void OnBnClickedBtnalreadypatient();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMenuDoctor();
	afx_msg void OnMcnSelectMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult);
	CString getTime();
	void detailPatient();
	CMonthCalCtrl m_officePageCal;
	DetailPage* m_detail=nullptr;
	CString m_resident;
	SearchPage* m_search = nullptr;
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonSearchpatient();
	afx_msg void OnNMRClicAppointment(NMHDR* pNMHDR, LRESULT* pResult);
	void drawItem();

};
