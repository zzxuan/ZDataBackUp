#include "StdAfx.h"
#include "EncrptCtrler.h"

#include "../../common/include/ZConvertDllBase.h"

#pragma comment(lib,"../../common/lib/ZConvertDllBase.lib")

DWORD golable_EncrptThreadProc(LPARAM pargram)
{
	return ((CEncrptCtrler *)pargram)->EncrptThreadProc();
}

CEncrptCtrler::CEncrptCtrler(void)
{
}

CEncrptCtrler::~CEncrptCtrler(void)
{
}

HRESULT CEncrptCtrler::EncrptThreadProc()
{
	if (m_srcFilelist.size() == 1)//只有一个文件直接加密
	{
		return ConvertFileToFileDll(
			m_filePath.GetBuffer(),
			m_srcFilelist[0].GetBuffer(),
			m_encrptType,
			TRUE,
			m_password.GetBuffer(),
			m_password.GetLength() * sizeof(WCHAR),
			NULL,0,
			NULL,0
			);
	}
	else
	{
		for (int i=0;i<m_srcFilelist.size();i++)
		{
			ConvertFileToZipDll(
				m_filePath.GetBuffer(),
				m_srcFilelist[i].GetBuffer(),
				m_encrptType,
				TRUE,
				m_password.GetBuffer(),
				m_password.GetLength() * sizeof(WCHAR),
				NULL,0,
				NULL,0
				);
		}
	}
	

	return S_OK;
}

HRESULT CEncrptCtrler::StopEncrpt()
{
	return S_OK;
}

HRESULT CEncrptCtrler::StartEncrpt()
{
	CloseHandle(
		CreateThread(
		NULL,NULL,(LPTHREAD_START_ROUTINE)golable_EncrptThreadProc,this,NULL,NULL
		));
	return S_OK;
}
