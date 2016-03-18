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
	ON_BN_CLICKED(IDC_BUTTON1, &CUi_Filelist::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUi_Filelist::OnBnClickedButton2)
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
	m_FileLstCtrl.InsertColumn(0, _T("全路径"), LVCFMT_CENTER, rect.Width()*3/5, 0);   
	m_FileLstCtrl.InsertColumn(1, _T("大小"), LVCFMT_CENTER, rect.Width()/5, 1);   
	m_FileLstCtrl.InsertColumn(2, _T("修改时间"), LVCFMT_CENTER, rect.Width()/5, 2); 

	
	return TRUE;
}

HBRUSH CUi_Filelist::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return (HBRUSH)::GetStockObject(WHITE_BRUSH);  // 设置背景色
}


//添加文件
// CUi_Filelist 消息处理程序

void CUi_Filelist::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CFileDialog dlg(TRUE); 
	if(dlg.DoModal() != IDOK) 
	{
		return;
	}

	//m_fileName = dlg.GetPathName();				//取文件名全称，包括完整路径。

	AddFileToList(dlg.GetPathName());
	UpdateData(FALSE); 
}

VOID CUi_Filelist::AddFileToList(CString &fileName)
{
	WIN32_FIND_DATA finddata;
	HANDLE findhand = FindFirstFile(fileName,&finddata);
	if (INVALID_HANDLE_VALUE == findhand)
	{
		return;
	}
	FindClose(findhand);

	m_FileLstCtrl.InsertItem(0,fileName);
	
	CString filesize;
	if (finddata.nFileSizeHigh > 0)
	{
		filesize.Format(_T("大于4G"));
	}
	else if (finddata.nFileSizeLow > 1024*1024*1024)
	{
		filesize.Format(_T("%.2f G"),((double)finddata.nFileSizeLow)/(1024*1024*1024));
	}
	else if (finddata.nFileSizeLow > 1024*1024)
	{
		filesize.Format(_T("%.2f M"),((double)finddata.nFileSizeLow)/(1024*1024));
	}
	else
	{
		filesize.Format(_T("%.2f K"),((double)finddata.nFileSizeLow)/(1024));
	}
	m_FileLstCtrl.SetItemText(0,1,filesize);

	CTime time(finddata.ftLastWriteTime);
	m_FileLstCtrl.SetItemText(0,2,time.Format(_T("%y-%m-%d %H:%M")));

}

void CUi_Filelist::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_FileLstCtrl.DeleteItem(m_FileLstCtrl.GetSelectionMark());
}

VOID CUi_Filelist::GetFileList(std::vector<CString> &filelist)
{
	UpdateData(TRUE);
	int count = m_FileLstCtrl.GetItemCount();
	for (int i = 0;i<count;i++)
	{
		CString filename;
		filename = m_FileLstCtrl.GetItemText(i,0);
		filelist.push_back(filename);
	}
}
