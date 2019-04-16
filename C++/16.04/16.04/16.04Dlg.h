
// 16.04Dlg.h : header file
//

#pragma once


// CMy1604Dlg dialog
class CMy1604Dlg : public CDialogEx
{
// Construction
public:
	CMy1604Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY1604_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	void presunout(CListBox &, CListBox &);
	CListBox list1;
	CListBox list2;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLbnDblclkList1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnLbnDblclkList2();
};
