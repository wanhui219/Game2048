#pragma once


// CCheat 对话框

class CCheat : public CDialog
{
	DECLARE_DYNAMIC(CCheat)

public:
	CCheat(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCheat();

// 对话框数据
	enum { IDD = IDD_DLG_Cheat };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    
	DECLARE_MESSAGE_MAP()
};
