// 2048Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "2048.h"
#include "2048Dlg.h"
#include "Mind.h"
#include "Help.h"
#include "Cheat.h"

#include <process.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy2048Dlg �Ի���

CMy2048Dlg::CMy2048Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy2048Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy2048Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BTN_01, m_Btn_01);
    DDX_Control(pDX, IDC_BTN_02, m_Btn_02);
    DDX_Control(pDX, IDC_BTN_03, m_Btn_03);
    DDX_Control(pDX, IDC_BTN_04, m_Btn_04);
    DDX_Control(pDX, IDC_BTN_05, m_Btn_05);
    DDX_Control(pDX, IDC_BTN_06, m_Btn_06);
    DDX_Control(pDX, IDC_BTN_07, m_Btn_07);
    DDX_Control(pDX, IDC_BTN_08, m_Btn_08);
    DDX_Control(pDX, IDC_BTN_09, m_Btn_09);
    DDX_Control(pDX, IDC_BTN_10, m_Btn_10);
    DDX_Control(pDX, IDC_BTN_11, m_Btn_11);
    DDX_Control(pDX, IDC_BTN_12, m_Btn_12);
    DDX_Control(pDX, IDC_BTN_13, m_Btn_13);
    DDX_Control(pDX, IDC_BTN_14, m_Btn_14);
    DDX_Control(pDX, IDC_BTN_15, m_Btn_15);
    DDX_Control(pDX, IDC_BTN_16, m_Btn_16);
    DDX_Control(pDX, IDC_STA_TOTNUM, m_sta_totnum);
    DDX_Control(pDX, IDC_STA_TOTSTEP, m_sta_totsteps);
    DDX_Control(pDX, IDC_STA_DIRE, m_sta_dire);
}

