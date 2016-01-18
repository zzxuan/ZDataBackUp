// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

UCHAR guid[] = 
{
	0x79,0x67,0x35,0xa9,0x67,0x34
};

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

size_t DefaultEncrpt(PVOID bufin,PVOID bufout,size_t lenin)
{
	size_t len = lenin;
	ZEncryptBuffer(bufin,lenin,bufout,&len,ENCRYPT_RC4,guid,sizeof(guid));
	return len;
}

size_t DefaultDecrpt(PVOID bufin,PVOID bufout,size_t lenin)
{
	size_t len = lenin;
	ZDecryptBuffer(bufin,lenin,bufout,&len,ENCRYPT_RC4,guid,sizeof(guid));
	return len;
}
