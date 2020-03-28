// 2048Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "Mind.h"


// CMy2048Dlg 对话框
class CMy2048Dlg : public CDialog
{
// 构造
public:
	CMy2048Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DLG_MAIN };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
    virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
    CBitmapButton m_Btn_01;
    CBitmapButton m_Btn_02;
    CBitmapButton m_Btn_03;
    CBitmapButton m_Btn_04;
    CBitmapButton m_Btn_05;
    CBitmapButton m_Btn_06;
    CBitmapButton m_Btn_07;
    CBitmapButton m_Btn_08;
    CBitmapButton m_Btn_09;
    CBitmapButton m_Btn_10;
    CBitmapButton m_Btn_11;
    CBitmapButton m_Btn_12;
    CBitmapButton m_Btn_13;
    CBitmapButton m_Btn_14;
    CBitmapButton m_Btn_15;
    CBitmapButton m_Btn_16;    

    bool DispAll(int iDire,long lNo);

    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    CStatic m_sta_totnum;
    CStatic m_sta_totsteps;
    CStatic m_sta_dire;
    afx_msg void OnMenuRestart();
    afx_msg void OnMenuExit();
    afx_msg void OnMenuRecord();
    afx_msg void OnMenuEnd();
    afx_msg void OnMenuDisplay();
    afx_msg void OnMenuDispEnd();

    bool bLunchDisp;
    afx_msg void OnMenuExplain();
    afx_msg void OnMenuCheat();
};
