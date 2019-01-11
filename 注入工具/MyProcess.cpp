// MyProcess.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ע�빤��.h"
#include "MyProcess.h"
#include "afxdialogex.h"


// CMyProcess �Ի���

IMPLEMENT_DYNAMIC(CMyProcess, CDialogEx)

CMyProcess::CMyProcess(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyProcess::IDD, pParent)
{

}

CMyProcess::~CMyProcess()
{
}

void CMyProcess::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CMyProcess, CDialogEx)
	ON_COMMAND(ID_32773, &CMyProcess::OnRefresh)
	ON_COMMAND(ID_32774, &CMyProcess::OnTerminateProcess)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CMyProcess::OnNMRClickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CMyProcess::OnNMDblclkList1)
END_MESSAGE_MAP()


// CMyProcess ��Ϣ�������

// ��д�麯��PreTranslateMessage
BOOL CMyProcess::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���

	if (pMsg->message == WM_KEYDOWN)
	{
		int nKey = (int)pMsg->wParam;
		if (nKey == VK_RETURN || nKey == VK_ESCAPE)
		{
			return true;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

// ��д�麯��OnInitDialog
BOOL CMyProcess::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	// list�б��ʼ��
	// ������չ�������ѡ��
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// ��ӱ���
	m_list.InsertColumn(0, _T("Index"), LVCFMT_LEFT, 45);
	m_list.InsertColumn(1, _T("��������"), LVCFMT_LEFT, 176);
	m_list.InsertColumn(3, _T("PID"), LVCFMT_LEFT, 50);

	// �Ҽ��˵�����λͼ
	m_subBmp[0].LoadBitmap(IDB_REFRESH);
	m_subBmp[1].LoadBitmap(IDB_TERMINATE);

	// ���ñ������̺��� 
	EnumProcess();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

// �������̵ĺ���
void CMyProcess::EnumProcess()
{
	// ɾ�����нڵ�
	m_list.DeleteAllItems();
	// ����һЩ�ֲ�����
	PROCESSENTRY32 pe = { sizeof(PROCESSENTRY32) };
	DWORD dwIndex = 0;
	CString CIndex;
	CString CPID;
	// ��������
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	// �õ���һ�����̵���Ϣ
	BOOL bSuccess = Process32First(hSnap, &pe);
	// ѭ���������н��̵���Ϣ
	if (bSuccess == TRUE)
	{
		do
		{
			if (Is64BitPorcess(pe.th32ProcessID))
			{
				// �Ȳ���һ��item���б�
				m_list.InsertItem(dwIndex, L"");
				// ���������뵽item ��0��
				CIndex.Format(_T("%d"), dwIndex);
				m_list.SetItemText(dwIndex, 0, CIndex);
				// �����������뵽item ��1��
				m_list.SetItemText(dwIndex, 1, pe.szExeFile);
				// ������PID���뵽item ��2��
				CPID.Format(_T("%d"), pe.th32ProcessID);
				m_list.SetItemText(dwIndex, 2, CPID);
				++dwIndex;
			}
		} while (Process32Next(hSnap, &pe));
	}
}

// �Ҽ��˵�ˢ�½���
void CMyProcess::OnRefresh()
{
	// TODO:  �ڴ���������������
	EnumProcess();
}

// �Ҽ��˵���������
void CMyProcess::OnTerminateProcess()
{
	// ����ID �����ڵ�2��
	int nIndex = 0;
	POSITION pos = { 0 };
	// ��ȡ��ѡ�нڵ�Ŀ�ʼλ��
	pos = m_list.GetFirstSelectedItemPosition();
	TCHAR buff[MAX_PATH];
	while ((nIndex = m_list.GetNextSelectedItem(pos)) != -1)
	{
		// ��ȡ��nIndex�еĵ�2�е��ı�
		m_list.GetItemText(nIndex, 2, buff, MAX_PATH);
	}
	// ��TCHAR����ת����DWORD
	DWORD lg;
	swscanf_s(buff, L"%d", &lg);
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, lg);
	TerminateProcess(hProcess, 0);
	EnumProcess();
}

// �޸�������ɫ
HBRUSH CMyProcess::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	if (pWnd->GetDlgCtrlID() == IDC_STATIC)
	{
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(0, 255, 0));
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

// �Ҽ�����������
void CMyProcess::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	// ��������Ҫ�õ���cmenu���� 
	CMenu menu, *pSubMenu;
	// װ���Զ�����Ҽ��˵� 
	menu.LoadMenu(IDR_MENU2);
	// ��ȡ�Ӳ˵���
	pSubMenu = menu.GetSubMenu(0);
	// ʵ���Ҽ��˵�ǰ���ͼ��
	pSubMenu->SetMenuItemBitmaps(0, MF_BYPOSITION, &m_subBmp[0], &m_subBmp[0]);
	pSubMenu->SetMenuItemBitmaps(1, MF_BYPOSITION, &m_subBmp[1], &m_subBmp[1]);
	// ����û���б��ѡ�У�����ý������̵Ĺ���
	if (pNMItemActivate->iItem == -1)
	{
		pSubMenu->EnableMenuItem(ID_32774, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}

	// ��ȡ��һ�������˵������Ե�һ���˵��������Ӳ˵�
	// ����һ������ȷ�����λ�õ�λ�� 
	CPoint oPoint;
	//��ȡ��ǰ����λ�ã��Ա�ʹ�ò˵����Ը�����
	GetCursorPos(&oPoint);
	// �����Ӳ˵�
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, oPoint.x, oPoint.y, this);
}

// �б�˫���¼�
void CMyProcess::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	if (m_list.GetSelectedCount() == 1)
	{
		POSITION pos_s;
		pos_s = m_list.GetFirstSelectedItemPosition();
		int item = m_list.GetNextSelectedItem(pos_s);
		m_exeName = m_list.GetItemText(item, 1);
	}
	else
	{
		MessageBox(L"��ѡ�����");
		return;
	}
	SendMessage(WM_CLOSE);

	*pResult = 0;
}

// �ж��ǲ���64λ����ϵͳ
BOOL CMyProcess::Is64BitOS()
{
	typedef VOID(WINAPI *LPFN_GetNativeSystemInfo)(__out LPSYSTEM_INFO lpSystemInfo);
	LPFN_GetNativeSystemInfo fnGetNativeSystemInfo = (LPFN_GetNativeSystemInfo)GetProcAddress(GetModuleHandleW(L"kernel32"), "GetNativeSystemInfo");
	if (fnGetNativeSystemInfo)
	{
		SYSTEM_INFO stInfo = { 0 };
		fnGetNativeSystemInfo(&stInfo);
		if (stInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64
			|| stInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
		{
			return TRUE;
		}
	}
	return FALSE;
}

// �ж��ǲ���64λ����
BOOL CMyProcess::Is64BitPorcess(DWORD dwProcessID)
{
	if (!Is64BitOS())
	{
		return FALSE;
	}
	else
	{
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcessID);
		if (hProcess)
		{
			typedef BOOL(WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
			LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandleW(L"kernel32"), "IsWow64Process");
			if (NULL != fnIsWow64Process)
			{
				BOOL bIsWow64 = FALSE;
				fnIsWow64Process(hProcess, &bIsWow64);
				CloseHandle(hProcess);
				if (bIsWow64)
				{
					return FALSE;
				}
				else
				{
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}