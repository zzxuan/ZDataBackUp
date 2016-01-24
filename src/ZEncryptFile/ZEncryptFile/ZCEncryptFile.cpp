#include "StdAfx.h"
#include "ZCEncryptFile.h"
#include <stdio.h>
#include "../../common/include/zlib.h"
#include <malloc.h>

#pragma comment(lib,"../../common/lib/minizlib.lib")


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


	PVOID comBuf = NULL;
	size_t comLen = 0;
	if (ERROR_SUCCESS != zCompressOneBulk(&comBuf,&comLen,writeBuf,sizeof(writeBuf)))
	{
		return ERROR_INVALID_PARAMETER;
	}



	UCHAR enwriteBuf[FREAD_HEAD_SIZE] = {NULL};
	size_t enlen = DefaultEncrpt(comBuf,enwriteBuf,comLen);
	free(comBuf);
	comBuf = NULL;

	USHORT lenwrite = converlen(enlen);
	USHORT uncomzisewrite = converlen(sizeof(writeBuf));//压缩加密前的长度

	if(NULL !=  m_PWriteFile(&lenwrite,sizeof(USHORT),m_handlewrite)
		&& NULL !=  m_PWriteFile(&uncomzisewrite,sizeof(USHORT),m_handlewrite)
		&& NULL != m_PWriteFile(enwriteBuf,enlen,m_handlewrite))
	{

		return ERROR_SUCCESS;
	}
	
	return GetLastError();
}

HRESULT CEncryptFile::WriteOneBulk( PVOID data,size_t datasize )
{
	PVOID comBuf = NULL;
	size_t comLen = 0;
	if (ERROR_SUCCESS != zCompressOneBulk(&comBuf,&comLen,data,datasize))
	{
		return ERROR_INVALID_PARAMETER;
	}

	static UCHAR enwriteBuf[FREAD_DATABLUK_SIZE] = {NULL};
	static size_t enlen = sizeof(enwriteBuf);
	enlen = sizeof(enwriteBuf);
	HRESULT result = ZEncryptBuffer(comBuf,comLen,enwriteBuf,&enlen,m_encryptType,m_password,m_passwordlen);

	if (ERROR_SUCCESS != result)
	{
		goto LAST;
	}

	USHORT lenwrite = converlen(enlen);
	USHORT uncomzisewrite = converlen(datasize);//压缩加密前的长度

	if(NULL !=  m_PWriteFile(&lenwrite,sizeof(USHORT),m_handlewrite)
		&&NULL !=  m_PWriteFile(&uncomzisewrite,sizeof(USHORT),m_handlewrite)
		&&NULL != m_PWriteFile(enwriteBuf,enlen,m_handlewrite))
	{
		result = ERROR_SUCCESS;
	}
	else
	{
		result = GetLastError();
	}

LAST:
	if (NULL != comBuf)
	{
		free(comBuf);
	}

	return result;
}

HRESULT CEncryptFile::zCompressOneBulk( PVOID * comdata,size_t *comdatalen,PVOID data,size_t datasize )
{
	ULONG comlen = compressBound(datasize);

	(* comdata) = (PUCHAR)malloc(sizeof(UCHAR) * comlen);
	if (NULL == (* comdata))
	{
		return ERROR_INVALID_PARAMETER;
	}
	/* 压缩 */  
	if(compress((PUCHAR)(* comdata), &comlen, (PUCHAR)data, datasize) != Z_OK)  
	{  
		free((* comdata)) ;
		return ERROR_INVALID_PARAMETER;  
	} 

	*comdatalen = comlen;
	return ERROR_SUCCESS;
}


