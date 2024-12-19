// CBillingDialog.cpp: 구현 파일

#include "pch.h"
#include "HospitalSystem.h"
#include "afxdialogex.h"
#include "CBillingDialog.h"
#include "Prescriptions.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// CBillingDialog 대화 상자

IMPLEMENT_DYNAMIC(CBillingDialog, CDialogEx)

CBillingDialog::CBillingDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DIALOG1_Payment, pParent)
{
    conn = nullptr; // DB 연결 객체 초기화
}

CBillingDialog::~CBillingDialog()
{
    if (conn) {
        mysql_close(conn); // MySQL 연결 해제
        conn = nullptr;
    }
}

void CBillingDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX); DDX_Control(pDX, IDC_EDIT_SSN, m_editSSN);          // 주민등록번호 입력 필드
    DDX_Control(pDX, IDC_EDIT_SSN, m_editSSN);          // 주민등록번호 입력 필드
    DDX_Control(pDX, IDC_STATIC_RESULT, m_staticResult); // 결과 표시 Static Text
    DDX_Control(pDX, IDC_LIST_RECORDS, m_recordList);    // 진료 내역 리스트
    DDX_Control(pDX, IDC_STATIC_PATIENT_NAME, m_staticName);
    DDX_Control(pDX, IDC_STATIC_PATIENT_GENDER, m_staticGender);
    DDX_Control(pDX, IDC_STATIC_PATIENT_ADDRESS, m_staticAddress);
    DDX_Control(pDX, IDC_STATIC_PATIENT_PHONE, m_staticPhone);
    DDX_Control(pDX, IDC_STATIC_PATIENT_EMERGENCY, m_staticEmergency);
    DDX_Control(pDX, IDC_STATIC_PATIENT_BLOOD, m_staticBlood);
    DDX_Control(pDX, IDC_BUTTON_MARK_PAID, m_buttonCompletePayment);
    DDX_Control(pDX, IDC_LIST_PRESCRIPTIONS, m_prescriptionList);
    DDX_Control(pDX, IDC_STATIC_PAYMENT_DATE, m_staticPaymentDate);
    DDX_Control(pDX, IDC_STATIC_PAYMENT_PDATE, m_staticPaymentPDate);
    DDX_Control(pDX, IDC_BUTTON_PRINT_RECEIPT, m_buttonPrintReceipt);
    DDX_Control(pDX, IDC_STATIC_MEMO, m_staticMemo);

}


BEGIN_MESSAGE_MAP(CBillingDialog, CDialogEx)

    ON_WM_CTLCOLOR() // WM_CTLCOLOR 메시지 추가
    ON_BN_CLICKED(IDC_BUTTON_Search, &CBillingDialog::OnBnClickedButtonSearch)
    ON_BN_CLICKED(IDC_BUTTON_MARK_PAID, &CBillingDialog::OnBnClickedButtonMarkPaid)
    ON_BN_CLICKED(IDC_BUTTON_PRINT_RECEIPT, &CBillingDialog::OnBnClickedButtonPrintReceipt)
    ON_COMMAND(ID_32772, &CBillingDialog::On32772)

   
END_MESSAGE_MAP()


// MySQL DB 연결
MYSQL* CBillingDialog::ConnectToDatabase()
{
    conn = mysql_init(nullptr);
    if (!conn) {
        AfxMessageBox(L"MySQL 초기화 실패");
        return nullptr;
    }

    // 자동 재연결 설정
    bool reconnect = true;
    mysql_options(conn, MYSQL_OPT_RECONNECT, &reconnect);

    // config.json 파일 읽기
    std::ifstream configFile("config.json");
    if (!configFile.is_open()) {
        AfxMessageBox(L"config.json 파일을 열 수 없습니다.");
        return nullptr;
    }

    // JSON 데이터 파싱
    nlohmann::json config;
    configFile >> config;
    configFile.close();

    std::string host = config["database"]["host"];
    std::string user = config["database"]["username"];
    std::string password = config["database"]["password"];
    std::string schema = config["database"]["schema"];
    std::string charset = config["database"]["charset"];

    // MySQL 서버에 연결
    if (!mysql_real_connect(conn, host.c_str(), user.c_str(), password.c_str(), schema.c_str(), 3306, nullptr, 0)) {
        CString error(mysql_error(conn));
        AfxMessageBox(L"DB 연결 실패: " + error);
        mysql_close(conn);
        return nullptr;
    }

    // 문자셋 설정 (utf8mb4로 강제 설정)
    if (mysql_set_character_set(conn, "euckr") != 0) {
        CString error(mysql_error(conn));
        AfxMessageBox(L"문자셋 설정 실패: " + error);
        mysql_close(conn);
        return nullptr;
    }

    return conn;
}

