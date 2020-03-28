#include "stdafx.h"
#include "Mind.h"
#include "Resource.h"
#include "Text/TextFile.h"

#include "Ini/IniFile.h"
//初始增加两个数字，(建议同行或同列)
//新增的数字从1开始，默认从边框范围处
//根据上下左右顺序，先进行计算，再移动位置

DWORD m_AllNo[MAX_SIZE];
bool m_AllDisp[MAX_SIZE];
int m_AddOne[ADDONE_SIZE];
int m_AddTwo[ADDTWO_SIZE];

int m_LastAddPos = -1;
int m_LastDire = -1;

DWORD m_TotalNum;
DWORD m_TotalSteps;

char g_ProgPath[512];
bool m_bIsRec;

//CBitmapButton **m_Btn = NULL;
char *GetProcPath()
{
    return g_ProgPath;
}

bool SetColor(CBitmapButton *pCBB,DWORD dwBtnID)
{    
    if(pCBB->LoadBitmaps(dwBtnID,dwBtnID) == FALSE)
    {
        return false;
    }
    return true;
}
//------------------------------------------------//
bool GetDisp(int pos)
{
    return m_AllDisp[pos];
}
void SetDisp(int pos,bool bIsDisp)
{
    m_AllDisp[pos] = bIsDisp;
}
DWORD GetNo(int pos)
{
    return m_AllNo[pos];
}
void SetNo(int pos,DWORD dwNo)
{
    m_AllNo[pos] = dwNo;
}

void AddTotal(DWORD num)
{
    m_TotalNum += num;
}
DWORD GetTotal()
{
    return m_TotalNum;
}
void AddSteps(DWORD steps)
{
    m_TotalSteps += steps;
}
DWORD GetSteps()
{
    return m_TotalSteps;
}

void SetLastDire(int iDire)
{
    m_LastDire = iDire;
}
int GetLastDire()
{
    return m_LastDire;
}

bool CheckLastOper()
{
    for(int i=0;i<MAX_SIZE;i++)
    {
        if(!GetDisp(i))
            return true;
    }
    return false;
}

DWORD RandAddNo()
{
    //生成初始数字
    srand(GetTickCount());
    DWORD dwNo = 1;
#ifdef ALLOW_RANDADD
    dwNo <<= rand() % RANDADD_MAX + 1;
#endif

    return dwNo;
}

int Button_GetRecMax(DWORD *dwCurrStep)
{
    char filename[512];
    char itemval[MAX_PATH];
    sprintf(filename,"%s%s\0",GetProcPath(),RECORD_FILE);

    if(Ini_GetString(filename,"sys","step",itemval,sizeof(itemval)))
    {
        *dwCurrStep = atol(itemval);
    }
    else
    {
        *dwCurrStep = 0;
    }

    return 0;
}

int Button_DispRecord(DWORD dwCurrStep,int *iDire,DWORD *dwTotal)
{
    char filename[512];
    char secname[MAX_PATH];
    char itemval[MAX_PATH];

    sprintf_s(secname,"STEP%d\0",dwCurrStep);

    sprintf(filename,"%s%s\0",GetProcPath(),RECORD_FILE);

    if(Ini_GetString(filename,secname,"data",itemval,sizeof(itemval)))
    {
        char *pHead = NULL,*pTail = NULL;

        pHead = itemval;
        DWORD dwTmp = 0;

        for(int i=0;i<MAX_SIZE;i++)
        {
            pTail = strchr(pHead,',');
            if(pTail == NULL)
            {
                if(pHead != pTail)
                {
                    dwTmp = atol(pHead);
                    SetNo(i,dwTmp);
                    if(dwTmp > 0)
                        SetDisp(i,true);
                    else
                        SetDisp(i,false);

                    break;
                }
                else
                    return -1;
            }
            else//有','结束符
            {
                if(pHead != pTail)
                {
                    *(pTail) = 0x00;
                    dwTmp = atol(pHead);
                    SetNo(i,dwTmp);
                    if(dwTmp > 0)
                        SetDisp(i,true);
                    else
                        SetDisp(i,false);

                    *(pTail) = ',';
                    pHead = ++pTail;
                }
            }            
        }
    }
    else
    {
        return -1;
    }

    if(Ini_GetString(filename,secname,"dire",itemval,sizeof(itemval)))
    {
        *iDire = atoi(itemval);
    }
    else
    {
        return -1;
    }

    if(Ini_GetString(filename,secname,"total",itemval,sizeof(itemval)))
    {
        *dwTotal = atol(itemval);
    }
    else
    {
        return -1;
    }

    return 0;
}

int Button_WriteRecord(int iDire)
{
    char filename[MAX_PATH];
    char tmp[512];
    sprintf_s(tmp,"%d\0",m_TotalSteps);
    sprintf(filename,"%s%s\0",GetProcPath(),RECORD_FILE);
    //写入总步数
    Ini_SetString(filename,"sys","step",tmp);

    //改为操作文本
    //way two
    ZeroMemory(tmp,sizeof(tmp));
    sprintf_s(tmp,"[STEP%d]\ndire=%d\ntotal=%d\ndata=\0",GetSteps(),iDire,GetTotal());
    
    for(int i=0;i<MAX_SIZE;i++)
    {
        if(i<MAX_SIZE-1)
            sprintf(tmp+strlen(tmp),"%d,",GetNo(i));
        else
            sprintf(tmp+strlen(tmp),"%d",GetNo(i));
    }
    WriteText(filename,tmp);

    return 0;
}

//void NewCont()
//{
//    if(m_Btn == NULL)
//    {
//        m_Btn = (CBitmapButton **)GlobalAlloc(GPTR,sizeof(CBitmapButton *)*MAX_SIZE);
//        for(int i=0;i<MAX_SIZE;i++)
//        {
//            *(m_Btn+i) = new CBitmapButton();
//        }
//    }
//}
//void DelCont()
//{
//    if(m_Btn != NULL)
//    {        
//        for(int i=0;i<MAX_SIZE;i++)
//        {
//            delete[] *(m_Btn+i);
//            *(m_Btn+i) = NULL;
//        }
//        GlobalFree(m_Btn);
//        m_Btn = NULL;
//    }
//}

//------------------------------------------------//
void Button_SetProcPath()
{
    ZeroMemory(g_ProgPath,sizeof(g_ProgPath));

    TCHAR szModule[MAX_PATH];
    GetModuleFileName(NULL, szModule, MAX_PATH);//得到本程序自身的全路径

    char *pDest = strrchr(szModule,'\\');
    if(pDest != NULL)
    {
        *(pDest + 1) = 0x00;
        //设置全局路径
        memcpy(g_ProgPath,szModule,pDest - szModule +1);
    }
}

void Button_SetRecFlag(bool bRec)
{
    m_bIsRec = bRec;
}

bool Button_GetRecFlag()
{
    return m_bIsRec;
}

void Button_InitNo()
{
    /*DelCont();
    NewCont();*/

    if(Button_GetRecFlag())
    {
        char filename[512];
        sprintf(filename,"%s%s\0",GetProcPath(),RECORD_FILE);
        DeleteFile(filename);
    }

    m_LastAddPos = -1;//最后新增位置
    m_LastDire = -1;//最后操作方向
    m_TotalNum = 0;//分数
    m_TotalSteps = 0;//次数

    ZeroMemory(m_AllNo,sizeof(m_AllNo));
    ZeroMemory(m_AllDisp,sizeof(m_AllDisp));

    for(int i=0;i<MAX_SIZE;i++)
    {
        m_AllNo[i] = 0;
        m_AllDisp[i] = false;
    }

    int iPos1 = 0;
    int iPos2 = 0;
    ZeroMemory(m_AddOne,sizeof(m_AddOne));
    ZeroMemory(m_AddTwo,sizeof(m_AddTwo));
    for(int Bei=0;Bei<LINE_SIZE;Bei++)
    {
        for(int Offset=0;Offset<LINE_SIZE;Offset++)
        {
            if(Bei == 0 || Bei == LINE_SIZE-1 ||
                Offset == 0 || Offset == LINE_SIZE-1)
            {
                m_AddOne[iPos1] = Bei * LINE_SIZE + Offset;
                iPos1++;
            }
            else
            {
                m_AddTwo[iPos2] = Bei * LINE_SIZE + Offset;
                iPos2++;
            }
        }
    }  
}

int Button_StartNo()
{
    //生成初始数字
    srand(GetTickCount());
    int pos = -1;
    int num = 0;

    do
    {
        pos = rand() % MAX_SIZE;
        if(!GetDisp(pos))
        {
            SetNo(pos,RandAddNo());            
            SetDisp(pos,true);
            num++;
            m_LastAddPos = pos;
        }
    } 
    while (num<2);

    return 0;
}

bool Button_AddNo()
{
    srand(GetTickCount());
    int randno = rand() % MAX_SIZE;
    int iYu = randno % 2;

    if(iYu == 0)
    {
        for(int i=0;i<ADDONE_SIZE;i++)
        {
            if(!GetDisp(m_AddOne[i]))
            {
                SetNo(m_AddOne[i],RandAddNo());           
                SetDisp(m_AddOne[i],true);
                m_LastAddPos = m_AddOne[i];
                return true;
            }
        }
    }
    else
    {
        for(int i = ADDONE_SIZE-1;i > -1;i--)
        {
            if(!GetDisp(m_AddOne[i]))
            {
                SetNo(m_AddOne[i],RandAddNo());
                SetDisp(m_AddOne[i],true);
                m_LastAddPos = m_AddOne[i];
                return true;
            }
        }
    }
    
    if(iYu == 1)
    {
        for(int i=0;i<ADDTWO_SIZE;i++)
        {
            if(!GetDisp(m_AddTwo[i]))
            {
                SetNo(m_AddTwo[i],RandAddNo()); 
                SetDisp(m_AddTwo[i],true);
                m_LastAddPos = m_AddTwo[i];
                return true;
            }
        }
    }
    else
    {
        for(int i = ADDTWO_SIZE-1;i > -1;i--)
        {
            if(!GetDisp(m_AddTwo[i]))
            {
                SetNo(m_AddTwo[i],RandAddNo());
                SetDisp(m_AddTwo[i],true);
                m_LastAddPos = m_AddTwo[i];
                return true;
            }
        }
    }
  
    return false;//直接报错退出
}

int Button_CalcNo(int iDirect)
{
#ifdef NOT_DMOVE
    if(GetLastDire() == iDirect)
        return -1;
    else
        SetLastDire(iDirect);
#endif

    int FPos1 = -1;
    int FPos2 = -1;

    int iTmp1 = -1;
    int iTmp2 = -1;

    int InitPos = -1;

    AddSteps(1);
    switch(iDirect)
    {
    case DIRE_L2R://从左往右
        for(int Bei=0;Bei<LINE_SIZE;Bei++)
        {
            InitPos = LINE_SIZE-1;
            while(InitPos>0)
            {
                FPos1 = -1;
                FPos2 = -1;

                for(int Offset = InitPos;Offset>-1;Offset--)
                {
                    iTmp1 = Offset+(Bei * LINE_SIZE);
                    if(GetDisp(iTmp1))
                    {
                        FPos1 = Offset;//得到空位
                        break;
                    }
                }

                if(FPos1 > -1)
                {
                    for(int Offset=FPos1-1;Offset>-1;Offset--)
                    {
                        iTmp1 = Offset+(Bei * LINE_SIZE);
                        if(GetDisp(iTmp1))
                        {
                            FPos2 = Offset;//得到数据位
                            break;
                        }
                    }

                    if(FPos2 > -1)//数据全有效
                    {
                        iTmp1 = FPos1+(Bei * LINE_SIZE);
                        iTmp2 = FPos2+(Bei * LINE_SIZE);

                        if(GetNo(iTmp1) == GetNo(iTmp2))
                        {
                            AddTotal(GetNo(iTmp1)*2);

                            SetNo(iTmp1,GetNo(iTmp1)*2);
                            SetDisp(iTmp1,true);
                            SetNo(iTmp2,0);
                            SetDisp(iTmp2,false);
                        }

                        InitPos--;
                    }
                    else
                        break;
                }
                else
                {
                    break;
                }
            }
        }

        break;
    case DIRE_R2L://从右往左
        for(int Bei=0;Bei<LINE_SIZE;Bei++)
        {
            InitPos = 0;
            while(InitPos< LINE_SIZE-1)
            {
                FPos1 = -1;
                FPos2 = -1;

                for(int Offset=InitPos;Offset<LINE_SIZE;Offset++)
                {
                    iTmp1 = Offset+(Bei * LINE_SIZE);
                    if(GetDisp(iTmp1))
                    {
                        FPos1 = Offset;//得到空位
                        break;
                    }
                }

                if(FPos1 > -1)
                {
                    for(int Offset=FPos1+1;Offset<LINE_SIZE;Offset++)
                    {
                        iTmp1 = Offset+(Bei * LINE_SIZE);
                        if(GetDisp(iTmp1))
                        {
                            FPos2 = Offset;//得到数据位
                            break;
                        }
                    }

                    if(FPos2 > -1)//数据全有效
                    {
                        iTmp1 = FPos1+(Bei * LINE_SIZE);
                        iTmp2 = FPos2+(Bei * LINE_SIZE);

                        if(GetNo(iTmp1) == GetNo(iTmp2))
                        {
                            AddTotal(GetNo(iTmp1)*2);
                            SetNo(iTmp1,GetNo(iTmp1)*2);
                            SetDisp(iTmp1,true);
                            SetNo(iTmp2,0);
                            SetDisp(iTmp2,false);
                            
                        }
                        InitPos++;
                    }
                    else
                        break;
                }
                else
                {
                    break;
                }
            }
        }
        break;
    case DIRE_U2D://从上往下
        for(int Offset=0;Offset<LINE_SIZE;Offset++)
        {
            InitPos = LINE_SIZE-1;
            while(InitPos>0)
            {
                FPos1 = -1;
                FPos2 = -1;

                for(int Bei=InitPos;Bei>-1;Bei--)
                {
                    iTmp1 = Offset+Bei*LINE_SIZE;
                    if(GetDisp(iTmp1))
                    {
                        FPos1 = Bei;//得到空位
                        break;
                    }
                }

                if(FPos1 > -1)
                {
                    for(int Bei=FPos1-1;Bei>-1;Bei--)
                    {
                        iTmp1 = Offset+Bei*LINE_SIZE;
                        if(GetDisp(iTmp1))
                        {
                            FPos2 = Bei;//得到数据位
                            break;
                        }
                    }

                    if(FPos2 > -1)//数据全有效
                    {
                        iTmp1 = Offset+FPos1*LINE_SIZE;
                        iTmp2 = Offset+FPos2*LINE_SIZE;

                        if(GetNo(iTmp1) == GetNo(iTmp2))
                        {
                            AddTotal(GetNo(iTmp1)*2);
                            SetNo(iTmp1,GetNo(iTmp1)*2);
                            SetDisp(iTmp1,true);
                            SetNo(iTmp2,0);
                            SetDisp(iTmp2,false);

                        }
                        InitPos--;
                    }
                    else
                        break;
                }
                else
                {
                    break;
                }
            }
        }

        break;
    case DIRE_D2U://从下往上
        for(int Offset=0;Offset<LINE_SIZE;Offset++)
        {
            InitPos = 0;
            while(InitPos < LINE_SIZE-1)
            {
                FPos1 = -1;
                FPos2 = -1;

                for(int Bei=InitPos;Bei<LINE_SIZE;Bei++)
                {
                    iTmp1 = Offset+Bei*LINE_SIZE;
                    if(GetDisp(iTmp1))
                    {
                        FPos1 = Bei;//得到空位
                        break;
                    }
                }

                if(FPos1 > -1)
                {
                    for(int Bei=FPos1+1;Bei<LINE_SIZE;Bei++)
                    {
                        iTmp1 = Offset+Bei*LINE_SIZE;
                        if(GetDisp(iTmp1))
                        {
                            FPos2 = Bei;//得到数据位
                            break;
                        }
                    }

                    if(FPos2 > -1)//数据全有效
                    {
                        iTmp1 = Offset+FPos1*LINE_SIZE;
                        iTmp2 = Offset+FPos2*LINE_SIZE;

                        if(GetNo(iTmp1) == GetNo(iTmp2))
                        {
                            AddTotal(GetNo(iTmp1)*2);
                            SetNo(iTmp1,GetNo(iTmp1)*2);
                            SetDisp(iTmp1,true);
                            SetNo(iTmp2,0);
                            SetDisp(iTmp2,false);
                        }
                        InitPos++;
                    }
                    else
                        break;
                }
                else
                {
                    break;
                }
            }
        }
        break;
    default:
        return -1;
    }
    return 0;
}

int Button_MoveNo(int iDirect)
{
    int BSet = -1;
    int FSet = -1;

    int iTmp1 = -1;
    int iTmp2 = -1;

    switch(iDirect)
    {
    case DIRE_L2R://从左往右
        for(int Bei=0;Bei<LINE_SIZE;Bei++)
        {
            while(true)
            {
                BSet = -1;
                FSet = -1;
                for(int Offset=LINE_SIZE-1;Offset>-1;Offset--)
                {
                    iTmp1 = Offset+(Bei*LINE_SIZE);
                    if(!GetDisp(iTmp1))
                    {
                        BSet = Offset;//得到空位
                        break;
                    }
                }

                if(BSet > -1)
                {
                    for(int Offset=BSet-1;Offset>-1;Offset--)
                    {
                        iTmp1 = Offset+(Bei*LINE_SIZE);
                        if(GetDisp(iTmp1))
                        {
                            FSet = Offset;//得到数据位
                            break;
                        }
                    }

                    if(FSet > -1 && FSet < BSet)//数据全有效
                    {
                        iTmp1 = BSet+(Bei*LINE_SIZE);
                        iTmp2 = FSet+(Bei*LINE_SIZE);

                        //移动
                        SetNo(iTmp1,GetNo(iTmp2));
                        SetDisp(iTmp1,true);
                        SetNo(iTmp2,0);
                        SetDisp(iTmp2,false);
                    }
                    else
                        break;
                }
                else
                {
                    break;
                }
            }
        }

        break;
    case DIRE_R2L://从右往左
        for(int Bei=0;Bei<LINE_SIZE;Bei++)
        {
            while(true)
            {
                BSet = -1;
                FSet = -1;

                for(int Offset=0;Offset<LINE_SIZE;Offset++)
                {
                    iTmp1 = Offset+(Bei*LINE_SIZE);
                    if(!GetDisp(iTmp1))
                    {
                        BSet = Offset;//得到空位
                        break;
                    }
                }

                if(BSet > -1)
                {
                    for(int Offset=BSet+1;Offset<LINE_SIZE;Offset++)
                    {
                        iTmp1 = Offset+(Bei*LINE_SIZE);
                        if(GetDisp(iTmp1))
                        {
                            FSet = Offset;//得到数据位
                            break;
                        }
                    }

                    if(FSet > -1 && FSet > BSet)//数据全有效
                    {
                        iTmp1 = BSet+(Bei*LINE_SIZE);
                        iTmp2 = FSet+(Bei*LINE_SIZE);

                        //移动
                        SetNo(iTmp1,GetNo(iTmp2));
                        SetDisp(iTmp1,true);
                        SetNo(iTmp2,0);
                        SetDisp(iTmp2,false);
                    }
                    else
                        break;
                }
                else
                {
                    break;
                }
            }
        }
        break;
    case DIRE_U2D://从上往下
        for(int Offset=0;Offset<LINE_SIZE;Offset++)
        {
            while(true)
            {
                BSet = -1;
                FSet = -1;

                for(int Bei=LINE_SIZE-1;Bei>-1;Bei--)
                {
                    iTmp1 = Offset+Bei*LINE_SIZE;
                    if(!GetDisp(iTmp1))
                    {
                        BSet = Bei;//得到空位
                        break;
                    }
                }

                if(BSet > -1)
                {
                    for(int Bei=BSet-1;Bei>-1;Bei--)
                    {
                        iTmp1 = Offset+Bei*LINE_SIZE;
                        if(GetDisp(iTmp1))
                        {
                            FSet = Bei;//得到数据位
                            break;
                        }
                    }

                    if(FSet > -1 && FSet < BSet)//数据全有效
                    {
                        iTmp1 = Offset+BSet*LINE_SIZE;
                        iTmp2 = Offset+FSet*LINE_SIZE;

                        //移动
                        SetNo(iTmp1,GetNo(iTmp2));
                        SetDisp(iTmp1,true);
                        SetNo(iTmp2,0);
                        SetDisp(iTmp2,false);
                    }
                    else
                        break;
                }
                else
                {
                    break;
                }
            }
        }

        break;
    case DIRE_D2U://从下往上
        for(int Offset=0;Offset<LINE_SIZE;Offset++)
        {
            while(true)
            {
                BSet = -1;
                FSet = -1;
                for(int Bei=0;Bei<LINE_SIZE;Bei++)
                {
                    iTmp1 = Offset+Bei*LINE_SIZE;
                    if(!GetDisp(iTmp1))
                    {
                        BSet = Bei;//得到空位
                        break;
                    }
                }

                if(BSet > -1)
                {
                    for(int Bei=BSet+1;Bei<LINE_SIZE;Bei++)
                    {
                        iTmp1 = Offset+Bei*LINE_SIZE;
                        if(GetDisp(iTmp1))
                        {
                            FSet = Bei;//得到数据位
                            break;
                        }
                    }

                    if(FSet > -1 && FSet > BSet)//数据全有效
                    {
                        iTmp1 = Offset+BSet*LINE_SIZE;
                        iTmp2 = Offset+FSet*LINE_SIZE;

                        //移动
                        SetNo(iTmp1,GetNo(iTmp2));
                        SetDisp(iTmp1,true);
                        SetNo(iTmp2,0);
                        SetDisp(iTmp2,false);
                    }
                    else
                        break;
                }
                else
                {
                    break;
                }
            }
        }
        break;
    default:
        return -1;
    }
    return 0;
}

bool Button_Display(int pos,CBitmapButton *pCBB)
{
    if(GetDisp(pos))
    {
        pCBB->ShowWindow(TRUE);

        DWORD dwBtnID = 0;
        DWORD dwNum = GetNo(pos); 

        switch(dwNum)
        {
        case 1:
            dwBtnID = IDB_BMP_1;
            break;
        case 2:
            dwBtnID = IDB_BMP_2;
            break;
        case 4:
            dwBtnID = IDB_BMP_4;
            break;
        case 8:
            dwBtnID = IDB_BMP_8;
            break;
        case 16:
            dwBtnID = IDB_BMP_16;
            break;
        case 32:
            dwBtnID = IDB_BMP_32;
            break;
        case 64:
            dwBtnID = IDB_BMP_64;
            break;
        case 128:
            dwBtnID = IDB_BMP_128;
            break;
        case 256:
            dwBtnID = IDB_BMP_256;
            break;
        case 512:
            dwBtnID = IDB_BMP_512;
            break;
        case 1024:
            dwBtnID = IDB_BMP_1024;
            break;
        case 2048:
            dwBtnID = IDB_BMP_2048;
            break;
        case 4096:
            dwBtnID = IDB_BMP_4096;
            break;
        case 8192:
            dwBtnID = IDB_BMP_8192;
            break;
        case 16384:
            dwBtnID = IDB_BMP_16384;
            break;
        case 32768:
            dwBtnID = IDB_BMP_32768;
            break;
        default:
            dwBtnID = IDB_BMP_0;
            break;
        }   
        if(!SetColor(pCBB,dwBtnID))
            return false;
    }
    else
    {
        pCBB->ShowWindow(FALSE);
    }
    //----------------------------------------------------------------//
    return true;
}

DWORD Button_GetTotal()
{
    return GetTotal();
}
DWORD Button_GetSteps()
{
    return GetSteps();
}

int Button_GetLastAddPos()
{
    return m_LastAddPos;
}

int Button_ClearNo(DWORD dwNo)
{
#ifdef ALLOW_LASTOPER
    if(CheckLastOper())
        return -1;
#endif
    AddSteps(1);
    for(int i=0;i<MAX_SIZE;i++)
    {
        if(GetNo(i) <= dwNo)
        {
            SetNo(i,0);
            SetDisp(i,false);
        }
    }
#ifdef ALLOW_SUBTOT
    m_TotalNum -= SUB_TOT_CLEAR;
#endif
    return 0;
}
int Button_UpdateNo(int iLeftPos)
{
#ifdef ALLOW_LASTOPER
    if(CheckLastOper())
        return -1;
#endif
    AddSteps(1);
    DWORD dwTmp;
    for(int i=0;i<MAX_SIZE;i++)
    {
        dwTmp = GetNo(i);
        if(dwTmp == 1)
        {
            dwTmp <<= iLeftPos;
            SetNo(i,dwTmp);
        }
    }
#ifdef ALLOW_SUBTOT
    m_TotalNum -= SUB_TOT_UPDATE;
#endif
    return 0;
}

int Button_ChangeNo()
{
#ifdef ALLOW_LASTOPER
    if(CheckLastOper())
        return -1;
#endif
    AddSteps(1);
    //生成初始数字
    srand(GetTickCount());

    long rand1 = -1;
    long rand2 = -1;

    int iTimes = 5;

    DWORD dwNum = 0;
    bool bDisp = false;
    while(iTimes-- > 0)
    {
        rand1 = rand() % MAX_SIZE;
        rand2 = rand() % MAX_SIZE;

        if(rand1 != rand2)
        {
            dwNum = GetNo(rand2);
            bDisp = GetDisp(rand2);
            SetNo(rand2,GetNo(rand1));
            SetDisp(rand2,GetDisp(rand1));
            SetNo(rand1,dwNum);
            SetDisp(rand1,bDisp);
            iTimes++;
        }
    }
#ifdef ALLOW_SUBTOT
    m_TotalNum -= SUB_TOT_CHANGE;
#endif
    return 0;
}
//---------------------------------------------------------------------//
bool Button_Test(DWORD testdata[MAX_SIZE])
{
    for(int i=0;i<MAX_SIZE;i++)
    {
        SetNo(i,testdata[i]);
        if(testdata[i]>0)
            SetDisp(i,true);
        else
            SetDisp(i,false);
    }
    return true;
}