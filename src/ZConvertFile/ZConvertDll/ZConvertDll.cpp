// ZConvertDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "ZConvertDll.h"
#include "../../common/include/ZShareMem.h"

#pragma comment(lib,"../../common/lib/ZShareMem.lib")//共享内存

#define MEMNAMELEN 256
#define MEMNAMEHEADER _T("Global\\ConvertFileMem_")

#define CONVERTEXE _T("ZConvertFile.exe")

ULONG g_exeIndex = 0;
DWORD g_pid = 0;

VOID getMemName(LPTSTR name,LPTSTR cmdLine)
{
	if (0 == g_pid)
	{
		g_pid = GetCurrentProcessId();
	}
	_stprintf(name,_T("%s%d_%08X_"),MEMNAMEHEADER,g_pid,g_exeIndex++);
	g_exeIndex = (g_exeIndex > 10000)?0:g_exeIndex;
	if (NULL != cmdLine)
	{
		_stprintf(cmdLine,_T("%s %s %s"),CONVERTEXE,CONVERT_CMD_OPTION_ENCRPT_BYMEM,name);
	}
}

HRESULT CreateExeAnNotify(__in ULONG optionType,
						  __in PVOID inputdata,
						  __in UINT inputlen,
						  __out PVOID outputdata,
						  __inout UINT &outputlen
						  )
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	TCHAR name[MEMNAMELEN] = {NULL};
	TCHAR cmdLine[MEMNAMELEN] = {NULL};
	getMemName(name,cmdLine);
	CZShareMem *memshare = CreateZShareMem();
	HRESULT state = memshare->InitShareMemCreator(name);
	if (ERROR_SUCCESS != state)
	{
		goto END;
	}

	// Start the child process. 
	if( !CreateProcess( NULL,  
		cmdLine,        
		NULL,           
		NULL,           
		FALSE,          
		0,              
		NULL,           
		NULL,           
		&si,           
		&pi )          
		) 
	{
		state =  GetLastError();
		goto END;
	}

	UINT msgType;
	UCHAR buf[MEM_BUF_SIZE] = {NULL};
	UINT bufsize = MEM_BUF_SIZE;
	state = memshare->ReadMsgByCreator(msgType,buf,bufsize);
	if (ERROR_SUCCESS != state)
	{
		goto END;
	}
	PWCHAR ExeMemName = (PWCHAR)buf;
	state = memshare->InitShareMemOpener(ExeMemName);
	if (ERROR_SUCCESS != state)
	{
		goto END;
	}

	state = memshare->WriteMsgByOpener(optionType,inputdata,inputlen);
	if (ERROR_SUCCESS != state)
	{
		goto END;
	}

	memset(buf,0,sizeof(buf));
	bufsize = MEM_BUF_SIZE;
	state = memshare->ReadMsgByCreator(msgType,buf,bufsize);
	if (ERROR_SUCCESS != state)
	{
		goto END;
	}

	state = msgType;
	if (NULL == outputdata)
	{
		goto END;
	}
	if (bufsize > outputlen)
	{
		state = ERROR_SUCCESS_BUT_BUFFERTOOSMALL;
	}
	memcpy(outputdata,buf,bufsize);
	outputlen = bufsize;
END:
	if ( pi.hProcess != NULL)
	{
		// Wait until child process exits.
		WaitForSingleObject( pi.hProcess, INFINITE );

		// Close process and thread handles. 
		CloseHandle( pi.hProcess );
		CloseHandle( pi.hThread );
	}

	if (NULL!=memshare)
	{
		delete memshare;
	}
	return state;
}


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
						)
{
	ZConvertData convertdata = {NULL};

	_tcscpy_s(convertdata.dstpath,sizeof(convertdata.dstpath),dstPath);
	_tcscpy_s(convertdata.srcpath,sizeof(convertdata.srcpath),srcPath);
	convertdata.optionType = optionType;
	convertdata.encyptType = encyptType;
	convertdata.showProcDialog = showProcDialog;
	memcpy(convertdata.passWord,passWord,passWorfLen);
	convertdata.passWorfLen = passWorfLen;
	memcpy(convertdata.extdata,pextdata,extlen);
	convertdata.extlen = extlen;
	memcpy(convertdata.reserve,reserve,reservelen);

	UINT n = 0;
	return CreateExeAnNotify(optionType,&convertdata,sizeof(convertdata),NULL,n);
}

