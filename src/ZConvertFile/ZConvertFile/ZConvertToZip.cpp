#include "StdAfx.h"
#include "ZConvertToZip.h"
#include <shlwapi.h>

#include "../../common/include/zip.h"
#include "../../common/include/ZEncryptFile.h"


#pragma comment(lib,"shlwapi.lib")
#pragma comment(lib,"../../common/lib/minizlib.lib")
#pragma comment(lib,"../../common/lib/ZEncryptFile.lib")


size_t WINAPI global_ZConvertZip_ReadFile(PVOID buf,UINT bufsize,PVOID handle)
{
	CZConvertToZip * pconvert = (CZConvertToZip *)handle;
	return pconvert->ZConvertReadFile(buf,bufsize);
}

size_t WINAPI global_ZConvertZip_WriteFile(PVOID buf,UINT bufsize,PVOID handle,DWORD totallen,DWORD readoffset)
{
	CZConvertToZip * pconvert = (CZConvertToZip *)handle;
	return pconvert->ZConvertWriteFilesize_t(buf,bufsize,totallen,readoffset);
}

CZConvertToZip::CZConvertToZip(void)
{
}

CZConvertToZip::~CZConvertToZip(void)
{
}

//dstPath zip Â·¾¶¸ñÊ½£ºc://sda/abc.zip|abc.txt
HRESULT CZConvertToZip::EncryptFileToZip(
	__in LPCTSTR dstPath, 
	__in LPCTSTR srcPath, 
	__in ULONG encyptType, 
	__in BOOL showProcDialog, 
	__in PVOID passWord, 
	__in ULONG passWorfLen, 
	__in PVOID reserve 
	)
{
	


	CHAR szAnsi[MAX_PATH] = {NULL};
	CHAR dstAnsi[MAX_PATH] = {NULL};

	if (0 == WideCharToMultiByte(CP_ACP, NULL, srcPath, wcslen(srcPath), szAnsi, sizeof(szAnsi), NULL, NULL)
		||0 == WideCharToMultiByte(CP_ACP, NULL, dstPath, wcslen(dstPath), dstAnsi, sizeof(dstAnsi), NULL, NULL))
	{
		if (showProcDialog)
		{
			ShowLastErrMsg();
		}
		return GetLastError();
	}

	PCHAR zipinfile = strchr(dstAnsi,'|');
	if (NULL != zipinfile)
	{
		(*zipinfile) = '\0';
		zipinfile += sizeof(CHAR);
	}
	else
	{
		zipinfile = PathFindFileNameA(szAnsi);
	}


	if (!PathFileExists(dstPath))
	{
		m_zipFileWrite = zipOpen(dstAnsi,APPEND_STATUS_CREATE);
	}
	else
	{
		m_zipFileWrite = zipOpen(dstAnsi,APPEND_STATUS_ADDINZIP);
	}

	if (NULL == m_zipFileWrite)
	{
		if (showProcDialog)
		{
			ShowLastErrMsg();
		}

		return GetLastError();
	}

	zipOpenNewFileInZip(
		m_zipFileWrite,
		zipinfile,NULL,
		NULL,NULL,NULL,NULL,NULL,NULL,Z_BEST_SPEED
		);

	HRESULT ulResult = ZEncryptFile(szAnsi,(PZEncryptFileWriteFile)global_ZConvertZip_WriteFile,this,encyptType,passWord,passWorfLen);
	zipCloseFileInZip(m_zipFileWrite);
	zipClose(m_zipFileWrite,NULL);
	m_zipFileWrite = NULL;

	if(ERROR_SUCCESS != ulResult)
	{
		if (showProcDialog)
		{
			ShowLastErrMsg();
		}
		return ulResult;
	}

	return ERROR_SUCCESS;
}

HRESULT CZConvertToZip::DecryptFileFromFile( __in LPCTSTR dstPath, __in LPCTSTR srcPath, __in BOOL showProcDialog, __in PVOID passWord, __in ULONG passWorfLen, __in PVOID reserve )
{
	return ERROR_SUCCESS;
}

size_t CZConvertToZip::ZConvertReadFile( PVOID buf,UINT bufsize )
{
	/*if (NULL == m_zipFileRead)
	{
		return 0;
	}

	return zipWriteInFileInZip(m_zipFileRead,buf,bufsize);*/
	return 0;
}

size_t CZConvertToZip::ZConvertWriteFilesize_t( PVOID buf,UINT bufsize,DWORD totallen,DWORD readoffset )
{
	if (NULL == m_zipFileWrite)
	{
		return 0;
	}

	int writeres = zipWriteInFileInZip(m_zipFileWrite,buf,bufsize);

	if (ERROR_SUCCESS == writeres)
	{
		return bufsize;
	}

	return 0;
}
