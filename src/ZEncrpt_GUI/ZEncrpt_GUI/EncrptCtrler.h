#pragma once
#include <vector>

class CEncrptCtrler
{
public:
	CEncrptCtrler(void);
	~CEncrptCtrler(void);

public:
	CString m_password;
	CString m_filePath;
	UINT	m_encrptType;
	BOOL	m_isshutDownOnFinish;
	BOOL	m_isdeleteOnFinish;
	BOOL	m_isSaveValue;
	std::vector<CString> m_srcFilelist;

	HRESULT	StartEncrpt();
	HRESULT	StopEncrpt();

private:
	HRESULT	EncrptThreadProc();

};
