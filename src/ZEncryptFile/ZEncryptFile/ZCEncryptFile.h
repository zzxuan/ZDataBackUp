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
		__in size_t passwordlen
		);

private:
	LPSTR m_filePath;
	PZEncryptFileWriteFile m_PWriteFile;
	PVOID m_handlewrite;
	UINT m_encryptType;
	PVOID m_password;
	size_t m_passwordlen;

	HRESULT WriteHeader();

	HRESULT WriteOneBulk(PVOID data,size_t datasize);

	HRESULT zCompressOneBulk(PVOID * comdata,size_t *comdatalen,PVOID data,size_t datasize);
};
