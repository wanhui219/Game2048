#include "stdafx.h"
#include "TextFile.h"

bool WriteText(char *filename,char *data)
{
    FILE *fp;
    if((fp = fopen(filename,"at+")) != NULL)//����
    {
        fputs(data,fp);
        fclose(fp);
        return true;
    }
    else
        return false;
}