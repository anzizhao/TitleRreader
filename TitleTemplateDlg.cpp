// TitleTemplateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "treeview.h"
#include "TitleTemplateDlg.h"
#include "afxdialogex.h"


// TitleTemplateDlg 对话框

IMPLEMENT_DYNAMIC(TitleTemplateDlg, CDialogEx)

const CString TitleTemplateDlg::m_titleContentDefine(_T("[标题内容]")); 

TitleTemplateDlg::TitleTemplateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(TitleTemplateDlg::IDD, pParent)
	, m_curTitle(0), m_titleShowDlg(this)
{

	InitTitle(); 
}

TitleTemplateDlg::~TitleTemplateDlg()
{
}

void TitleTemplateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(TitleTemplateDlg, CDialogEx)
	
	ON_BN_CLICKED(IDC_TITLESET_FIRSTTITLE, &TitleTemplateDlg::OnBnClickedTitlesetFirsttitle)
	ON_BN_CLICKED(IDC_TITLESET_PRETITLE, &TitleTemplateDlg::OnBnClickedTitlesetPretitle)
	ON_BN_CLICKED(IDC_TITLESET_NEXTTITLE, &TitleTemplateDlg::OnBnClickedTitlesetNexttitle)
	ON_BN_CLICKED(IDC_TITLESET_INSERTTITLE, &TitleTemplateDlg::OnBnClickedTitlesetInserttitle)
	ON_BN_CLICKED(IDC_TITLESET_CLEARTITLE, &TitleTemplateDlg::OnBnClickedTitlesetCleartitle)
	ON_BN_CLICKED(IDC_TITLESET_BIGALPHA, &TitleTemplateDlg::OnBnClickedTitlesetBigalpha)
	ON_BN_CLICKED(IDC_TITLESET_LITTLEALPHA, &TitleTemplateDlg::OnBnClickedTitlesetLittlealpha)
	ON_BN_CLICKED(IDC_TITLESET_NUM, &TitleTemplateDlg::OnBnClickedTitlesetNum)

	ON_BN_CLICKED(IDC_TITLESET_SAMECHAR, &TitleTemplateDlg::OnBnClickedTitlesetSamechar)
	ON_BN_CLICKED(IDC_TITLESET_ALLSTRING, &TitleTemplateDlg::OnBnClickedTitlesetAllstring)
	ON_BN_CLICKED(IDC_TITLESET_NEXTLINE, &TitleTemplateDlg::OnBnClickedTitlesetNextline)
	ON_BN_CLICKED(IDC_TITLESET_SPACE, &TitleTemplateDlg::OnBnClickedTitlesetSpace)
	ON_BN_CLICKED(IDC_TITLESET_TITLECONTENT, &TitleTemplateDlg::OnBnClickedTitlesetTitlecontent)
	ON_BN_CLICKED(IDC_TITLESET_INSERETBUTTON, &TitleTemplateDlg::OnBnClickedTitlesetInseretbutton)
	
	ON_BN_CLICKED(IDC_TITLESET_CANCELTITLE, &TitleTemplateDlg::OnBnClickedTitlesetCanceltitle)
	ON_BN_CLICKED ( IDC_TITLESET_ALLTITLE, &TitleTemplateDlg::OnBnClickedShowAllTitle  )
	ON_BN_CLICKED(IDC_CANCEL, &TitleTemplateDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &TitleTemplateDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// TitleTemplateDlg 消息处理程序


BOOL TitleTemplateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// 开始提供第一标题
	m_titleTemplatePre = m_titleTemplate; 
	m_titleNumPre = m_titleNum; 

	m_curTitle = 0; 
	m_changeTitle = true;
	showTitle(); 
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}




