
// PocoDBIOproject.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPocoDBIOprojectApp:
// �йش����ʵ�֣������ PocoDBIOproject.cpp
//

class CPocoDBIOprojectApp : public CWinAppEx
{
public:
	CPocoDBIOprojectApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPocoDBIOprojectApp theApp;