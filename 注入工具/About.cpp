// About.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ע�빤��.h"
#include "About.h"
#include "afxdialogex.h"


// CAbout �Ի���

IMPLEMENT_DYNAMIC(CAbout, CDialog)

CAbout::CAbout(CWnd* pParent /*=NULL*/)
	: CDialog(CAbout::IDD, pParent)
{

}

CAbout::~CAbout()
{
}

void CAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAbout, CDialog)
END_MESSAGE_MAP()

BOOL CAbout::PreTranslateMessage(MSG* PMsg)
{
	if (PMsg->message == WM_KEYDOWN)
	{
		int nKey = (int)PMsg->wParam;
		if (nKey == VK_RETURN || nKey == VK_ESCAPE)
		{
			return true;
		}
	}
	return CDialog::PreTranslateMessage(PMsg);
}