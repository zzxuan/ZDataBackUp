// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>
#include <shlwapi.h>

#include "../../common/include/zip.h"
#include "../../common/include/ZEncryptFile.h"


#pragma comment(lib,"shlwapi.lib")
#pragma comment(lib,"../../common/lib/minizlib.lib")
#pragma comment(lib,"../../common/lib/ZEncryptFile.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	zipFile zipfile = zipOpen("��˳��ccc.zip",FALSE);

	if (NULL == zipfile)
	{
		return 0;
	}
	zip_fileinfo zipfileInfo;
	zipOpenNewFileInZip4_64 (zipfile,"����������.txt",NULL
		,NULL,NULL,NULL,NULL,NULL,NULL,Z_BEST_SPEED, 0,
		-MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
		"123456", 0, NULL, 0, 0);
	/*zipOpenNewFileInZip(zipfile,"����������11.txt",NULL
		,NULL,NULL,NULL,NULL,NULL,NULL,Z_BEST_SPEED);*/

	char cc[] = "sdadasdasdasdsadsadsdsdasds������������������";
	zipWriteInFileInZip(zipfile,cc,sizeof(cc));

	zipCloseFileInZip(zipfile);

	zipClose(zipfile,NULL);

	fwrite("saf",2,1,NULL);
	return 0;
}

