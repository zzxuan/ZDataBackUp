#pragma once


// CUi_Normal 对话框

class CUi_Normal : public CDialog
{
	DECLARE_DYNAMIC(CUi_Normal)

public:
	CUi_Normal(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUi_Normal();

// 对话框数据
	enum { IDD = IDD_UI_NORMAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();


	CString m_fileName;
	CString m_passWord;
	CString m_passWord1;
	CComboBox m_cbEncrpt;
	BOOL m_isSaveValue;
	BOOL m_deleteOnFinish;
	BOOL m_isshutDownOnFinish;

	UINT getEncrptType();
};
