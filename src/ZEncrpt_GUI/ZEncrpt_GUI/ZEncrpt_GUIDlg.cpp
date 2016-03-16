// ZEncrpt_GUIDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ZEncrpt_GUI.h"
#include "ZEncrpt_GUIDlg.h"
#include "EncrptCtrler.h"

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


// CZEncrpt_GUIDlg �Ի���




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
END_MESSAGE_MAP()


// CZEncrpt_GUIDlg ��Ϣ��������

BOOL CZEncrpt_GUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵������ӵ�ϵͳ�˵��С�

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

	// TODO: �ڴ����Ӷ���ĳ�ʼ������

	//ΪTab Control��������ҳ��
	m_tab.InsertItem(0, _T("����ѡ��"));
	m_tab.InsertItem(1, _T("�ļ��б�"));

	//���������Ի���
	m_item_normal.Create(IDD_UI_NORMAL, &m_tab);
	m_item_filelist.Create(IDD_UI_FILELIST, &m_tab);
	//�趨��Tab����ʾ�ķ�Χ
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 20;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;
	m_item_normal.MoveWindow(&rc);
	m_item_filelist.MoveWindow(&rc);

	//�ѶԻ������ָ�뱣������
	pDialog[0] = &m_item_normal;
	pDialog[1] = &m_item_filelist;
	//��ʾ��ʼҳ��
	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);
	//���浱ǰѡ��
	m_CurSelTab = 0;




	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CZEncrpt_GUIDlg::OnPaint()
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
HCURSOR CZEncrpt_GUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CZEncrpt_GUIDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	//�ѵ�ǰ��ҳ����������
	pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
	//�õ��µ�ҳ������
	m_CurSelTab = m_tab.GetCurSel();
	//���µ�ҳ����ʾ����
	pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);
	*pResult = 0;
}

void CZEncrpt_GUIDlg::OnBnClickedOk()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	m_item_normal.UpdateData(TRUE);
	//����У��
	if (m_item_normal.m_fileName.GetLength() <= 0)
	{
		AfxMessageBox(_T("������һ����Ч·����"));
		return;
	}
	if (m_item_normal.m_passWord.GetLength() <= 0)
	{
		AfxMessageBox(_T("���벻��Ϊ�գ�"));
		return;
	}
	if (m_item_normal.m_passWord != m_item_normal.m_passWord1)
	{
		AfxMessageBox(_T("������������벻һ�£�"));
		return;
	}

	CEncrptCtrler ctrler;

	ctrler.m_encrptType = m_item_normal.getEncrptType();
	ctrler.m_filePath = m_item_normal.m_fileName;
	ctrler.m_isdeleteOnFinish = m_item_normal.m_deleteOnFinish;
	ctrler.m_isSaveValue = m_item_normal.m_isSaveValue;
	ctrler.m_isshutDownOnFinish = m_item_normal.m_isshutDownOnFinish;
	ctrler.m_password = m_item_normal.m_passWord;

	ctrler.StartEncrpt();

	OnOK();
}