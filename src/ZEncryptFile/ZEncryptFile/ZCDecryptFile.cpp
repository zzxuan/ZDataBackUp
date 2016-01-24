#include "StdAfx.h"
#include "ZCDecryptFile.h"
#include <malloc.h>
#include <stdio.h>
#include "..\..\minizlib\minizlib\zlib.h"

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
	UINT orgsize = 0;//原始长度

	UCHAR transbuf[FREAD_DATABLUK_SIZE] = {NULL};
	size_t tranbuflen = FREAD_DATABLUK_SIZE;


	while(TRUE)
	{
		tranbuflen = FREAD_DATABLUK_SIZE;
		PVOID buf = GetOneBulk(bulksize,orgsize);
		if (NULL == buf)
		{
			break;
		}

		__try
		{
			state = ZDecryptBuffer(buf,bulksize,transbuf,&tranbuflen,m_encryptType,m_password,m_passwordlen);
			if (ERROR_SUCCESS == state)
			{
				PUCHAR uncombuf = NULL;
				size_t uncombuflen = 0;
				if (ERROR_SUCCESS != UnCompressOneBuffer((PVOID *)&uncombuf,&uncombuflen,transbuf,tranbuflen))
				{
					state = ERROR_INVALID_PARAMETER;
					__leave;
				}
				if (uncombuflen != orgsize)
				{
					state = ERROR_FILE_HASCHANGED;
					__leave;
				}
				fwrite(uncombuf,uncombuflen,1,pFile);
			}
			else if (ERROR_DS_USER_BUFFER_TO_SMALL == state)
			{
				PUCHAR outBuf = new UCHAR[tranbuflen];
				state = ZDecryptBuffer(buf,bulksize,outBuf,&tranbuflen,m_encryptType,m_password,m_passwordlen);
				if (ERROR_SUCCESS == state)
				{
					PUCHAR uncombuf = NULL;
					size_t uncombuflen = 0;
					if (ERROR_SUCCESS != UnCompressOneBuffer((PVOID *)&uncombuf,&uncombuflen,outBuf,tranbuflen))
					{
						delete [] outBuf;
						outBuf = NULL;

						state = ERROR_INVALID_PARAMETER;
						__leave;
					}
					if (uncombuflen != orgsize)
					{
						state = ERROR_FILE_HASCHANGED;
						__leave;
					}
					fwrite(uncombuf,uncombuflen,1,pFile);
				}
				else
				{
					delete [] outBuf;
					outBuf = NULL;

					state = ERROR_ENCRYPTION_FAILED;
					__leave;
				}
			}
			else
			{
				state = ERROR_ENCRYPTION_FAILED;
				__leave;
			}
		}
		__finally
		{
			if (NULL != buf)
			{
				free(buf);
				buf = NULL;
			}
			if (ERROR_SUCCESS != state)
			{
				return state;
			}
		}
		
	}

	fclose(pFile);

	SetFileMsg();

	return ERROR_SUCCESS;
}

HRESULT CDecryptFile::GetHeaderAndCheckPassword()
{
	UINT bulksize = 0;
	UINT orgsize = 0;
	PVOID buf = GetOneBulk(bulksize,orgsize);
	if (NULL == buf)
	{
		return ERROR_END_OF_MEDIA;
	}
	PUCHAR outBuf = new UCHAR[bulksize];

	DefaultDecrpt(buf,outBuf,bulksize);
	free(buf);
	buf = NULL;

	PUCHAR uncombuf = NULL;
	size_t uncombuflen = 0;
	if (ERROR_SUCCESS != UnCompressOneBuffer((PVOID *)&uncombuf,&uncombuflen,outBuf,bulksize))
	{
		delete [] outBuf;
		outBuf = NULL;
		return ERROR_INVALID_PARAMETER;
	}
	delete [] outBuf;
	outBuf = NULL;
	if (orgsize != uncombuflen)
	{
		return ERROR_FILE_HASCHANGED;
	}

	UCHAR md5pass[256] = {NULL};
	size_t len = sizeof(md5pass);
	ZEncryptBuffer(m_password,m_passwordlen,md5pass,&len,ENCRYPT_MD5,NULL,NULL);

	if(0 != memcmp(md5pass,uncombuf,len))//校验密码
	{
		free(uncombuf);
		return ERROR_INVALID_PASSWORD;
	}

	memcpy(&m_encryptType,uncombuf + len ,sizeof(m_encryptType));
	len += sizeof(m_encryptType);

	memcpy(&m_fileData,uncombuf + len,sizeof(m_fileData));

	free(uncombuf);
	return ERROR_SUCCESS;
}

PVOID CDecryptFile::GetOneBulk(UINT &bulksize,UINT &orgSize)
{
	USHORT len = 0;
	size_t readlen = m_PReadFile((PVOID)&len,sizeof(len),m_handleread);
	if (readlen == 0)
	{
		return NULL;
	}

	len = converlen(len);
	USHORT orglen = 0;
	readlen = m_PReadFile((PVOID)&orglen,sizeof(orglen),m_handleread);
	if (readlen == 0)
	{
		return NULL;
	}
	orglen = converlen(orglen);

	PVOID buf = malloc(len);
	readlen = m_PReadFile((PVOID)buf,len,m_handleread);
	if (readlen == 0)
	{
		free(buf);
		return NULL;
	}

	bulksize = readlen;
	orgSize = orglen;
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

HRESULT CDecryptFile::UnCompressOneBuffer( PVOID * comdata,size_t *comdatalen,PVOID data,size_t datasize )
{
	PUCHAR buf = (PUCHAR)malloc(FREAD_DATABLUK_SIZE);
	size_t buflen = FREAD_DATABLUK_SIZE;

	if(uncompress((PUCHAR)buf, (ULONG *)&buflen, (PUCHAR)data, (ULONG)datasize) != Z_OK)  
	{  
		free(buf);
		return ERROR_INVALID_PARAMETER;
	} 
	( * comdata) = buf;
	(*comdatalen) = buflen;
	return ERROR_SUCCESS;
}

