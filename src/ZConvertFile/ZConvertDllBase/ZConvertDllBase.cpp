// ZConvertDllBase.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <vector>
#include "ZConvertToFile.h"
#include "ZConvertToZip.h"
#include "ZConvertDllBase.h"


HRESULT ZConvertFileBase(__in LPCWSTR dstPath, __in LPCWSTR srcPath, __in ULONG optionType, __in ULONG encyptType, __in BOOL showProcDialog, __in PVOID passWord, __in ULONG passWorfLen, __in PVOID pextdata, __in ULONG extlen, __in PVOID reserve, __in ULONG reservelen,
						   __in PConvertProgress pConvertPrg,PVOID handle)
{
	HRESULT state = ERROR_SUCCESS;
	switch(optionType)
	{
	case CONVERT_OPTIONCODE_ENCRPT_TOFILE:
		{
			CZConvertToFile ctofile;
			ctofile.m_PConvertPrg = pConvertPrg;
			ctofile.m_Handle = handle;
			state = ctofile.EncryptFileToFile(dstPath,srcPath,encyptType,showProcDialog,passWord,passWorfLen,pextdata,extlen,reserve);
		}
		break;
	case CONVERT_OPTIONCODE_DECRPT_FROMFILE:
		{
			CZConvertToFile ctofile;
			ctofile.m_PConvertPrg = pConvertPrg;
			ctofile.m_Handle = handle;
			state =  ctofile.DecryptFileFromFile(dstPath,srcPath,showProcDialog,passWord,passWorfLen,reserve);
		}
		break;
	case CONVERT_OPTIONCODE_ENCRPT_TOZIP:
		{
			CZConvertToZip ctozip;
			ctozip.m_PConvertPrg = pConvertPrg;
			ctozip.m_Handle = handle;
			state =  ctozip.EncryptFileToZip(dstPath,srcPath,encyptType,showProcDialog,passWord,passWorfLen,pextdata,extlen,reserve);
		}
		break;
	case CONVERT_OPTIONCODE_DECRPT_FROMZIP:
		{
			CZConvertToZip ctozip;
			ctozip.m_PConvertPrg = pConvertPrg;
			ctozip.m_Handle = handle;
			state =  ctozip.DecryptFileFromFile(dstPath,srcPath,showProcDialog,passWord,passWorfLen,reserve);
		}
		break;
	default:
		state = ERROR_INVALID_PARAMETER;
		break;
	}
	ZDbgPrint(DBG_INFO,_T("ZConvertFile: ConvertFileBase state = %d"),state);
	return state;
}

HRESULT ZGetFileInfoInFile(__in LPCWSTR srcPath,__out WIN32_FIND_DATAA &filedata,__out PVOID extdata,__inout UINT &extlen)
{
	HRESULT state = ERROR_SUCCESS;
	CZConvertToFile ctofile;
	state = ctofile.GetFileInfoInFile(&filedata,srcPath);
	if (ERROR_SUCCESS != state)
	{
		return state;
	}
	state = ctofile.GetExternDataInFile(extdata,&extlen,srcPath);
	if (ERROR_SUCCESS != state)
	{
		return state;
	}
	return state;
}

HRESULT ZGetFileInfoInZip(__in LPCWSTR srcPath,__out WIN32_FIND_DATAA &filedata,__out PVOID extdata,__inout UINT &extlen)
{
	HRESULT state = ERROR_SUCCESS;
	CZConvertToZip ctozip;
	state = ctozip.GetFileInfoInZip(&filedata,srcPath);
	if (ERROR_SUCCESS != state)
	{
		return state;
	}
	state = ctozip.GetExternDataInZip(extdata,&extlen,srcPath);
	if (ERROR_SUCCESS != state)
	{
		return state;
	}
	return state;
}

HRESULT ZGetFileListInZip(__in LPCWSTR srcPath,std::vector<std::string> &namelist)
{
	CZConvertToZip ctozip;
	ZZipListInfo ziplistinfo = {NULL};

	HRESULT state = ctozip.GetFileListInZip(ziplistinfo.listData,ziplistinfo.listcount
		,sizeof(ziplistinfo.listData),srcPath);

	if (ERROR_SUCCESS != state)
	{
		return state;
	}

	UINT index = 0;
	for (UINT i=0;i<ziplistinfo.listcount;i++)
	{
		PCHAR pstr = ziplistinfo.listData + index;
		namelist.push_back(pstr);
		index = strlen(pstr) + 1;
	}
	return state;
}

HRESULT ZConvertFileToFile(__in LPCWSTR dstPath, __in LPCWSTR srcPath, __in ULONG encyptType, __in BOOL showProcDialog, __in PVOID passWord, __in ULONG passWorfLen, __in PVOID pextdata, __in ULONG extlen, __in PVOID reserve, __in ULONG reservelen,__in PConvertProgress pConvertPrg,PVOID handle)
{
	return ZConvertFileBase(dstPath,srcPath,CONVERT_OPTIONCODE_ENCRPT_TOFILE,encyptType,showProcDialog,passWord,passWorfLen,pextdata,extlen,reserve,reservelen,pConvertPrg,handle);
}

HRESULT ZConvertFileToZip(__in LPCWSTR dstPath, __in LPCWSTR srcPath, __in ULONG encyptType, __in BOOL showProcDialog, __in PVOID passWord, __in ULONG passWorfLen, __in PVOID pextdata, __in ULONG extlen, __in PVOID reserve, __in ULONG reservelen,__in PConvertProgress pConvertPrg,PVOID handle)
{
	return ZConvertFileBase(dstPath,srcPath,CONVERT_OPTIONCODE_ENCRPT_TOZIP,encyptType,showProcDialog,passWord,passWorfLen,pextdata,extlen,reserve,reservelen,pConvertPrg,handle);
}

HRESULT ZConvertFileFromFile(__in LPCWSTR dstPath, __in LPCWSTR srcPath, __in BOOL showProcDialog, __in PVOID passWord, __in ULONG passWorfLen, __in PVOID pextdata, __in ULONG extlen, __in PVOID reserve, __in ULONG reservelen,__in PConvertProgress pConvertPrg,PVOID handle)
{
	return ZConvertFileBase(dstPath,srcPath,CONVERT_OPTIONCODE_DECRPT_FROMFILE,NULL,showProcDialog,passWord,passWorfLen,pextdata,extlen,reserve,reservelen,pConvertPrg,handle);
}

HRESULT ZConvertFileFromZip(__in LPCWSTR dstPath, __in LPCWSTR srcPath, __in BOOL showProcDialog, __in PVOID passWord, __in ULONG passWorfLen, __in PVOID pextdata, __in ULONG extlen, __in PVOID reserve, __in ULONG reservelen,__in PConvertProgress pConvertPrg,PVOID handle)
{
	return ZConvertFileBase(dstPath,srcPath,CONVERT_OPTIONCODE_DECRPT_FROMZIP,NULL,showProcDialog,passWord,passWorfLen,pextdata,extlen,reserve,reservelen,pConvertPrg,handle);
}

//HRESULT ZConvertDirToZip(__in LPCWSTR dstPath, __in LPCWSTR srcPath, __in ULONG encyptType, __in BOOL showProcDialog, __in PVOID passWord, __in ULONG passWorfLen, __in PVOID pextdata, __in ULONG extlen, __in PVOID reserve, __in ULONG reservelen,__in PConvertProgress pConvertPrg)
//{
//
//}