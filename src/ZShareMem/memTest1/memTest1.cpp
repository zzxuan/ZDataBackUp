// memTest1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "../ZShareMem/ZShareMem.h"

#pragma comment(lib,"../Debug/ZShareMem.lib")

CZShareMem *shareMem;

int _tmain(int argc, _TCHAR* argv[])
{
	shareMem = CreateZShareMem();

	shareMem->InitShareMemCreator(L"memtest");
	for (int i=0;i<5;i++)
	{
		UINT msgType;
		CHAR buf[MAX_PATH] = {NULL};
		UINT bufsize = MAX_PATH;
		shareMem->ReadMsgByCreator(msgType,buf,bufsize);

		printf("%s\n",buf);
	}

	delete shareMem;
	return 0;
}

