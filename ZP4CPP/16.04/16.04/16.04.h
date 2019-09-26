
// 16.04.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMy1604App:
// See 16.04.cpp for the implementation of this class
//

class CMy1604App : public CWinApp
{
public:
	CMy1604App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMy1604App theApp;
