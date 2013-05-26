
// treeviewDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "treeview.h"
#include "treeviewDlg.h"
#include "afxdialogex.h"

#include <tchar.h>

#include <fstream>
#include <string>
#include <cassert>
#include <cstdio>
#include "deelx.h"
#include <algorithm>
using namespace std; 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtreeviewDlg 对话框




CtreeviewDlg::CtreeviewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtreeviewDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CtreeviewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_treeCtl);
	//  DDX_Control(pDX, IDC_EDIT1, m_editDisplay);
	DDX_Text (pDX, IDC_EDIT1, m_editStr ); 
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}

BEGIN_MESSAGE_MAP(CtreeviewDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CtreeviewDlg::OnBnClickedOk)
	ON_BN_CLICKED(ID_FILE_OPEN, &CtreeviewDlg::OnBnClickedFileOpen)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CtreeviewDlg::OnSelchangedTree1)
//	ON_WM_VSCROLL()
	ON_EN_VSCROLL(IDC_EDIT1, &CtreeviewDlg::OnVscrollEdit1)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &CtreeviewDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &CtreeviewDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CtreeviewDlg 消息处理程序

BOOL CtreeviewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//m_edit.EnableScrollBar(); 
	
	//m_edit.EnableWindow(false); 
	//m_treeCtl.EnableWindow(false); 
	m_treeCtl.SetTextColor(RGB(10,10,10));
	m_treeCtl.SetBkColor ( RGB(200, 200, 200)); 
	m_treeCtl2Edit = false; 
	m_edit2TreeCtl = false;

	InitRectFactor(); 
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CtreeviewDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtreeviewDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	/*if ( ! m_preRect.Width() && ! m_preRect.Height()  )
		InitRectFactor(); */
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CtreeviewDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtreeviewDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CtreeviewDlg::OnBnClickedFileOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("*.txt|*.*||"),this);
	if (fDlg.DoModal()==IDOK)
	{
		m_editStr = _T(""); 
		fDlg.DestroyWindow();
		readFile( fDlg.GetPathName() ); 
	//	testRegexp(); 
		AnalyseToTree(); 
	//	m_edit.EnableWindow(true); 
		UpdateData(false); 
		this->SetWindowTextW( fDlg.GetPathName()); 

	//	m_edit.SetWindowTextW( m_editStr); 
	}	
}

bool CtreeviewDlg::AnalyseToTree(void)
{
	
	if ( m_editStr.IsEmpty() )
		return true; 
	// ready the tree control 
	m_treeCtl.DeleteAllItems(); 
	AnalyseToTree ( 0, m_editStr.GetLength(), TVI_ROOT , 0 ); 
	m_treeCtl.SetFocus();
	return true; 
}

//bool CtreeviewDlg::AnalyseToTree(void)
//{
//	// if empty, nothing to done 
//	if ( m_editStr.IsEmpty() )
//			return true; 
//	// ready the tree control 
//	// 
//// #define  UINT unsigned int
//	//m_treeCtl.EnableWindow(true); 
//	m_treeCtl.DeleteAllItems(); 
//	int pos = 0; 
//	
//	LPTSTR pszbuffer = m_editStr.GetBuffer( m_editStr.GetLength() ); 
//	
//	pair<LPTSTR, LPTSTR> curLine, preLine ; 
//	curLine = make_pair( pszbuffer ,pszbuffer ); 
//	preLine = make_pair((LPTSTR) NULL,(LPTSTR) NULL); 
//	int lineCount = 0 ; 
//	HTREEITEM defaultItem = NULL ; 
//	while ( (curLine.second = _tcschr( curLine.first , _T('\n') )) != NULL  ) 
//	{
//		lineCount ++; 
//		CString curStr(curLine.first, curLine.second-curLine.first ); 
//		if ( IsTitleMark(curStr) && preLine.first != NULL  )
//		{
//			// yes , deal with the title.
//			HTREEITEM treeItem; 
//			CString title (preLine.first, preLine.second-preLine.first );
//			treeItem = m_treeCtl.InsertItem(  title , 0, 0, TVI_ROOT); 
//			m_treeCtl.SetItemData( treeItem, (DWORD_PTR) lineCount-1 );
//			if ( ! defaultItem )
//			{
//				defaultItem = treeItem ; 
//				m_treeCtl.SelectItem( defaultItem);		
//			}
//		}
//		preLine = curLine; 	
//		curLine.first =  curLine.second + 1  ; 
//	}
//	// the last line didn't judge .
//	if ( IsTitleMark(CString( curLine.first, pszbuffer+m_editStr.GetLength()-curLine.first )) && preLine.first != NULL  )
//		{
//			// yes , deal with the title.
//			lineCount ++; 
//			HTREEITEM treeItem; 
//			CString title (preLine.first, preLine.second-preLine.first );
//			treeItem = m_treeCtl.InsertItem(  title , 0, 0, TVI_ROOT); 
//			m_treeCtl.SetItemData( treeItem, (DWORD_PTR) lineCount-1 ); 
//		}
//	// 
//	// m_treeCtl.Select( defaultItem, TVGN_CARET); 
//	m_treeCtl.SetFocus(); 
//	return true; 
//}



	


