#pragma once


// ZPrgDialog 对话框

class ZPrgDialog : public CDialog
{
	DECLARE_DYNAMIC(ZPrgDialog)

public:
	ZPrgDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ZPrgDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG_PRG };
	afx_msg LRESULT OnPrgChange(WPARAM wParam, LPARAM lParam); // add lyw
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
