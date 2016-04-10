// ZPrgDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "ZEncrpt_GUI.h"
#include "ZPrgDialog.h"


// ZPrgDialog 对话框

IMPLEMENT_DYNAMIC(ZPrgDialog, CDialog)

ZPrgDialog::ZPrgDialog(CWnd* pParent /*=NULL*/)
	: CDialog(ZPrgDialog::IDD, pParent)
{

}

ZPrgDialog::~ZPrgDialog()
{
}

void ZPrgDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ZPrgDialog, CDialog)
	ON_MESSAGE(WM_PRG_CHANGE, OnPrgChange)
END_MESSAGE_MAP()


BOOL ZPrgDialog::OnInitDialog()
{
	CProgressCtrl *myProCtrl2 = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS1);
	myProCtrl2->SetRange(0,100);
	return TRUE;
}



LRESULT ZPrgDialog::OnPrgChange( WPARAM wParam, LPARAM lParam )
{
	ULONG val = (ULONG)wParam;
	ULONG total = (ULONG)lParam;
	CProgressCtrl *myProCtrl2 = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS1);

	ULONG pos = ((double)val/(double)total) * 100;
	myProCtrl2->SetPos(pos);
	return 0;
}

// ZPrgDialog 消息处理程序
