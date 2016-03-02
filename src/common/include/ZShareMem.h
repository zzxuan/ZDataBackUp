#ifndef __ZSHAREMEM__H__
#define __ZSHAREMEM__H__

#include <Windows.h>
#include <tchar.h>

class CZShareMem {
public:
	CZShareMem();
	virtual ~CZShareMem() = 0;
	
	virtual HRESULT WINAPI InitShareMemCreater(LPWSTR memServerName) = 0;
	virtual HRESULT WINAPI InitShareMemOpener(LPWSTR memServerName) = 0;
	virtual HRESULT WINAPI WriteMsg(__in UINT msgType,__in PVOID msgBuffer,__in UINT bufSize) = 0;
	virtual HRESULT WINAPI ReadMsg(__out UINT &msgType,__out PVOID msgBuffer,__inout UINT &bufSize) = 0;

};

CZShareMem* WINAPI CreateZShareMem(void);
#endif