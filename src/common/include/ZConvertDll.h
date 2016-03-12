#ifndef __ZCONVERTDLL__H__
#define __ZCONVERTDLL__H__

#include <vector>
#include <string>

HRESULT ConvertFileBaseExe(
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

HRESULT GetFileInfoInFileExe(__in LPCWSTR srcPath,__out WIN32_FIND_DATAA &filedata,__out PVOID extdata,__inout UINT &extlen);
HRESULT GetFileInfoInZipExe(__in LPCWSTR srcPath,__out WIN32_FIND_DATAA &filedata,__out PVOID extdata,__inout UINT &extlen);
HRESULT GetFileListInZipExe(__in LPCWSTR srcPath,std::vector<std::string> &namelist);

HRESULT ConvertFileToFileExe(__in LPCWSTR dstPath,
						  __in LPCWSTR srcPath,
						  __in ULONG encyptType,
						  __in BOOL showProcDialog,
						  __in PVOID passWord,
						  __in ULONG passWorfLen,
						  __in PVOID pextdata,
						  __in ULONG extlen,
						  __in PVOID reserve,
						  __in ULONG reservelen);

HRESULT ConvertFileToZipExe(__in LPCWSTR dstPath,
						  __in LPCWSTR srcPath,
						  __in ULONG encyptType,
						  __in BOOL showProcDialog,
						  __in PVOID passWord,
						  __in ULONG passWorfLen,
						  __in PVOID pextdata,
						  __in ULONG extlen,
						  __in PVOID reserve,
						  __in ULONG reservelen);


HRESULT ConvertFileFromFileExe(__in LPCWSTR dstPath,
						  __in LPCWSTR srcPath,
						  __in BOOL showProcDialog,
						  __in PVOID passWord,
						  __in ULONG passWorfLen,
						  __in PVOID pextdata,
						  __in ULONG extlen,
						  __in PVOID reserve,
						  __in ULONG reservelen);


HRESULT ConvertFileFromZipExe(__in LPCWSTR dstPath,
						  __in LPCWSTR srcPath,
						  __in BOOL showProcDialog,
						  __in PVOID passWord,
						  __in ULONG passWorfLen,
						  __in PVOID pextdata,
						  __in ULONG extlen,
						  __in PVOID reserve,
						  __in ULONG reservelen);



#endif