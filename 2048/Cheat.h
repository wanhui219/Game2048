#pragma once


// CCheat �Ի���

class CCheat : public CDialog
{
	DECLARE_DYNAMIC(CCheat)

public:
	CCheat(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCheat();

// �Ի�������
	enum { IDD = IDD_DLG_Cheat };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
    
	DECLARE_MESSAGE_MAP()
};
