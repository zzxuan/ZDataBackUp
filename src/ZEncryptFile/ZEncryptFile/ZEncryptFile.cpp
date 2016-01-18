// ZEncryptFile.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "ZEncryptFile.h"

#include "EncryptFile.h"

CEncryptFile g_EncryptFile;

HRESULT WINAPI ZEncryptFile(
							__in LPSTR filePath,
							__in PZEncryptFileWriteFile PWriteFile,
							__in PVOID handlewrite,
							__in UINT encryptType,
							__in PVOID password,
							__in size_t passwordlen
							)
{
	return g_EncryptFile.EncryptFile(filePath,PWriteFile,handlewrite,encryptType,password,passwordlen);
}

HRESULT WINAPI ZDecryptFile(
							__in LPSTR filePath,
							__in PZEncryptFileReadFile PReadFile,
							__in PVOID handleread,
							__in UINT encryptType,
							__in PVOID password,
							__in size_t passwordlen
							)
{
	return ERROR_SUCCESS;
}