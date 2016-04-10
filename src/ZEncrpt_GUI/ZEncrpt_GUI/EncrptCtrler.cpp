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
		return ZConvertFileToFile(
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
			CString dst = m_filePath + _T(".zip");
			CString str(m_srcFilelist[i]);
			int n = str.ReverseFind(_T('\\'));
			TCHAR name[MAX_PATH] = {NULL};
			_tcscpy_s(name,str.GetBuffer() + n + 1);
			TCHAR * pstr = _tcsrchr(name,_T('.'));
			if (NULL != pstr)
			{
				_tcscpy_s(pstr,MAX_PATH - _tcslen(name),_T(".zenc"));
			}
			else
			{
				_tcscat_s(name,MAX_PATH ,ENCYFILE_EXT);
			}
			dst += _T("&");
			dst += name;

			WCHAR * pass = m_password.GetBuffer();
			UINT len = m_password.GetLength() * sizeof(WCHAR);
			ZConvertFileToZip(
				dst,
				str,
				m_encrptType,
				FALSE,
				pass,
				len,
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
