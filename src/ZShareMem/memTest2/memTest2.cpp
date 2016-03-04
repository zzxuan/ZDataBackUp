// memTest1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "../ZShareMem/ZShareMem.h"

#pragma comment(lib,"../Debug/ZShareMem.lib")

CZShareMem *shareMem;

int _tmain(int argc, _TCHAR* argv[])
{
	shareMem = CreateZShareMem();

	shareMem->InitShareMemOpener(L"memtest");
	for (int i=0;i<5;i++)
	{
		UINT msgType = i;
		CHAR buf[MAX_PATH] = "hello";
		UINT bufsize = MAX_PATH;
		shareMem->WriteMsgByOpener(msgType,buf,bufsize);

		printf("%s\n",buf);
		Sleep(1000);
	}

	delete shareMem;
	return 0;
}

