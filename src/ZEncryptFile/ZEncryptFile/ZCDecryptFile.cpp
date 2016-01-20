#include "StdAfx.h"
#include "ZCDecryptFile.h"
#include <malloc.h>
#include <stdio.h>

CDecryptFile::CDecryptFile(void)
{
}

CDecryptFile::~CDecryptFile(void)
{
}


HRESULT WINAPI CDecryptFile::ZCDecryptFile(
	__in LPSTR filePath,
	__in PZEncryptFileReadFile PReadFile,
	__in PVOID handleread,
	//__in UINT encryptType,
	__in PVOID password,
	__in size_t passwordlen
	)
{
	if (NULL == filePath
		||NULL == PReadFile
		||NULL == handleread
		||NULL == password
		||NULL == passwordlen
		)
	{
		return ERROR_INVALID_PARAMETER;
	}

	m_filePath = filePath;
	m_PReadFile = PReadFile;
	m_handleread = handleread;
	//m_encryptType = encryptType;
	m_password = password;
	m_passwordlen = passwordlen;
	memset(&m_fileData,0,sizeof(m_fileData));

	HRESULT state = ERROR_SUCCESS;

	state = GetHeaderAndCheckPassword();
	if (ERROR_SUCCESS != state)
	{
		return state;
	}

	FILE * pFile = fopen(m_filePath,"wb");
	if (NULL == pFile)
	{
		return ERROR_INVALID_NAME;
	}

	UINT bulksize = 0;

	UCHAR transbuf[FREAD_DATABLUK_SIZE] = {NULL};
	size_t tranbuflen = FREAD_DATABLUK_SIZE;

	while(TRUE)
	{
		PVOID buf = GetOneBulk(bulksize);
		if (NULL == buf)
		{
			break;
		}
		state = ZDecryptBuffer(buf,bulksize,transbuf,&tranbuflen,m_encryptType,m_password,m_passwordlen);
		if (ERROR_SUCCESS == state)
		{
			fwrite(transbuf,tranbuflen,1,pFile);
		}
		else if (ERROR_DS_USER_BUFFER_TO_SMALL == state)
		{
			PUCHAR outBuf = new UCHAR[tranbuflen];
			state = ZDecryptBuffer(buf,bulksize,outBuf,&tranbuflen,m_encryptType,m_password,m_passwordlen);
			if (ERROR_SUCCESS == state)
			{
				fwrite(outBuf,tranbuflen,1,pFile);
			}
			else
			{
				delete [] outBuf;
				outBuf = NULL;

				free(buf);
				buf = NULL;
				return ERROR_ENCRYPTION_FAILED;
			}
		}
		else
		{
			free(buf);
			buf = NULL;
			return ERROR_ENCRYPTION_FAILED;
		}
		free(buf);
		buf = NULL;
	}

	fclose(pFile);

	SetFileMsg();

	return ERROR_SUCCESS;
}

HRESULT CDecryptFile::GetHeaderAndCheckPassword()
{
	UINT bulksize = 0;
	PVOID buf = GetOneBulk(bulksize);
	if (NULL == buf)
	{
		return ERROR_END_OF_MEDIA;
	}
	PUCHAR outBuf = new UCHAR[bulksize];

	DefaultDecrpt(buf,outBuf,bulksize);
	free(buf);
	buf = NULL;

	UCHAR md5pass[256] = {NULL};
	size_t len = sizeof(md5pass);
	ZEncryptBuffer(m_password,m_passwordlen,md5pass,&len,ENCRYPT_MD5,NULL,NULL);

	if(0 != memcmp(md5pass,outBuf,len))//–£—È√‹¬Î
	{
		delete [] outBuf;
		outBuf = NULL;
		return ERROR_INVALID_PASSWORD;
	}

	memcpy(&m_encryptType,outBuf + len ,sizeof(m_encryptType));
	len += sizeof(m_encryptType);

	memcpy(&m_fileData,outBuf + len,sizeof(m_fileData));

	delete [] outBuf;
	outBuf = NULL;
	return ERROR_SUCCESS;
}

PVOID CDecryptFile::GetOneBulk(UINT &bulksize)
{
	USHORT len = 0;
	size_t readlen = m_PReadFile((PVOID)&len,sizeof(len),m_handleread);
	if (readlen == 0)
	{
		return NULL;
	}

	len = converlen(len);

	PVOID buf = malloc(len);
	readlen = m_PReadFile((PVOID)buf,len,m_handleread);
	if (readlen == 0)
	{
		return NULL;
	}
	bulksize = readlen;
	return buf;
}

void CDecryptFile::SetFileMsg()
{
	HANDLE hFile = CreateFileA( 
		m_filePath,
		GENERIC_WRITE, 
		FILE_SHARE_READ | FILE_SHARE_WRITE, 
		NULL, 
		OPEN_EXISTING,
		0, 
		NULL );
	if (hFile != INVALID_HANDLE_VALUE)
	{
		SetFileTime( hFile, &m_fileData.ftCreationTime, &m_fileData.ftLastAccessTime, &m_fileData.ftLastWriteTime );
		CloseHandle(hFile);
	}
}

