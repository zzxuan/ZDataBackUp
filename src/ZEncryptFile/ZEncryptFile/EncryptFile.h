//¼ÓÃÜÎÄ¼þ
#pragma once
#include "ZEncryptFile.h"

#define FREAD_HEAD_SIZE	512
#define FREAD_DATABLUK_SIZE	1024*4

class CEncryptFile
{
public:
	CEncryptFile(void);
	~CEncryptFile(void);

	HRESULT WINAPI EncryptFile(
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
};
