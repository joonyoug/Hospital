// CBillingDialog.cpp: ���� ����

#include "pch.h"
#include "HospitalSystem.h"
#include "afxdialogex.h"
#include "CBillingDialog.h"

// CBillingDialog ��ȭ ����

IMPLEMENT_DYNAMIC(CBillingDialog, CDialogEx)

CBillingDialog::CBillingDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DIALOG1_Payment, pParent)
{
    conn = nullptr; // DB ���� ��ü �ʱ�ȭ
}

CBillingDialog::~CBillingDialog()
{
    if (conn) {
        mysql_close(conn); // MySQL ���� ����
        conn = nullptr;
    }
}

void CBillingDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_SSN, m_editSSN);          // �ֹε�Ϲ�ȣ �Է� �ʵ�
    DDX_Control(pDX, IDC_STATIC_RESULT, m_staticResult); // ��� ǥ�� Static Text
    DDX_Control(pDX, IDC_LIST_RECORDS, m_recordList);    // ���� ���� ����Ʈ
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
    DDX_Control(pDX, IDC_EDIT_MEMO, m_editMemo); // �޸� �Է� �ʵ� ���ε�
}


BEGIN_MESSAGE_MAP(CBillingDialog, CDialogEx)

    ON_WM_CTLCOLOR() // WM_CTLCOLOR �޽��� �߰�
    ON_COMMAND(ID_32772, &CBillingDialog::On32772)
    ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CBillingDialog::OnBnClickedButtonSearch)
    ON_BN_CLICKED(IDC_BUTTON_SAVE_MEMO, &CBillingDialog::OnBnClickedButtonSaveMemo)
    ON_BN_CLICKED(IDC_BUTTON_MARK_PAID, &CBillingDialog::OnBnClickedButtonMarkPaid)
    ON_BN_CLICKED(IDC_BUTTON_PRINT_RECEIPT, &CBillingDialog::OnBnClickedButtonPrintReceipt)
END_MESSAGE_MAP()


// MySQL DB ����
MYSQL* CBillingDialog::ConnectToDatabase()
{
    conn = mysql_init(nullptr);
    if (!conn) {
        AfxMessageBox(L"MySQL �ʱ�ȭ ����");
        return nullptr;
    }

    // MySQL ������ ����
    if (!mysql_real_connect(conn, "34.64.187.178", "root", "Dhalstjs!", "EMR", 3306, nullptr, 0)) {
        CString error(mysql_error(conn));
        AfxMessageBox(L"DB ���� ����: " + error);
        mysql_close(conn);
        return nullptr;
    }

    // ���ڼ� ���� (utf8mb4�� ���� ����)
    if (mysql_set_character_set(conn, "euckr") != 0) {
        CString error(mysql_error(conn));
        AfxMessageBox(L"���ڼ� ���� ����: " + error);
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
        AfxMessageBox(L"DB ������ �������� �ʾҽ��ϴ�.");
        return;
    }

    // sum ���̺�� decisions ���̺� JOIN ���� (��� ������ �ҷ�����)
    CString query;
    query.Format(L"SELECT s.chart_id, d.k_name, COALESCE(d.k_cost, 0), d.status "
        L"FROM sum s "
        L"JOIN decisions d ON s.chart_id = d.chart_id "
        L"WHERE s.resident_number = '%s'", residentNumber);

    if (mysql_query(conn, CStringA(query)) != 0) {
        CString error(mysql_error(conn));
        AfxMessageBox(L"���� ���� ����: " + error);
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        AfxMessageBox(L"DB ��� ó�� ����");
        return;
    }

    m_recordList.DeleteAllItems(); // ���� ����Ʈ �ʱ�ȭ

    MYSQL_ROW row;
    int index = 0;
    double totalSum = 0.0; // �̳� �׸� �ջ� ��

    // ��� �׸� �ҷ�����
    while ((row = mysql_fetch_row(res))) {
        CString chartID(row[0]);  // chart_id
        CString kName(row[1]);    // k_name
        CString kCost(row[2]);    // k_cost
        CString status(row[3]);   // status (�̳� or �ϳ�)
        //AfxMessageBox(L"�ҷ��� k_cost: " + kCost);

        // **����� �޽��� �߰�**
        //CString debugMessage;
        //debugMessage.Format(L"chartID: %s, kCost: %s, status: %s", chartID, kCost, status);
        //AfxMessageBox(debugMessage); // �����͸� Ȯ���ϴ� �޽��� �ڽ�

        // ����Ʈ�� �׸� �߰�
        m_recordList.InsertItem(index, chartID);
        m_recordList.SetItemText(index, 1, kName);
        m_recordList.SetItemText(index, 2, kCost);
        m_recordList.SetItemText(index, 3, status);

        // �̳� ������ k_cost�� �ջ�
        if (status == L"�̳�") {
            kCost.Trim(); // ���� ����
            if (!kCost.IsEmpty() && _ttof(kCost) != 0.0) { // ���� ������� �ʰ� ������ ��츸 ó��
                totalSum += _ttof(kCost); // k_cost ���ڿ��� double�� ��ȯ�Ͽ� �ջ�
            }
        }
        index++;
    }

    mysql_free_result(res);

    // Static Control�� �ջ�� �̳� �ݾ� ǥ��
    CString resultText;
    resultText.Format(L"������ �� �ݾ� : %.0f ��", totalSum);
    //AfxMessageBox(resultText);  // ��� Ȯ��
    m_staticResult.SetWindowText(resultText);
}


