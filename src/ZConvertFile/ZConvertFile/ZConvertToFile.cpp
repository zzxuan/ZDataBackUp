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
	__in PVOID extendData,
	__in size_t extendlen ,
	__in PVOID reserve 
	)
{
	
	CHAR szAnsi[MAX_PATH] = {NULL};
	if (0 == WideCharToMultiByte(CP_ACP, NULL, srcPath, wcslen(srcPath), szAnsi, sizeof(szAnsi), NULL, NULL))
	{
		if (showProcDialog)
		{
			ShowLastErrMsg();
		}
		return GetLastError();
	}
	m_pDstFile = _wfopen(dstPath,L"wb");
	if (NULL == m_pDstFile)
	{
		if (showProcDialog)
		{
			ShowLastErrMsg();
		}

		return GetLastError();
	}


	HRESULT ulResult = ZEncryptFile(szAnsi,(PZEncryptFileWriteFile)global_ZConvertFile_WriteFile,
		this,encyptType,passWord,passWorfLen,extendData,extendlen);
	fclose(m_pDstFile);
	m_pDstFile = NULL;

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
	
	CHAR szAnsi[MAX_PATH] = {NULL};
	if (0 == WideCharToMultiByte(CP_ACP, NULL, dstPath, wcslen(dstPath), szAnsi, sizeof(szAnsi), NULL, NULL))
	{
		if (showProcDialog)
		{
			ShowLastErrMsg();
		}
		return GetLastError();
	}

	m_pSrcFile = _wfopen(srcPath,L"rb");
	if (NULL == m_pSrcFile)
	{
		if (showProcDialog)
		{
			ShowLastErrMsg();
		}

		return GetLastError();
	}

	HRESULT ulResult = ZDecryptFile(szAnsi,(PZEncryptFileReadFile)global_ZConvertFile_FileReadFile,this,passWord,passWorfLen);
	fclose(m_pSrcFile);
	m_pSrcFile = NULL;

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

HRESULT CZConvertToFile::GetFileInfoInFile( __out PWIN32_FIND_DATAA pfileData, __in LPCTSTR srcPath )
{
	m_pSrcFile = _wfopen(srcPath,L"rb");
	if (NULL == m_pSrcFile)
	{
		return GetLastError();
	}

	HRESULT ulResult = ZGetFileInfo(pfileData,(PZEncryptFileReadFile)global_ZConvertFile_FileReadFile,this);
	fclose(m_pSrcFile);
	m_pSrcFile = NULL;

	return ulResult;
}

HRESULT CZConvertToFile::GetExternDataInFile( __out PVOID pextendData, __inout size_t *pextendLen, __in LPCTSTR srcPath )
{
	m_pSrcFile = _wfopen(srcPath,L"rb");
	if (NULL == m_pSrcFile)
	{
		return GetLastError();
	}

	HRESULT ulResult = ZGetExternData(pextendData,pextendLen,(PZEncryptFileReadFile)global_ZConvertFile_FileReadFile,this);
	fclose(m_pSrcFile);
	m_pSrcFile = NULL;

	return ulResult;
}