void CBillingDialog::CloseDB()
{
    if (conn) {
        mysql_close(conn);
        conn = nullptr;
    }
}

void CBillingDialog::LoadChartRecords(const CString& residentNumber)
{
    if (!conn) {
        AfxMessageBox(L"DB 연결이 설정되지 않았습니다.");
        return;
    }

    // sum 테이블과 decisions 테이블 JOIN 쿼리 (모든 데이터 불러오기)
    CString query;
    query.Format(L"SELECT s.chart_id, d.k_name, COALESCE(d.k_cost, 0), d.status "
        L"FROM sum s "
        L"JOIN decisions d ON s.chart_id = d.chart_id "
        L"WHERE s.resident_number = '%s'", residentNumber);

    if (mysql_query(conn, CStringA(query)) != 0) {
        CString error(mysql_error(conn));
        AfxMessageBox(L"쿼리 실행 실패: " + error);
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        AfxMessageBox(L"DB 결과 처리 실패");
        return;
    }

    m_recordList.DeleteAllItems(); // 기존 리스트 초기화

    MYSQL_ROW row;
    int index = 0;
    double totalSum = 0.0; // 미납 항목 합산 값

    // 모든 항목 불러오기
    while ((row = mysql_fetch_row(res))) {
        CString chartID(row[0]);  // chart_id
        CString kName(row[1]);    // k_name
        CString kCost(row[2]);    // k_cost
        CString status(row[3]);   // status (미납 or 완납)
        //AfxMessageBox(L"불러온 k_cost: " + kCost);

        // **디버그 메시지 추가**
        //CString debugMessage;
        //debugMessage.Format(L"chartID: %s, kCost: %s, status: %s", chartID, kCost, status);
        //AfxMessageBox(debugMessage); // 데이터를 확인하는 메시지 박스

        // 리스트에 항목 추가
        m_recordList.InsertItem(index, chartID);
        m_recordList.SetItemText(index, 1, kName);
        m_recordList.SetItemText(index, 2, kCost);
        m_recordList.SetItemText(index, 3, status);

        // 미납 상태의 k_cost만 합산
        if (status == L"미납") {
            kCost.Trim(); // 공백 제거
            if (!kCost.IsEmpty() && _ttof(kCost) != 0.0) { // 값이 비어있지 않고 숫자인 경우만 처리
                totalSum += _ttof(kCost); // k_cost 문자열을 double로 변환하여 합산
            }
        }
        index++;
    }

    mysql_free_result(res);

    // Static Control에 합산된 미납 금액 표시
    CString resultText;
    resultText.Format(L"수납할 총 금액 : %.0f 원", totalSum);
    //AfxMessageBox(resultText);  // 출력 확인
    m_staticResult.SetWindowText(resultText);
}


