#ifndef __ZSHAREMEM__H__
#define __ZSHAREMEM__H__

#include <Windows.h>
#include <tchar.h>

#define MEM_BUF_SIZE 1024*10

class CZShareMem {
public:
	CZShareMem();
	virtual ~CZShareMem() = 0;
	
	virtual HRESULT WINAPI InitShareMemCreator(LPWSTR memServerName) = 0;
	virtual HRESULT WINAPI InitShareMemOpener(LPWSTR memServerName) = 0;

	virtual HRESULT WINAPI WriteMsgByCreator(__in UINT msgType,__in PVOID msgBuffer,__in UINT bufSize) = 0;
	virtual HRESULT WINAPI WriteMsgByOpener(__in UINT msgType,__in PVOID msgBuffer,__in UINT bufSize) = 0;

		virtual HRESULT WINAPI ReadMsgByCreator(__out UINT &msgType,__out PVOID msgBuffer,__inout UINT &bufSize) = 0;
	virtual HRESULT WINAPI ReadMsgByOpener(__out UINT &msgType,__out PVOID msgBuffer,__inout UINT &bufSize) = 0;

};

CZShareMem* WINAPI CreateZShareMem(void);
#endif