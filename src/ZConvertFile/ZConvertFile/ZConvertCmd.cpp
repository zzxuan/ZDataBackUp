#include "StdAfx.h"
#include "ZConvertCmd.h"
#include "../../common/include/ZEncryptFile.h"
#include "../../common/include/ZEncrypt.h"
#include "../../common/include/ZShareMem.h"

#include "ZConvertToFile.h"
#include "ZConvertToZip.h"

#pragma comment(lib,"../../common/lib/ZShareMem.lib")//共享内存

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

	if (nArgs == 3&& NULL != szArglist)
	{
		if (0==_tcscmp(szArglist[1],CONVERT_CMD_OPTION_ENCRPT_BYMEM))
		{
			LPTSTR memName = szArglist[2];
			ZDbgPrint(DBG_INFO,_T("ZDATABACK memName = %s"),memName);
			return TransferByMem(memName);
		}
		else
		{
			return ERROR_INVALID_PARAMETER;
		}
	}
	else if( szArglist == NULL || nArgs < 5)
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
	else if  (0==_tcscmp(szArglist[1],CONVERT_CMD_OPTION_ENCRPT_TOZIP))
	{
		optionType = CONVERT_OPTIONCODE_ENCRPT_TOZIP;
	}
	else if  (0==_tcscmp(szArglist[1],CONVERT_CMD_OPTION_DECRPT_FROMZIP))
	{
		optionType = CONVERT_OPTIONCODE_DECRPT_FROMZIP;
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

	return ConvertFileBase(dstPath,srcPath,optionType,encyptType,showProcDialog,passWord,passWorfLen,NULL,0,NULL);
}

HRESULT CZConvertCmd::ConvertFileBase(
									  __in LPCTSTR dstPath, 
									  __in LPCTSTR srcPath,
									  __in ULONG optionType, 
									  __in ULONG encyptType, 
									  __in BOOL showProcDialog, 
									  __in PVOID passWord, 
									  __in ULONG passWorfLen,
									  __in PVOID pextdata,
									  __in ULONG extlen,
									  __in PVOID reserve 
									  )
{
	switch(optionType)
	{
	case CONVERT_OPTIONCODE_ENCRPT_TOFILE:
		{
			CZConvertToFile ctofile;
			return ctofile.EncryptFileToFile(dstPath,srcPath,encyptType,showProcDialog,passWord,passWorfLen,pextdata,extlen,reserve);
		}
		break;
	case CONVERT_OPTIONCODE_DECRPT_FROMFILE:
		{
			CZConvertToFile ctofile;
			return ctofile.DecryptFileFromFile(dstPath,srcPath,showProcDialog,passWord,passWorfLen,reserve);
		}
		break;
	case CONVERT_OPTIONCODE_ENCRPT_TOZIP:
		{
			CZConvertToZip ctozip;
			return ctozip.EncryptFileToZip(dstPath,srcPath,encyptType,showProcDialog,passWord,passWorfLen,pextdata,extlen,reserve);
		}
		break;
	case CONVERT_OPTIONCODE_DECRPT_FROMZIP:
		{
			CZConvertToZip ctozip;
			return ctozip.DecryptFileFromFile(dstPath,srcPath,showProcDialog,passWord,passWorfLen,reserve);
		}
		break;
	default:
		break;
	}
	return ERROR_INVALID_PARAMETER;
}

