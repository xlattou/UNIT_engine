#pragma once

// CMessageDecide �Ի���

class CMessageDecide : public CDialog
{
	DECLARE_DYNAMIC(CMessageDecide)

public:
	CMessageDecide(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMessageDecide();

// �Ի�������
	enum { IDD = IDD_DIALOG_DECIDE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
