// ZEncrpt_GUIDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ZEncrpt_GUI.h"
#include "ZEncrpt_GUIDlg.h"
#include "EncrptCtrler.h"
#include "ZPrgDialog.h"

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


// CZEncrpt_GUIDlg 对话框




CZEncrpt_GUIDlg::CZEncrpt_GUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZEncrpt_GUIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZEncrpt_GUIDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_TAB_MAIN, m_tab);
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CZEncrpt_GUIDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CZEncrpt_GUIDlg::OnTcnSelchangeTab)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CZEncrpt_GUIDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CZEncrpt_GUIDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CZEncrpt_GUIDlg 消息处理程序

BOOL CZEncrpt_GUIDlg::OnInitDialog()
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

	//为Tab Control增加两个页面
	m_tab.InsertItem(0, _T("常规选项"));
	m_tab.InsertItem(1, _T("文件列表"));

	//创建两个对话框
	m_item_normal.Create(IDD_UI_NORMAL, &m_tab);
	m_item_filelist.Create(IDD_UI_FILELIST, &m_tab);
	//设定在Tab内显示的范围
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 20;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;
	m_item_normal.MoveWindow(&rc);
	m_item_filelist.MoveWindow(&rc);

	//把对话框对象指针保存起来
	pDialog[0] = &m_item_normal;
	pDialog[1] = &m_item_filelist;
	//显示初始页面
	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);
	//保存当前选择
	m_CurSelTab = 0;




	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CZEncrpt_GUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CZEncrpt_GUIDlg::OnPaint()
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
HCURSOR CZEncrpt_GUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CZEncrpt_GUIDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	//把当前的页面隐藏起来
	pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
	//得到新的页面索引
	m_CurSelTab = m_tab.GetCurSel();
	//把新的页面显示出来
	pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);
	*pResult = 0;
}



void CZEncrpt_GUIDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_item_normal.UpdateData(TRUE);
	//这里校验
	if (m_item_normal.m_fileName.GetLength() <= 0)
	{
		AfxMessageBox(_T("请输入一个有效路径！"));
		return;
	}
	if (m_item_normal.m_passWord.GetLength() <= 0)
	{
		AfxMessageBox(_T("密码不能为空！"));
		return;
	}
	if (m_item_normal.m_passWord != m_item_normal.m_passWord1)
	{
		AfxMessageBox(_T("两次输入的密码不一致！"));
		return;
	}

	
	CEncrptCtrler ctrler;
	ctrler.m_encrptType = m_item_normal.getEncrptType();
	ctrler.m_filePath = m_item_normal.m_fileName;
	ctrler.m_isdeleteOnFinish = m_item_normal.m_deleteOnFinish;
	ctrler.m_isSaveValue = m_item_normal.m_isSaveValue;
	ctrler.m_isshutDownOnFinish = m_item_normal.m_isshutDownOnFinish;
	ctrler.m_password = m_item_normal.m_passWord;

	m_item_filelist.GetFileList(ctrler.m_srcFilelist);

	if (ctrler.m_srcFilelist.size() == 0)
	{
		AfxMessageBox(_T("请选择源文件！"));
		return;
	}
	this->ShowWindow(SW_HIDE);
	ZPrgDialog prg;
	ctrler.m_prgDlg = &prg;
	ctrler.StartEncrpt();
	prg.DoModal();
	OnOK();
}

void CZEncrpt_GUIDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