// 改变edit 组合框的内容
void TitleTemplateDlg::showTitle(void)
{
	CWnd *pWnd; 
	// 显示框文字变化
	if ( m_changeTitle )
	{
		pWnd = this->GetDlgItem ( IDC_STATIC_TITLENUMSHOW ); 
		pWnd->SetWindowTextW ( _T("") ); 
		CString titleNumShow; 
		if ( m_titleNum )
			titleNumShow.Format( _T("第%d级标题"), m_curTitle + 1 );  
		else 
			titleNumShow.Format(_T("没有标题，请先插入")); 
		pWnd->SetWindowTextW ( titleNumShow ); 
		m_changeTitle = false; 
	}


	pWnd = this->GetDlgItem ( IDC_TITLESET_TITLESHOW ); 
	pWnd->SetWindowTextW ( _T("") ); 
	CString toShow; 
	changeTitleToShow ( m_curTitle, toShow ); 
	
	pWnd->SetWindowTextW ( toShow ); 

}


// 浏览所有标题
void TitleTemplateDlg::showAllTitle(void)
{
}

void TitleTemplateDlg::InitTitle(void)
{
	m_titleTemplate.clear(); 
	m_titleTemplate.push_back( CString(_T("\\d\\. [标题内容]"))); 
	m_curTitle = 0;
	m_titleNum = 1; 
}


void TitleTemplateDlg::OnBnClickedTitlesetFirsttitle()
{
	// TODO: 在此添加控件通知处理程序代码
	// 没有标题模板什么也不做
	if ( m_titleNum == 0 )
		return ; 

	m_curTitle = 0; 
	m_changeTitle = true; 
	showTitle(); 
}


void TitleTemplateDlg::OnBnClickedTitlesetPretitle()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( m_curTitle > 0 )
	{
		-- m_curTitle ; 
		m_changeTitle = true; 
		showTitle(); 
	}
}


void TitleTemplateDlg::OnBnClickedTitlesetNexttitle()
{
	// TODO: 在此添加控件通知处理程序代码
	// 标题模板非空 且 非最后一项
	if ( m_titleNum &&  m_curTitle  < (m_titleNum - 1) )
	{
		m_curTitle ++; 
		m_changeTitle = true; 
		showTitle (); 
	}
}


void TitleTemplateDlg::OnBnClickedTitlesetInserttitle()
{
	// TODO: 在此添加控件通知处理程序代码
	// 如果vector空间不够 插入
	if ( m_titleNum >= m_titleTemplate.size() )
	{
	      m_titleTemplate.push_back ( CString(_T(""))); 
	}
	for ( int i=m_titleNum-1;  i > m_curTitle ; i-- )
	{
		m_titleTemplate[i+1] = m_titleTemplate[i]; 
	}
	m_curTitle ++; 
	m_titleTemplate[m_curTitle] = _T(""); 
	m_titleNum ++; 
	// 插入后 显示最新的title
	m_changeTitle = true; 
	showTitle (); 
}


void TitleTemplateDlg::OnBnClickedTitlesetCleartitle()
{
	// TODO: 在此添加控件通知处理程序代码
	// 没有title模板 或现在不在任何标题上
	if ( ! m_titleNum || m_curTitle == -1  )
		return ; 
	if ( m_curTitle < m_titleNum  )
	{
		m_titleTemplate[m_curTitle] = _T(""); 
		m_changeTitle = true; 
		showTitle(); 
	}
	
}


void TitleTemplateDlg::OnBnClickedTitlesetBigalpha()
{
	// TODO: 在此添加控件通知处理程序代码
	// m_curTitle 是 m_titleTemplate 的有效下标，函数外得到确保。
	if ( m_curTitle == -1 )
	{
		
		MessageBoxW ( _T("please insert title firstly .")); 
		return ; 
	}
	// 
	CString *title =  &  m_titleTemplate[m_curTitle]; 
	if ( title->Right( _tcsclen( _T("[A-Z]+"))) != _T("[A-Z]+") )
		*title += _T("[A-Z]+"); 
	showTitle(); 
}


void TitleTemplateDlg::OnBnClickedTitlesetLittlealpha()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( m_curTitle == -1 )
	{
		MessageBoxW ( _T("please insert title firstly.")); 
		return ; 
	}
	// 
	CString *title =  &  m_titleTemplate[m_curTitle]; 
	if ( title->Right( _tcsclen( _T("[a-z]+"))) != _T("[a-z]+") )
		*title += _T("[a-z]+"); 

	showTitle(); 
}




