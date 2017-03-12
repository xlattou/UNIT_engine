#pragma once
#include "afxwin.h"
//#include "OperateFunc.h"


// CMessageInput 对话框

class CMessageInput : public CDialog
{
	DECLARE_DYNAMIC(CMessageInput)

public:
	CMessageInput(CWnd* pParent = NULL);   // 标准构造函数
	CMessageInput(CString key,CString message,CString unit,CWnd* pParent);   // 自定义构造函数
	virtual ~CMessageInput();

// 对话框数据
	enum { IDD = IDD_DIALOG_INPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_message;
	CString m_unit;
	CString m_key;
	virtual BOOL OnInitDialog();
	CString m_input;
	afx_msg void OnBnClickedOkk();
};
