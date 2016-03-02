// memTest1.cpp : 定义控制台应用程序的入口点。
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
		shareMem->WriteMsg(msgType,buf,bufsize);

		printf("%s\n",buf);
		Sleep(1000);
	}

	delete shareMem;
	return 0;
}

