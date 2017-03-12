// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__027549E7_2D3B_4EF7_8984_6CC95FEF90A6__INCLUDED_)
#define AFX_STDAFX_H__027549E7_2D3B_4EF7_8984_6CC95FEF90A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <string>
#include <vector>
#include <bitset>
#include <cmath>
using std::string;
//#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#include "resource.h"

//lua环境头文件
extern "C" 
{
#include "./lua/lua.h"
#include "./lua/lualib.h"
#include "./lua/lauxlib.h"
#include "./lua/luaconf.h"
};


extern char m_ConfigPath[MAX_PATH];


#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__027549E7_2D3B_4EF7_8984_6CC95FEF90A6__INCLUDED_)
