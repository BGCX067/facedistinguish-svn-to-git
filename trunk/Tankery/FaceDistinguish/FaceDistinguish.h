// FaceDistinguish.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFaceDistinguishApp:
// �йش����ʵ�֣������ FaceDistinguish.cpp
//

class CFaceDistinguishApp : public CWinApp
{
public:
	CFaceDistinguishApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFaceDistinguishApp theApp;