#ifndef __ZCONVERTDLL__H__
#define __ZCONVERTDLL__H__

#include <vector>
#include <string>

HRESULT ConvertFileBase(
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

HRESULT GetFileInfoInFile(__in LPCWSTR srcPath,__out WIN32_FIND_DATAA &filedata,__out PVOID extdata,__inout UINT &extlen);
HRESULT GetFileInfoInZip(__in LPCWSTR srcPath,__out WIN32_FIND_DATAA &filedata,__out PVOID extdata,__inout UINT &extlen);
HRESULT GetFileListInZip(__in LPCWSTR srcPath,std::vector<std::string> &namelist);

HRESULT ConvertFileToFile(__in LPCWSTR dstPath,
						  __in LPCWSTR srcPath,
						  __in ULONG encyptType,
						  __in BOOL showProcDialog,
						  __in PVOID passWord,
						  __in ULONG passWorfLen,
						  __in PVOID pextdata,
						  __in ULONG extlen,
						  __in PVOID reserve,
						  __in ULONG reservelen);

HRESULT ConvertFileToZip(__in LPCWSTR dstPath,
						  __in LPCWSTR srcPath,
						  __in ULONG encyptType,
						  __in BOOL showProcDialog,
						  __in PVOID passWord,
						  __in ULONG passWorfLen,
						  __in PVOID pextdata,
						  __in ULONG extlen,
						  __in PVOID reserve,
						  __in ULONG reservelen);


HRESULT ConvertFileFromFile(__in LPCWSTR dstPath,
						  __in LPCWSTR srcPath,
						  __in BOOL showProcDialog,
						  __in PVOID passWord,
						  __in ULONG passWorfLen,
						  __in PVOID pextdata,
						  __in ULONG extlen,
						  __in PVOID reserve,
						  __in ULONG reservelen);


HRESULT ConvertFileFromZip(__in LPCWSTR dstPath,
						  __in LPCWSTR srcPath,
						  __in BOOL showProcDialog,
						  __in PVOID passWord,
						  __in ULONG passWorfLen,
						  __in PVOID pextdata,
						  __in ULONG extlen,
						  __in PVOID reserve,
						  __in ULONG reservelen);



#endif