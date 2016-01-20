// ZEncryptFile.cpp : ���� DLL Ӧ�ó���ĵ���������
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
							__in size_t passwordlen
							)
{
	return g_EncryptFile.ZCEncryptFile(filePath,PWriteFile,handlewrite,encryptType,password,passwordlen);
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