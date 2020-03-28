#include "stdafx.h"
#include "IniFile.h"

bool Ini_SetString(char *sFileName, char *sSection, char *sValueName, char *sValue)
{
    if(WritePrivateProfileString(sSection, sValueName, sValue, sFileName) == FALSE)
    {
        return false;
    }
    return true;
}

bool Ini_GetString(char *sFileName, char *sSection, char *sValueName, 
                    char *sResult, DWORD dwResSize)
{
	DWORD dwNum  = GetPrivateProfileString(sSection, sValueName, "", 
        sResult, dwResSize, sFileName);
	if(dwNum > 0)
	{
        return true;
	}
    else
    {        
        return false;
    }
}