#pragma once
#include <mysql/jdbc.h>
#include "afxdialogex.h"
#include <fstream>
#include <string>
#include <mysql.h> // MySQL 헤더 파일 포함


// CBillingDialog 대화 상자

class CBillingDialog : public CDialogEx
{
    DECLARE_DYNAMIC(CBillingDialog)

public:
    CBillingDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
    virtual ~CBillingDialog();

    // 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DIALOG1_Payment };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

    DECLARE_MESSAGE_MAP()

private:
    // UI 컨트롤 변수
    //CEdit m_editMemo; // 메모 입력 필드
    CStatic m_staticMemo;
    CEdit m_editSSN;           // 주민등록번호 입력 필드
    CStatic m_staticResult;    // 결과 표시 Static Text
    CListCtrl m_recordList; // 진료 내역을 표시할 List Control
    CListCtrl m_prescriptionList; // 처방전 리스트 추가
    CStatic m_staticAge; // 나이 표시용 Static Control
    CStatic m_staticName;        // 이름 값 표시
    CStatic m_staticGender;      // 성별 값 표시
    CStatic m_staticAddress;     // 주소 값 표시
    CStatic m_staticPhone;       // 전화번호 값 표시
    CStatic m_staticEmergency;   // 긴급 연락처 값 표시
    CStatic m_staticBlood;       // 혈액형 값 표시
    CString m_residentNumber; // 주민등록번호 저장
    CFont m_font;  // CFont를 멤버 변수로 선언
    CButton m_buttonCompletePayment;  // 결제 완료 버튼 변수
    CButton m_buttonPrintReceipt;  // 결제 완료 버튼 변수
    CString residentNumber; // 사용자 입력 값을 저장
    CBrush m_whiteBrush; // 흰색 브러시 선언
    CStatic m_staticPaymentDate; // 진료 날짜
    CStatic m_staticPaymentPDate; // 결제 날짜
    MYSQL* conn;               // MySQL 연결 객체

    // 함수
    MYSQL* ConnectToDatabase(); // DB 연결
    void CloseDB();             // DB 연결 종료
    void LoadChartRecords(const CString& resident_Number); // DB에서 차트 기록 로드
    void LoadTotalSum(const CString& resident_Number);     // DB에서 총 금액 계산 및 표시
    void LoadPrescriptions(const CString& residentNumber); // 처방전 불러오기
    void LoadPatientInfo(const CString& resident_number);
    void UpdateTotalSum(const CString& residentNumber);
    void LoadPaymentDates(const CString& residentNumber);
    void AdjustColumnWidth();   // 열(Column) 너비 조정
    void AdjustColumnWidthForRecords();
    void PrintReceipt(); // 영수증 출력 함수
    void LoadNotes(const CString& residentNumber);
    void MarkAsPaid(const CString& chartID); // 상태를 '완납'으로 변경하는 함수

public:

    afx_msg void On32772();
    afx_msg void OnBnClickedButtonSearch();
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedButtonMarkPaid();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnBnClickedButtonPrintReceipt();
    //afx_msg void OnStnClickedStaticMemo();
};
