// MessageInput.cpp : 实现文件
//

#include "stdafx.h"
#include "CWPowerTest.h"
#include "MessageInput.h"


// CMessageInput 对话框

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
	// TODO:  在此添加额外的初始化
    UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



void CMessageInput::OnBnClickedOkk()
{
	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	char* s=new char[MAX_PATH];
	GetModuleFileName(NULL,s,MAX_PATH); //获得程序路径
	(_tcsrchr(s,_T('\\')))[1]=0; //获取程序运行目录
	CString s_temp(s);
	s_temp+="DeviceHandle.ini";
	CString myValue="";
	myValue.Format("status=1;value=%s",m_input);
	int mark=WritePrivateProfileString("TPStatusCache",m_key,myValue,s_temp);
	CDialog::EndDialog(mark);
}
