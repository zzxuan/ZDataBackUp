#pragma once


// ZPrgDialog �Ի���

class ZPrgDialog : public CDialog
{
	DECLARE_DYNAMIC(ZPrgDialog)

public:
	ZPrgDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ZPrgDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_PRG };
	afx_msg LRESULT OnPrgChange(WPARAM wParam, LPARAM lParam); // add lyw
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
