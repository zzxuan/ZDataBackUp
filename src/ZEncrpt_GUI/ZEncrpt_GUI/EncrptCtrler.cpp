#include "StdAfx.h"
#include "EncrptCtrler.h"

#include "../../common/include/ZConvertDllBase.h"
#include "../../common/include/ConverHelper.h"

#pragma comment(lib,"../../common/lib/ZConvertDllBase.lib")

DWORD golable_EncrptThreadProc(LPARAM pargram)
{
	return ((CEncrptCtrler *)pargram)->EncrptThreadProc();
}

VOID WINAPI golable_EncPrg(ULONG val,ULONG total,PVOID handle)
{
	((CEncrptCtrler *)handle)->EncPorgess(val,total);
}

CEncrptCtrler::CEncrptCtrler(void)
{
	m_prgDlg = NULL;
}

CEncrptCtrler::~CEncrptCtrler(void)
{
}

HRESULT CEncrptCtrler::EncrptThreadProc()
{
	HRESULT state = S_OK;
	if (m_srcFilelist.size() == 1)//只有一个文件直接加密
	{
		state = ZConvertFileToFile(
			m_filePath.GetBuffer(),
			m_srcFilelist[0].GetBuffer(),
			m_encrptType,
			FALSE,
			m_password.GetBuffer(),
			m_password.GetLength() * sizeof(WCHAR),
			NULL,0,
			NULL,0,
			golable_EncPrg,
			this
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
			state = ZConvertFileToZip(
				dst,
				str,
				m_encrptType,
				FALSE,
				pass,
				len,
				NULL,0,
				NULL,0,
				golable_EncPrg,
				this
				);
			if (S_OK != state)
			{
				SetLastError(state);
				break;
			}
		}
	}

	if (S_OK != state)
	{
		SetLastError(state);
		ShowLastErrMsg();
	}
	
	if (NULL != m_prgDlg)
	{
		HWND hwnd = m_prgDlg->GetSafeHwnd();
		if (NULL != hwnd)
		{
			SendMessage(hwnd,WM_CLOSE,NULL,NULL);
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

VOID CEncrptCtrler::EncPorgess( ULONG val,ULONG total)
{
	if (NULL != m_prgDlg)
	{
		HWND hwnd = m_prgDlg->GetSafeHwnd();
		if (NULL != hwnd)
		{
			SendMessage(hwnd,WM_PRG_CHANGE,val,total);
		}
	}
}
