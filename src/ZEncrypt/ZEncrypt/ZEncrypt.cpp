// ZEncrypt.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <stdio.h>
#include <map>
#include "ZEncrypt.h"

#include "EncryptBase.h"
#include "EncryptNULL.h"
#include "EncryptXOR.h"
#include "EncryptRC4.h"

#define ENCRYPTMAP std::map<ULONG,CEncryptBase*> 

ENCRYPTMAP g_EncryptMap;

HRESULT InitEncrypt()
{
	printf("InitEncrypt\n");
	g_EncryptMap[ENCRYPT_NULL] = new CEncryptNULL;
	g_EncryptMap[ENCRYPT_XOR] = new CEncryptXOR;
	g_EncryptMap[ENCRYPT_RC4] = new CEncryptRC4;


	return ERROR_SUCCESS;
}

HRESULT UnInitEncrypt()
{
	printf("UnInitEncrypt\n");

	ENCRYPTMAP::iterator it;
	for(it=g_EncryptMap.begin();it!=g_EncryptMap.end();it++)
	{
		delete it->second;
	}

	g_EncryptMap.clear();

	return ERROR_SUCCESS;
}

HRESULT WINAPI ZEncryptBuffer(
					   __in PVOID inputbuf,
					   __in size_t intputbuflen,
					   __out PVOID outputbuf,
					   __inout size_t* outputbuflen,
					   __in ULONG encrypttype,
					   __in PVOID password,
					   __in size_t passwordlen
					   )
{
	if (g_EncryptMap.find(encrypttype) != g_EncryptMap.end())
	{
		return g_EncryptMap[encrypttype]->EncryptBuffer(
			inputbuf,
			intputbuflen,
			outputbuf,
			outputbuflen,
			password,
			passwordlen
			);
	}

	return ERROR_INVALID_FUNCTION;
}

HRESULT WINAPI ZDecryptBuffer(
					   __in PVOID inputbuf,
					   __in size_t intputbuflen,
					   __inout PVOID outputbuf,
					   __out size_t* outputbuflen,
					   __in ULONG encrypttype,
					   __in PVOID password,
					   __in size_t passwordlen
					   )
{
	if (g_EncryptMap.find(encrypttype) != g_EncryptMap.end())
	{
		return g_EncryptMap[encrypttype]->DecryptBuffer(
			inputbuf,
			intputbuflen,
			outputbuf,
			outputbuflen,
			password,
			passwordlen
			);
	}

	return ERROR_INVALID_FUNCTION;
}