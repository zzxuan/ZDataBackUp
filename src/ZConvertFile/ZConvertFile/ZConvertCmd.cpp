#include "StdAfx.h"
#include "ZConvertCmd.h"
#include "../../common/include/ZEncryptFile.h"
#include "../../common/include/ZEncrypt.h"

#include "ZConvertToFile.h"

CZConvertCmd::CZConvertCmd(void)
{
}

CZConvertCmd::~CZConvertCmd(void)
{
}

// xxx.exe -enc dst.path src.path xxxxx 1 rc4 0  
HRESULT CZConvertCmd::TransferCmdLine()
{
	LPWSTR *szArglist;
	int nArgs;

	szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	if( NULL == nArgs || nArgs < 5)
	{
		return ERROR_INVALID_PARAMETER;
	}

	TCHAR dstPath[MAX_PATH] = {NULL};
	TCHAR srcPath[MAX_PATH] = {NULL};
	ULONG optionType = 0;
	ULONG encyptType = ENCRYPT_RC4;
	BOOL showProcDialog = FALSE;
	UCHAR passWord[MAX_PATH];
	ULONG passWorfLen = 0;

	if (0==_tcscmp(szArglist[1],CONVERT_CMD_OPTION_ENCRPT_TOFILE))
	{
		optionType = CONVERT_OPTIONCODE_ENCRPT_TOFILE;
	}
	else if  (0==_tcscmp(szArglist[1],CONVERT_CMD_OPTION_DECRPT_FROMFILE))
	{
		optionType = CONVERT_OPTIONCODE_DECRPT_FROMFILE;
	}

	_tcscpy_s(dstPath,_countof(dstPath),szArglist[2]);
	_tcscpy_s(srcPath,_countof(srcPath),szArglist[3]);

	memcpy(passWord,szArglist[4],_tcslen(szArglist[4]) * sizeof(TCHAR));
	passWorfLen = _tcslen(szArglist[4]) * sizeof(TCHAR);

	if (nArgs > 5)
	{
		if (0==_tcscmp(szArglist[5],CONVERT_CMD_SHOWPROCDIALOG))
		{
			showProcDialog = TRUE;
		}
		else if (0==_tcscmp(szArglist[5],CONVERT_CMD_NOTSHOWPROCDIALOG))
		{
			showProcDialog = FALSE;
		}
	}

	if (nArgs > 6)
	{
		if (0==_tcscmp(szArglist[6],CONVERT_CMD_ENCRPTTYPE_RC4))
		{
			encyptType = ENCRYPT_RC4;
		}
	}
	ZDbgPrint(DBG_INFO,_T("ZDATABACK srcpath = %s"),srcPath);

	return ConvertFileBase(dstPath,srcPath,optionType,encyptType,showProcDialog,passWord,passWorfLen,NULL);
}

HRESULT CZConvertCmd::ConvertFileBase( __in LPCTSTR dstPath, __in LPCTSTR srcPath, __in ULONG optionType, __in ULONG encyptType, __in BOOL showProcDialog, __in PVOID passWord, __in ULONG passWorfLen, __in PVOID reserve )
{
	switch(optionType)
	{
	case CONVERT_OPTIONCODE_ENCRPT_TOFILE:
		{
			return EncryptFileToFile(dstPath,srcPath,encyptType,showProcDialog,passWord,passWorfLen,reserve);
		}
		break;
	case CONVERT_OPTIONCODE_DECRPT_FROMFILE:
		{
			return DecryptFileFromFile(dstPath,srcPath,showProcDialog,passWord,passWorfLen,reserve);
		}
		break;
	}
	return ERROR_SUCCESS;
}

HRESULT CZConvertCmd::EncryptFileToFile( __in LPCTSTR dstPath, __in LPCTSTR srcPath, __in ULONG encyptType, __in BOOL showProcDialog, __in PVOID passWord, __in ULONG passWorfLen, __in PVOID reserve )
{
	CZConvertToFile ctofile;
	return ctofile.EncryptFileToFile(dstPath,srcPath,encyptType,showProcDialog,passWord,passWorfLen,reserve);
}

HRESULT CZConvertCmd::DecryptFileFromFile( __in LPCTSTR dstPath, __in LPCTSTR srcPath, __in BOOL showProcDialog, __in PVOID passWord, __in ULONG passWorfLen, __in PVOID reserve )
{
	CZConvertToFile ctofile;
	return ctofile.DecryptFileFromFile(dstPath,srcPath,showProcDialog,passWord,passWorfLen,reserve);
}
