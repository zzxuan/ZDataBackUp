#pragma once

#include <map>

typedef std::map<CString,UINT> ENCRPTMAP;

class CEncrptConfig
{
private:
	static CEncrptConfig *m_configInstance;
private:
	CEncrptConfig(void);
	~CEncrptConfig(void);

	VOID Init();

public:  
	static CEncrptConfig * GetInstance(); 
	 
	ENCRPTMAP m_EncrptTypeMap;
};