BEGIN_MESSAGE_MAP(CMy2048Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP

    ON_COMMAND(ID_MENU_RESTART, &CMy2048Dlg::OnMenuRestart)
    ON_COMMAND(ID_MENU_EXIT, &CMy2048Dlg::OnMenuExit)
    ON_COMMAND(ID_MENU_RECORD, &CMy2048Dlg::OnMenuRecord)
    ON_COMMAND(ID_MENU_END, &CMy2048Dlg::OnMenuEnd)
    ON_COMMAND(ID_MENU_DISPLAY, &CMy2048Dlg::OnMenuDisplay)
    ON_COMMAND(ID_MENU_DISPEND, &CMy2048Dlg::OnMenuDispEnd)
    ON_COMMAND(ID_MENU_EXPLAIN, &CMy2048Dlg::OnMenuExplain)
    ON_COMMAND(ID_MENU_CHEAT, &CMy2048Dlg::OnMenuCheat)
END_MESSAGE_MAP()


// CMy2048Dlg ��Ϣ�������


BOOL CMy2048Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������   
    Button_SetProcPath();

    CMenu* cmenu = GetMenu();
    cmenu->EnableMenuItem(ID_MENU_END,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
    cmenu->EnableMenuItem(ID_MENU_DISPEND,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
    bLunchDisp = false;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ��������Ƹ�ͼ�ꡣ
// ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó����⽫�ɿ���Զ���ɡ�

void CMy2048Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy2048Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CMy2048Dlg::DispAll(int iDire,long lNo)
{    
    this->Invalidate(FALSE);    
    Button_Display(0,&m_Btn_01);
    Button_Display(1,&m_Btn_02);
    Button_Display(2,&m_Btn_03);
    Button_Display(3,&m_Btn_04);
    Button_Display(4,&m_Btn_05);
    Button_Display(5,&m_Btn_06);
    Button_Display(6,&m_Btn_07);
    Button_Display(7,&m_Btn_08);
    Button_Display(8,&m_Btn_09);
    Button_Display(9,&m_Btn_10);
    Button_Display(10,&m_Btn_11);
    Button_Display(11,&m_Btn_12);
    Button_Display(12,&m_Btn_13);
    Button_Display(13,&m_Btn_14);
    Button_Display(14,&m_Btn_15);
    Button_Display(15,&m_Btn_16);

    char tmp[MAX_PATH];
    sprintf_s(tmp,"�ܷ���: %d\0",Button_GetTotal());
    m_sta_totnum.SetWindowText(tmp);

    sprintf_s(tmp,"�ƶ�����: %d\0",Button_GetSteps());
    m_sta_totsteps.SetWindowText(tmp);

    switch(iDire)
    {
    case DIRE_DMOVE:
        sprintf_s(tmp,"�����ϴζ����ظ���\0");
        m_sta_dire.SetWindowText(tmp);
        break;
    case DIRE_CHANGE:
        if(lNo < 0)
            sprintf_s(tmp,"����λδ��������ֹ����λ�á�\0");
        else
            sprintf_s(tmp,"���������λ�á�\0");
        m_sta_dire.SetWindowText(tmp);
        break;
    case DIRE_UPDATE:
        if(lNo < 0)
            sprintf_s(tmp,"����λδ��������ֹ��������һ��\0");
        else
            sprintf_s(tmp,"������һ����Ϊ %d��\0",lNo);
        m_sta_dire.SetWindowText(tmp);
        break;
    case DIRE_CLEAR:
        if(lNo < 0)
            sprintf_s(tmp,"����λδ��������ֹ�����\0");
        else
            sprintf_s(tmp,"����� %d ���������֡�\0",lNo);
        m_sta_dire.SetWindowText(tmp);
        break;
    case DIRE_INIT:
        sprintf_s(tmp,"����:����ʼ������λ��:��%d��\0",Button_GetLastAddPos()+1);
        m_sta_dire.SetWindowText(tmp);
        break;
    case DIRE_R2L:
        sprintf_s(tmp,"����:���� ��������λ��:��%d��\0",Button_GetLastAddPos()+1);
        m_sta_dire.SetWindowText(tmp);
        break;
    case DIRE_L2R:
        sprintf_s(tmp,"����:���� ��������λ��:��%d��\0",Button_GetLastAddPos()+1);
        m_sta_dire.SetWindowText(tmp);
        break;
    case DIRE_D2U:
        sprintf_s(tmp,"����:���� ��������λ��:��%d��\0",Button_GetLastAddPos()+1);
        m_sta_dire.SetWindowText(tmp);
        break;
    case DIRE_U2D:
        sprintf_s(tmp,"����:���� ��������λ��:��%d��\0",Button_GetLastAddPos()+1);
        m_sta_dire.SetWindowText(tmp);
        break;
    default:
        break;
    }

    this->Invalidate(TRUE);
    return true;
}

BOOL CMy2048Dlg::PreTranslateMessage(MSG* pMsg)
{
    if(bLunchDisp)
        return FALSE;

    int KeyValue = -1;
    int iDire = -1;
    long lNo = -1;

    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if(pMsg->message == WM_KEYUP)
    {
        KeyValue = pMsg->wParam;
        switch(KeyValue)
        {
#ifdef ALLOW_CLEAR
        case VK_F2:
            lNo = 1;
            iDire = DIRE_CLEAR;
            if(Button_ClearNo(lNo) < 0)
            {
                DispAll(iDire,-1);
                return FALSE;
            }
            else
            {
                DispAll(iDire,lNo);
            }
            break;
        case VK_F3:
            lNo = 2;
            iDire = DIRE_CLEAR;
            if(Button_ClearNo(lNo) < 0)
            {
                DispAll(iDire,-1);
                return FALSE;
            }
            else
            {
                DispAll(iDire,lNo);
            }
            break;
#endif
#ifdef ALLOW_CHANGE
        case VK_F4:
            iDire = DIRE_CHANGE;
            if(Button_ChangeNo() < 0)
            {
                DispAll(iDire,-1);
                return FALSE;
            }
            else
            {
                DispAll(iDire,0);
            }
            break;
#endif
#ifdef ALLOW_UPDATE
        case VK_F5:
            lNo = 2;
            iDire = DIRE_UPDATE;
            if(Button_UpdateNo(1) < 0)
            {
                DispAll(iDire,-1);
                return FALSE;
            }
            else
            {
                DispAll(iDire,lNo);
            }
            break;
        case VK_F6:
            lNo = 4;
            iDire = DIRE_UPDATE;
            if(Button_UpdateNo(8) < 0)//2-8
            {
                DispAll(iDire,-1);
                return FALSE;
            }
            else
            {
                DispAll(iDire,lNo);
            }
            break;
#endif
        case VK_LEFT:
            iDire = DIRE_R2L;
            if(Button_CalcNo(iDire) == 0)
            {
                Button_MoveNo(iDire);
            }
            else
            {
                DispAll(DIRE_DMOVE,-1);
                return FALSE;
            }
            break;
        case VK_RIGHT:
            iDire = DIRE_L2R;
            if(Button_CalcNo(iDire) == 0)
            {
                Button_MoveNo(iDire);
            }
            else
            {
                DispAll(DIRE_DMOVE,-1);
                return FALSE;
            }
            break;
        case VK_UP:
            iDire = DIRE_D2U;
            if(Button_CalcNo(iDire) == 0)
            {
                Button_MoveNo(iDire);
            }
            else
            {
                DispAll(DIRE_DMOVE,-1);
                return FALSE;
            }            
            break;
        case VK_DOWN:
            iDire = DIRE_U2D;
            if(Button_CalcNo(iDire) == 0)
            {
                Button_MoveNo(iDire);
            }
            else
            {
                DispAll(DIRE_DMOVE,-1);
                return FALSE;
            }
            break;
        default:
            return FALSE;
        }        
        
        if(iDire >= DIRE_L2R && iDire <= DIRE_D2U)
        {
            if(!Button_AddNo())
            {
                int iSel = this->MessageBox("��ǰ�����޷��ϲ�����! �Ƿ����¿�ʼ?","ʧ��",MB_YESNO);
                if(iSel == IDYES)
                {
                    Button_InitNo();
                    Button_StartNo();
                    iDire = DIRE_INIT;
                    lNo = -1;
                }                
            }
            DispAll(iDire,lNo);            
        }
        
        if(Button_GetRecFlag())
            Button_WriteRecord(iDire);        
    }

    //return CDialog::PreTranslateMessage(pMsg);
    return FALSE;
}

void CMy2048Dlg::OnMenuRestart()
{
    Button_InitNo();
    Button_StartNo();
    DispAll(DIRE_INIT,-1);

    if(Button_GetRecFlag())
        Button_WriteRecord(DIRE_INIT);

    CMenu* cmenu = GetMenu();
    cmenu->EnableMenuItem(ID_MENU_RECORD,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED); 
    cmenu->EnableMenuItem(ID_MENU_DISPLAY,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
    cmenu->EnableMenuItem(ID_MENU_RESTART,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
    cmenu->EnableMenuItem(ID_MENU_END,MF_BYCOMMAND | MF_ENABLED);
}

void CMy2048Dlg::OnMenuExit()
{
    this->OnOK();
}

void CMy2048Dlg::OnMenuRecord()
{
    // TODO: �ڴ���������������
    CMenu* cmenu = GetMenu();
    if (MF_CHECKED == cmenu->GetMenuState(ID_MENU_RECORD,MF_BYCOMMAND))
    {
        cmenu->CheckMenuItem(ID_MENU_RECORD,MF_UNCHECKED);
        Button_SetRecFlag(false);
    }
    else
    {       
        char strHint[512];
        sprintf(strHint,"��ѡ����¼���衿���ܣ�ԭ������ %s ����������Ƿ����?\0",RECORD_FILE);

        int iSel = this->MessageBox(strHint,"��ʾ",MB_YESNO);
        if(iSel == IDNO)
        {
            return;
        }

        cmenu->CheckMenuItem(ID_MENU_RECORD,MF_CHECKED);
        Button_SetRecFlag(true);
    }
}

void CMy2048Dlg::OnMenuEnd()
{
    CMenu* cmenu = GetMenu();
    cmenu->EnableMenuItem(ID_MENU_RECORD,MF_BYCOMMAND | MF_ENABLED); 
    cmenu->EnableMenuItem(ID_MENU_DISPLAY,MF_BYCOMMAND | MF_ENABLED);
    cmenu->EnableMenuItem(ID_MENU_RESTART,MF_BYCOMMAND | MF_ENABLED);
    cmenu->EnableMenuItem(ID_MENU_END,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
    Button_SetRecFlag(false);    
}




UINT WINAPI ThdDisp(LPVOID lpParam)
{
    CMy2048Dlg *my2048 = (CMy2048Dlg*)lpParam;

    CMenu* cmenu = my2048->GetMenu();
    cmenu->EnableMenuItem(ID_MENU_RECORD,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED); 
    cmenu->EnableMenuItem(ID_MENU_DISPLAY,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED); 
    cmenu->EnableMenuItem(ID_MENU_RESTART,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
    cmenu->EnableMenuItem(ID_MENU_END,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
    cmenu->EnableMenuItem(ID_MENU_DISPEND,MF_BYCOMMAND | MF_ENABLED);

    my2048->bLunchDisp = true;

    DWORD dwStep;
    DWORD dwTotal;
    int iDire;
    
    //�õ��ļ���
    Button_GetRecMax(&dwStep); //�õ��ļ���    

    char sTotal[MAX_PATH];
    char sStep[MAX_PATH];
    char sDire[MAX_PATH];
    for(DWORD i = 0;i <= dwStep;i++)
    {
        if(my2048->bLunchDisp && Button_DispRecord(i,&iDire,&dwTotal) == 0)
        {
            my2048->Invalidate(FALSE);            

            ZeroMemory(sTotal,sizeof(sTotal));
            sprintf_s(sTotal,"�ܷ���: %d\0",dwTotal);
            my2048->m_sta_totnum.SetWindowText(sTotal);

            ZeroMemory(sStep,sizeof(sStep));
            sprintf_s(sStep,"��ǰ����: %d/%d(�ܲ���)\0",i,dwStep);
            my2048->m_sta_totsteps.SetWindowText(sStep);

            ZeroMemory(sDire,sizeof(sDire));
            switch(iDire)
            {  
            case DIRE_DMOVE:
                sprintf_s(sDire,"�����ϴζ����ظ���\0");
                my2048->m_sta_dire.SetWindowText(sDire);
                break;
            case DIRE_CHANGE:
                sprintf_s(sDire,"���������λ�á�\0");
                my2048->m_sta_dire.SetWindowText(sDire);
                break;
            case DIRE_UPDATE:
                sprintf_s(sDire,"������һ������\0");
                my2048->m_sta_dire.SetWindowText(sDire);
                break;
            case DIRE_CLEAR:
                sprintf_s(sDire,"��������֡�\0");
                my2048->m_sta_dire.SetWindowText(sDire);
                break;
            case DIRE_INIT:
                sprintf_s(sDire,"����:����ʼ��\0");
                my2048->m_sta_dire.SetWindowText(sDire);
                break;
            case DIRE_R2L:
                sprintf_s(sDire,"����:���� ����\0");
                my2048->m_sta_dire.SetWindowText(sDire);
                break;
            case DIRE_L2R:
                sprintf_s(sDire,"����:���� ����\0");
                my2048->m_sta_dire.SetWindowText(sDire);
                break;
            case DIRE_D2U:
                sprintf_s(sDire,"����:���� ����\0");
                my2048->m_sta_dire.SetWindowText(sDire);
                break;
            case DIRE_U2D:
                sprintf_s(sDire,"����:���� ����\0");
                my2048->m_sta_dire.SetWindowText(sDire);
                break;
            default:
                break;
            }
            if(!Button_Display(0,&my2048->m_Btn_01) ||
               !Button_Display(1,&my2048->m_Btn_02) ||
               !Button_Display(2,&my2048->m_Btn_03) ||
               !Button_Display(3,&my2048->m_Btn_04) ||
               !Button_Display(4,&my2048->m_Btn_05) ||
               !Button_Display(5,&my2048->m_Btn_06) ||
               !Button_Display(6,&my2048->m_Btn_07) ||
               !Button_Display(7,&my2048->m_Btn_08) ||
               !Button_Display(8,&my2048->m_Btn_09) ||
               !Button_Display(9,&my2048->m_Btn_10) ||
               !Button_Display(10,&my2048->m_Btn_11)||
               !Button_Display(11,&my2048->m_Btn_12)||
               !Button_Display(12,&my2048->m_Btn_13)||
               !Button_Display(13,&my2048->m_Btn_14)||
               !Button_Display(14,&my2048->m_Btn_15)||
               !Button_Display(15,&my2048->m_Btn_16))
            {
                my2048->MessageBox("ͼƬ��ʾʧ��","�쳣",MB_OK);
                break;
            } 
           
            my2048->Invalidate(TRUE);
            ::Sleep(500);
        }
        else
        {
            break;
        }
    }

    //CMenu* cmenu = my2048->GetMenu();
    cmenu->EnableMenuItem(ID_MENU_RECORD,MF_BYCOMMAND | MF_ENABLED); 
    cmenu->EnableMenuItem(ID_MENU_DISPLAY,MF_BYCOMMAND | MF_ENABLED); 
    cmenu->EnableMenuItem(ID_MENU_RESTART,MF_BYCOMMAND | MF_ENABLED);
    cmenu->EnableMenuItem(ID_MENU_END,MF_BYCOMMAND | MF_ENABLED);
    cmenu->EnableMenuItem(ID_MENU_DISPEND,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED); 
    my2048->bLunchDisp = false;
    return 2;
}

void CMy2048Dlg::OnMenuDisplay()
{
    HANDLE hSerThd = (HANDLE)_beginthreadex(NULL,0,ThdDisp,this,
        0,NULL);
    if(hSerThd == NULL)
    {
        this->MessageBox("��ʾ��¼ʧ��","�쳣",MB_OK);
    }
}

void CMy2048Dlg::OnMenuDispEnd()
{
    bLunchDisp = false;
}

void CMy2048Dlg::OnMenuExplain()
{
    // TODO: �ڴ���������������
    CHelp chelp = new CHelp();
    chelp.DoModal();
}

void CMy2048Dlg::OnMenuCheat()
{
    CCheat ccheat = new CCheat();
    ccheat.DoModal();
}
