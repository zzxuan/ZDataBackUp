#include "StdAfx.h"
#include "ZCEncryptFile.h"
#include <stdio.h>


CEncryptFile::CEncryptFile(void)
{
}

CEncryptFile::~CEncryptFile(void)
{
}

HRESULT CEncryptFile::ZCEncryptFile(
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
	m_encryptType = encryptType;
	m_password = password;
	m_passwordlen = passwordlen;

	HRESULT result = ERROR_SUCCESS;
	FILE *pFile = fopen(m_filePath,"rb");
	if (NULL == pFile)
	{
		return ERROR_FILE_NOT_FOUND;
	}

	result = WriteHeader();
	if (ERROR_SUCCESS != result)
	{
		fclose(pFile);
		return result;
	}

	UCHAR readBuf[FREAD_DATABLUK_SIZE] = {NULL};
	size_t readlen = 0;
	

	while (TRUE)
	{
		readlen = fread(readBuf,sizeof(UCHAR),sizeof(readBuf),pFile);
		if (0 == readlen)
		{
			break;
		}
		result = WriteOneBulk((PVOID)readBuf,readlen);
		if (ERROR_SUCCESS != result)
		{
			fclose(pFile);
			return result;
		}
	}
	fclose(pFile);
	return ERROR_SUCCESS;
}

HRESULT CEncryptFile::WriteHeader()
{
	//PVOID buf = NULL;
	UCHAR writeBuf[FREAD_HEAD_SIZE] = {NULL};

	//md5
	UCHAR md5pass[256] = {NULL};
	size_t len = sizeof(md5pass);
	ZEncryptBuffer(m_password,m_passwordlen,md5pass,&len,ENCRYPT_MD5,NULL,NULL);
	memcpy(writeBuf,md5pass,len);

	memcpy(writeBuf+len,&m_encryptType,sizeof(m_encryptType));
	len += sizeof(m_encryptType);

	WIN32_FIND_DATAA find_dataa = {NULL};
	HANDLE handle = FindFirstFileA(m_filePath,&find_dataa);
	
	if (INVALID_HANDLE_VALUE == handle)
	{
		return GetLastError();
	}

	FindClose(handle);
	memcpy(writeBuf+len,&find_dataa,sizeof(WIN32_FIND_DATAA));
	len += sizeof(WIN32_FIND_DATAA);

	UCHAR enwriteBuf[FREAD_HEAD_SIZE] = {NULL};
	size_t enlen = DefaultEncrpt(writeBuf,enwriteBuf,sizeof(writeBuf));

	USHORT lenwrite = converlen(enlen);

	if(NULL !=  m_PWriteFile(&lenwrite,sizeof(USHORT),m_handlewrite)
		&& NULL != m_PWriteFile(enwriteBuf,enlen,m_handlewrite))
	{
		return ERROR_SUCCESS;
	}
	
	return GetLastError();
}

HRESULT CEncryptFile::WriteOneBulk( PVOID data,size_t datasize )
{
	static UCHAR enwriteBuf[FREAD_DATABLUK_SIZE] = {NULL};
	static size_t enlen = sizeof(enwriteBuf);
	HRESULT result = ZEncryptBuffer(data,datasize,enwriteBuf,&enlen,m_encryptType,m_password,m_passwordlen);

	if (ERROR_SUCCESS != result)
	{
		return result;
	}

	USHORT lenwrite = converlen(enlen);

	if(NULL !=  m_PWriteFile(&lenwrite,sizeof(USHORT),m_handlewrite)
		&&NULL != m_PWriteFile(enwriteBuf,enlen,m_handlewrite))
	{
		return ERROR_SUCCESS;
	}

	return GetLastError();
}


