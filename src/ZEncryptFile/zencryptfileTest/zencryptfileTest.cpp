// zencryptfileTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include "../ZEncryptFile/ZEncryptFile.h"
#include "../../common/include/ZEncrypt.h"
#include "../../common/include/zlib.h"

#pragma comment(lib,"../Debug/ZEncryptFile.lib");
#pragma comment(lib,"../../common/lib/minizlib.lib")

size_t WINAPI WriteFile(PVOID buf,UINT bufsize,PVOID handle)
{
	return fwrite(buf,bufsize,1,(FILE *)handle);
}

size_t WINAPI ReadFile(PVOID buf,UINT bufsize,PVOID handle)
{
	return fread(buf,sizeof(UCHAR),bufsize,(FILE *)handle);
}

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD tick = GetTickCount();
	FILE *file = fopen("ttt.txt","wb");
	if (NULL != file)
	{
		ZEncryptFile(
			"test.txt",
			(PZEncryptFileWriteFile)WriteFile,file,
			ENCRYPT_RC4,"123",3,
			"123456",7);
		fclose(file);
	}

	printf("加密文件 共花费 %d\n",GetTickCount() - tick);
	tick = GetTickCount();

	FILE *defile = fopen("ttt.txt","rb");
	if (NULL != defile)
	{
		ZDecryptFile("aaa.txt",(PZEncryptFileReadFile)ReadFile,
			defile,"123",3);
		fclose(defile);
	}
	printf("解密文件 共花费 %d\n",GetTickCount() - tick);
	defile = fopen("ttt.txt","rb");
	if (NULL != defile)
	{
		WIN32_FIND_DATAA filedata = {NULL};
		ZGetFileInfo(&filedata,(PZEncryptFileReadFile)ReadFile,defile);
		fclose(defile);
	}

	defile = fopen("ttt.txt","rb");
	if (NULL != defile)
	{
		char exdata[1024] = {NULL};
		size_t exlen = 1024;
		ZGetExternData(exdata,&exlen,(PZEncryptFileReadFile)ReadFile,defile);
		fclose(defile);
	}

	system("pause");
	return 0;
}