void CBillingDialog::LoadPatientInfo(const CString& resident_number)
{
    if (!conn) {
        AfxMessageBox(L"DB 연결이 설정되지 않았습니다.");
        return;
    }

    // 쿼리 실행
    CString query;
    query.Format(L"SELECT name, gender, address, phone_number, emergency_number, blood_type "
        L"FROM patients WHERE resident_number = '%s'", resident_number);

    if (mysql_query(conn, CStringA(query)) != 0) {
        CString error(mysql_error(conn));
        AfxMessageBox(L"쿼리 실행 실패: " + error);
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        AfxMessageBox(L"DB 결과 처리 실패");
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    if (row) {
        m_staticName.SetWindowText(CString(row[0]));        // 이름
        m_staticGender.SetWindowText(CString(row[1]));      // 성별
        m_staticAddress.SetWindowText(CString(row[2]));     // 주소
        m_staticPhone.SetWindowText(CString(row[3]));       // 전화번호
        m_staticEmergency.SetWindowText(CString(row[4]));   // 긴급 연락처
        m_staticBlood.SetWindowText(CString(row[5]));       // 혈액형
    }
    else {
        AfxMessageBox(L"환자 정보를 찾을 수 없습니다.");
    }

    mysql_free_result(res);
}


void CBillingDialog::OnBnClickedButtonSearch()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CString residentNumber;
    m_editSSN.GetWindowText(residentNumber);

    if (residentNumber.IsEmpty()) {
        AfxMessageBox(L"주민등록번호를 입력하세요.");
        return;
    }

    LoadChartRecords(residentNumber); // 진료 내역 불러오기;
    LoadPatientInfo(residentNumber); // 환자 정보 불러오기
    LoadPrescriptions(residentNumber);  // 처방전 데이터 불러오기   
    LoadPaymentDates(residentNumber); // 진료 날짜 및 결제 날짜 표시
    LoadNotes(residentNumber); // 메모 불러오기
}

BOOL CBillingDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 리스트 컨트롤 초기화 (Details 뷰, Grid Lines 등 설정)
    m_recordList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    // 흰색 브러시 초기화
    m_whiteBrush.CreateSolidBrush(RGB(255, 255, 255));


    // List Control 초기화
    m_recordList.InsertColumn(0, L"차트 ID", LVCFMT_LEFT, 100);
    m_recordList.InsertColumn(1, L"진 단 명", LVCFMT_LEFT, 150);     // 두 번째 열: k_name
    m_recordList.InsertColumn(2, L"비 용", LVCFMT_LEFT, 100);      // 세 번째 열: k_cost
    m_recordList.InsertColumn(3, L"결 제 상 태", LVCFMT_LEFT, 100); // 미납/완납 상태 추가

    AdjustColumnWidthForRecords();

    // m_recordList.ModifyStyle(0, LVS_SINGLESEL); // 중복 선택 허용 해제 (LVS_SINGLESEL 제거)

    // 처방전 리스트 컨트롤 초기화
    m_prescriptionList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    m_prescriptionList.InsertColumn(0, L"날 짜", LVCFMT_LEFT, 100);
    m_prescriptionList.InsertColumn(1, L"처방 의약품 명칭", LVCFMT_LEFT, 150);
    m_prescriptionList.InsertColumn(2, L"복용 방법", LVCFMT_LEFT, 100);

    /*CFont* pFont = new CFont();
    pFont->CreatePointFont(100, L"맑은 고딕");
    m_recordList.SetFont(pFont);
    m_staticResult.SetFont(pFont);*/

    // Static Control 초기화 (합산 금액)
    m_staticResult.SetWindowText(L"0"); // 초기값을 "0"으로 설정

    AdjustColumnWidth();  // 열 너비 자동 조정

    // Static Control 폰트 설정
    m_staticPaymentDate.SetFont(&m_font);
    m_staticPaymentPDate.SetFont(&m_font);

    ConnectToDatabase(); // DB 연결

    return TRUE;
}


HBRUSH CBillingDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

    // Static Control의 배경을 흰색으로 설정
    if (nCtlColor == CTLCOLOR_STATIC)
    {
        pDC->SetBkColor(RGB(255, 255, 255)); // 흰색 배경 설정
        return m_whiteBrush; // 흰색 브러시 반환
    }

    return hbr;
}


