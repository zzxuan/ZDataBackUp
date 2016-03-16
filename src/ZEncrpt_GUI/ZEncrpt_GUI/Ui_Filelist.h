#pragma once


// CUi_Filelist 对话框

class CUi_Filelist : public CDialog
{
	DECLARE_DYNAMIC(CUi_Filelist)

public:
	CUi_Filelist(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUi_Filelist();

// 对话框数据
	enum { IDD = IDD_UI_FILELIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();
public:
	CListCtrl m_FileLstCtrl;
};
