// ZEncryptFile.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "ZEncryptFile.h"

#include "ZCEncryptFile.h"
#include "ZCDecryptFile.h"

CEncryptFile g_EncryptFile;
CDecryptFile g_DecryptFile;

HRESULT WINAPI ZEncryptFile(
							__in LPSTR filePath,
							__in PZEncryptFileWriteFile PWriteFile,
							__in PVOID handlewrite,
							__in UINT encryptType,
							__in PVOID password,
							__in size_t passwordlen,
							__in PVOID extendData,
							__in size_t extendlen
							)
{
	return g_EncryptFile.ZCEncryptFile(
		filePath,PWriteFile,
		handlewrite,encryptType,password,passwordlen
		,extendData,extendlen);
}

HRESULT WINAPI ZDecryptFile(
							__in LPSTR filePath,
							__in PZEncryptFileReadFile PReadFile,
							__in PVOID handleread,
							//__in UINT encryptType,
							__in PVOID password,
							__in size_t passwordlen
							)
{
	return g_DecryptFile.ZCDecryptFile(filePath,PReadFile,handleread,password,passwordlen);
}

HRESULT WINAPI ZGetFileInfo(__out PWIN32_FIND_DATAA pfileData,
							__in PZEncryptFileReadFile PReadFile,
							__in PVOID handleread)
{
	return g_DecryptFile.ZCGetFileInfo(pfileData,PReadFile,handleread);
}

HRESULT WINAPI ZGetExternData(
							   __out PVOID pextendData,
							   __inout size_t *pextendLen,
							   __in PZEncryptFileReadFile PReadFile,
							   __in PVOID handleread
							   )
{
	return g_DecryptFile.ZCGetExternData(pextendData,pextendLen,PReadFile,handleread);
}