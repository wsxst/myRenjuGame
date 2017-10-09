
// renjuGameDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

#define BLACK 1
#define WHITE 2
#define NONE 0
#define SIZE 16

// CrenjuGameDlg 对话框
class CrenjuGameDlg : public CDialogEx
{
// 构造
public:
	CrenjuGameDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RENJUGAME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_picBoard;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void InitBoard();//初始化整个棋盘，让棋盘上每个位置都是无子状态
	bool judgeWin(int i,int j);//判断当前行动方是否达成胜利条件，返回值为true代表胜利，false代表未胜利
private:
	int board[SIZE][SIZE];//存储棋盘信息的数组
	int act;//行动权，当前应该白子走还是应该黑子走
};