void CBillingDialog::LoadPatientInfo(const CString& resident_number)
{
    if (!conn) {
        AfxMessageBox(L"DB ������ �������� �ʾҽ��ϴ�.");
        return;
    }

    // ���� ����
    CString query;
    query.Format(L"SELECT name, gender, address, phone_number, emergency_number, blood_type "
                 L"FROM patients WHERE resident_number = '%s'", resident_number);

    if (mysql_query(conn, CStringA(query)) != 0) {
        CString error(mysql_error(conn));
        AfxMessageBox(L"���� ���� ����: " + error);
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        AfxMessageBox(L"DB ��� ó�� ����");
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    if (row) {
        m_staticName.SetWindowText(CString(row[0]));        // �̸�
        m_staticGender.SetWindowText(CString(row[1]));      // ����
        m_staticAddress.SetWindowText(CString(row[2]));     // �ּ�
        m_staticPhone.SetWindowText(CString(row[3]));       // ��ȭ��ȣ
        m_staticEmergency.SetWindowText(CString(row[4]));   // ��� ����ó
        m_staticBlood.SetWindowText(CString(row[5]));       // ������
    }
    else {
        AfxMessageBox(L"ȯ�� ������ ã�� �� �����ϴ�.");
    }

    mysql_free_result(res);
}


void CBillingDialog::On32772()
{
    // TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
    CBillingDialog billingDialog;
    billingDialog.DoModal(); // ��� ������� ����
}


void CBillingDialog::OnBnClickedButtonSearch()
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
    CString residentNumber;
    m_editSSN.GetWindowText(residentNumber);

    if (residentNumber.IsEmpty()) {
        AfxMessageBox(L"�ֹε�Ϲ�ȣ�� �Է��ϼ���.");
        return;
    }

    LoadChartRecords(residentNumber); // ���� ���� �ҷ�����;

    // ȯ�� ���� �ҷ�����
    LoadPatientInfo(residentNumber);

    LoadPrescriptions(residentNumber);  // ó���� ������ �ҷ�����

    // ���� ��¥ �� ���� ��¥ ǥ��
    LoadPaymentDates(residentNumber);
}

