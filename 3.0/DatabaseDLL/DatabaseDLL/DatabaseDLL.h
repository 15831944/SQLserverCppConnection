// DatabaseDLL.h : DatabaseDLL DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDatabaseDLLApp
// �йش���ʵ�ֵ���Ϣ������� DatabaseDLL.cpp
//

class CDatabaseDLLApp : public CWinApp
{
public:
	CDatabaseDLLApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
