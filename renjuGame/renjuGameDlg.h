
// renjuGameDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#define BLACK 1
#define WHITE 2
#define NONE 0
#define SIZE 16

// CrenjuGameDlg �Ի���
class CrenjuGameDlg : public CDialogEx
{
// ����
public:
	CrenjuGameDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RENJUGAME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_picBoard;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void InitBoard();//��ʼ���������̣���������ÿ��λ�ö�������״̬
	bool judgeWin(int i,int j);//�жϵ�ǰ�ж����Ƿ���ʤ������������ֵΪtrue����ʤ����false����δʤ��
private:
	int board[SIZE][SIZE];//�洢������Ϣ������
	int act;//�ж�Ȩ����ǰӦ�ð����߻���Ӧ�ú�����
};
