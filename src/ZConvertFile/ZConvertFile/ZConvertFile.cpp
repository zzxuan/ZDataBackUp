// ZConvertFile.cpp : 定义应用程序的类行为。
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


// CZConvertFileApp 构造

CZConvertFileApp::CZConvertFileApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CZConvertFileApp 对象

CZConvertFileApp theApp;


// CZConvertFileApp 初始化

BOOL CZConvertFileApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
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
	//	// TODO: 在此放置处理何时用
	//	//  “确定”来关闭对话框的代码
	//}
	//else if (nResponse == IDCANCEL)
	//{
	//	// TODO: 在此放置处理何时用
	//	//  “取消”来关闭对话框的代码
	//}

	//// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	////  而不是启动应用程序的消息泵。
	return FALSE;
}
