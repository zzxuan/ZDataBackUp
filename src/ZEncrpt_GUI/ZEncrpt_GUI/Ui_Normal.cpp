// Ui_Normal.cpp : 实现文件
//

#include "stdafx.h"
#include "ZEncrpt_GUI.h"
#include "Ui_Normal.h"


// CUi_Normal 对话框

IMPLEMENT_DYNAMIC(CUi_Normal, CDialog)

CUi_Normal::CUi_Normal(CWnd* pParent /*=NULL*/)
	: CDialog(CUi_Normal::IDD, pParent)
{

}

CUi_Normal::~CUi_Normal()
{
}

void CUi_Normal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUi_Normal, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BOOL CUi_Normal::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;
}

HBRUSH CUi_Normal::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return (HBRUSH)::GetStockObject(WHITE_BRUSH);  // 设置背景色
}


// CUi_Normal 消息处理程序