HRESULT CZConvertCmd::TransferByMem(LPTSTR memName)
{
	CZShareMem *memshare = CreateZShareMem();
	HRESULT nstate = ERROR_SUCCESS;

	nstate = memshare->InitShareMemOpener(memName);
	if (ERROR_SUCCESS != nstate)
	{
		goto END;
	}
	WCHAR createName[MAX_PATH] = {NULL};
	wsprintf(createName,L"%s%s",memName,CONVERT_MEM_CREATENAME_EXT);
	memshare->InitShareMemCreator(createName);
	nstate = memshare->WriteMsgByOpener(0,memName,wcslen(memName)*sizeof(WCHAR));
	if (ERROR_SUCCESS != nstate)
	{
		goto END;
	}
	UINT msgType = 0;
	UCHAR buf[MEM_BUF_SIZE] = {NULL};
	UINT bufsize = MEM_BUF_SIZE;
	nstate = memshare->ReadMsgByCreator(msgType,buf,bufsize);
	if (ERROR_SUCCESS != nstate)
	{
		goto END;
	}

	switch(msgType)
	{
	case CONVERT_OPTIONCODE_GETINFO_FROMFILE:
		{
			CZConvertToFile ctofile;
			LPCTSTR srcPath = (LPCTSTR)buf;//传入路径
			ZFileinfo fileinfo = {NULL};
			nstate = ctofile.GetFileInfoInFile(&fileinfo.fileData,srcPath);
			if (ERROR_SUCCESS != nstate)
			{
				goto END;
			}
			nstate = ctofile.GetExternDataInFile(fileinfo.extendData,&fileinfo.extendLen,srcPath);
			if (ERROR_SUCCESS != nstate)
			{
				goto END;
			}
			nstate = memshare->WriteMsgByOpener(ERROR_SUCCESS,&fileinfo,sizeof(ZFileinfo));
			if (ERROR_SUCCESS != nstate)
			{
				goto END;
			}
		}
		break;
	case CONVERT_OPTIONCODE_GETINFO_FROMZIP:
		{
			CZConvertToZip ctozip;
			LPCTSTR srcPath = (LPCTSTR)buf;//传入路径
			ZFileinfo fileinfo = {NULL};
			nstate = ctozip.GetFileInfoInZip(&fileinfo.fileData,srcPath);
			if (ERROR_SUCCESS != nstate)
			{
				goto END;
			}
			nstate = ctozip.GetExternDataInZip(fileinfo.extendData,&fileinfo.extendLen,srcPath);
			if (ERROR_SUCCESS != nstate)
			{
				goto END;
			}
			nstate = memshare->WriteMsgByOpener(ERROR_SUCCESS,&fileinfo,sizeof(ZFileinfo));
			if (ERROR_SUCCESS != nstate)
			{
				goto END;
			}
		}
		break;
	case CONVERT_OPTIONCODE_GETLIST_FROMZIP:
		{
			CZConvertToZip ctozip;
			LPCTSTR srcPath =  (LPCTSTR)buf;//传入路径
			ZZipListInfo ziplistinfo = {NULL};

			nstate = ctozip.GetFileListInZip(ziplistinfo.listData,ziplistinfo.listcount
				,sizeof(ziplistinfo.listData),srcPath);
			if (ERROR_SUCCESS != nstate)
			{
				goto END;
			}
			nstate = memshare->WriteMsgByOpener(ERROR_SUCCESS,&ziplistinfo,sizeof(ziplistinfo));
			if (ERROR_SUCCESS != nstate)
			{
				goto END;
			}
		}
		break;
	default:
		{
			PZConvertData convdata = (PZConvertData)buf;
			nstate = ConvertFileBase(
				convdata->dstpath,
				convdata->srcpath,
				convdata->optionType,
				convdata->encyptType,
				convdata->showProcDialog,
				convdata->passWord,
				convdata->passWorfLen,
				convdata->extdata,
				convdata->extlen,
				convdata->reserve
				);
			if (ERROR_SUCCESS != nstate)
			{
				goto END;
			}
			nstate = memshare->WriteMsgByOpener(ERROR_SUCCESS,NULL,0);
			if (ERROR_SUCCESS != nstate)
			{
				goto END;
			}
		}
		break;
	}
END:
	if (ERROR_SUCCESS != nstate)
	{
		memshare->WriteMsgByOpener(nstate,NULL,0);
	}
	delete memshare;
	return nstate;
}



