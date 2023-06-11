// TabuGADlg.h : header file
//

#if !defined(AFX_TABUGADLG_H__B843E0E0_A63F_402D_A8E2_A0EFA3473283__INCLUDED_)
#define AFX_TABUGADLG_H__B843E0E0_A63F_402D_A8E2_A0EFA3473283__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CTabuGADlg dialog

class CTabuGADlg : public CDialog
{
// Construction
public:
//	int LocasNum;
	void DrawPIC3();
	void DrawPIC2();
	void Mainpro();
	void DrawPIC();
	void chooseBest(UnitGT Group[]);
	void TextOut(UnitGT HistBest);
	void GA(UnitGT Group[]);
	void SITEoptim(UnitGT group[]);
	double CalcuFitness(UnitGT indiv);
	int StatActNum(UnitGT indiv);
	double CalCoverRate(UnitGT indiv);
	void InitiGene();
	CTabuGADlg(CWnd* pParent = NULL);	// standard constructor

	int UnitNum;  //种群个体数
	int nInherit; //遗传代数

	vector<UnitGT> Father; //记录父代种群
	vector<UnitGT> Son;    //记录子代种群
	
	float AcrossOdds;  //交叉概率
	float VarOdds;     //变异概率	
	int nNowbest;//存储当前个体在种群中的标号
	
	CRect recPIC1;  //定义PIC1的一个区域对象
	double Rx,Ry; //定义传感器感知椭圆的两条直径
	
	UnitGT NOWbest;//遗传算法当前最优
	UnitGT HISTbest;//遗传算法历史最优
	UnitGT nFather[100];
	UnitGT nSon[100];

	int t1,t2;//测试时间
	CString aa,bb;//输出文本记录

	vector<StatRes>SR;//定义统计传感器个数和适应度值的数组
	int nf,nA;//定义显示适应度或传感器个数的标记

	vector<UnitGT>statStab;//稳定性统计数组

	int LocasNum;

	double HL;//定义被覆盖矩形的长宽
	double sR;//定义传感器感知半径

	int N0;//全覆盖最小传感器数目


// Dialog Data
	//{{AFX_DATA(CTabuGADlg)
	enum { IDD = IDD_TABUGA_DIALOG };
	CEdit	m_sensnum;
	CEdit	m_statnum;
	CEdit	m_circtimes;
	CEdit	m_tabulg;
	CEdit	m_candnum;
	CEdit	m_acrOdds;
	CEdit	m_unitnum;
	CEdit	m_varodds;
	CEdit	m_nIheritimes;
	CString	m_textout;
	int		m_time;
	long	m_avernum;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabuGADlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTabuGADlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTtest();
	afx_msg void OnBUTsN();
	afx_msg void OnBUTsF();
	afx_msg void OnBUTstatStab();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABUGADLG_H__B843E0E0_A63F_402D_A8E2_A0EFA3473283__INCLUDED_)
