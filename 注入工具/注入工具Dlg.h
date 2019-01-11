
// ע�빤��Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <Psapi.h>
#include <TlHelp32.h>
#include "About.h"
#include "afxcmn.h"
#include "MyProcess.h"


// Cע�빤��Dlg �Ի���
class Cע�빤��Dlg : public CDialogEx
{
// ����
public:
	Cע�빤��Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DWORD EnumProcess(CString ProcessName);
	HMODULE EnumMoudle(CString ProcessName, DWORD dwPid);
	BOOL LoadDll(DWORD dwProcessId, char* szDllPathname);
	BOOL FreeDll(DWORD dwProcessId, CString szDllPathname);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Edit2;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CEdit m_Edit1;
	CMenu m_Menu;
	CBitmap m_Bmp[2];
	afx_msg void OnAbout();
	afx_msg void OnExit();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	CListCtrl m_List;
	afx_msg void OnBnClickedButton3();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
