#include "StdAfx.h"
#include "EncrptConfig.h"


CEncrptConfig * CEncrptConfig::m_configInstance;

CEncrptConfig::CEncrptConfig(void)
{
	Init();
}

CEncrptConfig::~CEncrptConfig(void)
{
}

CEncrptConfig * CEncrptConfig::GetInstance()
{
	if(m_configInstance == NULL)  //判断是否第一次调用  
		m_configInstance = new CEncrptConfig();  
	return m_configInstance;  
}

VOID CEncrptConfig::Init()
{
	//初始化加密算法列表
	m_EncrptTypeMap[_T("RC4")] = ENCRYPT_RC4;
}


