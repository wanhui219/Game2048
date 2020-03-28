// Cheat.cpp : 实现文件
//

#include "stdafx.h"
#include "2048.h"
#include "Cheat.h"


// CCheat 对话框

IMPLEMENT_DYNAMIC(CCheat, CDialog)

CCheat::CCheat(CWnd* pParent /*=NULL*/)
	: CDialog(CCheat::IDD, pParent)
{
    
}

CCheat::~CCheat()
{
}

void CCheat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCheat, CDialog)
END_MESSAGE_MAP()
