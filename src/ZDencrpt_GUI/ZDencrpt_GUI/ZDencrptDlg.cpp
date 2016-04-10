// ZDencrptDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ZDencrpt.h"
#include "ZDencrptDlg.h"
#include "DencrptCtrler.h"
#include <shlwapi.h>
#include "..\..\common\include\ConverHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CZDencrptDlg 对话框




CZDencrptDlg::CZDencrptDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZDencrptDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZDencrptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_fileName);  
	DDX_Text(pDX, IDC_EDIT2, m_passWord); 
}

BEGIN_MESSAGE_MAP(CZDencrptDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON2, &CZDencrptDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &CZDencrptDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CZDencrptDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CZDencrptDlg 消息处理程序

BOOL CZDencrptDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CZDencrptDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CZDencrptDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CZDencrptDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//浏览
void CZDencrptDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CFileDialog dlg(
		TRUE, 
		_T("zenc"), 
		_T("*.zenc"),
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		_T("*.zenc")
		); 
	if(dlg.DoModal() != IDOK) 
	{
		return;
	}

	m_fileName = dlg.GetPathName();				//取文件名全称，包括完整路径。

	UpdateData(FALSE); 
}

void CZDencrptDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (!PathFileExists(m_fileName))
	{
		AfxMessageBox(_T("文件不存在"));
		return;
	}
	CDencrptCtrler ctrl;
	WIN32_FIND_DATAA filedata;
	HRESULT state = ctrl.GetFileInfoInFile(m_fileName,filedata);

	if (S_OK != state)
	{
		SetLastError(state);
		ShowLastErrMsg();
		return ;
	}

	WCHAR fileName[MAX_PATH] = {NULL};
	MultiByteToWideChar(CP_ACP,0,filedata.cFileName,strlen(filedata.cFileName)+1,fileName,sizeof(fileName));

	TCHAR fileTmpPath[MAX_PATH] = _T("C:\\ProgramData\\ZDataback\\");
	TCHAR winPath[MAX_PATH] = {NULL};
	GetWindowsDirectory(winPath,sizeof(winPath));
	fileTmpPath[0] = winPath[0];
	if (!PathFileExists(fileTmpPath))
	{
		if(!CreateDirectory(fileTmpPath,NULL))
		{
			ShowLastErrMsg();
			return;
		}
	}
	_tcscat_s(fileTmpPath,fileName);

	if(S_OK != ctrl.DencrptFile(m_fileName,fileTmpPath,m_passWord))
	{
		return;
	}

	
	ShellExecute(NULL,_T("open"),fileTmpPath,NULL,NULL, SW_SHOW );

	OnOK();
}

//解密
void CZDencrptDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (!PathFileExists(m_fileName))
	{
		AfxMessageBox(_T("文件不存在"));
		return;
	}
	CDencrptCtrler ctrl;
	WIN32_FIND_DATAA filedata;
	HRESULT state = ctrl.GetFileInfoInFile(m_fileName,filedata);

	if (S_OK != state)
	{
		SetLastError(state);
		ShowLastErrMsg();
		return ;
	}

	WCHAR fileName[MAX_PATH] = {NULL};
	MultiByteToWideChar(CP_ACP,0,filedata.cFileName,strlen(filedata.cFileName)+1,fileName,sizeof(fileName));

	CFileDialog dlg(
		FALSE, 
		NULL, 
		fileName,
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT
		); 
	if(dlg.DoModal() != IDOK) 
	{
		return;
	}

	CString dstpath = dlg.GetPathName();				//取文件名全称，包括完整路径。
	
	if(S_OK == ctrl.DencrptFile(m_fileName,dstpath,m_passWord))
	{
		OnOK();
	}
}