void CBillingDialog::OnBnClickedButtonMarkPaid()
{
    // 리스트에서 선택된 항목 확인
    POSITION pos = m_recordList.GetFirstSelectedItemPosition();
    if (pos == nullptr) {
        AfxMessageBox(L"항목을 선택해주세요.");
        return;
    }

    // 선택된 항목의 chart_id 가져오기
    int selectedItem = m_recordList.GetNextSelectedItem(pos);
    CString chartID = m_recordList.GetItemText(selectedItem, 0); // 첫 번째 열에서 chart_id 가져오기

    // 상태를 '완납'으로 변경하는 함수 호출
    MarkAsPaid(chartID);
}

void CBillingDialog::MarkAsPaid(const CString& chartID)
{
    if (!conn) {
        AfxMessageBox(L"DB 연결이 설정되지 않았습니다.");
        return;
    }

    // chartID 값이 비어 있는지 확인
    if (chartID.IsEmpty()) {
        AfxMessageBox(L"선택된 항목의 chart_id가 없습니다.");
        return;
    }

    // chartID 값이 숫자인지 확인
    int numericChartID = _ttoi(chartID);
    if (numericChartID == 0) {
        AfxMessageBox(L"chart_id 값이 잘못되었습니다. 숫자 형태여야 합니다.");
        return;
    }

    // 디버그 메시지: chartID 값 확인
    // CString debugMessage;
    // debugMessage.Format(L"UPDATE 실행: chartID = %d", numericChartID);
    // AfxMessageBox(debugMessage);



    // 상태를 '완납'으로 변경하는 SQL 쿼리 실행
    CString query;
    query.Format(L"UPDATE decisions SET status = '완납' WHERE chart_id = '%d'", numericChartID);

    if (mysql_query(conn, CStringA(query)) == 0) {
        AfxMessageBox(L"결제가 완료되었습니다.");


        // 리스트와 합산 금액 업데이트
        CString residentNumber;
        m_editSSN.GetWindowText(residentNumber);
        LoadChartRecords(residentNumber); // 리스트 새로고침
        UpdateTotalSum(residentNumber);   // 합산 금액 갱신
    }
    else {
        CString error(mysql_error(conn));
        AfxMessageBox(L"결제 상태 변경 실패: " + error);
    }
}

