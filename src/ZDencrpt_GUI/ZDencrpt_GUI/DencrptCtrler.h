#pragma once

class CDencrptCtrler
{
public:
	CDencrptCtrler(BOOL isShowMsg = TRUE);
	~CDencrptCtrler(void);

	HRESULT DencrptFile(CString srcPath,CString dstpath,CString password);

	HRESULT GetFileInfoInFile(
		__in LPCWSTR srcPath,
		__out WIN32_FIND_DATAA &filedata
		);

	BOOL m_isShowMsg;
};