BOOL CBillingDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // ����Ʈ ��Ʈ�� �ʱ�ȭ (Details ��, Grid Lines �� ����)
    m_recordList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    // ��� �귯�� �ʱ�ȭ
    m_whiteBrush.CreateSolidBrush(RGB(255, 255, 255));


    // List Control �ʱ�ȭ
    m_recordList.InsertColumn(0, L"��Ʈ ID", LVCFMT_LEFT, 100);
    m_recordList.InsertColumn(1, L"�� �� ��", LVCFMT_LEFT, 150);     // �� ��° ��: k_name
    m_recordList.InsertColumn(2, L"�� ��", LVCFMT_LEFT, 100);      // �� ��° ��: k_cost
    m_recordList.InsertColumn(3, L"�� �� �� ��", LVCFMT_LEFT, 100); // �̳�/�ϳ� ���� �߰�

    AdjustColumnWidthForRecords();

    // m_recordList.ModifyStyle(0, LVS_SINGLESEL); // �ߺ� ���� ��� ���� (LVS_SINGLESEL ����)

    // ó���� ����Ʈ ��Ʈ�� �ʱ�ȭ
    m_prescriptionList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    m_prescriptionList.InsertColumn(0, L"�� ¥", LVCFMT_LEFT, 100);
    m_prescriptionList.InsertColumn(1, L"ó�� �Ǿ�ǰ ��Ī", LVCFMT_LEFT, 150);
    m_prescriptionList.InsertColumn(2, L"���� ���", LVCFMT_LEFT, 100);

    /*CFont* pFont = new CFont();
    pFont->CreatePointFont(100, L"���� ���");
    m_recordList.SetFont(pFont);
    m_staticResult.SetFont(pFont);*/

    // Static Control �ʱ�ȭ (�ջ� �ݾ�)
     m_staticResult.SetWindowText(L"0"); // �ʱⰪ�� "0"���� ����

    AdjustColumnWidth();  // �� �ʺ� �ڵ� ����

    // Static Control ��Ʈ ����
    m_staticPaymentDate.SetFont(&m_font);
    m_staticPaymentPDate.SetFont(&m_font);

    ConnectToDatabase(); // DB ����

    return TRUE;
}

void CBillingDialog::OnBnClickedButtonSaveMemo()
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
    if (!conn) {
        AfxMessageBox(L"DB ������ �������� �ʾҽ��ϴ�.");
        return;
    }

    // �ֹε�Ϲ�ȣ�� �޸� ���� ��������
    CString residentNumber, memoContent;
    m_editSSN.GetWindowText(residentNumber);
    m_editMemo.GetWindowText(memoContent);

    if (residentNumber.IsEmpty()) {
        AfxMessageBox(L"�ֹε�Ϲ�ȣ�� �Է��ϼ���.");
        return;
    }

    if (memoContent.IsEmpty()) {
        AfxMessageBox(L"�޸� ������ �Է��ϼ���.");
        return;
    }

    // SQL ����: �޸� ������ payments ���̺��� notes Į���� ����
    CString query;
    query.Format(L"UPDATE payments SET notes = '%s' WHERE resident_number = '%s'",
        CStringA(memoContent), CStringA(residentNumber));

    if (mysql_query(conn, CStringA(query)) == 0) {
        AfxMessageBox(L"�޸� ���������� ����Ǿ����ϴ�.");
    }
    else {
        CString error(mysql_error(conn));
        AfxMessageBox(L"�޸� ���� ����: " + error);
    }
}



HBRUSH CBillingDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

    // Static Control�� ����� ������� ����
    if (nCtlColor == CTLCOLOR_STATIC)
    {
        pDC->SetBkColor(RGB(255, 255, 255)); // ��� ��� ����
        return m_whiteBrush; // ��� �귯�� ��ȯ
    }

    return hbr;
}


void CBillingDialog::OnBnClickedButtonMarkPaid()
{
    // ����Ʈ���� ���õ� �׸� Ȯ��
    POSITION pos = m_recordList.GetFirstSelectedItemPosition();
    if (pos == nullptr) {
        AfxMessageBox(L"�׸��� �������ּ���.");
        return;
    }

    // ���õ� �׸��� chart_id ��������
    int selectedItem = m_recordList.GetNextSelectedItem(pos);
    CString chartID = m_recordList.GetItemText(selectedItem, 0); // ù ��° ������ chart_id ��������

    // ���¸� '�ϳ�'���� �����ϴ� �Լ� ȣ��
    MarkAsPaid(chartID);
}

