
// ע�빤��.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cע�빤��App: 
// �йش����ʵ�֣������ ע�빤��.cpp
//

class Cע�빤��App : public CWinApp
{
public:
	Cע�빤��App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cע�빤��App theApp;