
// workDlg.h: soubor hlaviček
//

#pragma once


// Dialog CworkDlg
class CworkDlg : public CDialogEx
{
// Konstrukce
public:
	CworkDlg(CWnd* pParent = nullptr);	// standardní konstruktor

// Data dialogu
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WORK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Podpora DDX/DDV


// Implementace
protected:
	HICON m_hIcon;

	// Vygenerované funkce mapy zpráv
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit input;
	CEdit output;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedButton1();
	CButton bin;
	CButton oct;
	CButton hex;
};
