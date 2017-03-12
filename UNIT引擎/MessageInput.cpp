// MessageInput.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CWPowerTest.h"
#include "MessageInput.h"


// CMessageInput �Ի���

IMPLEMENT_DYNAMIC(CMessageInput, CDialog)

CMessageInput::CMessageInput(CWnd* pParent /*=NULL*/)
	: CDialog(CMessageInput::IDD, pParent)
{

}
CMessageInput::CMessageInput(CString key,CString message,CString unit,CWnd* pParent)
    : CDialog(CMessageInput::IDD, pParent)
{
	m_key=key;
	m_message=message;
	m_unit=unit;
}

CMessageInput::~CMessageInput()
{
}

void CMessageInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_TEXT, m_message);
	DDX_Text(pDX, IDC_STATIC_UNIT, m_unit);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_input);
}


BEGIN_MESSAGE_MAP(CMessageInput, CDialog)
	ON_BN_CLICKED(IDOKK, &CMessageInput::OnBnClickedOkk)
END_MESSAGE_MAP()



BOOL CMessageInput::OnInitDialog()
{
	CDialog::OnInitDialog();
    //this->SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
    UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}



void CMessageInput::OnBnClickedOkk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	char* s=new char[MAX_PATH];
	GetModuleFileName(NULL,s,MAX_PATH); //��ó���·��
	(_tcsrchr(s,_T('\\')))[1]=0; //��ȡ��������Ŀ¼
	CString s_temp(s);
	s_temp+="DeviceHandle.ini";
	CString myValue="";
	myValue.Format("status=1;value=%s",m_input);
	int mark=WritePrivateProfileString("TPStatusCache",m_key,myValue,s_temp);
	CDialog::EndDialog(mark);
}
