#pragma once
#include "zsharemem.h"

typedef struct _shareData_
{
	HANDLE shareEvent;
	HANDLE shareMutx;
	HANDLE shareFileMap;
}ShareData,*PShareData;

class CShareClass :
	public CZShareMem
{
	ShareData m_serverData;
	ShareData m_clientData;
public:
	CShareClass(void);
	~CShareClass(void);

	virtual HRESULT WINAPI InitShareMemCreater(LPWSTR memServerName);

	virtual HRESULT WINAPI InitShareMemOpener(LPWSTR memServerName);

	virtual HRESULT WINAPI WriteMsg(__in UINT msgType,__in PVOID msgBuffer,__in UINT bufSize);

	virtual HRESULT WINAPI ReadMsg(__out UINT &msgType,__out PVOID msgBuffer,__inout UINT &bufSize);



};
