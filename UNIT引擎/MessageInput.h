#pragma once
#include "afxwin.h"
//#include "OperateFunc.h"


// CMessageInput �Ի���

class CMessageInput : public CDialog
{
	DECLARE_DYNAMIC(CMessageInput)

public:
	CMessageInput(CWnd* pParent = NULL);   // ��׼���캯��
	CMessageInput(CString key,CString message,CString unit,CWnd* pParent);   // �Զ��幹�캯��
	virtual ~CMessageInput();

// �Ի�������
	enum { IDD = IDD_DIALOG_INPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_message;
	CString m_unit;
	CString m_key;
	virtual BOOL OnInitDialog();
	CString m_input;
	afx_msg void OnBnClickedOkk();
};
