#include "StdAfx.h"
#include "EncryptFile.h"


CEncryptFile::CEncryptFile(void)
{
}

CEncryptFile::~CEncryptFile(void)
{
}

HRESULT CEncryptFile::EncryptFile(
								  __in LPSTR filePath,
								  __in PZEncryptFileWriteFile PWriteFile,
								  __in PVOID handlewrite,
								  __in UINT encryptType,
								  __in PVOID password,
								  __in size_t passwordlen
								  )
{
	if (NULL == filePath
		||NULL == PWriteFile
		||NULL == handlewrite
		||NULL == password
		||NULL == passwordlen
		)
	{
		return ERROR_INVALID_PARAMETER;
	}

	m_filePath = filePath;
	m_PWriteFile = PWriteFile;
	m_handlewrite = handlewrite;
	m_password = password;
	m_passwordlen = passwordlen;

	return ERROR_SUCCESS;
}

HRESULT CEncryptFile::WriteHeader()
{
	//PVOID buf = NULL;
	UCHAR writeBuf[FREAD_DATABLUK_SIZE] = {NULL};

	WIN32_FIND_DATAA find_dataa = {NULL};
	HANDLE handle = FindFirstFileA(m_filePath,&find_dataa);
	
	if (INVALID_HANDLE_VALUE == handle)
	{
		return GetLastError();
	}

	FindClose(handle);

	memcpy(writeBuf,&find_dataa,sizeof(WIN32_FIND_DATAA));
	WriteOneBulk(writeBuf,sizeof(writeBuf));

	return ERROR_SUCCESS;
}

HRESULT CEncryptFile::WriteOneBulk( PVOID data,size_t datasize )
{
	


	return ERROR_SUCCESS;
}


