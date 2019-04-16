
// 16.dubna.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMy16dubnaApp:
// See 16.dubna.cpp for the implementation of this class
//

class CMy16dubnaApp : public CWinApp
{
public:
	CMy16dubnaApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMy16dubnaApp theApp;
