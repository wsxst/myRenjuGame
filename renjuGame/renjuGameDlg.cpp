
// renjuGameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "renjuGame.h"
#include "renjuGameDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CrenjuGameDlg �Ի���



CrenjuGameDlg::CrenjuGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RENJUGAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CrenjuGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_BOARD, m_picBoard);
}

BEGIN_MESSAGE_MAP(CrenjuGameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CrenjuGameDlg ��Ϣ�������

BOOL CrenjuGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitBoard();
	act = BLACK;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CrenjuGameDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CrenjuGameDlg::OnPaint()
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
HCURSOR CrenjuGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CrenjuGameDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int x0 = -1,y0 = -1;//��������ʵ�����ӵ�λ��
	double l = 26.5;
	int i,j;
	
	for (i = 0; i <= 15; i++) {
		if (point.x >= 40 + l * i - 5 && point.x <= 40 + l * i + 5) {
			x0 = 40 + l * i;
			break;
		}
	}
	for (j = 0; j <= 15; j++) {
		if (point.y >= 40 + l * j - 5 && point.y <= 40 + l * j + 5) {
			y0 = 40 + l * j;
			break;
		}
	}
	if (x0 == -1 || y0 == -1) return;//���λ�ò��Ϸ�

	if (board[i][j] != NONE) return;//��λ���Ѿ���������

	//�����������ӣ����½���
	CDC *pDC = GetDC();
	CImage Image;
	if(act == WHITE) Image.Load(L"res/white.png");
	else Image.Load(L"res/black.png");
	if (Image.IsNull())
	{
		MessageBox(_T("û���سɹ�"));
		return;
	}
	if (Image.GetBPP() == 32) //ȷ�ϸ�ͼ�����Alphaͨ��
	{
		int i;
		int j;
		for (i = 0; i < Image.GetWidth(); i++)
		{
			for (j = 0; j < Image.GetHeight(); j++)
			{
				byte *pByte = (byte *)Image.GetPixelAddress(i, j);
				pByte[0] = pByte[0] * pByte[3] / 255;
				pByte[1] = pByte[1] * pByte[3] / 255;
				pByte[2] = pByte[2] * pByte[3] / 255;
			}
		}
	}
	Image.Draw(pDC->m_hDC, x0-9, y0-9);
	Image.Destroy();
	ReleaseDC(pDC);

	//�������ݽṹ�����̵���Ϣ
	board[i][j] = act;

	//�ж��Ƿ���ʤ������
	if (judgeWin(i, j)) {
		if(act == BLACK) MessageBox(L"�ڷ�Ӯ�ˣ�");
		else MessageBox(L"�׷�Ӯ�ˣ�");
		return;
	}

	//�ı��ж�Ȩ
	act = (act == BLACK ? WHITE : BLACK);

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CrenjuGameDlg::InitBoard()
{
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			board[i][j] = NONE;
		}
	}
}

bool CrenjuGameDlg::judgeWin(int i,int j)
{
	int sum = 1;
	for (int a = 1;; a++) {
		if (board[i][j - a] == act) {
			sum++;
			if (sum == 5) return true;
		}
		else break;
	}
	for (int a = 1;; a++) {
		if (board[i][j + a] == act) {
			sum++;
			if (sum == 5) return true;
		}
		else break;
	}
	sum = 1;
	for (int a = 1;; a++) {
		if (board[i-a][j] == act) {
			sum++;
			if (sum == 5) return true;
		}
		else break;
	}
	for (int a = 1;; a++) {
		if (board[i + a][j] == act) {
			sum++;
			if (sum == 5) return true;
		}
		else break;
	}
	sum = 1;
	for (int a = 1;; a++) {
		if (board[i - a][j - a] == act) {
			sum++;
			if (sum == 5) return true;
		}
		else break;
	}
	for (int a = 1;; a++) {
		if (board[i + a][j + a] == act) {
			sum++;
			if (sum == 5) return true;
		}
		else break;
	}
	sum = 1;
	for (int a = 1;; a++) {
		if (board[i - a][j + a] == act) {
			sum++;
			if (sum == 5) return true;
		}
		else break;
	}
	for (int a = 1;; a++) {
		if (board[i + a][j - a] == act) {
			sum++;
			if (sum == 5) return true;
		}
		else break;
	}

	return false;
}
