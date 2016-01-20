// zencryptfileTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include "../ZEncryptFile/ZEncryptFile.h"
#include "../../common/include/ZEncrypt.h"

#pragma comment(lib,"../Debug/ZEncryptFile.lib");

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
	FILE *file = fopen("ttt.txt","wb");
	if (NULL != file)
	{
		ZEncryptFile(
			"test.txt",(PZEncryptFileWriteFile)WriteFile,file,ENCRYPT_RC4,"123",3);
		fclose(file);
	}


	FILE *defile = fopen("ttt.txt","rb");
	if (NULL != defile)
	{
		ZDecryptFile("aaa.txt",(PZEncryptFileReadFile)ReadFile,
			defile,"123",3);
		fclose(file);
	}

	return 0;
}