// 判断是否title的标志
bool CtreeviewDlg::IsTitleMark(const CString & line)
{
	// set the char flag 
	TCHAR titleChar(_T('\0')); 

	switch ( line.GetAt(0) ){
	case _T('-'):
		titleChar =  _T('-'); 
		break ;
	case _T('='):
		titleChar =  _T('='); 
		break ; 
	default:
		return false; 
	} 
	UINT len = line.GetLength(); 
	CString compareStr;
	while (  --len )
	{
		compareStr +=  titleChar; 
	}
	// maybe the \r in the last , if the system is Windows; 
	// deal with it specially; 
	if ( line.GetAt( line.GetLength()-1) == _T('\r') )
		compareStr += _T('\r'); 
	else 
		compareStr +=  titleChar ; 

	if ( line == compareStr )
		return true;

	return false; 
}


void CtreeviewDlg::OnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	if ( m_edit2TreeCtl ){
		m_edit2TreeCtl = false; 
		return ; 
	}
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	HTREEITEM SelItem;
	SelItem=m_treeCtl.GetSelectedItem();//获取选中的子项
	DWORD_PTR line;
	line =m_treeCtl.GetItemData(SelItem);//读取子项的值
	
	UINT curLine = m_edit.GetFirstVisibleLine(); 
	// 移动
	m_treeCtl2Edit = true; 
	m_edit.LineScroll( line - curLine  ); 

	
}


bool CtreeviewDlg::readUnicodeFile(FILE *fp )
{
	//FILE *fp ;
	ULONG fileSize = 0 ; 
	ULONG fileSizeW = 0; 
	//_tfopen_s ( &fp, filename, _T("rb") );

	fseek ( fp, 0, SEEK_END );
	// the size is the number of byte. should ignore the unicode flag, 0xFEFF or 0xFFFE
	fileSize  = ftell(fp) - 2 ; 
	fileSizeW = fileSize /  (sizeof(wchar_t) / sizeof(char)); 
	// 跳过开头的标志
	fseek ( fp, 2, SEEK_SET );
	
	// CString use wchar_t to storage the data. 
	LPTSTR pszBuffer = m_editStr.GetBuffer( fileSizeW ); 
	fread( pszBuffer, sizeof(wchar_t), fileSizeW, fp ); 
	m_editStr.ReleaseBuffer(); 
	// add '\0', because it will be the C string operation.  
	m_editStr.Append( _T('\0')); 
	return true; 
}




void CtreeviewDlg::OnVscrollEdit1()
{
	// if the scroll message from the tree contorl select , it will do nothing . 
	if ( m_treeCtl2Edit ){
		m_treeCtl2Edit = false;	 
		return ; 
	}
	// TODO: 在此添加控件通知处理程序代码
	UINT editMarkLine  = m_edit.GetFirstVisibleLine(); 

	HTREEITEM selItem = m_treeCtl.GetSelectedItem(); 
	ULONG treeMarkLine  = m_treeCtl.GetItemData( selItem ); 
	// treeCtl已经跟edit有关联，加上edit与treeCtl的关联就可以
	if ( treeMarkLine == editMarkLine + 1 )
		return ; 
	if ( treeMarkLine > editMarkLine + 1 )
	{
		// not after the select tree, set to the first 
		//m_treeCtl.GetNextItem( )
		//m_treeCtl.SelectItem(TVI_ROOT); 
		selItem = m_treeCtl.GetNextItem(TVI_ROOT, TVGN_CHILD ); 
		treeMarkLine = m_treeCtl.GetItemData( selItem ); 
		if ( treeMarkLine > editMarkLine )
			// there is no titl at first. 
			return ; 
			//assert(false); 
	}
	
	ULONG preMarkLine = treeMarkLine;  
	HTREEITEM preSelItem = selItem; 

	for ( HTREEITEM temp = m_treeCtl.GetNextItem(selItem, TVGN_NEXT); temp != NULL ; )
	{

		treeMarkLine = m_treeCtl.GetItemData( temp  );
		if ( treeMarkLine > editMarkLine )
		{
			// the first edit line is between this two tree title.
			m_edit2TreeCtl = true; 
			m_treeCtl.SelectItem( preSelItem); 
			break ;
		}
		preSelItem = temp ; 
		temp = m_treeCtl.GetNextItem(temp, TVGN_NEXT); 

	}
	
}


