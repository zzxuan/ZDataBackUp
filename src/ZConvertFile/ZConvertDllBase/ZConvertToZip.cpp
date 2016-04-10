#include "StdAfx.h"
#include "ZConvertToZip.h"
#include <shlwapi.h>

#include "../../common/include/zip.h"
#include "../../common/include/unzip.h"
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
	m_PConvertPrg = NULL;
}

CZConvertToZip::~CZConvertToZip(void)
{
}

//dstPath zip 路径格式：c://sda/abc.zip&abc.txt
HRESULT CZConvertToZip::EncryptFileToZip(
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

	PCHAR zipinfile = strchr(dstAnsi,'&');
	if (NULL != zipinfile)
	{
		(*zipinfile) = '\0';
		zipinfile += sizeof(CHAR);
	}
	else
	{
		zipinfile = PathFindFileNameA(szAnsi);
	}


	if (!PathFileExistsA(dstAnsi))
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

	HRESULT ulResult = ZEncryptFile(szAnsi,(PZEncryptFileWriteFile)global_ZConvertZip_WriteFile,
		this,encyptType,passWord,passWorfLen,extendData,extendlen);

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

//srcPath zip 路径格式：c://sda/abc.zip&abc.txt
HRESULT CZConvertToZip::DecryptFileFromFile( __in LPCTSTR dstPath, __in LPCTSTR srcPath, __in BOOL showProcDialog, __in PVOID passWord, __in ULONG passWorfLen, __in PVOID reserve )
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

	HRESULT zipRes = zipOpenFileRead(szAnsi,dstAnsi);
	if (ERROR_SUCCESS != zipRes)
	{
		return zipRes;
	}

	HRESULT ulResult = ZDecryptFile(dstAnsi,(PZEncryptFileReadFile)global_ZConvertZip_ReadFile,this,passWord,passWorfLen);
	zipCloseFileRead();
	return ulResult;
}

size_t CZConvertToZip::ZConvertReadFile( PVOID buf,UINT bufsize )
{
	if (NULL == m_zipFileRead)
	{
		return 0;
	}

	int n = unzReadCurrentFile(m_zipFileRead,buf,bufsize);
	
	if (NULL != m_PConvertPrg)
	{
		m_srcReadSize += n;
		m_PConvertPrg(m_srcReadSize,m_srcFileSize);
	}
	return n;
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
		if (NULL != m_PConvertPrg)
		{
			m_PConvertPrg(readoffset,totallen);
		}
		return bufsize;
	}

	ZDbgPrint(DBG_ERROR,_T("CZConvertToZip ::zipWriteInFileInZip Failed err = %d"),GetLastError());

	return 0;
}

HRESULT CZConvertToZip::zipOpenFileRead( CHAR* szAnsi,CHAR *dstAnsi )
{
	PCHAR zipinfile = strchr(szAnsi,'&');
	if (NULL != zipinfile)
	{
		(*zipinfile) = '\0';
		zipinfile += sizeof(CHAR);
	}
	else if (NULL != dstAnsi)
	{
		zipinfile = PathFindFileNameA(dstAnsi);
	}
	else
	{
		return ERROR_INVALID_PARAMETER;
	}

	WIN32_FIND_DATAA fileInfo; 
	HANDLE hFind; 
	m_srcFileSize = 0;
	m_srcReadSize = 0;
	hFind = FindFirstFileA(szAnsi ,&fileInfo); 
	if(hFind != INVALID_HANDLE_VALUE) 
		m_srcFileSize = fileInfo.nFileSizeLow; 
	FindClose(hFind); 

	m_zipFileRead = unzOpen(szAnsi);
	if (NULL == m_zipFileRead)
	{
		return ERROR_FILE_NOT_FOUND;
	}

	if (UNZ_OK != unzLocateFile(m_zipFileRead,zipinfile,1))
	{
		return ERROR_FILE_NOT_FOUND;
	}

	if (UNZ_OK != unzOpenCurrentFile(m_zipFileRead))
	{
		return ERROR_FILE_INVALID;
	}

	return ERROR_SUCCESS;
}


VOID CZConvertToZip::zipCloseFileRead()
{
	if (NULL == m_zipFileRead)
	{
		return;
	}
	unzCloseCurrentFile(m_zipFileRead);
	unzClose(m_zipFileRead);
	m_zipFileRead = NULL;
}