void TitleTemplateDlg::OnBnClickedTitlesetNum()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( m_curTitle == -1 )
	{
		MessageBoxW ( _T("please insert title firstly.")); 
		return ; 
	}
	// 
	CString *title =  &  m_titleTemplate[m_curTitle]; 
	if ( title->Right( _tcsclen( _T("\\d+"))) != _T("\\d+") )
		*title += _T("\\d+"); 
	
	showTitle(); 
}





void TitleTemplateDlg::OnBnClickedTitlesetSamechar()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( m_curTitle == -1 )
	{
		MessageBoxW ( _T("please insert title firstly.")); 
		return ; 
	}
	// 

	m_titleTemplate[m_curTitle] += _T("+");
	showTitle(); 
}



void TitleTemplateDlg::OnBnClickedTitlesetAllstring()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( m_curTitle == -1 )
	{
		MessageBoxW ( _T("please insert title firstly.")); 
		return ; 
	}
	// 
	CString *title =  &  m_titleTemplate[m_curTitle]; 
	if ( title->Right( _tcsclen( _T(".+"))) != _T(".+") )
		*title += _T(".+"); 
	
	showTitle(); 
}



void TitleTemplateDlg::OnBnClickedTitlesetNextline()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( m_curTitle == -1 )
	{
		MessageBoxW ( _T("please insert title firstly.")); 
		return ; 
	}
	// 
	
	m_titleTemplate[m_curTitle] += _T("\r?\n");
	showTitle(); 
}




void TitleTemplateDlg::OnBnClickedTitlesetSpace()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( m_curTitle == -1 )
	{
		MessageBoxW ( _T("please insert title firstly.")); 
		return ; 
	}
	// 
	CString *title =  &  m_titleTemplate[m_curTitle]; 
	if ( title->Right( _tcsclen( _T("[ \\t]+"))) != _T("[ \\t]+") )
		*title += _T("[ \\t]+"); 
	
	showTitle(); 
}




void TitleTemplateDlg::OnBnClickedTitlesetTitlecontent()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( m_curTitle == -1 )
	{
		MessageBoxW ( _T("please insert title firstly.")); 
		return ; 
	}
	// 
	
	m_titleTemplate[m_curTitle] += _T("[标题内容]");
	showTitle(); 
}


void TitleTemplateDlg::OnBnClickedTitlesetInseretbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( m_curTitle == -1 )
	{
		MessageBoxW ( _T("please insert title firstly.")); 
		return ; 
	}
	

	CWnd *pWnd = this->GetDlgItem( IDC_TITLESET_INSERTCHAR ); 
	CString editText, nonEscape; 
	
	pWnd->GetWindowTextW(  editText ); 
	UINT pos = 0; 
	CString *title =  &  m_titleTemplate[m_curTitle]; 
	while ( pos < editText.GetLength() )
	{
		TCHAR textChar = editText.GetAt(pos ++); 
		switch ( textChar ) 
		{
		case _T('['):
		case _T('\\'):
		case _T('.'):
		case _T('+'):
		case _T('*'):
		case _T(']'):
			*title += _T('\\'); 
			*title +=  textChar ;
			break; 
		default:
			*title +=  textChar; 

		}
	}
	
	showTitle(); 
}

void TitleTemplateDlg::OnBnClickedShowAllTitle ()
{
	 m_titleShowDlg.DoModal(); 
	
}
//void TitleTemplateDlg::OnBnClickedButton1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//
//}


void TitleTemplateDlg::OnBnClickedTitlesetCanceltitle()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( m_titleNum == 0 )
	{
		return ; 
	}
	for ( int i=m_curTitle; i<m_titleNum-1; i++ )
		m_titleTemplate[i] = m_titleTemplate[i+1]; 
	m_titleTemplate[m_titleNum-1] = _T(""); 
	// 删除的是最后一个
	if ( m_curTitle == m_titleNum-1 )
		m_curTitle -= 1; 
	m_titleNum --; 
	m_changeTitle = true; 
	showTitle (); 
}


void TitleTemplateDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_titleTemplate = m_titleTemplatePre; 
	m_titleNum = m_titleNumPre; 
	CDialogEx::OnCancel();
}


void TitleTemplateDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_titleTemplatePre = m_titleTemplate; 
	m_titleNumPre = m_titleNum; 
	CDialogEx::OnOK();
}


void TitleTemplateDlg::changeTitleToShow( UINT id, CString & showTitle)
{
	const CString findCharSet(_T("[\\.+\n\r")); 
	CString *curTitle = &m_titleTemplate[id]; 
	CString tempTile;
	showTitle = _T("") ;
	int pos; 
	// 方括号的内容
	CString squareContent, preContent ; 
	while ( ( pos =  curTitle->FindOneOf ( findCharSet )) != -1 )
	{
		  
		showTitle += curTitle->Left(pos); 
		switch ( curTitle->GetAt(pos) ) {
		case _T('['):
			int endPos; 
			endPos = curTitle->Find( _T(']'), ++pos ); 
			if ( endPos == -1 )
			{
				MessageBoxW ( _T("title标题组成错误\n") +  *curTitle );  
				return ;  
			}
			squareContent = curTitle->Mid(pos , endPos - pos );
			if ( squareContent == _T("A-Z") )
			{
				showTitle += _T("A"); 
			}
			else if ( squareContent == _T("a-z") )
			{
				showTitle += _T("a"); 
			}
			else if ( squareContent == _T(" \\t") )
			{ 
				showTitle += _T(" "); 
			}
			else if ( squareContent == _T("标题内容") )
			{
				showTitle += _T("标题内容"); 
			}
			else 
			{
				MessageBoxW ( _T("title标题组成错误\n") +  *curTitle );  
				return ;
			}
			pos = endPos ;
			if ( curTitle->GetAt(pos+1) == _T('+') )
				pos ++ ;

			break; 

		case _T('\\'):
			++ pos ; 
			if ( curTitle->GetAt(pos) == _T('d') )
				{
					showTitle += _T("1");
					if ( pos + 1 < curTitle->GetLength() && curTitle->GetAt(pos+1) == _T('+') )
					{
						++pos; 
					}
					break; 
				}
			if ( curTitle->GetAt(pos) == _T('+') )
					showTitle += _T("+"); 
			else if ( curTitle->GetAt(pos) == _T('.') )
					showTitle += _T(".");	
			else if ( curTitle->GetAt(pos) == _T('[') )
					showTitle += _T("[");
			else if ( curTitle->GetAt(pos) == _T('\\') )
					showTitle += _T("\\");
			else if ( curTitle->GetAt(pos) == _T(']') )
					showTitle += _T("]");
			else if ( curTitle->GetAt(pos) == _T('*') )
					showTitle += _T("*");
			if ( pos + 1 < curTitle->GetLength() && curTitle->GetAt(pos+1) == _T('+') )
			{
				showTitle += _T("..."); 
				showTitle += curTitle->GetAt(pos); 
				++ pos; 
			}
			break; 
		case _T('.'):
			// 后面肯定跟+
			if ( ++pos  < curTitle->GetLength() && curTitle->GetAt(pos) == _T('+') )
			{
				showTitle += _T("****"); 
			}
			break; 
		case _T('+'):
			// ]+ .+ has operator above
			
			//showTitle += curTitle->GetAt(pos-1);
			showTitle += _T("..."); 
			showTitle += curTitle->GetAt(pos-1); 
			break ;

		case _T('\r'):
			pos += 2; 
		case _T('\n'):
			showTitle += _T("\r\n");
			break; 

		}
		// 到title的结尾的时候 跳出
		if ( ++pos >=  curTitle->GetLength() )
			break ; 
		CString temp = curTitle->Right( curTitle->GetLength() - pos ); 
		tempTile = temp ; 
		curTitle = &tempTile; 
	}
	// 非末尾处理
	if ( pos < curTitle->GetLength() )
		showTitle += *curTitle; 

}


CString TitleTemplateDlg::getTitle(UINT id)
{
	if ( id < m_titleNum )
		return m_titleTemplate[id]; 

	return CString();
}


int TitleTemplateDlg::getTitleSize(void)
{
	return m_titleNum;
}