bool CtreeviewDlg::readFile(const CString& filename)
{
	FILE *fp ;
	_tfopen_s ( &fp, filename, _T("rb") );
	WORD unicodeFlag = 0; 
	if ( fread( &unicodeFlag, sizeof(WORD), 1, fp ) == 1 )
	{
		// 小字节unicode file 
		if ( (unicodeFlag >> 8) == 0xFE &&  (unicodeFlag &0x00FF ) == 0xFF ) 
			readUnicodeFile (fp); 
		// 大字节unicode file 
		else if ( (unicodeFlag >> 8) == 0xFF &&  (unicodeFlag &0x00FF ) == 0xFE )
			readUnicodeFile ( fp ); 
		else 
			readAsciiFile ( fp );
		fclose(fp); 
		return true; 
	}
	fclose(fp); 
//	_tfclose_s(fp); 
	return false;
}


bool CtreeviewDlg::readAsciiFile(FILE * fp)
{
	ULONG fileSize = 0 ; 
	fseek ( fp, 0, SEEK_END );
	fileSize = ftell ( fp ); 
	rewind(fp); 
	char *pszBuffer; 
	pszBuffer = (char *) malloc ( sizeof(char)*(fileSize+1) ); 
	if ( ! pszBuffer )
		MessageBox ( _T("Wrong to malloc") ); 
	if ( fread(pszBuffer, sizeof(char), fileSize, fp ) != fileSize )
		assert(false);  
	pszBuffer[fileSize] = '\0'; 
	m_editStr = _T(""); 

	ULONG lenW = MultiByteToWideChar(CP_ACP, 0, pszBuffer, -1, NULL, 0); 
	ULONG lackLineR = 0;
	char *p = pszBuffer; 
	while ( (p = strchr( p, '\n')) != NULL )
	{
		if ( *(p-1) != '\r' )
			lackLineR ++;	
		++ p ; 
	}
	LPTSTR pszBufferW ; 
	if ( lackLineR == 0 )
	{
		 pszBufferW  = m_editStr.GetBuffer( lenW ); 
		 MultiByteToWideChar(CP_ACP, 0, pszBuffer, -1, pszBufferW, lenW );
	} else {
		 pszBufferW  = m_editStr.GetBuffer( lenW + lackLineR ); 
		
		 char *pcur, *pnext;
		 pcur =  pszBuffer;
		 while ( (pnext = strchr( pcur , '\n')) != NULL )
		 {
			 // space line 
			 if ( pnext != pcur  )
			{
				ULONG lineLen = MultiByteToWideChar(CP_ACP, 0, pcur, pnext-pcur-1, NULL, 0 );
				MultiByteToWideChar(CP_ACP, 0, pcur, pnext-pcur-1, pszBufferW, lineLen  );
				pszBufferW += lineLen  ;  
			 }
			if ( *(pnext-1) != '\r' )
			{
				// add \r 
				*(pszBufferW ) = _T('\r');
				pszBufferW += 1; 
			}
			*(pszBufferW ) = _T('\n'); 
			pszBufferW += 1; 
			pcur = pnext + 1; 
		 }
		 ULONG lineLen = MultiByteToWideChar(CP_ACP, 0, pcur, -1, NULL, 0 );
		 MultiByteToWideChar(CP_ACP, 0, pcur, -1, pszBufferW, lineLen  );
	}
	m_editStr.ReleaseBuffer();  
	free( pszBuffer ); 
	return true;
}


void CtreeviewDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	
	// TODO: 在此处添加消息处理程序代码

	if ( ! m_preRect.Width() && ! m_preRect.Height()  )
		return ; 
	 
	CRect rect, rectWnd; 
	int left , top, width, height; 
	CRect *opRect , preRect ;
	GetWindowRect ( &rectWnd );	
	if ( nType == SIZE_MAXIMIZED   )
	{	
		GetClientRect ( &rect ); 
	// redraw treectl 
		float widthMultiply , heightMultiply; 
		widthMultiply = (float) rect.Width() / m_preRect.Width() ;
		heightMultiply = ( float ) rect.Height() /m_preRect.Height(); 

		// redraw open file button 
		CWnd *pWnd = GetDlgItem ( ID_FILE_OPEN );
		opRect = &m_rectFactors.openfileButF ; 
		left = opRect->left * widthMultiply + rect.left ; 
		top  = rect.bottom - ( m_preRect.bottom - opRect->top );  ;  		
		pWnd->MoveWindow ( left , top , opRect->Width(), opRect->Height() ); 

		// redraw cancle button 
		pWnd = GetDlgItem ( IDCANCEL  ); 
		opRect = & m_rectFactors.cancelButF ; 
		left = opRect->left * widthMultiply + rect.left; 
		pWnd->MoveWindow ( left  , top  , opRect->Width(), opRect->Height() );
		pWnd->GetWindowRect ( &preRect ); 
		this->ScreenToClient ( &preRect ); 
		// redraw tree contorl 
		opRect = & m_rectFactors.treeCtlF; 
		left = opRect->left;
		top = opRect->top ; 
		width = opRect->Width() * widthMultiply * 0.7; 
		height = preRect.top  - top ; 
		m_treeCtl.MoveWindow( left, top, width, height );
		m_treeCtl.GetWindowRect ( &preRect ); 
		this->ScreenToClient ( &preRect ); 
		// redraw edit
		opRect = & m_rectFactors.editCtlF ; 
		left = preRect.right + opRect->left - m_rectFactors.treeCtlF.right  ;
		width = rect.right - left; 
		m_edit.MoveWindow ( left, top, width, height  ); 
		
	}
	else if (  nType == SIZE_RESTORED ) 
	{
		
		opRect = & m_rectFactors.treeCtlF; 
		m_treeCtl.MoveWindow ( opRect->left , opRect->top  , opRect->Width()  , opRect->Height() ); 
		opRect = & m_rectFactors.editCtlF ; 
		m_edit.MoveWindow( opRect->left , opRect->top  , opRect->Width()  , opRect->Height() ); 

		CWnd *pWnd = GetDlgItem ( ID_FILE_OPEN ); 
		opRect = &m_rectFactors.openfileButF ; 
		pWnd->MoveWindow ( opRect->left, opRect->top   , opRect->Width()  , opRect->Height() );

		pWnd = GetDlgItem ( IDCANCEL  ); 
		opRect = & m_rectFactors.cancelButF ; 
		pWnd->MoveWindow ( opRect->left , opRect->top   , opRect->Width()  , opRect->Height() );
	//	pWnd->MoveWindow ( opRect->left + rectWnd.left , opRect->top + rectWnd.top  , opRect->Width()  , opRect->Height() );
	}
	
}


void CtreeviewDlg::InitRectFactor(void)
{


	this->GetClientRect ( &m_preRect ); 
	
	m_edit.GetWindowRect ( &m_rectFactors.editCtlF );
	this->ScreenToClient ( &m_rectFactors.editCtlF ); 

	m_treeCtl.GetWindowRect ( &m_rectFactors.treeCtlF ); 
	this->ScreenToClient (  &m_rectFactors.treeCtlF );

	CWnd *pWnd = GetDlgItem ( ID_FILE_OPEN );
	pWnd->GetWindowRect ( &m_rectFactors.openfileButF  );
	this->ScreenToClient ( &m_rectFactors.openfileButF ); 

	pWnd = GetDlgItem ( IDCANCEL  ); 
	pWnd->GetWindowRect ( &m_rectFactors.cancelButF );  
	this->ScreenToClient (  &m_rectFactors.cancelButF );  
}


void CtreeviewDlg::MoveContorlAlongDlg( CWnd *pWnd , const CRect & contorlRect, const CRect & dlgRect)
{
	int left , top , width, height ;
	left = contorlRect.left - m_preRect.left + dlgRect.left; 
	top = contorlRect.top - m_preRect.top + dlgRect.top; 
	width =  dlgRect.Width () - ( m_preRect.Width()-contorlRect.Width() ); 
	height = dlgRect.Height() - ( m_preRect.Height() - contorlRect.Height() ); 
	pWnd->MoveWindow ( left, top , width, height ); 
}


void CtreeviewDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( m_titleSet.DoModal() == IDOK )
	{
		return ; 
	}
	else 
	{
		
	}
	
}


void CtreeviewDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

bool CtreeviewDlg::testRegexp(void)
{
	CRegexpT<TCHAR>  regexp( _T("\n-+\r?\n"), SINGLELINE); 
	LPTSTR pszStr = (LPTSTR)m_editStr.GetString(); 
	UINT start = 0; 
	MatchResult result = regexp.Match( pszStr );
	CString toShow ; 
	while(result.IsMatched())
	{
		// print found
		LPCTSTR pTitleStart; 
		if ( ( pTitleStart = strchrRT ( pszStr+start, pszStr + result.GetStart()-1, _T('\n'))) == NULL ) 
			this->MessageBoxW ( _T("No title content ")); 
		else {
			toShow.AppendFormat( _T("%.*s\r\n"),  pszStr + result.GetStart() - pTitleStart , pTitleStart ); 
		}
		start = result.GetEnd(); 
		// find next
		result = regexp.Match(pszStr, result.GetEnd());
	}
	this->MessageBoxW( toShow ); 
	return true; 
}

//在pStart和pIncludeEnd一段区域里反向搜素字符tc
LPTSTR CtreeviewDlg::strchrRT(LPTSTR pStart, LPTSTR pIncludeEnd, TCHAR tc)
{
	TCHAR temp = *pIncludeEnd; 
	LPTSTR  result; 
	*pIncludeEnd = _T('\0'); 
	result = _tcsrchr( pStart, tc );
	*pIncludeEnd = temp ; 
	return result ;
}


// 处理同标题的


void CtreeviewDlg::AnalyseToTree(UINT posStart, UINT posEnd, HTREEITEM treeID, UINT titlePos )
{
	
	if ( titlePos > m_titleSet.getTitleSize()-1 )
		return ; 
// 分析title模板， 分成 beforeTag ， titleContent， afterTag
	CString beforeTag, afterTag; 
	AnalyseTitleTemplate( titlePos, beforeTag, afterTag ); 
	// 根据前向标签是否为空，使用不同分析方法
	if ( ! beforeTag.IsEmpty() )
	{ 
		AnalyseBB ( posStart, posEnd, treeID, titlePos,  beforeTag, afterTag ); 
	
	}
	else 
	{
		AnalyseBA ( posStart, posEnd, treeID, titlePos, afterTag ); 
	}

}


int CtreeviewDlg::AnalyseTitleTemplate(int pos, CString& beforeTag, CString &afterTag )
{
	const  CString *tcTemplate = & m_titleSet.m_titleContentDefine; 
	int titleStart, titleEnd; 
	CString titles = m_titleSet.getTitle ( pos ); 
	titleStart = titles.Find ( *tcTemplate ); 
	afterTag = beforeTag = _T("");
	// titleStart == 0 表示没有beforeTag
	if ( titleStart > 0 )
	{
		beforeTag.AppendFormat( _T("%.*s"), titleStart-1, (LPTSTR)titles.GetBuffer()); 
	}
	else if ( titleStart == -1 )
	{
		this->MessageBoxW( _T( "title template has no title content "));
		assert(false); 
	}
	else 
		titleStart = 0; 
	titleEnd = tcTemplate->GetLength() + titleStart; 
	if ( titleEnd < titles.GetLength() )
	{
		afterTag.AppendFormat ( _T("%.*s\r?\n"), titles.GetLength()-titleEnd , (LPTSTR)titles.GetBuffer()+titleEnd );
	}
	return 0;
}