HRESULT GetFileInfoInFile(__in LPCWSTR srcPath,__out WIN32_FIND_DATAA &filedata,__out PVOID extdata,__inout UINT &extlen)
{
	ZFileinfo fileinfo = {NULL};
	UINT infosize = sizeof(ZFileinfo);
	HRESULT state = CreateExeAnNotify(
		CONVERT_OPTIONCODE_GETINFO_FROMFILE,
		(PVOID)srcPath,
		(wcslen(srcPath) + 1) * sizeof(WCHAR),
		&fileinfo,
		infosize
		);

	if (ERROR_SUCCESS != state)
	{
		return state;
	}

	memcpy(&filedata,&fileinfo.fileData,sizeof(WIN32_FIND_DATAA));
	memcpy(extdata,fileinfo.extendData,fileinfo.extendLen);
	extlen = fileinfo.extendLen;
	return state;
}

HRESULT GetFileInfoInZip(__in LPCWSTR srcPath,__out WIN32_FIND_DATAA &filedata,__out PVOID extdata,__inout UINT &extlen)
{
	ZFileinfo fileinfo = {NULL};
	UINT infosize = sizeof(ZFileinfo);
	HRESULT state = CreateExeAnNotify(
		CONVERT_OPTIONCODE_GETINFO_FROMZIP,
		(PVOID)srcPath,
		(wcslen(srcPath) + 1) * sizeof(WCHAR),
		&fileinfo,
		infosize
		);

	if (ERROR_SUCCESS != state)
	{
		return state;
	}

	memcpy(&filedata,&fileinfo.fileData,sizeof(WIN32_FIND_DATAA));
	memcpy(extdata,fileinfo.extendData,fileinfo.extendLen);
	extlen = fileinfo.extendLen;
	return state;
}


HRESULT GetFileListInZip(__in LPCWSTR srcPath,std::vector<std::string> &namelist)
{
	ZZipListInfo ziplistinfo = {NULL};
	UINT size = sizeof(ZZipListInfo);
	HRESULT state = CreateExeAnNotify(
		CONVERT_OPTIONCODE_GETLIST_FROMZIP,
		(PVOID)srcPath,
		(wcslen(srcPath) + 1) * sizeof(WCHAR),
		&ziplistinfo,
		size
		);
	if (ERROR_SUCCESS != state)
	{
		return state;
	}

	UINT index = 0;
	for (int i=0;i<ziplistinfo.listcount;i++)
	{
		PCHAR pstr = ziplistinfo.listData + index;
		namelist.push_back(pstr);
		index = strlen(pstr) + 1;
	}
	return state;
}

HRESULT ConvertFileToFile(__in LPCWSTR dstPath, __in LPCWSTR srcPath, __in ULONG encyptType, __in BOOL showProcDialog, __in PVOID passWord, __in ULONG passWorfLen, __in PVOID pextdata, __in ULONG extlen, __in PVOID reserve, __in ULONG reservelen)
{
	return ConvertFileBase(dstPath,srcPath,CONVERT_OPTIONCODE_ENCRPT_TOFILE,encyptType,showProcDialog,passWord,passWorfLen,pextdata,extlen,reserve,reservelen);
}

HRESULT ConvertFileToZip(__in LPCWSTR dstPath, __in LPCWSTR srcPath, __in ULONG encyptType, __in BOOL showProcDialog, __in PVOID passWord, __in ULONG passWorfLen, __in PVOID pextdata, __in ULONG extlen, __in PVOID reserve, __in ULONG reservelen)
{
	return ConvertFileBase(dstPath,srcPath,CONVERT_OPTIONCODE_ENCRPT_TOZIP,encyptType,showProcDialog,passWord,passWorfLen,pextdata,extlen,reserve,reservelen);
}

HRESULT ConvertFileFromFile(__in LPCWSTR dstPath, __in LPCWSTR srcPath, __in BOOL showProcDialog, __in PVOID passWord, __in ULONG passWorfLen, __in PVOID pextdata, __in ULONG extlen, __in PVOID reserve, __in ULONG reservelen)
{
	return ConvertFileBase(dstPath,srcPath,CONVERT_OPTIONCODE_DECRPT_FROMFILE,NULL,showProcDialog,passWord,passWorfLen,pextdata,extlen,reserve,reservelen);
}

HRESULT ConvertFileFromZip(__in LPCWSTR dstPath, __in LPCWSTR srcPath, __in BOOL showProcDialog, __in PVOID passWord, __in ULONG passWorfLen, __in PVOID pextdata, __in ULONG extlen, __in PVOID reserve, __in ULONG reservelen)
{
	return ConvertFileBase(dstPath,srcPath,CONVERT_OPTIONCODE_DECRPT_FROMZIP,NULL,showProcDialog,passWord,passWorfLen,pextdata,extlen,reserve,reservelen);
}
