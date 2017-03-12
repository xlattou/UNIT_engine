// CWPowerTest.h : main header file for the CWPOWERTEST DLL
//

#if !defined(AFX_CWPOWERTEST_H__81FF4688_4C85_4266_B8AD_09A5A55BD368__INCLUDED_)
#define AFX_CWPOWERTEST_H__81FF4688_4C85_4266_B8AD_09A5A55BD368__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCWPowerTestApp
// See CWPowerTest.cpp for the implementation of this class
//

class CCWPowerTestApp : public CWinApp
{
public:
	CCWPowerTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCWPowerTestApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CCWPowerTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CWPOWERTEST_H__81FF4688_4C85_4266_B8AD_09A5A55BD368__INCLUDED_)
