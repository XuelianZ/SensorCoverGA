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

	int UnitNum;  //��Ⱥ������
	int nInherit; //�Ŵ�����

	vector<UnitGT> Father; //��¼������Ⱥ
	vector<UnitGT> Son;    //��¼�Ӵ���Ⱥ
	
	float AcrossOdds;  //�������
	float VarOdds;     //�������	
	int nNowbest;//�洢��ǰ��������Ⱥ�еı��
	
	CRect recPIC1;  //����PIC1��һ���������
	double Rx,Ry; //���崫������֪��Բ������ֱ��
	
	UnitGT NOWbest;//�Ŵ��㷨��ǰ����
	UnitGT HISTbest;//�Ŵ��㷨��ʷ����
	UnitGT nFather[100];
	UnitGT nSon[100];

	int t1,t2;//����ʱ��
	CString aa,bb;//����ı���¼

	vector<StatRes>SR;//����ͳ�ƴ�������������Ӧ��ֵ������
	int nf,nA;//������ʾ��Ӧ�Ȼ򴫸��������ı��

	vector<UnitGT>statStab;//�ȶ���ͳ������

	int LocasNum;

	double HL;//���屻���Ǿ��εĳ���
	double sR;//���崫������֪�뾶

	int N0;//ȫ������С��������Ŀ


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
