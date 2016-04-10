#include "stdafx.h"
#include "ConverHelper.h"
#include <Windows.h>

VOID ShowLastErrMsg()
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL
		);

	// Process any inserts in lpMsgBuf.
	// ...

	// Display the string.
	MessageBox(NULL,(LPCTSTR)lpMsgBuf, _T("Error"), MB_OK | MB_ICONINFORMATION );

	// Free the buffer.
	LocalFree( lpMsgBuf );
}

VOID ZDbgPrint(UINT level,TCHAR * szFormat, ...)
{
	TCHAR   szBuffer [1024] ;
	va_list pArgList ;

	// The va_start macro (defined in STDARG.H) is usually equivalent to:
	// pArgList = (char *) &szFormat + sizeof (szFormat) ;

	va_start (pArgList, szFormat) ;

	// The last argument to wvsprintf points to the arguments

	_vsntprintf (szBuffer, sizeof (szBuffer) / sizeof (TCHAR), 
		szFormat, pArgList) ;

	// The va_end macro just zeroes out pArgList for no good reason

	va_end (pArgList) ;

	return OutputDebugString ( szBuffer) ;
}


/****************************************************

* 注册文件关联
* strExe: 要检测的扩展名(例如: ".txt")
* strAppName: 要关联的应用程序名(例如: "C:/MyApp/MyApp.exe")
* strAppKey: ExeName扩展名在注册表中的键值(例如: "txtfile")
* strDefaultIcon: 扩展名为strAppName的图标文件(例如: *"C:/MyApp/MyApp.exe,0")
* strDescribe: 文件类型描述

****************************************************/

void RegisterFileRelation(char *strExt, char *strAppName, char *strAppKey, char *strDefaultIcon, char *strDescribe)
{
	char strTemp[MAX_PATH];
	HKEY hKey;

	RegCreateKeyA(HKEY_CLASSES_ROOT,strExt,&hKey);
	RegSetValueA(hKey,"",REG_SZ,strAppKey,strlen(strAppKey)+1);
	RegCloseKey(hKey);

	RegCreateKeyA(HKEY_CLASSES_ROOT,strAppKey,&hKey);
	RegSetValueA(hKey,"",REG_SZ,strDescribe,strlen(strDescribe)+1);
	RegCloseKey(hKey);

	
	RegCreateKeyA(HKEY_CLASSES_ROOT,strTemp,&hKey);
	RegSetValueA(hKey,"",REG_SZ,strDefaultIcon,strlen(strDefaultIcon)+1);
	RegCloseKey(hKey);

	
	RegCreateKeyA(HKEY_CLASSES_ROOT,strTemp,&hKey);
	RegSetValueA(hKey,"",REG_SZ,"Open",strlen("Open")+1);
	RegCloseKey(hKey);

	
	RegCreateKeyA(HKEY_CLASSES_ROOT,strTemp,&hKey);
	
	RegSetValueA(hKey,"",REG_SZ,strTemp,strlen(strTemp)+1);
	RegCloseKey(hKey);
}


/****************************************************
* 检测文件关联情况
* strExt: 要检测的扩展名(例如: ".txt")
* strAppKey: ExeName扩展名在注册表中的键值(例如: "txtfile")
* 返回TRUE: 表示已关联，FALSE: 表示未关联

******************************************************/

BOOL CheckFileRelation(const char *strExt, const char *strAppKey)
{
    int nRet=FALSE;
    HKEY hExtKey;
    char szPath[MAX_PATH]; 
    DWORD dwSize=sizeof(szPath); 
    if(RegOpenKeyA(HKEY_CLASSES_ROOT,strExt,&hExtKey)==ERROR_SUCCESS)
    {
        RegQueryValueExA(hExtKey,NULL,NULL,NULL,(LPBYTE)szPath,&dwSize);
        if(_stricmp(szPath,strAppKey)==0)
        {
            nRet=TRUE;
        }
        RegCloseKey(hExtKey);
        return nRet;
    }
    return nRet;
}