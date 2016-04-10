#ifndef __ZCONVERTDLLBASE__H__
#define __ZCONVERTDLLBASE__H__
#include <vector>

typedef VOID (WINAPI *PConvertProgress)(ULONG val,ULONG total);

HRESULT ZConvertFileBase(
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
						   __in ULONG reservelen,
						   __in PConvertProgress pConvertPrg = NULL
						   );

HRESULT ZGetFileInfoInFile(
							 __in LPCWSTR srcPath,
							 __out WIN32_FIND_DATAA &filedata,
							 __out PVOID extdata,
							 __inout UINT &extlen
							 );
HRESULT ZGetFileInfoInZip(__in LPCWSTR srcPath,
							__out WIN32_FIND_DATAA &filedata,
							__out PVOID extdata,
							__inout UINT &extlen
							);
HRESULT ZGetFileListInZip(__in LPCWSTR srcPath,
							std::vector<std::string> &namelist
							);

HRESULT ZConvertFileToFile(__in LPCWSTR dstPath,
							 __in LPCWSTR srcPath,
							 __in ULONG encyptType,
							 __in BOOL showProcDialog,
							 __in PVOID passWord,
							 __in ULONG passWorfLen,
							 __in PVOID pextdata,
							 __in ULONG extlen,
							 __in PVOID reserve,
							 __in ULONG reservelen,
							 __in PConvertProgress pConvertPrg = NULL);

HRESULT ZConvertFileToZip(__in LPCWSTR dstPath,
							__in LPCWSTR srcPath,
							__in ULONG encyptType,
							__in BOOL showProcDialog,
							__in PVOID passWord,
							__in ULONG passWorfLen,
							__in PVOID pextdata,
							__in ULONG extlen,
							__in PVOID reserve,
							__in ULONG reservelen,
							__in PConvertProgress pConvertPrg = NULL);


HRESULT ZConvertFileFromFile(__in LPCWSTR dstPath,
							   __in LPCWSTR srcPath,
							   __in BOOL showProcDialog,
							   __in PVOID passWord,
							   __in ULONG passWorfLen,
							   __in PVOID pextdata,
							   __in ULONG extlen,
							   __in PVOID reserve,
							   __in ULONG reservelen,
							   __in PConvertProgress pConvertPrg = NULL);


HRESULT ZConvertFileFromZip(__in LPCWSTR dstPath,
							  __in LPCWSTR srcPath,
							  __in BOOL showProcDialog,
							  __in PVOID passWord,
							  __in ULONG passWorfLen,
							  __in PVOID pextdata,
							  __in ULONG extlen,
							  __in PVOID reserve,
							  __in ULONG reservelen,
							  __in PConvertProgress pConvertPrg = NULL);

#endif