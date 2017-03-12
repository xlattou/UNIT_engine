#pragma once

// CMessageDecide 对话框

class CMessageDecide : public CDialog
{
	DECLARE_DYNAMIC(CMessageDecide)

public:
	CMessageDecide(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMessageDecide();

// 对话框数据
	enum { IDD = IDD_DIALOG_DECIDE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
