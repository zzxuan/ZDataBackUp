// Ui_Normal.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ZEncrpt_GUI.h"
#include "Ui_Normal.h"


// CUi_Normal �Ի���

IMPLEMENT_DYNAMIC(CUi_Normal, CDialog)

CUi_Normal::CUi_Normal(CWnd* pParent /*=NULL*/)
	: CDialog(CUi_Normal::IDD, pParent)
{

}

CUi_Normal::~CUi_Normal()
{
}

void CUi_Normal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUi_Normal, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BOOL CUi_Normal::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;
}

HBRUSH CUi_Normal::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return (HBRUSH)::GetStockObject(WHITE_BRUSH);  // ���ñ���ɫ
}


// CUi_Normal ��Ϣ�������
