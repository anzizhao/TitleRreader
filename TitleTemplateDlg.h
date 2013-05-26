#pragma once
#include <vector>


using namespace std; 

#include "titleShowDlg.h"
// TitleTemplateDlg 对话框

class TitleTemplateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TitleTemplateDlg)

public:
	TitleTemplateDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TitleTemplateDlg();

// 对话框数据
	enum { IDD = IDD_TITLETEMPLATE_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	static const CString m_titleContentDefine; 
	
private:
	int m_curTitle;
	bool m_changeTitle;
	unsigned int m_titleNum;
	// 标题模板
	vector<CString > m_titleTemplate;

	UINT m_titleNumPre; 
	vector< CString > m_titleTemplatePre;
	titleShowDlg m_titleShowDlg; 
public:
	virtual BOOL OnInitDialog();

	// 改变edit 组合框的内容
	void showTitle(void);
	// 浏览所有标题
	void showAllTitle(void);
	void InitTitle (void); 
	afx_msg void OnBnClickedTitlesetFirsttitle();
	afx_msg void OnBnClickedTitlesetPretitle();
	afx_msg void OnBnClickedTitlesetNexttitle();
	afx_msg void OnBnClickedTitlesetInserttitle();
	afx_msg void OnBnClickedTitlesetCleartitle();
	afx_msg void OnBnClickedTitlesetBigalpha();
	afx_msg void OnBnClickedTitlesetLittlealpha();
	afx_msg void OnBnClickedTitlesetNum();
	afx_msg void OnBnClickedTitlesetSamechar();
	afx_msg void OnBnClickedTitlesetAllstring();
	afx_msg void OnBnClickedTitlesetNextline();
	afx_msg void OnBnClickedTitlesetSpace();
	afx_msg void OnBnClickedTitlesetTitlecontent();
	afx_msg void OnBnClickedTitlesetInseretbutton();
	afx_msg void OnBnClickedTitlesetCanceltitle();

	afx_msg void OnBnClickedShowAllTitle(); 

	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	void changeTitleToShow( UINT curTitle , CString & showTitle);
	CString getTitle(UINT id);
	int getTitleSize(void);
};
