#pragma once


// CHelp �Ի���

class CHelp : public CDialog
{
	DECLARE_DYNAMIC(CHelp)

public:
	CHelp(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHelp();

// �Ի�������
	enum { IDD = IDD_DLG_Explain };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
