// ZEncrpt_GUI.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CZEncrpt_GUIApp:
// �йش����ʵ�֣������ ZEncrpt_GUI.cpp
//

class CZEncrpt_GUIApp : public CWinApp
{
public:
	CZEncrpt_GUIApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CZEncrpt_GUIApp theApp;