// 使用前向标签定位
void CtreeviewDlg::AnalyseBB(UINT posStart, UINT posEnd, HTREEITEM treeID, UINT titlePos,  CString & beforeTag,  CString & afterTag)
{
	LPTSTR pszBuffer = ( LPTSTR ) m_editStr.GetBuffer();
	CRegexpT<TCHAR>  regexp( beforeTag, SINGLELINE); 
	UINT preTitleEnd = 0; 
	HTREEITEM preTreeItem; 
	MatchResult result = regexp.Match( pszBuffer , posEnd-posStart ,posStart);
	while ( result.IsMatched() )
	{
		//分析得到标题内容
		LPTSTR titleContentStart = pszBuffer + result.GetEnd() ; 
		LPTSTR titleEnd; 
		CString searchContent = afterTag.IsEmpty() ?  _T("\n"):afterTag;  
	
		if ( ( titleEnd = _tcsstr ( titleContentStart, (LPTSTR)searchContent.GetBuffer())) == NULL )
		{
			this->MessageBoxW ( _T("Can't find the end of the title ")); 
		}
		CString title ( titleContentStart , titleEnd - titleContentStart );
		HTREEITEM treeItem = m_treeCtl.InsertItem(  title , 0, 0, treeID ); 
		m_treeCtl.SetItemData( treeItem, (DWORD_PTR)posInLine ( titleContentStart-pszBuffer)  );
		// 非第一标题
		if (  preTitleEnd  )
		{
			AnalyseToTree ( preTitleEnd, result.GetStart(), preTreeItem, ++titlePos  ); 
		}
		titleEnd = _tcschr ( titleEnd , _T('\n'));
		if ( titleEnd == NULL )
		{
		
		}
		preTreeItem = treeItem; 
		preTitleEnd = titleEnd - pszBuffer + 1; 
		result = regexp.Match ( pszBuffer , posEnd-preTitleEnd, preTitleEnd ); 
	}
	m_editStr.ReleaseBuffer(); 
}

void CtreeviewDlg::AnalyseBA(UINT posStart, UINT posEnd, HTREEITEM treeID, UINT titlePos,  CString & afterTag)
{
	LPTSTR pszBuffer = ( LPTSTR ) m_editStr.GetBuffer();
	CRegexpT<TCHAR>  regexp( afterTag, SINGLELINE); 
	UINT preTitleEnd = 0; 
	HTREEITEM preTreeItem; 
	MatchResult result = regexp.Match( pszBuffer, posEnd-posStart, posStart );
	LPTSTR ptemp = pszBuffer; 
	while ( result.IsMatched() )
	{
		//分析得到标题内容
		LPTSTR titleContentEnd = pszBuffer  + result.GetStart() ; 
		LPTSTR titleStart; 
		titleStart = strchrRT( pszBuffer + preTitleEnd, titleContentEnd-1, _T('\n') );
		if ( titleStart == NULL )
		{
			this->MessageBoxW ( _T("Can't find the start of the title ")); 
		}
		CString title ( titleStart , titleContentEnd - titleStart);
		HTREEITEM treeItem = m_treeCtl.InsertItem(  title , 0, 0, treeID ); 
		m_treeCtl.SetItemData( treeItem, (DWORD_PTR)posInLine( titleStart-pszBuffer)  );
		// 非第一标题
		if (  preTitleEnd  )
		{
			AnalyseToTree ( preTitleEnd, titleStart-pszBuffer, preTreeItem, ++titlePos  ); 
		}
		preTreeItem = treeItem ; 
		preTitleEnd = result.GetEnd(); 
		result = regexp.Match ( pszBuffer, posEnd-posStart , preTitleEnd ); 
	}
	m_editStr.ReleaseBuffer(); 
}


// 字符位置对应的行数
int CtreeviewDlg::posInLine(UINT pos)
{
	
	if ( m_posMapLine.empty() && makePosMap() == -1 )
		return -1 ; 
	vector<UINT>::iterator lineIter = lower_bound( m_posMapLine.begin(), m_posMapLine.end(), pos ); 
	if ( lineIter == m_posMapLine.end() )
	{
		this->MessageBoxW ( _T("the pos %d is larger than the file length %d", pos, m_editStr.GetLength()) ); 
		return  -1; 
	}
	return lineIter - m_posMapLine.begin(); 
}


int CtreeviewDlg::makePosMap(void)
{
	if ( m_editStr.IsEmpty() )
		return -1;
	UINT pos = 0, lineCount = 0; 
	m_posMapLine.clear(); 
	while ( pos < m_editStr.GetLength() )
	{
		pos = m_editStr.Find(_T('\n'), pos ); 
		
		if ( pos == -1 )
		{
			m_posMapLine.push_back(  m_editStr.GetLength() ); 
			break; 
		}
		m_posMapLine.push_back( pos ); 
		pos ++; 
	}
	
	return 0;
}
