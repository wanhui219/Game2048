// Help.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "2048.h"
#include "Help.h"


// CHelp �Ի���

IMPLEMENT_DYNAMIC(CHelp, CDialog)

CHelp::CHelp(CWnd* pParent /*=NULL*/)
	: CDialog(CHelp::IDD, pParent)
{

}

CHelp::~CHelp()
{
}

void CHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelp, CDialog)
END_MESSAGE_MAP()


// CHelp ��Ϣ�������
