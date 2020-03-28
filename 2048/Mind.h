#include "stdafx.h"
//��ʼ�����������֣�(����ͬ�л�ͬ��)
//���������ִ�1��ʼ��Ĭ�ϴӱ߿�Χ��
//������������˳���Ƚ��м��㣬���ƶ�λ��
#define LINE_SIZE 4
#define MAX_SIZE (LINE_SIZE*LINE_SIZE)

//ÿ�����ӵ�λ��
#define ADDTWO_SIZE (LINE_SIZE-2)*(LINE_SIZE-2)
#define ADDONE_SIZE (MAX_SIZE-ADDTWO_SIZE)

#define DIRE_INIT   0
#define DIRE_L2R    1
#define DIRE_R2L    2
#define DIRE_U2D    3
#define DIRE_D2U    4
#define DIRE_CLEAR  10
#define DIRE_UPDATE 11
#define DIRE_CHANGE 12
#define DIRE_DMOVE  20  //����ظ��ƶ�

//#define ALLOW_RANDADD   //�����������
#define RANDADD_MAX 9

#define ALLOW_LASTOPER  //�Ƿ�ֻ�����һ������

#define ALLOW_CLEAR     //�Ƿ��������
#define ALLOW_UPDATE    //�Ƿ���������
#define ALLOW_CHANGE    //�Ƿ�����ı�λ��
//#define NOT_DMOVE     //�Ƿ����ظ�ͬ�����ƶ�

#define ALLOW_SUBTOT
#define SUB_TOT_CLEAR   100
#define SUB_TOT_UPDATE  100
#define SUB_TOT_CHANGE  50

#define RECORD_FILE "User.dat"

void Button_InitNo();
int Button_StartNo();
bool Button_AddNo();
int Button_CalcNo(int iDirect);
int Button_MoveNo(int iDirect);
bool Button_Display(int pos,CBitmapButton *cb);

DWORD Button_GetTotal();
DWORD Button_GetSteps();

int Button_UpdateNo(int iLeftPos);
int Button_ClearNo(DWORD dwNo);
int Button_GetLastAddPos();
int Button_ChangeNo();

int Button_DispRecord(DWORD dwCurrStep,int *iDire,DWORD *dwTotal);
int Button_WriteRecord(int iDire);

void Button_SetRecFlag(bool bRec);
bool Button_GetRecFlag();
int Button_GetRecMax(DWORD *dwCurrStep);

void Button_SetProcPath();

bool Button_Test(int testdata[MAX_SIZE]);