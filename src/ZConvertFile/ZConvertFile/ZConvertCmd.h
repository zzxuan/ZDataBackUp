#pragma once

class CZConvertCmd
{
public:
	CZConvertCmd(void);
	~CZConvertCmd(void);

	HRESULT TransferCmdLine();

	HRESULT ConvertFileBase(
		__in LPCTSTR dstPath,
		__in LPCTSTR srcPath,
		__in ULONG optionType,
		__in ULONG encyptType,
		__in BOOL showProcDialog,
		__in PVOID passWord,
		__in ULONG passWorfLen,
		__in PVOID reserve
		);

	
};
