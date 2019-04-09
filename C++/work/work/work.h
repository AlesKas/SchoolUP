
// work.h: hlavní soubor hlaviček pro aplikaci PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "zahrnout soubor stdafx.h před zahrnutím tohoto souboru pro soubor PCH"
#endif

#include "resource.h"		// hlavní symboly


// CworkApp:
// Implementaci této třídy najdete v work.cpp.
//

class CworkApp : public CWinApp
{
public:
	CworkApp();

// Přepsání
public:
	virtual BOOL InitInstance();

// Implementace

	DECLARE_MESSAGE_MAP()
};

extern CworkApp theApp;
