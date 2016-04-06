#ifndef __CONVEERTHELPER__H__
#define __CONVEERTHELPER__H__

#define DBG_ERROR 4
#define DBG_WARING 3
#define DBG_TRACE 2
#define DBG_INFO 1

VOID ShowLastErrMsg();

VOID ZDbgPrint(UINT level,TCHAR * szFormat, ...);



#endif