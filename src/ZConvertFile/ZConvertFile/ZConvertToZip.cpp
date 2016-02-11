#include "StdAfx.h"
#include "ZConvertToZip.h"

CZConvertToZip::CZConvertToZip(void)
{
}

CZConvertToZip::~CZConvertToZip(void)
{
}

HRESULT CZConvertToZip::EncryptFileToZip( __in LPCTSTR dstPath, __in LPCTSTR srcPath, __in ULONG encyptType, __in BOOL showProcDialog, __in PVOID passWord, __in ULONG passWorfLen, __in PVOID reserve )
{
	return ERROR_SUCCESS;
}

HRESULT CZConvertToZip::DecryptFileFromFile( __in LPCTSTR dstPath, __in LPCTSTR srcPath, __in BOOL showProcDialog, __in PVOID passWord, __in ULONG passWorfLen, __in PVOID reserve )
{
	return ERROR_SUCCESS;
}
