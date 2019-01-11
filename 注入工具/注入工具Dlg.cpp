
// ע�빤��Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ע�빤��.h"
#include "ע�빤��Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cע�빤��Dlg �Ի���



Cע�빤��Dlg::Cע�빤��Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cע�빤��Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cע�빤��Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_LIST5, m_List);
}

BEGIN_MESSAGE_MAP(Cע�빤��Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cע�빤��Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Cע�빤��Dlg::OnBnClickedButton2)
	ON_COMMAND(ID_32772, &Cע�빤��Dlg::OnAbout)
	ON_COMMAND(ID_32771, &Cע�빤��Dlg::OnExit)
	ON_BN_CLICKED(IDC_BUTTON4, &Cע�빤��Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &Cע�빤��Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON3, &Cע�빤��Dlg::OnBnClickedButton3)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// Cע�빤��Dlg ��Ϣ�������

//************************************************************
// ��������:	OnInitDialog
// ����˵��: ��дOnInitDialog���������ݳ�ʼ������
// ��	��: �����
// ʱ	��: 2018/12/20
//************************************************************
BOOL Cע�빤��Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	// ���ز˵�
	m_Menu.LoadMenuW(IDR_MENU1);
	// ʵ�����˵����Ӳ˵�ǰ���ͼ��
	m_Bmp[0].LoadBitmap(IDB_EXIT);
	m_Bmp[1].LoadBitmap(IDB_ABOUT);
	GetMenu()->GetSubMenu(0)->SetMenuItemBitmaps(0, MF_BYPOSITION, &m_Bmp[0], &m_Bmp[0]);
	GetMenu()->GetSubMenu(1)->SetMenuItemBitmaps(0, MF_BYPOSITION, &m_Bmp[1], &m_Bmp[1]);

	// list�б��ʼ��
	// ������չ�������ѡ��
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// ��ӱ���
	m_List.InsertColumn(0, _T("ģ������"), LVCFMT_LEFT, 150);
	m_List.InsertColumn(1, _T("���ػ�ַ"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(3, _T("ģ��·��"), LVCFMT_LEFT, 350);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cע�빤��Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cע�빤��Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//************************************************************
// ��������:	PreTranslateMessage
// ����˵��: ��дPreTranslateMessage�������ó��������ڵ�Enter����Esc��ʧЧ
// ��	��: �����
// ʱ	��: 2018/12/20
//************************************************************
BOOL Cע�빤��Dlg::PreTranslateMessage(MSG* PMsg)
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

//************************************************************
// ��������:	EnumProcess
// ����˵��: ���ݽ������ƻ�ȡ����PID
// ��	��: �����
// ʱ	��: 2018/12/20
//************************************************************
DWORD Cע�빤��Dlg::EnumProcess(CString ProcessName)
{
	// ��������
	PROCESSENTRY32 pe = { sizeof(PROCESSENTRY32) };
	// ��������
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	// �õ���һ�����̵���Ϣ
	BOOL bSuccess = Process32First(hSnap, &pe);
	DWORD dwIndex = 0;
	CString str;
	// ѭ���������н��̵���Ϣ
	if (bSuccess)
	{
		do
		{
			if (wcscmp(pe.szExeFile, ProcessName) == 0)
			{
				return pe.th32ProcessID;
			}
			// dwIndex��1
			++dwIndex;
		} while (Process32Next(hSnap, &pe));
	}
	return 0;
}

//************************************************************
// ��������:	LoadDll
// ����˵��: ���ݽ���PID��dll·����Զ���߳�ע��DLL
// ��	��: �����
// ʱ	��: 2018/12/20
//************************************************************
// ����DLL����
BOOL Cע�빤��Dlg::LoadDll(DWORD dwProcessId, char* szDllPathname)
{
	BOOL bRet;
	HANDLE hProcess;
	HANDLE hThread;
	size_t dwLength;
	DWORD dwLoadAddr;
	LPVOID lpAllocAddr;
	//HMODULE hMoudule;

	bRet = 0;
	dwLoadAddr = 0;
	// 1:��ȡ���̾��
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
	// 2:����DLL·�����ֳ��ȣ�����Ҫ����0��β�ĳ���
	dwLength = strlen(szDllPathname);
	// 3:��Ŀ����̷����ڴ�
	lpAllocAddr = VirtualAllocEx(hProcess, NULL, dwLength, MEM_COMMIT, PAGE_READWRITE);
	// 4:����DLL·�����ֵ�Ŀ����̵��ڴ�
	bRet = WriteProcessMemory(hProcess, lpAllocAddr, szDllPathname, dwLength, NULL);
	// 5: ����Զ���̣߳�����DLL
	hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, lpAllocAddr, 0, NULL);
	CloseHandle(hThread);
	CloseHandle(hProcess);
	return TRUE;
}

//************************************************************
// ��������: EnumMoule
// ����˵��: ���ݽ���PID��dll·������ȡģ��Ļ�ַ
// ��	��: �����
// ʱ	��: 2018/12/20
//************************************************************
HMODULE Cע�빤��Dlg::EnumMoudle(CString ProcessName, DWORD dwPid)
{
	/*��ʼ����ģ��*/
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32 = { sizeof(MODULEENTRY32) };
	// ����һ��ģ����صĿ��վ��
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPid);
	Module32First(hModuleSnap, &me32);
	// ѭ����ȡģ����Ϣ
	do
	{
		if (wcscmp(ProcessName, me32.szExePath) == 0)
		{
			return me32.hModule;
		}
	} while (Module32Next(hModuleSnap, &me32));
	CloseHandle(hModuleSnap);
	MessageBox(L"δ�ҵ�ע��DLL��");
	return 0;
}

