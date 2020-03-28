#ifndef _INI_FILE_H_
#define _INI_FILE_H_

bool Ini_GetString(char *sFileName, char *sSection, char *sValueName, 
                   char *sResult, DWORD dwResSize);
bool Ini_SetString(char *sFileName, char *sSection, char *sValueName, char *sValue);

#endif