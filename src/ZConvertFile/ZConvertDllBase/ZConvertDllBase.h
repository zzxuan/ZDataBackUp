#ifndef __ZCONVERTDLLBASE__H__
#define __ZCONVERTDLLBASE__H__

HRESULT ConvertFileBaseDll(
						   __in LPCWSTR dstPath,
						   __in LPCWSTR srcPath,
						   __in ULONG optionType,
						   __in ULONG encyptType,
						   __in BOOL showProcDialog,
						   __in PVOID passWord,
						   __in ULONG passWorfLen,
						   __in PVOID pextdata,
						   __in ULONG extlen,
						   __in PVOID reserve,
						   __in ULONG reservelen
						   );

HRESULT GetFileInfoInFileDll(__in LPCWSTR srcPath,__out WIN32_FIND_DATAA &filedata,__out PVOID extdata,__inout UINT &extlen);
HRESULT GetFileInfoInZipDll(__in LPCWSTR srcPath,__out WIN32_FIND_DATAA &filedata,__out PVOID extdata,__inout UINT &extlen);
HRESULT GetFileListInZipDll(__in LPCWSTR srcPath,std::vector<std::string> &namelist);

HRESULT ConvertFileToFileDll(__in LPCWSTR dstPath,
							 __in LPCWSTR srcPath,
							 __in ULONG encyptType,
							 __in BOOL showProcDialog,
							 __in PVOID passWord,
							 __in ULONG passWorfLen,
							 __in PVOID pextdata,
							 __in ULONG extlen,
							 __in PVOID reserve,
							 __in ULONG reservelen);

HRESULT ConvertFileToZipDll(__in LPCWSTR dstPath,
							__in LPCWSTR srcPath,
							__in ULONG encyptType,
							__in BOOL showProcDialog,
							__in PVOID passWord,
							__in ULONG passWorfLen,
							__in PVOID pextdata,
							__in ULONG extlen,
							__in PVOID reserve,
							__in ULONG reservelen);


HRESULT ConvertFileFromFileDll(__in LPCWSTR dstPath,
							   __in LPCWSTR srcPath,
							   __in BOOL showProcDialog,
							   __in PVOID passWord,
							   __in ULONG passWorfLen,
							   __in PVOID pextdata,
							   __in ULONG extlen,
							   __in PVOID reserve,
							   __in ULONG reservelen);


HRESULT ConvertFileFromZipDll(__in LPCWSTR dstPath,
							  __in LPCWSTR srcPath,
							  __in BOOL showProcDialog,
							  __in PVOID passWord,
							  __in ULONG passWorfLen,
							  __in PVOID pextdata,
							  __in ULONG extlen,
							  __in PVOID reserve,
							  __in ULONG reservelen);

#endif