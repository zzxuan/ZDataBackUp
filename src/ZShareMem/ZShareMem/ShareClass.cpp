#include "StdAfx.h"
#include "ShareClass.h"

#define BUF_SIZE 1024

#define EVENTTAIL _T("_EVENT")
#define MUTEXTAIL _T("_MUXT")
#define FILEMAPTAIL _T("_FILEMAP")

CShareClass::CShareClass(void)
{	
	memset(&m_serverData,0,sizeof(ShareData));
	memset(&m_clientData,0,sizeof(ShareData));
}

CShareClass::~CShareClass(void)
{
	if (NULL != m_serverData.shareEvent)
	{
		CloseHandle(m_serverData.shareEvent);
		CloseHandle(m_serverData.shareMutx);
		CloseHandle(m_serverData.shareFileMap);
	}

	if (NULL != m_clientData.shareEvent)
	{
		CloseHandle(m_clientData.shareEvent);
		CloseHandle(m_clientData.shareMutx);
		CloseHandle(m_clientData.shareFileMap);
	}
}

HRESULT WINAPI CShareClass::InitShareMemCreater(LPWSTR memServerName)
{
	if (NULL != memServerName)
	{
		TCHAR szName[MAX_PATH] = {NULL};
		_stprintf_s(szName,_T("%s%s"),memServerName,EVENTTAIL);
		m_serverData.shareEvent = CreateEvent(NULL,FALSE,FALSE,szName);
		if (NULL == m_serverData.shareEvent)
		{
			return GetLastError();
		}
		if (ERROR_ALREADY_EXISTS == GetLastError())
		{
			CloseHandle(m_serverData.shareEvent);
			return ERROR_ALREADY_EXISTS;
		}

		_stprintf_s(szName,_T("%s%s"),memServerName,MUTEXTAIL);
		m_serverData.shareMutx = CreateMutex( 
			NULL,              // default security attributes
			FALSE,             // initially not owned
			szName);             // unnamed mutex

		if (NULL == m_serverData.shareMutx)
		{
			return GetLastError();
		}

		_stprintf_s(szName,_T("%s%s"),memServerName,FILEMAPTAIL);
		m_serverData.shareFileMap = CreateFileMapping(
			INVALID_HANDLE_VALUE,    // use paging file
			NULL,                    // default security 
			PAGE_READWRITE,          // read/write access
			0,                       // max. object size 
			BUF_SIZE,                // buffer size  
			szName);                 // name of mapping object

		if (NULL == m_serverData.shareFileMap)
		{
			return GetLastError();
		}
	}
	return ERROR_SUCCESS;
}

HRESULT WINAPI CShareClass::InitShareMemOpener(LPWSTR memClientName)
{
	if (NULL != memClientName)
	{
		TCHAR szName[MAX_PATH] = {NULL};
		_stprintf_s(szName,_T("%s%s"),memClientName,EVENTTAIL);
		m_clientData.shareEvent = OpenEvent(EVENT_ALL_ACCESS,NULL,szName);
		if (NULL == m_clientData.shareEvent)
		{
			return GetLastError();
		}

		_stprintf_s(szName,_T("%s%s"),memClientName,MUTEXTAIL);
		m_clientData.shareMutx = OpenMutex(MUTEX_ALL_ACCESS,NULL,szName);
		if (NULL == m_clientData.shareMutx)
		{
			return GetLastError();
		}

		_stprintf_s(szName,_T("%s%s"),memClientName,FILEMAPTAIL);
		m_clientData.shareFileMap = OpenFileMapping(
			FILE_MAP_ALL_ACCESS,   // read/write access
			FALSE,                 // do not inherit the name
			szName);               // name of mapping object 



		if (NULL == m_clientData.shareFileMap)
		{
			return GetLastError();
		}
	}
	return ERROR_SUCCESS;
}


HRESULT WINAPI CShareClass::WriteMsg(__in UINT msgType,__in PVOID msgBuffer,__in UINT bufSize)
{
	if (NULL == m_clientData.shareEvent)
	{
		return ERROR_FILE_NOT_FOUND;
	}
	if (sizeof(UINT) + sizeof(UINT) + bufSize > BUF_SIZE)
	{
		return ERROR_BUFFER_OVERFLOW;
	}

	HRESULT state = ERROR_SUCCESS;
	PUCHAR pBuf;

	WaitForSingleObject(m_clientData.shareMutx,INFINITE);
	do 
	{
		pBuf = (PUCHAR) MapViewOfFile(m_clientData.shareFileMap,   // handle to map object
			FILE_MAP_ALL_ACCESS, // read/write permission
			0,                   
			0,                   
			BUF_SIZE);           

		if (pBuf == NULL) 
		{ 
			state = GetLastError();
			break;
		}
		PUCHAR pubuf = pBuf;

		memcpy(pubuf,&msgType,sizeof(UINT));
		pubuf += sizeof(UINT);
		memcpy(pubuf,&bufSize,sizeof(UINT));
		pubuf += sizeof(UINT);
		memcpy(pubuf,msgBuffer,bufSize);

		UnmapViewOfFile(pBuf);
		SetEvent(m_clientData.shareEvent);
	} while (FALSE);
	ReleaseMutex(m_clientData.shareMutx);

	return state;
}

HRESULT WINAPI CShareClass::ReadMsg(__out UINT &msgType,__out PVOID msgBuffer,__inout UINT &bufSize)
{
	if (NULL == m_serverData.shareEvent)
	{
		return ERROR_FILE_NOT_FOUND;
	}
	WaitForSingleObject(m_serverData.shareEvent,INFINITE);
	HRESULT state = ERROR_SUCCESS;
	PUCHAR pBuf;

	WaitForSingleObject(m_serverData.shareMutx,INFINITE);
	do 
	{
		pBuf = (PUCHAR) MapViewOfFile(m_serverData.shareFileMap,   // handle to map object
			FILE_MAP_ALL_ACCESS, // read/write permission
			0,                   
			0,                   
			BUF_SIZE);           

		if (pBuf == NULL) 
		{ 
			state = GetLastError();
			break;
		}
		PUCHAR pubuf = pBuf;

		memcpy(&msgType,pubuf,sizeof(UINT));
		pubuf += sizeof(UINT);

		UINT bufMaxsize = bufSize;

		memcpy(&bufSize,pubuf,sizeof(UINT));
		pubuf += sizeof(UINT);

		if (bufMaxsize < bufSize)
		{
			state = ERROR_BUFFER_OVERFLOW;
			break;
		}
		memcpy(msgBuffer,pubuf,bufSize);

		UnmapViewOfFile(pBuf);
	} while (FALSE);

	ReleaseMutex(m_serverData.shareMutx);
	return state;
}

