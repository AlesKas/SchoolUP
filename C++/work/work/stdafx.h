
// stdafx.h: soubor k zahrnutí pro standardní systémové soubory k zahrnutí,
// nebo často používané soubory k zahrnutí specifické pro projekt,
// které se mění jen zřídka

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Vyloučit málo používané položky z hlavičkových souborů Windows
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // některé konstruktory CString budou explicitní

// vypne skrývání MFC některých běžných a často bez problémů ignorovaných zpráv upozornění
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // základní a standardní součásti MFC
#include <afxext.h>         // rozšíření MFC


#include <afxdisp.h>        // Automatizační třídy MFC



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // podpora MFC pro běžné ovládací prvky Internet Exploreru 4
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // podpora MFC pro běžné ovládací prvky Windows
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // Podpora pásů karet a ovládacích panelů v MFC









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


