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
	if(m_configInstance == NULL)  //�ж��Ƿ��һ�ε���  
		m_configInstance = new CEncrptConfig();  
	return m_configInstance;  
}

VOID CEncrptConfig::Init()
{
	//��ʼ�������㷨�б�
	m_EncrptTypeMap[_T("RC4")] = ENCRYPT_RC4;
}


