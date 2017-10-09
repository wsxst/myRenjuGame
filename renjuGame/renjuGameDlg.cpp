
// renjuGameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "renjuGame.h"
#include "renjuGameDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CrenjuGameDlg 对话框



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


// CrenjuGameDlg 消息处理程序

BOOL CrenjuGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	InitBoard();
	act = BLACK;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CrenjuGameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CrenjuGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CrenjuGameDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int x0 = -1,y0 = -1;//这是棋子实际落子的位置
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
	if (x0 == -1 || y0 == -1) return;//点的位置不合法

	if (board[i][j] != NONE) return;//该位置已经有棋子了

	//在棋盘上下子，更新界面
	CDC *pDC = GetDC();
	CImage Image;
	if(act == WHITE) Image.Load(L"res/white.png");
	else Image.Load(L"res/black.png");
	if (Image.IsNull())
	{
		MessageBox(_T("没加载成功"));
		return;
	}
	if (Image.GetBPP() == 32) //确认该图像包含Alpha通道
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

	//更新数据结构中棋盘的信息
	board[i][j] = act;

	//判断是否达成胜利条件
	if (judgeWin(i, j)) {
		if(act == BLACK) MessageBox(L"黑方赢了！");
		else MessageBox(L"白方赢了！");
		return;
	}

	//改变行动权
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
