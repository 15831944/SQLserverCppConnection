
// DatabaseTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DatabaseTest.h"
#include "DatabaseTestDlg.h"
#include "..\..\Include\IDatabaseIO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CDatabaseTestDlg �Ի���




CDatabaseTestDlg::CDatabaseTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDatabaseTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDatabaseTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDatabaseTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CDatabaseTestDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDatabaseTestDlg ��Ϣ�������

BOOL CDatabaseTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDatabaseTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDatabaseTestDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDatabaseTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDatabaseTestDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

// 	 	{
// 	 		CSQLServerIO sqldata(L"LENOVO-PC",L"stu.mdb",DATABASE_TYPE::ACCESS,L"",L"123");
// 	 		CString s;
// 	 		s.Format("ACCESS: sa���й�%d��",sqldata.GetTableCount("sa"));
// 	 		MessageBox(s);
// 	 	}
// 	 
// 	 
// 	 	{
// 	 		CSQLServerIO sqldata(L"LENOVO-PC",L"stu.xls",DATABASE_TYPE::EXCEL);
// 	 		CString s;
// 	 		s.Format("EXCEL: sa���й�%d��",sqldata.GetTableCount("[StuScore$]"));
// 	 		MessageBox(s);
// 	 	}

// 	{
// 		CSQLServerIO sqldata(L"LENOVO-PC",L"stu",DATABASE_TYPE::SQLSERVER);//,L"sa",L"xiexiaojun" //������Ϊwindows���֤
// 		CString s;
// 		s.Format("SQLSERVER: sa���й�%d��",sqldata.GetTableCount("ss"));
// 	 	MessageBox(s);
// 	}
// 
// 	{
// 		CSQLServerIO sqldata(L"LENOVO-PC",L"stu",DATABASE_TYPE::SQLSERVER,L"sa",L"xiexiaojun");// //������Ϊwindows���֤
// 		CString s;
// 		s.Format("SQLSERVER: sa���й�%d��",sqldata.GetTableCount("ss"));
// 		MessageBox(s);
// 	}

	{
		IDataBaseModule * lpiDataBaseSql = NULL;
		if (CreatIDataBaseSql("./DatabaseDLLD.dll",lpiDataBaseSql))
		{
			long n = lpiDataBaseSql->OnInit(L"LENOVO-PC",L"./stu.mdb",DATABASE_TYPE::ACCESS,L"",L"123");
			CString s;
			s.Format("SQLSERVER: sa���й�%d��",lpiDataBaseSql->GetTableCount("sa"));
			MessageBox(s);
			s.Format("SELECT * from sa");

			_RecordsetPtr m_RecordSetPtr;
			lpiDataBaseSql->MyQuarty(s,m_RecordSetPtr);
			MessageBox("yes");
		}
		
		ReleaseIDataBaseSql(lpiDataBaseSql);
	 	
	}
	//OnOK();
}
