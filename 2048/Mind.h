#include "stdafx.h"
//初始增加两个数字，(建议同行或同列)
//新增的数字从1开始，默认从边框范围处
//根据上下左右顺序，先进行计算，再移动位置
#define LINE_SIZE 4
#define MAX_SIZE (LINE_SIZE*LINE_SIZE)

//每次增加的位置
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
#define DIRE_DMOVE  20  //多次重复移动

//#define ALLOW_RANDADD   //随机新增数字
#define RANDADD_MAX 9

#define ALLOW_LASTOPER  //是否只能最后一步操作

#define ALLOW_CLEAR     //是否允许清除
#define ALLOW_UPDATE    //是否允许升级
#define ALLOW_CHANGE    //是否允许改变位置
//#define NOT_DMOVE     //是否检查重复同方向移动

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