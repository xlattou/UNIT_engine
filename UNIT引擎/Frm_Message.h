#pragma once


// Frm_Message �Ի���

class Frm_Message : public CDialog
{
	DECLARE_DYNAMIC(Frm_Message)

public:
	Frm_Message(CWnd* pParent = NULL);   // ��׼���캯��
    Frm_Message(CString strMessage,CWnd* pParent = NULL);   // �Զ��幹�캯��
	virtual ~Frm_Message();
    CString m_strMessage;

// �Ի�������
	enum { IDD = IDD_DIALOG_MESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
