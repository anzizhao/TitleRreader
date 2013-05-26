// titleShowDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "treeview.h"
#include "titleShowDlg.h"
#include "TitleTemplateDlg.h"
#include "afxdialogex.h"


// titleShowDlg �Ի���

IMPLEMENT_DYNAMIC(titleShowDlg, CDialogEx)

titleShowDlg::titleShowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(titleShowDlg::IDD, pParent)
{

}

titleShowDlg::~titleShowDlg()
{
}

void titleShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(titleShowDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &titleShowDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// titleShowDlg ��Ϣ�������


BOOL titleShowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CWnd *pWnd = this->GetDlgItem( IDC_SHOWTITLE_STATICSHOW ); 
	pWnd->SetWindowTextW ( _T("") ); 
	CString showAllTitle, showTitle; 
	TitleTemplateDlg *ttdlg = ( TitleTemplateDlg *)this->m_pParentWnd; 
	for ( int i=0; i< ttdlg->getTitleSize(); i++ )
	{
		ttdlg->changeTitleToShow( i ,showTitle ); 
		for ( int j=i; j>0; j-- )
			showAllTitle += _T('  '); 
		showAllTitle +=  showTitle ;
		showAllTitle.AppendFormat( _T(" ����%d�����⣩"), i+1 );
		showAllTitle += _T("\r\n"); 
	}
	pWnd->SetWindowTextW ( showAllTitle ); 
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void titleShowDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
