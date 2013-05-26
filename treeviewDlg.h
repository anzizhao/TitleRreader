
// treeviewDlg.h : 头文件
//
#include "TitleTemplateDlg.h"
#include <vector>
using namespace std; 
#pragma once


// 记录原始控件的大小
struct DlgContorlRectFactor {
	CRect treeCtlF;             //树控件
	CRect editCtlF;             //编辑控件
	CRect openfileButF;         //打开文件按钮
	CRect cancelButF;           //删除按钮
	CRect setTitleButF;         // 设置title按钮

}; 

// CtreeviewDlg 对话框
class CtreeviewDlg : public CDialogEx
{
// 构造
public:
	CtreeviewDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TREEVIEW_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	


	afx_msg void OnBnClickedFileOpen();
	afx_msg void OnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	bool readUnicodeFile(FILE *fp );
//	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVscrollEdit1();
	bool readFile(const CString& filename);
	bool readAsciiFile(FILE * fp);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void MoveContorlAlongDlg( CWnd *pWnd , const CRect & contorlRect, const CRect & dlgRect);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();

protected:
	void InitRectFactor(void);
	bool AnalyseToTree(void);
	bool testRegexp(void); 
	// 判断是否title的标志
	bool IsTitleMark(const CString & line);

private:
	CString m_editStr;
	CEdit m_edit;
	CTreeCtrl m_treeCtl;

	TitleTemplateDlg m_titleSet;
	CRect m_preRect;
	DlgContorlRectFactor m_rectFactors;	
	bool m_treeCtl2Edit;
	bool m_edit2TreeCtl;
	vector<UINT> m_posMapLine; 
public:
	LPTSTR strchrRT(LPTSTR pStart, LPTSTR pIncludeEnd, TCHAR tc);
//	void _AnalyseToTree(UINT posStart);
protected:
	void AnalyseToTree(UINT posStart, UINT posEnd, HTREEITEM treeID, UINT titlePos);
public:
	int AnalyseTitleTemplate(int pos, CString &beforeTag, CString& afterTag );
	// 使用前向标签定位
	void AnalyseBB(UINT posStart, UINT posEnd, HTREEITEM treeID, UINT titlePos , CString & beforeTag, CString & afterTag);
	void AnalyseBA(UINT posStart, UINT posEnd, HTREEITEM treeID, UINT titlePos , CString & afterTag);
	
	// 字符位置对应的行数
	int posInLine(UINT pos);
protected:
	int makePosMap(void);
};
