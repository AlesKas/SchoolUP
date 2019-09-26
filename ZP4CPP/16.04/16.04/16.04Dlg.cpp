
// 16.04Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "16.04.h"
#include "16.04Dlg.h"
#include "afxdialogex.h"
#include "Jmena2.cpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy1604Dlg dialog



CMy1604Dlg::CMy1604Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY1604_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy1604Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, list1);
	DDX_Control(pDX, IDC_LIST1, list2);
}

BEGIN_MESSAGE_MAP(CMy1604Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy1604Dlg::OnBnClickedButton1)
	ON_LBN_DBLCLK(IDC_LIST1, &CMy1604Dlg::OnLbnDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy1604Dlg::OnBnClickedButton2)
	ON_LBN_DBLCLK(IDC_LIST2, &CMy1604Dlg::OnLbnDblclkList2)
END_MESSAGE_MAP()


// CMy1604Dlg message handlers

BOOL CMy1604Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	for (int i = 0; i < 20; i++)
	{
		list1.AddString(CString(Jmena[i]));
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy1604Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy1604Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void presun(CListBox &a, CListBox &b) {
	
	for (int i = a.GetCount(); i >= 0; i--) {
		if (a.GetSel(i) > 0) {
			CString name;

			a.GetText(i, name);
			b.AddString(name);

			a.DeleteString(i);

		}
	}

}


void CMy1604Dlg::OnBnClickedButton1()
{
	presun(list1, list2);
}

void CMy1604Dlg::OnLbnDblclkList1()
{
	presun(list2, list1);
}


void CMy1604Dlg::OnBnClickedButton2()
{
	presun(list2, list1);
}

void CMy1604Dlg::OnLbnDblclkList2()
{
	presun(list1, list2);
}
