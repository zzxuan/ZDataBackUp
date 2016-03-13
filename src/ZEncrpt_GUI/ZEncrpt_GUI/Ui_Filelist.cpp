// Ui_Filelist.cpp : 实现文件
//

#include "stdafx.h"
#include "ZEncrpt_GUI.h"
#include "Ui_Filelist.h"


// CUi_Filelist 对话框

IMPLEMENT_DYNAMIC(CUi_Filelist, CDialog)

CUi_Filelist::CUi_Filelist(CWnd* pParent /*=NULL*/)
	: CDialog(CUi_Filelist::IDD, pParent)
{

}

CUi_Filelist::~CUi_Filelist()
{
}

void CUi_Filelist::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUi_Filelist, CDialog)
END_MESSAGE_MAP()


// CUi_Filelist 消息处理程序
