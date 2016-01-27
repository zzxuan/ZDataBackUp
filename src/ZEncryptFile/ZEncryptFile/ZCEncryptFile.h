//¼ÓÃÜÎÄ¼þ
#pragma once
#include "ZEncryptFile.h"



class CEncryptFile
{
public:
	CEncryptFile(void);
	~CEncryptFile(void);

	HRESULT WINAPI ZCEncryptFile(
		__in LPSTR filePath,
		__in PZEncryptFileWriteFile PWriteFile,
		__in PVOID handlewrite,
		__in UINT encryptType,
		__in PVOID password,
		__in size_t passwordlen,
		__in PVOID extendData = NULL,
		__in size_t extendlen = 0
		);

private:
	LPSTR m_filePath;
	PZEncryptFileWriteFile m_PWriteFile;
	PVOID m_handlewrite;
	UINT m_encryptType;
	PVOID m_password;
	size_t m_passwordlen;

	PVOID m_extendData;
	size_t m_extendLen;

	DWORD m_filetotalsize;
	DWORD m_readsize;

	HRESULT WriteHeader();

	HRESULT WriteOneBulk(PVOID data,size_t datasize);

	HRESULT zCompressOneBulk(PVOID * comdata,size_t *comdatalen,PVOID data,size_t datasize);
};
