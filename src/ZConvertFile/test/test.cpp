// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <shlwapi.h>

#include "../../common/include/CommonDefine.h"
#include "../ZConvertDll/ZConvertDll.h"

#pragma comment(lib,"../../common/lib/ZConvertDll.lib")

int _tmain(int argc, _TCHAR* argv[])
{

	//ConvertFileFromZip(L"E:\\test2.txt",L"E:\\abcd.zip&test1.txt",1,"123",strlen("123"),NULL,0,NULL,0);
	std::vector<std::string> names;
	GetFileListInZip(L"E:\\abcd.zip",names);
	return 0;
}

