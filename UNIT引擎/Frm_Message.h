#pragma once


// Frm_Message 对话框

class Frm_Message : public CDialog
{
	DECLARE_DYNAMIC(Frm_Message)

public:
	Frm_Message(CWnd* pParent = NULL);   // 标准构造函数
    Frm_Message(CString strMessage,CWnd* pParent = NULL);   // 自定义构造函数
	virtual ~Frm_Message();
    CString m_strMessage;

// 对话框数据
	enum { IDD = IDD_DIALOG_MESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