void CBillingDialog::MarkAsPaid(const CString& chartID)
{
    if (!conn) {
        AfxMessageBox(L"DB ������ �������� �ʾҽ��ϴ�.");
        return;
    }

    // chartID ���� ��� �ִ��� Ȯ��
    if (chartID.IsEmpty()) {
        AfxMessageBox(L"���õ� �׸��� chart_id�� �����ϴ�.");
        return;
    }

    // chartID ���� �������� Ȯ��
    int numericChartID = _ttoi(chartID);
    if (numericChartID == 0) {
        AfxMessageBox(L"chart_id ���� �߸��Ǿ����ϴ�. ���� ���¿��� �մϴ�.");
        return;
    }

    // ����� �޽���: chartID �� Ȯ��
    // CString debugMessage;
    // debugMessage.Format(L"UPDATE ����: chartID = %d", numericChartID);
    // AfxMessageBox(debugMessage);

    

    // ���¸� '�ϳ�'���� �����ϴ� SQL ���� ����
    CString query;
    query.Format(L"UPDATE decisions SET status = '�ϳ�' WHERE chart_id = '%d'", numericChartID);

    if (mysql_query(conn, CStringA(query)) == 0) {
        AfxMessageBox(L"������ �Ϸ�Ǿ����ϴ�.");


        // ����Ʈ�� �ջ� �ݾ� ������Ʈ
        CString residentNumber;
        m_editSSN.GetWindowText(residentNumber);
        LoadChartRecords(residentNumber); // ����Ʈ ���ΰ�ħ
        UpdateTotalSum(residentNumber);   // �ջ� �ݾ� ����
    }
    else {
        CString error(mysql_error(conn));
        AfxMessageBox(L"���� ���� ���� ����: " + error);
    }
}

