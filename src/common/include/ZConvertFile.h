// ZConvertFile.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CZConvertFileApp:
// �йش����ʵ�֣������ ZConvertFile.cpp
//

class CZConvertFileApp : public CWinApp
{
public:
	CZConvertFileApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CZConvertFileApp theApp;