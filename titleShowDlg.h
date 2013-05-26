#pragma once


// titleShowDlg 对话框

class titleShowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(titleShowDlg)

public:
	titleShowDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~titleShowDlg();

// 对话框数据
	enum { IDD = IDD_TITLETEMPLATE_SHOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	
public:
	virtual BOOL OnInitDialog();


	afx_msg void OnBnClickedButton1();
};