void CBillingDialog::UpdateTotalSum(const CString& residentNumber)
{
    if (!conn) return;

    // SQL ����: �̳��� k_cost �� �ջ�
    CString query;
    query.Format(L"SELECT SUM(k_cost) "
        L"FROM decisions "
        L"WHERE status = '�̳�' AND chart_id IN "
        L"(SELECT chart_id FROM sum WHERE resident_number = '%s')", residentNumber);

    if (mysql_query(conn, CStringA(query)) != 0) {
        CString error(mysql_error(conn));
        AfxMessageBox(L"�ջ� �ݾ� ��� ����: " + error);
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        AfxMessageBox(L"DB ��� ó�� ����");
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    CString totalSum = row && row[0] ? CString(row[0]) : L"0"; // ��� ���� ������ "0" ��ȯ

    // Static Control�� �ջ� �ݾ� ǥ��
    CString resultText;
    resultText.Format(L"�̳� �հ�: %s ��", totalSum);
    m_staticResult.SetWindowText(resultText);

    mysql_free_result(res);
}


void CBillingDialog::LoadPrescriptions(const CString& residentNumber)
{
    if (!conn) {
        AfxMessageBox(L"DB ������ �������� �ʾҽ��ϴ�.");
        return;
    }

    // prescriptions ���̺��� �ش� �ֹε�Ϲ�ȣ�� ������ �ҷ�����
    CString query;
    query.Format(L"SELECT date, drugs_name, notes "
        L"FROM prescriptions "
        L"WHERE resident_number = '%s'", residentNumber);

    if (mysql_query(conn, CStringA(query)) != 0) {
        CString error(mysql_error(conn));
        AfxMessageBox(L"ó���� ������ �ҷ����� ����: " + error);
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        AfxMessageBox(L"DB ��� ó�� ����");
        return;
    }

    m_prescriptionList.DeleteAllItems(); // ���� ����Ʈ �ʱ�ȭ

    MYSQL_ROW row;
    int index = 0;

    while ((row = mysql_fetch_row(res))) {
        CString date(row[0]);
        CString drugs_name(row[1]);
        CString notes(row[2]);

        m_prescriptionList.InsertItem(index, date);
        m_prescriptionList.SetItemText(index, 1, drugs_name);
        m_prescriptionList.SetItemText(index, 2, notes);

        index++;
    }

    mysql_free_result(res);
}

void CBillingDialog::AdjustColumnWidth()
{
    // ����Ʈ ��Ʈ���� ��ü �ʺ� ��������
    CRect rect;
    m_prescriptionList.GetClientRect(&rect);
    int totalWidth = rect.Width();

    // ��(Column) ��
    const int columnCount = 3;

    // �� ���� �ʺ� �յ��ϰ� ����
    int columnWidth = totalWidth / columnCount;

    for (int i = 0; i < columnCount; ++i) {
        m_prescriptionList.SetColumnWidth(i, columnWidth);
    }
}

void CBillingDialog::AdjustColumnWidthForRecords()
{
    // ����Ʈ ��Ʈ���� ��ü �ʺ� ��������
    CRect rect;
    m_recordList.GetClientRect(&rect);
    int totalWidth = rect.Width();

    // ��(Column) ��
    const int columnCount = 4;

    // �� ���� �ʺ� �յ��ϰ� ����
    int columnWidth = totalWidth / columnCount;

    for (int i = 0; i < columnCount; ++i) {
        m_recordList.SetColumnWidth(i, columnWidth);
    }
}

void CBillingDialog::LoadPaymentDates(const CString& residentNumber)
{
    if (!conn) {
        AfxMessageBox(L"DB ������ �������� �ʾҽ��ϴ�.");
        return;
    }

    // payments ���̺��� date, p_date ��������
    CString query;
    query.Format(L"SELECT date, p_date FROM payments WHERE resident_number = '%s'", residentNumber);

    if (mysql_query(conn, CStringA(query)) != 0) {
        CString error(mysql_error(conn));
        AfxMessageBox(L"���� ���� ����: " + error);
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) {
        AfxMessageBox(L"DB ��� ó�� ����");
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    if (row) {
        CString paymentDate = CString(row[0]);  // date ��
        CString paymentPDate = CString(row[1]); // p_date ��

        m_staticPaymentDate.SetWindowText(paymentDate); // �����͸� ���
        m_staticPaymentPDate.SetWindowText(paymentPDate); // �����͸� ���
    }
    else {
        m_staticPaymentDate.SetWindowText(L"");
        m_staticPaymentPDate.SetWindowText(L"");
    }

    mysql_free_result(res);
}


void CBillingDialog::OnBnClickedButtonPrintReceipt()
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
    PrintReceipt(); // ������ ��� �Լ� ȣ��
}

void CBillingDialog::PrintReceipt()
{
    CPrintDialog printDlg(FALSE, PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS, this);

    if (printDlg.DoModal() == IDOK) // ����Ʈ ���̾�α� ǥ��
    {
        CDC printerDC;
        printerDC.Attach(printDlg.GetPrinterDC()); // ������ DC ��������
        printerDC.StartDoc(L"���� ���� �� ó���� ������");

        // ��� ����
        printerDC.StartPage();

        // ��Ʈ ����
        CFont font;
        font.CreatePointFont(100, L"���� ���", &printerDC);
        CFont* oldFont = printerDC.SelectObject(&font);

        int y = 100; // ���� y��ǥ

        // **���� ���**
        printerDC.TextOut(100, y, L"���� ���� �� ó���� ������");
        y += 150;

        // **���� ���� ���**
        printerDC.TextOut(100, y, L"[���� ����]");
        y += 50;

        for (int i = 0; i < m_recordList.GetItemCount(); ++i)
        {
            CString chartID = m_recordList.GetItemText(i, 0);
            CString kName = m_recordList.GetItemText(i, 1);
            CString kCost = m_recordList.GetItemText(i, 2);
            CString status = m_recordList.GetItemText(i, 3);

            CString line;
            line.Format(L"��Ʈ ID: %s, ���ܸ�: %s, ���: %s ��, ����: %s", chartID, kName, kCost, status);

            printerDC.TextOut(100, y, line);
            y += 50;
        }

        y += 100; // ���� �߰�

        // **ó���� ���**
        printerDC.TextOut(100, y, L"[ó����]");
        y += 50;

        for (int i = 0; i < m_prescriptionList.GetItemCount(); ++i)
        {
            CString date = m_prescriptionList.GetItemText(i, 0);
            CString drugName = m_prescriptionList.GetItemText(i, 1);
            CString notes = m_prescriptionList.GetItemText(i, 2);

            CString line;
            line.Format(L"��¥: %s, ó�� �Ǿ�ǰ: %s, ���� ���: %s", date, drugName, notes);

            printerDC.TextOut(100, y, line);
            y += 50;
        }

        // **����Ʈ ����**
        printerDC.SelectObject(oldFont);
        printerDC.EndPage();
        printerDC.EndDoc();
        printerDC.Detach();
    }
}