//************************************************************
// ��������:	FreeDll
// ����˵��: ���ݽ���PID��dll·����Զ���߳�ж��DLL
// ��	��: �����
// ʱ	��: 2018/12/20
//************************************************************
BOOL Cע�빤��Dlg::FreeDll(DWORD dwProcessId, CString szDllPathname)
{
	BOOL bRet;
	HANDLE hProcess;
	HANDLE hThread;
	size_t dwFreeAddr;
	HMODULE hMoudule;
	HMODULE hMouduleInjectDll;
	bRet = 0;
	dwFreeAddr = 0;
	// 1:��ȡ���̾��
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
	// 2:��ȡģ����
	hMouduleInjectDll = EnumMoudle(szDllPathname, dwProcessId);
	if (hMouduleInjectDll)
	{
		// 3:��ȡģ���ַ
		hMoudule = GetModuleHandle(L"kernel32.dll");
		// 4:��ȡLoadLibraryA ������ַ
		dwFreeAddr = (size_t)GetProcAddress(hMoudule, "FreeLibrary");
		// 5: ����Զ���̣߳�����DLL
		size_t nNum = (size_t)hMouduleInjectDll;
		hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)dwFreeAddr, (LPVOID)nNum, 0, NULL);
		if (hThread)
		{
			MessageBox(L"ж�سɹ�!");
		}
		CloseHandle(hThread);
		CloseHandle(hProcess);
		return TRUE;
	}
	return FALSE;
}

//************************************************************
// ��������:	OnBnClickedButton1
// ����˵��: ѡ��DLL������·�����õ��༭��ؼ�
// ��	��: �����
// ʱ	��: 2018/12/20
//************************************************************
void Cע�빤��Dlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// 1����һ���ļ���ѡ��Ի���
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		CString path = dlg.GetFolderPath();
		// 2����ȡѡ����ļ��ĺ�׺�����ж��Ƿ���DLL
		CString path1 = dlg.GetFileName();
		PCTSTR FileType = PathFindExtension(path1);
		if (wcscmp(FileType, L".dll") != 0)
		{
			MessageBox(L"��ѡ����ļ�����������ѡ��");
			return;
		}
		// 3�����ļ�·����ʾ���༭��
		m_Edit2.SetWindowText(path + L"\\" + path1);
	}
}

//************************************************************
// ��������:	OnBnClickedButton2
// ����˵��: ʵ��һ��ע��DLL
// ��	��: �����
// ʱ	��: 2018/12/20
//************************************************************
void Cע�빤��Dlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// 1����ȡҪע��ĳ�������
	CString ProcessName;
	m_Edit1.GetWindowTextW(ProcessName);
	// 2����ȡҪע��ĳ������Ƶ�PID
	DWORD PID = EnumProcess(ProcessName);
	if (PID == 0)
	{
		MessageBox(L"��ѡ��ĳ�������������ѡ��");
		return;
	}
	// 3����ȡҪע���DLL��·��
	CString DllPath;
	m_Edit2.GetWindowTextW(DllPath);
	if (wcscmp(DllPath, L"�����ťѡ����Ҫע��/ж�ص�DLL...") == 0 || wcscmp(DllPath, L"") == 0)
	{
		MessageBox(L"��ѡ��DLL��");
		return;
	}
	// 4��char* ���͵�DLL ·��
	USES_CONVERSION;
	char* CharDllPath = W2A(DllPath);
	// 5��ע��DLL
	LoadDll(PID, CharDllPath);
}

