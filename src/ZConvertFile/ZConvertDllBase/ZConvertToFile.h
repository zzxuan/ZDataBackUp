#pragma once
#include "ZConvertDllBase.h"

class CZConvertToFile
{
private:
	FILE * m_pSrcFile;
	FILE * m_pDstFile;

	ULONG m_srcFileSize;

public:
	CZConvertToFile(void);
	~CZConvertToFile(void);

	PConvertProgress m_PConvertPrg;
	PVOID m_Handle;

	HRESULT EncryptFileToFile(
		__in LPCTSTR dstPath,
		__in LPCTSTR srcPath,
		__in ULONG encyptType,
		__in BOOL showProcDialog,
		__in PVOID passWord,
		__in ULONG passWorfLen,
		__in PVOID extendData,
		__in size_t extendlen ,
		__in PVOID reserve
		);

	HRESULT DecryptFileFromFile(
		__in LPCTSTR dstPath,
		__in LPCTSTR srcPath,
		__in BOOL showProcDialog,
		__in PVOID passWord,
		__in ULONG passWorfLen,
		__in PVOID reserve
		);

	HRESULT GetFileInfoInFile(
		__out PWIN32_FIND_DATAA pfileData,
		__in LPCTSTR srcPath
		);

	HRESULT GetExternDataInFile(
		__out PVOID pextendData,
		__inout size_t *pextendLen,
		__in LPCTSTR srcPath
		);

	size_t ZConvertReadFile(PVOID buf,UINT bufsize);

	size_t ZConvertWriteFilesize_t(PVOID buf,UINT bufsize,DWORD totallen,DWORD readoffset);
};
