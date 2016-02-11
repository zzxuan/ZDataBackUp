#pragma once

class CZConvertToZip
{
public:
	CZConvertToZip(void);
	~CZConvertToZip(void);

	HRESULT EncryptFileToZip(
		__in LPCTSTR dstPath,
		__in LPCTSTR srcPath,
		__in ULONG encyptType,
		__in BOOL showProcDialog,
		__in PVOID passWord,
		__in ULONG passWorfLen,
		__in PVOID reserve
		);

	HRESULT DecryptFileFromFile(
		__in LPCTSTR dstPath,
		__in LPCTSTR srcPath,
		__in BOOL showProcDialog,
		__in PVOID passWord,
		__in ULONG passWorfLen,
		__in PVOID reserve
		);
};
