// ZEncryptTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include "../ZEncrypt/ZEncrypt.h"

#pragma comment(lib,"../Debug/ZEncrypt.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	char cc[256] = "dasdasdafasf";
	char output[256] = {NULL};;
	UINT outsize = 256;

	ZEncryptBuffer(cc,sizeof(cc),output,&outsize,ENCRYPT_RC4,"sdasad",6);

	char decbuf[256] = {NULL};
	UINT decsize = 256;

	ZDecryptBuffer(output,outsize,decbuf,&decsize,ENCRYPT_RC4,"sdasad",6);

	return 0;
}

