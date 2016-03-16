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
	m_FileLstCtrl.InsertColumn(0, _T("ȫ·��"), LVCFMT_CENTER, rect.Width()*2/3, 0);   
	m_FileLstCtrl.InsertColumn(1, _T("��С"), LVCFMT_CENTER, rect.Width()/6, 1);   
	m_FileLstCtrl.InsertColumn(2, _T("�޸�ʱ��"), LVCFMT_CENTER, rect.Width()/6, 2); 

	// ���б���ͼ�ؼ��в����б���������б������ı�   
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
	return (HBRUSH)::GetStockObject(WHITE_BRUSH);  // ���ñ���ɫ
}



// CUi_Filelist ��Ϣ�������
