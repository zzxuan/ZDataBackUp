// ZEncryptFile.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "ZEncryptFile.h"

HRESULT WINAPI ZEncryptFile(
							__in LPSTR filePath,
							__in PZEncryptFileWriteFile PWriteFile,
							__in PVOID handlewrite,
							__in UINT encryptType,
							__in PVOID password,
							__in size_t passwordlen
							)
{
	return ERROR_SUCCESS;
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