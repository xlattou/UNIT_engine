// MessageDecide.cpp : 实现文件
//

#include "stdafx.h"
#include "CWPowerTest.h"
#include "MessageDecide.h"


// CMessageDecide 对话框

IMPLEMENT_DYNAMIC(CMessageDecide, CDialog)

CMessageDecide::CMessageDecide(CWnd* pParent /*=NULL*/)
	: CDialog(CMessageDecide::IDD, pParent)
{

}

CMessageDecide::~CMessageDecide()
{
}

void CMessageDecide::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMessageDecide, CDialog)
END_MESSAGE_MAP()


// CMessageDecide 消息处理程序
