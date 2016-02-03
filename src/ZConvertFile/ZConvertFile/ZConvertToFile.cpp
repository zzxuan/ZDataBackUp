#include "StdAfx.h"
#include "ZConvertToFile.h"
#include "../../common/include/ZEncryptFile.h"

#pragma comment(lib,"../../common/lib/ZEncryptFile.lib")

size_t WINAPI global_ZConvertFile_FileReadFile(PVOID buf,UINT bufsize,PVOID handle)
{
	CZConvertToFile * pconvert = (CZConvertToFile *)handle;
	return pconvert->ZConvertReadFile(buf,bufsize);
}

size_t WINAPI global_ZConvertFile_WriteFile(PVOID buf,UINT bufsize,PVOID handle,DWORD totallen,DWORD readoffset)
{
	CZConvertToFile * pconvert = (CZConvertToFile *)handle;
	return pconvert->ZConvertWriteFilesize_t(buf,bufsize,totallen,readoffset);
}

CZConvertToFile::CZConvertToFile(void)
{
}

CZConvertToFile::~CZConvertToFile(void)
{
}

HRESULT CZConvertToFile::EncryptFileToFile(
	__in LPCTSTR dstPath, 
	__in LPCTSTR srcPath, 
	__in ULONG encyptType, 
	__in BOOL showProcDialog, 
	__in PVOID passWord, 
	__in ULONG passWorfLen, 
	__in PVOID reserve 
	)
{
	m_pDstFile = _wfopen(dstPath,L"wb");
	if (NULL == m_pDstFile)
	{
		if (showProcDialog)
		{
			ShowLastErrMsg();
		}
		
		return GetLastError();
	}
	
	CHAR szAnsi[MAX_PATH] = {NULL};
	if (0 == WideCharToMultiByte(CP_ACP, NULL, srcPath, wcslen(srcPath), szAnsi, sizeof(szAnsi), NULL, NULL))
	{
		if (showProcDialog)
		{
			ShowLastErrMsg();
		}
		return GetLastError();
	}
	

	HRESULT ulResult = ZEncryptFile(szAnsi,(PZEncryptFileWriteFile)global_ZConvertFile_WriteFile,this,encyptType,passWord,passWorfLen);
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

HRESULT  CZConvertToFile::DecryptFileFromFile(
							__in LPCTSTR dstPath,
							__in LPCTSTR srcPath,
							__in BOOL showProcDialog,
							__in PVOID passWord,
							__in ULONG passWorfLen,
							__in PVOID reserve
							)
{
	m_pSrcFile = _wfopen(srcPath,L"rb");
	if (NULL == m_pSrcFile)
	{
		if (showProcDialog)
		{
			ShowLastErrMsg();
		}

		return GetLastError();
	}

	CHAR szAnsi[MAX_PATH] = {NULL};
	if (0 == WideCharToMultiByte(CP_ACP, NULL, dstPath, wcslen(dstPath), szAnsi, sizeof(szAnsi), NULL, NULL))
	{
		if (showProcDialog)
		{
			ShowLastErrMsg();
		}
		return GetLastError();
	}
	HRESULT ulResult = ZDecryptFile(szAnsi,(PZEncryptFileReadFile)global_ZConvertFile_FileReadFile,this,passWord,passWorfLen);
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

size_t CZConvertToFile::ZConvertReadFile( PVOID buf,UINT bufsize )
{
	if (NULL != m_pSrcFile)
	{
		size_t readsize = fread(buf,1,bufsize,m_pSrcFile);
		return readsize;
	}
	return 0;
}

size_t CZConvertToFile::ZConvertWriteFilesize_t( PVOID buf,UINT bufsize,DWORD totallen,DWORD readoffset )
{
	if (NULL != m_pDstFile)
	{
		size_t writesize = fwrite(buf,bufsize,1,m_pDstFile);
		return writesize;
	}
	return 0;
}
