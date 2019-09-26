
// work.cpp: Definuje chování tříd pro aplikaci.
//

#include "stdafx.h"
#include "work.h"
#include "workDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CworkApp

BEGIN_MESSAGE_MAP(CworkApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CworkApp – vytváření

CworkApp::CworkApp()
{
	// podpora Restart Manageru
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: sem přidejte kód konstrukce
	// Umístěte veškerou důležitou inicializaci do funkce InitInstance.
}


// Jediný objekt CworkApp

CworkApp theApp;


// CworkApp – inicializace

BOOL CworkApp::InitInstance()
{
	// Ve Windows XP se vyžaduje InitCommonControlsEx(), pokud manifest aplikace
	// určuje, aby se použila knihovna ComCtl32.dll ve verzi 6 nebo novější a povolily se tak
	// vizuální styly. Jinak se nepovede vytvořit žádné okno.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Toto nastavte, pokud chcete zahrnout všechny běžné třídy ovládacích prvků, které chcete použít
	// v aplikaci.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Vytvoření správce prostředí pro případ, že dialog obsahuje
	// nějaký ovládací prvek stromového zobrazení nebo seznamu prostředí
	CShellManager *pShellManager = new CShellManager;

	// Aktivace správce vzhledu Windows Native, aby se v ovládacích prvcích MFC povolily motivy
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standardní inicializace
	// Pokud tyto funkce nepoužíváte a chcete zmenšit velikost
	// svého konečného spustitelného souboru, měli byste odebrat následující
	// konkrétní inicializační rutiny, které nepotřebujete.
	// Změňte klíč registru, ve kterém jsou uložená nastavení.
	// TODO: Tento řetězec byste měli upravit na nějakou vhodnou hodnotu,
	// například název společnosti nebo organizace.
	SetRegistryKey(_T("Místní aplikace vygenerované průvodcem aplikací"));

	CworkDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Sem vložte kód, který bude reagovat na situaci, kdy se dialog
		//  ukončí příkazem OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Sem vložte kód, který bude reagovat na situaci, kdy se dialog
		//  ukončí příkazem Zrušit
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Upozornění: Dialog se nepovedlo vytvořit, proto se aplikace neočekávaně ukončuje.\n");
		TRACE(traceAppMsg, 0, "Upozornění: Pokud v dialogu používáte ovládací prvky MFC, nemůžete zadat #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Odstraňte správce prostředí vytvořeného výše.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Dialog se zavřel, proto se vrátí FALSE, aby se aplikace
	//  ukončila a nespouštěla se její pumpa zpráv.
	return FALSE;
}

