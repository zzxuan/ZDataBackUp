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
	DDX_Text(pDX, IDC_EDIT1, m_fileName);  
	DDX_Text(pDX, IDC_EDIT2, m_passWord); 
	DDX_Text(pDX, IDC_EDIT3, m_passWord1); 
	DDX_Control(pDX,IDC_COMBO1,m_cbEncrpt);
	DDX_Check(pDX, IDC_CHECK1, m_isSaveValue); 
	DDX_Check(pDX, IDC_CHECK2, m_deleteOnFinish); 
	DDX_Check(pDX, IDC_CHECK5, m_isshutDownOnFinish); 
}


BEGIN_MESSAGE_MAP(CUi_Normal, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON2, &CUi_Normal::OnBnClickedButton2)
END_MESSAGE_MAP()

BOOL CUi_Normal::OnInitDialog()
{
	CDialog::OnInitDialog();

	ENCRPTMAP * pEncrptMap = &(CEncrptConfig::GetInstance()->m_EncrptTypeMap);
	for (ENCRPTMAP::iterator it = pEncrptMap->begin();
		it != pEncrptMap->end();
		it++
		)
	{
		m_cbEncrpt.AddString(it->first);
	}
	m_cbEncrpt.SelectString(0,pEncrptMap->begin()->first);
	return TRUE;
}

HBRUSH CUi_Normal::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return (HBRUSH)::GetStockObject(WHITE_BRUSH);  // ���ñ���ɫ
}


// CUi_Normal ��Ϣ�������
//���
void CUi_Normal::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CFileDialog dlg(
			FALSE, 
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

UINT CUi_Normal::getEncrptType()
{
	UINT enctpye = ENCRYPT_RC4;
	CString strstatus;
	m_cbEncrpt.GetLBText(m_cbEncrpt.GetCurSel(), strstatus);
	ENCRPTMAP *encmap = &(CEncrptConfig::GetInstance()->m_EncrptTypeMap);
	if (encmap->find(strstatus) != encmap->end())
	{
		enctpye = (*encmap)[strstatus];
	}
	return enctpye;
}
