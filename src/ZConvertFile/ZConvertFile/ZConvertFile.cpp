// ZConvertFile.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "ZConvertFile.h"
#include "ZConvertFileDlg.h"
#include "ZConvertCmd.h"
#include "../../common/include/zip.h"

#pragma comment(lib,"../../common/lib/minizlib.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CZConvertFileApp

BEGIN_MESSAGE_MAP(CZConvertFileApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CZConvertFileApp ����

CZConvertFileApp::CZConvertFileApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CZConvertFileApp ����

CZConvertFileApp theApp;


// CZConvertFileApp ��ʼ��

BOOL CZConvertFileApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	CZConvertCmd convert;
	convert.TransferCmdLine();

	//CZConvertFileDlg dlg;
	//m_pMainWnd = &dlg;
	//INT_PTR nResponse = dlg.DoModal();
	//if (nResponse == IDOK)
	//{
	//	// TODO: �ڴ˷��ô����ʱ��
	//	//  ��ȷ�������رնԻ���Ĵ���
	//}
	//else if (nResponse == IDCANCEL)
	//{
	//	// TODO: �ڴ˷��ô����ʱ��
	//	//  ��ȡ�������رնԻ���Ĵ���
	//}

	//// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	////  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
