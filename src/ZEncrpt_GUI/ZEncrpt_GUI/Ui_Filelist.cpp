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
	DDX_Control(pDX,IDC_FILELIST,m_FileLstCtrl);
}


BEGIN_MESSAGE_MAP(CUi_Filelist, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


BOOL CUi_Filelist::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rect;   

	// 获取编程语言列表视图控件的位置和大小   
	m_FileLstCtrl.GetClientRect(&rect);   

	// 为列表视图控件添加全行选中和栅格风格   
	m_FileLstCtrl.SetExtendedStyle(m_FileLstCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   

	// 为列表视图控件添加三列   
	m_FileLstCtrl.InsertColumn(0, _T("全路径"), LVCFMT_CENTER, rect.Width()*2/3, 0);   
	m_FileLstCtrl.InsertColumn(1, _T("大小"), LVCFMT_CENTER, rect.Width()/6, 1);   
	m_FileLstCtrl.InsertColumn(2, _T("修改时间"), LVCFMT_CENTER, rect.Width()/6, 2); 

	// 在列表视图控件中插入列表项，并设置列表子项文本   
	m_FileLstCtrl.InsertItem(0, _T("Java"));   
	m_FileLstCtrl.SetItemText(0, 1, _T("1"));   
	m_FileLstCtrl.SetItemText(0, 2, _T("1"));   
	m_FileLstCtrl.InsertItem(1, _T("C"));   
	m_FileLstCtrl.SetItemText(1, 1, _T("2"));   
	m_FileLstCtrl.SetItemText(1, 2, _T("2"));   
	m_FileLstCtrl.InsertItem(2, _T("C#"));   
	m_FileLstCtrl.SetItemText(2, 1, _T("3"));   
	m_FileLstCtrl.SetItemText(2, 2, _T("6"));   
	m_FileLstCtrl.InsertItem(3, _T("C++"));   
	m_FileLstCtrl.SetItemText(3, 1, _T("4"));   
	m_FileLstCtrl.SetItemText(3, 2, _T("3"));   

	return TRUE;
}

HBRUSH CUi_Filelist::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return (HBRUSH)::GetStockObject(WHITE_BRUSH);  // 设置背景色
}



// CUi_Filelist 消息处理程序
