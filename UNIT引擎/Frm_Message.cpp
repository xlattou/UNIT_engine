// Frm_Message.cpp : 实现文件
//

#include "stdafx.h"
#include "CWPowerTest.h"
#include "Frm_Message.h"


// Frm_Message 对话框

IMPLEMENT_DYNAMIC(Frm_Message, CDialog)

Frm_Message::Frm_Message(CWnd* pParent /*=NULL*/)
	: CDialog(Frm_Message::IDD, pParent)
{

}

Frm_Message::Frm_Message(CString strMessage,CWnd* pParent)
: CDialog(Frm_Message::IDD, pParent)
{
	m_strMessage=strMessage;
}

Frm_Message::~Frm_Message()
{
}

void Frm_Message::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Frm_Message, CDialog)
END_MESSAGE_MAP()


// Frm_Message 消息处理程序

BOOL Frm_Message::OnInitDialog()
{
	//CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
    this->SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	this->GetDlgItem(IDC_EDIT_MESSAGE)->SetWindowText(m_strMessage);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
