#include "StdAfx.h"
#include "DencrptCtrler.h"
#include "../../common/include/ZConvertDllBase.h"
#include "../../common/include/ConverHelper.h"

#pragma comment(lib,"../../common/lib/ZConvertDllBase.lib")

CDencrptCtrler::CDencrptCtrler(BOOL isShowMsg)
{
	m_isShowMsg = isShowMsg;
}

CDencrptCtrler::~CDencrptCtrler(void)
{
}

HRESULT CDencrptCtrler::DencrptFile( CString srcPath,CString dstpath,CString password )
{
	HRESULT bstate = ZConvertFileFromFile(
		dstpath,
		srcPath,
		FALSE,
		password.GetBuffer(),
		password.GetLength() * sizeof(TCHAR),
		NULL,0,
		NULL,0
		);

	if (S_OK == bstate)
	{
		return bstate;
	}
	if (ERROR_INVALID_PASSWORD == bstate)
	{
		if (m_isShowMsg)
		{
			AfxMessageBox(_T("√‹¬Î¥ÌŒÛ"));
		}
		
		return bstate;
	}

	SetLastError(bstate);
	if (m_isShowMsg)
	{
		ShowLastErrMsg();
	}
	return bstate;
}

HRESULT CDencrptCtrler::GetFileInfoInFile( __in LPCWSTR srcPath, __out WIN32_FIND_DATAA &filedata)
{
	UCHAR extdata[2048] = {NULL};
	UINT extlen=sizeof(extdata);
	return ZGetFileInfoInFile(srcPath,filedata,extdata,extlen);
}
