#pragma once
#include "afxdialogex.h"
#include "AppointmentDto.h"

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
	afx_msg void OnBnClickedButtonaddappointment();
	afx_msg void OnBnClickedButtonAddpatient();
	void drawAppointment();
	void drawPatient();
	void UpdatePatientInfo(std::string name);
	afx_msg void OnNMClickListAppointment(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_patientInfoList;
	afx_msg void OnNMClickListPatientInfo(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_list_wait;
	void drawWait();
	void UpdateWait(CString name);
	afx_msg void OnBnClickedBtnalreadypatient();
};
