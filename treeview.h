
// treeview.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CtreeviewApp:
// �йش����ʵ�֣������ treeview.cpp
//

class CtreeviewApp : public CWinApp
{
public:
	CtreeviewApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CtreeviewApp theApp;