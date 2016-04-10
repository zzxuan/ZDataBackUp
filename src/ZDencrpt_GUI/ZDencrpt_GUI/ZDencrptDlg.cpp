// ZDencrptDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CZDencrptDlg �Ի���




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


// CZDencrptDlg ��Ϣ�������

BOOL CZDencrptDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CZDencrptDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CZDencrptDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//���
void CZDencrptDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	m_fileName = dlg.GetPathName();				//ȡ�ļ���ȫ�ƣ���������·����

	UpdateData(FALSE); 
}

void CZDencrptDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (!PathFileExists(m_fileName))
	{
		AfxMessageBox(_T("�ļ�������"));
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

//����
void CZDencrptDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (!PathFileExists(m_fileName))
	{
		AfxMessageBox(_T("�ļ�������"));
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

	CString dstpath = dlg.GetPathName();				//ȡ�ļ���ȫ�ƣ���������·����
	
	if(S_OK == ctrl.DencrptFile(m_fileName,dstpath,m_passWord))
	{
		OnOK();
	}
}
