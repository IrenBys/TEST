
// Test_APIDlg.h: файл заголовка
//

#pragma once

#include "SerialGate.h"

// Диалоговое окно CTestAPIDlg
class CTestAPIDlg : public CDialogEx
{
// Создание
public:
	CTestAPIDlg(CWnd* pParent = nullptr);	// стандартный конструктор
	SerialGate sg;

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_API_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenCom();
	// Номер порта
	UINT COM_NUM;
	// Скорость
	UINT BAUD_RATE;
	// Передаваемое сообщение
	CString Tx_data;
	// Принятое сообщение
	CString Rx_data;
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedSend();
};