HRESULT CZConvertToZip::GetFileInfoInZip( __out PWIN32_FIND_DATAA pfileData, __in LPCTSTR srcPath )
{
	CHAR szAnsi[MAX_PATH] = {NULL};

	if (0 == WideCharToMultiByte(CP_ACP, NULL, srcPath, wcslen(srcPath), szAnsi, sizeof(szAnsi), NULL, NULL))
	{
		return GetLastError();
	}

	HRESULT zipRes = zipOpenFileRead(szAnsi,NULL);
	if (ERROR_SUCCESS != zipRes)
	{
		return zipRes;
	}

	HRESULT ulResault = ZGetFileInfo(pfileData,(PZEncryptFileReadFile)global_ZConvertZip_ReadFile,this);
	zipCloseFileRead();
	return ulResault;
}

HRESULT CZConvertToZip::GetExternDataInZip( __out PVOID pextendData, __inout size_t *pextendLen, __in LPCTSTR srcPath )
{
	CHAR szAnsi[MAX_PATH] = {NULL};

	if (0 == WideCharToMultiByte(CP_ACP, NULL, srcPath, wcslen(srcPath), szAnsi, sizeof(szAnsi), NULL, NULL))
	{
		return GetLastError();
	}

	HRESULT zipRes = zipOpenFileRead(szAnsi,NULL);
	if (ERROR_SUCCESS != zipRes)
	{
		return zipRes;
	}

	HRESULT ulResault = ZGetExternData(pextendData,pextendLen,(PZEncryptFileReadFile)global_ZConvertZip_ReadFile,this);
	zipCloseFileRead();
	return ulResault;
}

HRESULT CZConvertToZip::GetFileListInZip(
	__out PCHAR NameBuf, 
	__out ULONG& countList, 
	__in size_t NameBufSize, 
	__in LPCTSTR srcPath 
	)
{
	CHAR name[MAX_PATH] = {NULL};

	PCHAR pstr = NameBuf;
	ULONG nindex = 0;
	memset(NameBuf,0,NameBufSize);
	countList = 0;

	CHAR szAnsi[MAX_PATH] = {NULL};

	if (0 == WideCharToMultiByte(CP_ACP, NULL, srcPath, wcslen(srcPath), szAnsi, sizeof(szAnsi), NULL, NULL))
	{
		return GetLastError();
	}

	PVOID zipfile = unzOpen(szAnsi);
	if (NULL == zipfile)
	{
		return ERROR_FILE_NOT_FOUND;
	}

	HRESULT nResult = ERROR_SUCCESS;

	do 
	{
		if (UNZ_OK != unzGoToFirstFile(zipfile))
		{
			nResult = ERROR_FILE_NOT_FOUND;
			break;
		}

		if (UNZ_OK !=unzGetCurrentFileInfo(
			zipfile,
			NULL,
			name,
			sizeof(name),
			NULL,0,
			NULL,0
			))
		{
			nResult = ERROR_FILE_INVALID;
			break;
		}
		//---copy name--------
		if (NameBufSize - nindex < strlen(name))
		{
			nResult = ERROR_MORE_DATA;
			break;
		}
		strncpy(pstr,name,NameBufSize - nindex);
		ULONG len = strlen(pstr);
		nindex += len + 1;
		pstr += len + 1;
		countList++;

		while(TRUE)
		{
			memset(name,0,sizeof(name));
			int nstate = unzGoToNextFile(zipfile);
			if (UNZ_OK != nstate)
			{
				if (UNZ_END_OF_LIST_OF_FILE == nstate)
				{
					nResult = ERROR_SUCCESS;
				}
				else
				{
					nResult = ERROR_FILE_NOT_FOUND;
				}
				break;
			}

			if (UNZ_OK !=unzGetCurrentFileInfo(
				zipfile,
				NULL,
				name,
				sizeof(name),
				NULL,0,
				NULL,0
				))
			{
				nResult = ERROR_FILE_INVALID;
				break;
			}
			//---copy name--------
			if (NameBufSize - nindex < strlen(name))
			{
				nResult = ERROR_MORE_DATA;
				break;
			}
			strncpy(pstr,name,NameBufSize - nindex);
			ULONG len = strlen(pstr);
			nindex += len + 1;
			pstr += len + 1;
			countList++;

		}
	} while (FALSE);

	unzClose(zipfile);
	zipfile = NULL;
	return ERROR_SUCCESS;
}
