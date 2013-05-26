
// treeviewDlg.h : ͷ�ļ�
//
#include "TitleTemplateDlg.h"
#include <vector>
using namespace std; 
#pragma once


// ��¼ԭʼ�ؼ��Ĵ�С
struct DlgContorlRectFactor {
	CRect treeCtlF;             //���ؼ�
	CRect editCtlF;             //�༭�ؼ�
	CRect openfileButF;         //���ļ���ť
	CRect cancelButF;           //ɾ����ť
	CRect setTitleButF;         // ����title��ť

}; 

// CtreeviewDlg �Ի���
class CtreeviewDlg : public CDialogEx
{
// ����
public:
	CtreeviewDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TREEVIEW_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	// �ж��Ƿ�title�ı�־
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
	// ʹ��ǰ���ǩ��λ
	void AnalyseBB(UINT posStart, UINT posEnd, HTREEITEM treeID, UINT titlePos , CString & beforeTag, CString & afterTag);
	void AnalyseBA(UINT posStart, UINT posEnd, HTREEITEM treeID, UINT titlePos , CString & afterTag);
	
	// �ַ�λ�ö�Ӧ������
	int posInLine(UINT pos);
protected:
	int makePosMap(void);
};
