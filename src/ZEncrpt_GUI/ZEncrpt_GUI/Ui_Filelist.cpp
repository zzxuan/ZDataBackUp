// Ui_Filelist.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ZEncrpt_GUI.h"
#include "Ui_Filelist.h"


// CUi_Filelist �Ի���

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

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_FileLstCtrl.GetClientRect(&rect);   

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_FileLstCtrl.SetExtendedStyle(m_FileLstCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   

	// Ϊ�б���ͼ�ؼ��������   
	m_FileLstCtrl.InsertColumn(0, _T("ȫ·��"), LVCFMT_CENTER, rect.Width()*3/5, 0);   
	m_FileLstCtrl.InsertColumn(1, _T("��С"), LVCFMT_CENTER, rect.Width()/5, 1);   
	m_FileLstCtrl.InsertColumn(2, _T("�޸�ʱ��"), LVCFMT_CENTER, rect.Width()/5, 2); 

	
	return TRUE;
}

HBRUSH CUi_Filelist::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return (HBRUSH)::GetStockObject(WHITE_BRUSH);  // ���ñ���ɫ
}


//����ļ�
// CUi_Filelist ��Ϣ�������

void CUi_Filelist::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CFileDialog dlg(TRUE); 
	if(dlg.DoModal() != IDOK) 
	{
		return;
	}

	//m_fileName = dlg.GetPathName();				//ȡ�ļ���ȫ�ƣ���������·����

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
		filesize.Format(_T("����4G"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
