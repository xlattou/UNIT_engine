// Frm_Message.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CWPowerTest.h"
#include "Frm_Message.h"


// Frm_Message �Ի���

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


// Frm_Message ��Ϣ�������

BOOL Frm_Message::OnInitDialog()
{
	//CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
    this->SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	this->GetDlgItem(IDC_EDIT_MESSAGE)->SetWindowText(m_strMessage);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