void CBillingDialog::UpdateTotalSum(const CString& residentNumber)
{
    if (!conn) return;

    // SQL 쿼리: 미납된 k_cost 값 합산
    CString query;
    query.Format(L"SELECT SUM(k_cost) "
        L"FROM decisions "
        L"WHERE status = '미납' AND chart_id IN "
        L"(SELECT chart_id FROM sum WHERE resident_number = '%s')", residentNumber);

    if (mysql_query(conn, CStringA(query)) != 0) {
        CString error(mysql_error(conn));
        AfxMessageBox(L"합산 금액 계산 실패: " + error);
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        AfxMessageBox(L"DB 결과 처리 실패");
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    CString totalSum = row && row[0] ? CString(row[0]) : L"0"; // 결과 값이 없으면 "0" 반환

    // Static Control에 합산 금액 표시
    CString resultText;
    resultText.Format(L"미납 합계: %s 원", totalSum);
    m_staticResult.SetWindowText(resultText);

    mysql_free_result(res);
}


void CBillingDialog::LoadPrescriptions(const CString& residentNumber)
{
    if (!conn) {
        AfxMessageBox(L"DB 연결이 설정되지 않았습니다.");
        return;
    }

    // prescriptions 테이블에서 해당 주민등록번호의 데이터 불러오기
    CString query;
    query.Format(L"SELECT date, drugs_name, method "
        L"FROM prescriptions "
        L"WHERE resident_number = '%s'", residentNumber);

    if (mysql_query(conn, CStringA(query)) != 0) {
        CString error(mysql_error(conn));
        AfxMessageBox(L"처방전 데이터 불러오기 실패: " + error);
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        AfxMessageBox(L"DB 결과 처리 실패");
        return;
    }

    m_prescriptionList.DeleteAllItems(); // 기존 리스트 초기화

    MYSQL_ROW row;
    int index = 0;

    while ((row = mysql_fetch_row(res))) {
        CString date(row[0]);
        CString drugs_name(row[1]);
        CString method(row[2]);

        m_prescriptionList.InsertItem(index, date);
        m_prescriptionList.SetItemText(index, 1, drugs_name);
        m_prescriptionList.SetItemText(index, 2, method);

        index++;
    }

    mysql_free_result(res);
}

void CBillingDialog::AdjustColumnWidth()
{
    // 리스트 컨트롤의 전체 너비 가져오기
    CRect rect;
    m_prescriptionList.GetClientRect(&rect);
    int totalWidth = rect.Width();

    // 열(Column) 수
    const int columnCount = 3;

    // 각 열의 너비를 균등하게 나눔
    int columnWidth = totalWidth / columnCount;

    for (int i = 0; i < columnCount; ++i) {
        m_prescriptionList.SetColumnWidth(i, columnWidth);
    }
}

void CBillingDialog::AdjustColumnWidthForRecords()
{
    // 리스트 컨트롤의 전체 너비 가져오기
    CRect rect;
    m_recordList.GetClientRect(&rect);
    int totalWidth = rect.Width();

    // 열(Column) 수
    const int columnCount = 4;

    // 각 열의 너비를 균등하게 나눔
    int columnWidth = totalWidth / columnCount;

    for (int i = 0; i < columnCount; ++i) {
        m_recordList.SetColumnWidth(i, columnWidth);
    }
}

void CBillingDialog::LoadPaymentDates(const CString& residentNumber)
{
    if (!conn) {
        AfxMessageBox(L"DB 연결이 설정되지 않았습니다.");
        return;
    }

    // payments 테이블에서 date, p_date 가져오기
    CString query;
    query.Format(L"SELECT date, p_date FROM payments WHERE resident_number = '%s'", residentNumber);

    if (mysql_query(conn, CStringA(query)) != 0) {
        CString error(mysql_error(conn));
        AfxMessageBox(L"쿼리 실행 실패: " + error);
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        AfxMessageBox(L"DB 결과 처리 실패");
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    if (row) {
        CString paymentDate = CString(row[0]);  // date 값
        CString paymentPDate = CString(row[1]); // p_date 값

        m_staticPaymentDate.SetWindowText(paymentDate); // 데이터만 출력
        m_staticPaymentPDate.SetWindowText(paymentPDate); // 데이터만 출력
    }
    else {
        m_staticPaymentDate.SetWindowText(L"");
        m_staticPaymentPDate.SetWindowText(L"");
    }

    mysql_free_result(res);
}


void CBillingDialog::OnBnClickedButtonPrintReceipt()
{
    PrintReceipt(); // 영수증 출력 함수 호출
}

void CBillingDialog::PrintReceipt()
{
    CPrintDialog printDlg(FALSE, PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS, this);

    if (printDlg.DoModal() == IDOK) // 프린트 다이얼로그 표시
    {
        // 프린터 DEVMODE 설정
        DEVMODE* pDevMode = printDlg.GetDevMode();
        if (pDevMode != nullptr)
        {
            pDevMode->dmFields |= DM_PAPERSIZE;
            pDevMode->dmPaperSize = DMPAPER_A5; // A5 용지 설정
        }

        // 프린터 DC 다시 생성
        HDC hPrinterDC = printDlg.CreatePrinterDC();
        if (!hPrinterDC)
        {
            AfxMessageBox(L"프린터 DC 생성 실패");
            return;
        }

        CDC printerDC;
        printerDC.Attach(printDlg.GetPrinterDC()); // 프린터 DC 가져오기
        DOCINFO docInfo = { sizeof(DOCINFO), L"진료 내역 및 처방전 영수증" };
        printerDC.StartDoc(&docInfo); // 문서 시작

        // A5 용지 설정 (종이 크기 지정)
        printerDC.SetMapMode(MM_LOMETRIC); // 밀리미터 단위 사용
        CRect pageRect(0, 0, 2100, -1100);  // A5 용지 크기: 210 x 148 mm

        // 폰트 설정
        CFont titleFont, contentFont;
        titleFont.CreatePointFont(160, L"맑은 고딕", &printerDC);  // 제목 폰트 (16pt)
        contentFont.CreatePointFont(100, L"맑은 고딕", &printerDC); // 내용 폰트 (10pt)

        // 출력 시작
        printerDC.StartPage();

        int y = -100; // Y좌표 초기값 (위에서부터 출력)
        int x = 100;  // X좌표 여백

        // **제목 출력**
        CFont* oldFont = printerDC.SelectObject(&titleFont);
        printerDC.TextOut(x, y, L"진료 내역 및 처방전 영수증");
        y -= 150;

        // **환자 정보 출력**
        printerDC.SelectObject(&contentFont);
        CString patientInfo;
        CString patientName, patientAge;
        m_staticName.GetWindowText(patientName);
        patientInfo.Format(L"환자명: %s   출력일: %s", patientName, CTime::GetCurrentTime().Format(L"%Y-%m-%d"));
        printerDC.TextOut(x, y, patientInfo);
        y -= 200;

        // **진료 내역 출력**
        printerDC.TextOut(x, y, L"[진료 내역]");
        y -= 100;

        for (int i = 0; i < m_recordList.GetItemCount(); ++i)
        {
            CString chartID = m_recordList.GetItemText(i, 0);
            CString kName = m_recordList.GetItemText(i, 1);
            CString kCost = m_recordList.GetItemText(i, 2);
            CString status = m_recordList.GetItemText(i, 3);

            CString line;
            line.Format(L"차트 ID: %s | 진단명: %s | 비용: %s 원 | 상태: %s", chartID, kName, kCost, status);
            printerDC.TextOut(x, y, line);
            y -= 100; // 다음 줄로 이동
        }

        y -= 150; // 여백 추가

        // **처방전 출력**
        printerDC.TextOut(x, y, L"[처방전]");
        y -= 100;

        for (int i = 0; i < m_prescriptionList.GetItemCount(); ++i)
        {
            CString date = m_prescriptionList.GetItemText(i, 0);
            CString drugName = m_prescriptionList.GetItemText(i, 1);
            CString method = m_prescriptionList.GetItemText(i, 2);

            CString line;
            line.Format(L"날짜: %s | 처방 의약품: %s | 복용 방법: %s", date, drugName, method);
            printerDC.TextOut(x, y, line);
            y -= 100; // 다음 줄로 이동
        }

        // **출력 종료**
        printerDC.SelectObject(oldFont);
        printerDC.EndPage();
        printerDC.EndDoc();
        printerDC.Detach();
    }
}

// CBillingDialog 메시지 처리기
void CBillingDialog::On32772()
{
    CBillingDialog billingDialog;
    billingDialog.DoModal(); // 모달 방식으로 실행
}


void CBillingDialog::LoadNotes(const CString& residentNumber) {
    if (!conn) {
        AfxMessageBox(L"DB 연결이 설정되지 않았습니다.");
        return;
    }

    // DB에서 notes 불러오기 쿼리
    CString query;
    query.Format(L"SELECT notes FROM payments WHERE resident_number = '%s'", residentNumber);

    if (mysql_query(conn, CStringA(query)) != 0) {
        CString error(mysql_error(conn));
        AfxMessageBox(L"쿼리 실행 실패: " + error);
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        AfxMessageBox(L"DB 결과 처리 실패");
        return;
    }

    // DB에서 결과 읽기
    MYSQL_ROW row = mysql_fetch_row(res);
    if (row && row[0]) { // row가 NULL이 아니고 notes 값이 존재하면
        CString notes = CString(row[0]);
        m_staticMemo.SetWindowText(notes); // Static Control에 notes 표시
    }
    else {
        m_staticMemo.SetWindowText(L"메모가 없습니다."); // notes가 없으면 기본값 출력
    }

    mysql_free_result(res); // 결과 해제
}



