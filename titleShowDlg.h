#pragma once


// titleShowDlg �Ի���

class titleShowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(titleShowDlg)

public:
	titleShowDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~titleShowDlg();

// �Ի�������
	enum { IDD = IDD_TITLETEMPLATE_SHOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	
public:
	virtual BOOL OnInitDialog();


	afx_msg void OnBnClickedButton1();
};
