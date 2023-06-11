// TabuGA.h : main header file for the TABUGA application
//

#if !defined(AFX_TABUGA_H__C64237CB_B1EC_477F_BE22_C4CBC15D89A6__INCLUDED_)
#define AFX_TABUGA_H__C64237CB_B1EC_477F_BE22_C4CBC15D89A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTabuGAApp:
// See TabuGA.cpp for the implementation of this class
//

class CTabuGAApp : public CWinApp
{
public:
	CTabuGAApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabuGAApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTabuGAApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABUGA_H__C64237CB_B1EC_477F_BE22_C4CBC15D89A6__INCLUDED_)
