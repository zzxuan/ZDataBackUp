// ZDencrpt.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CZDencrptApp:
// �йش����ʵ�֣������ ZDencrpt.cpp
//

class CZDencrptApp : public CWinApp
{
public:
	CZDencrptApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CZDencrptApp theApp;