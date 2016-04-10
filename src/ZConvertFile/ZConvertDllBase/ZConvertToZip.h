#pragma once
#include "ZConvertDllBase.h"

class CZConvertToZip
{
public:
	CZConvertToZip(void);
	~CZConvertToZip(void);

	HRESULT EncryptFileToZip(
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

	HRESULT GetFileInfoInZip(
		__out PWIN32_FIND_DATAA pfileData,
		__in LPCTSTR srcPath
		);

	HRESULT GetExternDataInZip(
		__out PVOID pextendData,
		__inout size_t *pextendLen,
		__in LPCTSTR srcPath
		);

	//获得zip的文件列表 出参为字符串以\0隔开
	HRESULT GetFileListInZip(
		__out PCHAR NameBuf,
		__out ULONG& countList,
		__in size_t NameBufSize,
		__in LPCTSTR srcPath
		);

	HRESULT zipOpenFileRead(CHAR* szAnsi,CHAR *dstAnsi);
	VOID zipCloseFileRead();

	size_t ZConvertReadFile(PVOID buf,UINT bufsize);

	size_t ZConvertWriteFilesize_t(PVOID buf,UINT bufsize,DWORD totallen,DWORD readoffset);

	PConvertProgress m_PConvertPrg;
	PVOID m_Handle;
private:
	PVOID m_zipFileRead;
	PVOID m_zipFileWrite;
	ULONG m_srcFileSize;
	ULONG m_srcReadSize;
};
