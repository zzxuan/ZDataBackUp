#pragma once


// CUi_Normal �Ի���

class CUi_Normal : public CDialog
{
	DECLARE_DYNAMIC(CUi_Normal)

public:
	CUi_Normal(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUi_Normal();

// �Ի�������
	enum { IDD = IDD_UI_NORMAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();


	CString m_fileName;
	CString m_passWord;
	CString m_passWord1;
	CComboBox m_cbEncrpt;
	BOOL m_isDeleteSource;
	BOOL m_isCompressFile;
	BOOL m_isShutDown;
};
