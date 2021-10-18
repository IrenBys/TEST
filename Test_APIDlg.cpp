
// Test_APIDlg.cpp: файл реализации
//


#include "pch.h"
#include "framework.h"
#include "Test_API.h"
#include "Test_APIDlg.h"
#include "afxdialogex.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CTestAPIDlg



CTestAPIDlg::CTestAPIDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST_API_DIALOG, pParent)
	, COM_NUM(0)
	, BAUD_RATE(0)
	, Tx_data(_T(""))
	, Rx_data(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestAPIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, COM_NUM);
	DDX_Text(pDX, IDC_EDIT4, BAUD_RATE);
	DDX_Text(pDX, IDC_EDIT2, Tx_data);
	DDX_Text(pDX, IDC_EDIT3, Rx_data);
}

BEGIN_MESSAGE_MAP(CTestAPIDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN_COM, &CTestAPIDlg::OnBnClickedOpenCom)
	ON_BN_CLICKED(IDC_SEND, &CTestAPIDlg::OnBnClickedSend)
END_MESSAGE_MAP()


// Обработчики сообщений CTestAPIDlg

BOOL CTestAPIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию


	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CTestAPIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CTestAPIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestAPIDlg::OnBnClickedOpenCom()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(TRUE);

	if (COM_NUM == 0 || BAUD_RATE == 0)
	{
		MessageBox(L"Not correct data", L"Error", MB_ICONERROR);
		return;;
	}

	bool b = sg.Open(COM_NUM, BAUD_RATE);
	if (b == false)
	{
		MessageBox(L"Cant't open port", L"Error", MB_ICONERROR);
		return;;
	}
	else
	{
		MessageBox(L"Port open", L"Info", MB_ICONASTERISK);
		
	}

	SetTimer(1, 1000, NULL);
}


void CTestAPIDlg::OnTimer(UINT nIDEvent)
{
	// TODO: Добавьте сюда код реализации.

	char buff[128];

	int rcv = sg.Recv(buff, sizeof(buff));

	if (rcv > 0)
	{
		for (int i = 0; i < rcv; i++)
			this->Rx_data += buff[i];

		UpdateData(false);
	}

	CDialog::OnTimer(nIDEvent);
}


void CTestAPIDlg::OnBnClickedSend()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData(true);

	int len = this->Tx_data.GetLength();
	if (len > 0)
	{
		char * LocBuf = Tx_data.GetBuffer(128);
		sg.Send(LocBuf, len);
		Tx_data.ReleaseBuffer();
	}
}