//************************************************************
// ��������:	OnAbout
// ����˵��: �˵����ڰ�ť�¼�������
// ��	��: �����
// ʱ	��: 2018/12/20
//************************************************************
void Cע�빤��Dlg::OnAbout()
{
	// TODO:  �ڴ���������������
	CAbout dlg(this);
	dlg.DoModal();
}

//************************************************************
// ��������:	OnExit
// ����˵��: �˵��˳���ť�¼�������
// ��	��: �����
// ʱ	��: 2018/12/20
//************************************************************
void Cע�빤��Dlg::OnExit()
{
	// TODO:  �ڴ���������������
	SendMessage(WM_CLOSE);
}

//************************************************************
// ��������:	OnBnClickedButton4
// ����˵��: ʵ��һ��ж��DLL
// ��	��: �����
// ʱ	��: 2018/12/20
//************************************************************
void Cע�빤��Dlg::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// 1����ȡҪж�صĳ�������
	CString ProcessName;
	m_Edit1.GetWindowTextW(ProcessName);
	// 2����ȡҪж�صĳ������Ƶ�PID
	DWORD PID = EnumProcess(ProcessName);
	if (PID == 0)
	{
		MessageBox(L"��ѡ��ĳ�������������ѡ��");
		return;
	}
	// 3����ȡҪж�ص�DLL��·��
	CString DllPath;
	m_Edit2.GetWindowTextW(DllPath);
	if (wcscmp(DllPath, L"�����ťѡ����Ҫע��/ж�ص�DLL...") == 0 || wcscmp(DllPath, L"") == 0)
	{
		MessageBox(L"��ѡ��DLL��");
		return;
	}
	// 4��ж��DLL
	FreeDll(PID, DllPath);
}

//************************************************************
// ��������:	OnBnClickedButton5
// ����˵��: �鿴ģ��
// ��	��: �����
// ʱ	��: 2018/12/20
//************************************************************
void Cע�빤��Dlg::OnBnClickedButton5()
{
	// 1.����б�
	m_List.DeleteAllItems();
	// 2.��ʼ������
	DWORD nIndex = 0;
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32 = { sizeof(MODULEENTRY32) };

	// 3.��ȡ����PID
	// 3.1 ��ȡҪж�صĳ�������
	CString ProcessName;
	m_Edit1.GetWindowTextW(ProcessName);
	// 3.2 ��ȡҪж�صĳ������Ƶ�PID
	DWORD PID = EnumProcess(ProcessName);
	if (PID == 0)
	{
		MessageBox(L"��ѡ��ĳ�������������ѡ��");
		return;
	}
	// 4.����һ��ģ����صĿ��վ��
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);
	Module32First(hModuleSnap, &me32);
	// 5.ѭ����ȡģ����Ϣ
	do
	{
		// 5.1 �Ȳ���һ��item ���б�
		m_List.InsertItem(nIndex, L"");
		// 5.2 ��ģ�������뵽item ��0��
		m_List.SetItemText(nIndex, 0, me32.szModule);
		// 5.3 ��ģ����ػ�ַ���뵽item ��1��
		size_t nNum = (size_t)me32.hModule;  // ��HMOUDLEת��Ϊsize_t
		CString strMoudle2;
		strMoudle2.Format(L"0x%llx", nNum);
		m_List.SetItemText(nIndex, 1, strMoudle2);
		// 5.4 ��ģ��·�����뵽item��2��
		m_List.SetItemText(nIndex, 2, me32.szExePath);
		nIndex++;
	} while (Module32Next(hModuleSnap, &me32));
	CloseHandle(hModuleSnap);
}

// ѡ�����ť������
void Cע�빤��Dlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CMyProcess dlg(this);
	dlg.DoModal();
	CString strExeName;
	strExeName = dlg.m_exeName;
	GetDlgItem(IDC_EDIT1)->SetWindowText(strExeName);
}

// �ı�༭����ɫ
HBRUSH Cע�빤��Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	if (pWnd->GetDlgCtrlID() == IDC_EDIT1)
	{
		pDC->SetTextColor(RGB(136, 23, 152));
	}
	else if (pWnd->GetDlgCtrlID() == IDC_EDIT2)
	{
		pDC->SetTextColor(RGB(136, 23, 152));
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
