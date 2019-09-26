
// 16.dubnaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "16.dubna.h"
#include "16.dubnaDlg.h"
#include "afxdialogex.h"
#include "Jmena2.cpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy16dubnaDlg dialog



CMy16dubnaDlg::CMy16dubnaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY16DUBNA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy16dubnaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, list1);
	DDX_Control(pDX, IDC_LIST2, list2);
}

BEGIN_MESSAGE_MAP(CMy16dubnaDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMy16dubnaDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CMy16dubnaDlg::OnBnClickedButton1)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMy16dubnaDlg::OnLbnSelchangeList1)
	ON_LBN_SELCHANGE(IDC_LIST2, &CMy16dubnaDlg::OnLbnSelchangeList2)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy16dubnaDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMy16dubnaDlg message handlers

BOOL CMy16dubnaDlg::OnInitDialog()
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

void CMy16dubnaDlg::OnPaint()
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
HCURSOR CMy16dubnaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy16dubnaDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void presunout(CListBox &l1, CListBox &l2)
{
	for (int i = l1.GetCount(), m = l1.GetSelCount(); m > 0; --i)
	{
		if (l1.GetSel(i) > 0)
		{
			CString name;
			l1.GetText(i, name);
			l2.AddString(name);
			l1.DeleteString(i);
			--m;
		}
	}
}
