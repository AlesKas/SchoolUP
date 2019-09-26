
// workDlg.cpp: soubor implementace
//

#include "stdafx.h"
#include "work.h"
#include "workDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Dialog CworkDlg



CworkDlg::CworkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WORK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CworkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, input);
	DDX_Control(pDX, IDC_EDIT1, output);
	DDX_Control(pDX, IDC_RADIO1, bin);
	DDX_Control(pDX, IDC_RADIO2, oct);
	DDX_Control(pDX, IDC_RADIO3, hex);
}

BEGIN_MESSAGE_MAP(CworkDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, &CworkDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CworkDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON1, &CworkDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Popisovače zpráv CworkDlg

BOOL CworkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Nastavit ikonu pro tento dialog. Rozhraní toto dělá automaticky,
	//  když hlavní okno aplikace není dialog.
	SetIcon(m_hIcon, TRUE);			// Nastavit velkou ikonu
	SetIcon(m_hIcon, FALSE);		// Nastavit malou ikonu

	// TODO: Sem přidejte dodatečnou inicializaci.

	return TRUE;  // vrátí hodnotu TRUE, pokud neaktivujete ovládací prvek
}

// Pokud do dialogu přidáte tlačítko pro minimalizaci, budete potřebovat kód uvedený níže,
//  aby se ikona vykreslila. U aplikací MFC, které používají model dokument/zobrazení,
//  toto za vás automaticky dělá rozhraní.

void CworkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // kontext zařízení pro kreslení

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Zarovnat ikonu v obdélníku klienta na střed
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Vykreslit ikonu
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Systém tuto funkci volá, aby získal kurzor, který se zobrazí ve chvíli, kdy uživatel přetahuje
//  minimalizované okno.
HCURSOR CworkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CworkDlg::OnBnClickedRadio1()
{
	// TODO: Sem přidejte obslužnou rutinu oznámení ovládacích prvků.
}


void CworkDlg::OnBnClickedRadio2()
{
	// TODO: Sem přidejte obslužnou rutinu oznámení ovládacích prvků.
}


void CworkDlg::OnBnClickedButton1()
{

	char buff[50];
	CString c;
	input.GetWindowText(c);
	int num = _ttoi(c); 
	

	if (IsDlgButtonChecked(IDC_RADIO1) == BST_CHECKED)
	{
		_itoa_s(num, buff, 2);
	}
	else if (IsDlgButtonChecked(IDC_RADIO2) == BST_CHECKED)
	{
		_itoa_s(num, buff, 8);
	}
	else if (IsDlgButtonChecked(IDC_RADIO3) == BST_CHECKED)
	{
		_itoa_s(num, buff, 16);
	}
	c = buff;
	output.SetWindowText(c);
}
