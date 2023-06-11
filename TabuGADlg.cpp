// TabuGADlg.cpp : implementation file
//

#include "stdafx.h"
#include "TabuGA.h"
#include "TabuGADlg.h"
#include "TABU.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabuGADlg dialog

CTabuGADlg::CTabuGADlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTabuGADlg::IDD, pParent)
{
	HL = 100;
	sR = 13;
	N0=ceil(HL/(sqrt(3)*sR))*ceil((2*HL-sR)/(3.0*sR));
	//{{AFX_DATA_INIT(CTabuGADlg)
	m_textout = _T("");
	m_time = 0;
	m_avernum = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTabuGADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabuGADlg)
	DDX_Control(pDX, IDC_EDIT12, m_sensnum);
	DDX_Control(pDX, IDC_EDIT10, m_statnum);
	DDX_Control(pDX, IDC_EDIT7, m_circtimes);
	DDX_Control(pDX, IDC_EDIT6, m_tabulg);
	DDX_Control(pDX, IDC_EDIT5, m_candnum);
	DDX_Control(pDX, IDC_EDIT3, m_acrOdds);
	DDX_Control(pDX, IDC_EDIT8, m_unitnum);
	DDX_Control(pDX, IDC_EDIT4, m_varodds);
	DDX_Control(pDX, IDC_EDIT2, m_nIheritimes);
	DDX_Text(pDX, IDC_EDIT1, m_textout);
	DDX_Text(pDX, IDC_EDIT9, m_time);
	DDX_Text(pDX, IDC_EDIT11, m_avernum);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTabuGADlg, CDialog)
	//{{AFX_MSG_MAP(CTabuGADlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTtest, OnBUTtest)
	ON_BN_CLICKED(IDC_BUTsN, OnBUTsN)
	ON_BN_CLICKED(IDC_BUTsF, OnBUTsF)
	ON_BN_CLICKED(IDC_BUTstatStab, OnBUTstatStab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabuGADlg message handlers

BOOL CTabuGADlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	m_nIheritimes.SetWindowText("100");//�Ŵ�����
	m_acrOdds.SetWindowText("0.8");//�������
	m_varodds.SetWindowText("0.1");//�������
	m_unitnum.SetWindowText("20");//��Ⱥ����
	m_statnum.SetWindowText("5");
	m_sensnum.SetWindowText("80");
	
	m_circtimes.SetWindowText("200");//����������ѭ������
	m_candnum.SetWindowText("10"); //����������ѡ�����
	m_tabulg.SetWindowText("10");//���ɳ���

	SR.clear();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTabuGADlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTabuGADlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		DrawPIC();
		DrawPIC2();
		DrawPIC3();
		
		

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTabuGADlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//*********���ɳ�ʼ��Ⱥ*************
void CTabuGADlg::InitiGene()
{
	//		srand(time(NULL));
	for (int i=0;i<UnitNum;i++)
	{//����ʽ��ʼ����
		UnitGT InitiTempUnit;       //���������ʱ����
		/*
		int shang=LocasNum/25;
		for (int z=0;z<5;z++)
		{
			for (int h=0;h<5;h++)
			{
				for (int fz=0;fz<shang;fz++)
				{
					InitiTempUnit.Chromo[(5*z+h)*shang+fz].x=h*20+rand()%21;
					InitiTempUnit.Chromo[(5*z+h)*shang+fz].y=z*20+rand()%21;
					InitiTempUnit.Chromo[(5*z+h)*shang+fz].chara=1;
				}
			}
		}

		for (int y=25*shang;y<LocasNum;y++)
		{
			InitiTempUnit.Chromo[y].x=(rand()%87)+7;
			InitiTempUnit.Chromo[y].y=(rand()%87)+7;
			InitiTempUnit.Chromo[y].chara=1;        //��ʼʱÿ��������������Ϊ����״̬
		}
		
		for (int j=0;j<LocasNum;j++)
		{
			InitiTempUnit.Chromo[j].x=(rand()%101);
			InitiTempUnit.Chromo[j].y=(rand()%101);
			InitiTempUnit.Chromo[j].chara=1;        //��ʼʱÿ��������������Ϊ����״̬
		}*/
		for ( int j=0;j<LocasNum;j++)
		{
			InitiTempUnit.Chromo[j].x=(rand()%int(HL));
			InitiTempUnit.Chromo[j].y=(rand()%int(HL));
			InitiTempUnit.Chromo[j].chara=1;        //��ʼʱÿ��������������Ϊ����״̬
		}

		
		InitiTempUnit.number=i;//��������Ⱥ�е����
		
		InitiTempUnit.CovRate=CalCoverRate(InitiTempUnit); //��ȡ���帲����
		
		
		InitiTempUnit.activNum=StatActNum(InitiTempUnit); //��ȡ���屻��������ĸ���
		
		InitiTempUnit.fit=CalcuFitness(InitiTempUnit); //��ȡ��Ӧ��
		Father.push_back(InitiTempUnit); //������ѹ���ʼ������Ⱥ��
	}

}


//********���㸲���ʺ���***************
double CTabuGADlg::CalCoverRate(UnitGT indiv)
{

	//�·���
	double crate=0;   //���帲����
	double S1=0;    //ͳ��ʸ����������
	double S2=0;    //�������
	double OutS=0;  //�������
	vector<JeiYai>circAbord;//ͳ������Բ����߽�Ľ���
	vector<JeiYai>okPoint;//ͳ�����հ����
	vector<Loca>margin;//��¼��Ե�ϵļ������������ѭ������

	for (int bj=0;bj<LocasNum;bj++)
	{
		if (indiv.Chromo[bj].chara==1)
		{
			if ((indiv.Chromo[bj].x<13)||(indiv.Chromo[bj].x>87)||(indiv.Chromo[bj].y<13)||(indiv.Chromo[bj].y>87))
			{
				margin.push_back(indiv.Chromo[bj]);
			}
		}

	}

	for (int i=0;i<LocasNum;i++)
	{
		
		if (indiv.Chromo[i].chara==1)
		{

			//����ÿһ����������Լ��Բ��
			vector<cyclo>radArray;//����ÿ��Բ�洢Լ��Բ���Ŀɱ䳤����
			radArray.reserve(5);//Ԥ���ռ�

			//ͳ��Լ��Բ��////
			for (int j=0;j<LocasNum;j++)
			{
				if ((j!=i)&&(indiv.Chromo[j].chara==1))
				{
					//�����ھӽڵ�ľ���
					double dis=sqrt(pow(indiv.Chromo[i].x-indiv.Chromo[j].x,2)+pow(indiv.Chromo[i].y-indiv.Chromo[j].y,2));
					if (dis==0.0)//�����������Բ�غ����غϵ�Բ����
					{
						indiv.Chromo[j].chara=0;
						continue;//����ѭ��Ѱ����һ����Բi�ཻ��Բ
					}
					else if ((dis<26.0)&&(dis>0.0))//�����Բ�н���
					{
						cyclo tempRad;
						//����Բj��Բi����ϵ�µ�Բ�ļ�����Ƕ�
						double temdis=sqrt(pow(indiv.Chromo[j].x-(indiv.Chromo[i].x+13),2)+pow(indiv.Chromo[j].y-indiv.Chromo[i].y,2));
						double angleA;//�����ҹ�ʽ����õ��Ƕ�
						if (indiv.Chromo[j].y>=indiv.Chromo[i].y)
						{
							angleA=acos((dis*dis+13*13-temdis*temdis)/(2*dis*13.0));
						}
						else
						{
							angleA=2*PI-acos((dis*dis+13*13-temdis*temdis)/(2*dis*13.0));
						}

						double angleB=acos((dis/2)/13.0);//�õ��ཻ���ȶ�ӦԲ�Ľǵ�һ��
						tempRad.radian=2*angleB;

						if (angleA-angleB<0) //�õ�������ʼ�Ƕ�
						{
							tempRad.start_angle=2*PI+(angleA-angleB);
						} 
						else
						{
							tempRad.start_angle=angleA-angleB;
						}
						tempRad.end_angle=tempRad.start_angle+2*angleB; //�õ����Ƚ����Ƕ�

						tempRad.start_x=indiv.Chromo[i].x+13*cos(tempRad.start_angle);//������ʼ������
						tempRad.start_y=indiv.Chromo[i].y+13*sin(tempRad.start_angle);
						tempRad.end_x=indiv.Chromo[i].x+13*cos(tempRad.end_angle);//�������������
						tempRad.end_y=indiv.Chromo[i].y+13*sin(tempRad.end_angle);
						radArray.push_back(tempRad);
					}
				}
			}
			//ͳ��Լ��Բ�����////


			if (radArray.size()>0) //�����Լ��Բ��
			{
				//��radArray�еĻ��ΰ������С��������
				cyclo paiXu;
				for (int px1=0;px1<radArray.size();px1++)
				{
					for (int px2=px1+1;px2<radArray.size();px2++)
					{
						if (radArray[px2].start_angle<radArray[px1].start_angle)
						{
							paiXu=radArray[px2];
							radArray[px2]=radArray[px1];
							radArray[px1]=paiXu;
						}
					}
					
				}
				//�������////
				
				//�ϲ�Լ��Բ������//ȷ����ʼ��ͽ�����
				vector<cyclo>completeRad;//����ɱ䳤�������ڴ洢�ϲ����Լ��Բ������
				vector<cyclo>reviseRad;//�����������һ���ϲ�Բ������ʱ����
				cyclo hbrad;
				hbrad=radArray[0];
				for (int hb=1;hb<radArray.size();hb++)
				{
					if (radArray[hb].end_angle<=hbrad.end_angle)
					{
						hbrad=hbrad;
					}
					else if ((radArray[hb].end_angle>hbrad.end_angle)&&(radArray[hb].start_angle<hbrad.end_angle))
					{
						hbrad.end_angle=radArray[hb].end_angle;
						hbrad.end_x=radArray[hb].end_x;
						hbrad.end_y=radArray[hb].end_y;
						hbrad.radian=hbrad.end_angle-hbrad.start_angle;
					}
					else
					{
						completeRad.push_back(hbrad);
						reviseRad.push_back(hbrad);
						hbrad=radArray[hb];
					}
				}
				completeRad.push_back(hbrad);
				reviseRad.push_back(hbrad);
				//��������������ϵ�Լ��Բ������ĩ�θ�����ǰ�˶�
				if ((reviseRad.size()>1)&&((reviseRad[reviseRad.size()-1].end_angle-2*PI)>reviseRad[0].start_angle))
				{
					for (int xz=0;xz<reviseRad.size()-1;xz++)
					{
						if ((reviseRad[reviseRad.size()-1].end_angle-2*PI)<reviseRad[xz].start_angle)
						{
							break;
						}
						else if (reviseRad[reviseRad.size()-1].end_angle-2*PI<reviseRad[xz].end_angle)
						{
							completeRad[completeRad.size()-1].end_x=reviseRad[xz].end_x;
							completeRad[completeRad.size()-1].end_y=reviseRad[xz].end_y;
							completeRad[completeRad.size()-1].end_angle=reviseRad[xz].end_angle+2*PI;
							completeRad[completeRad.size()-1].radian=completeRad[completeRad.size()-1].end_angle-completeRad[completeRad.size()-1].start_angle;
							completeRad.erase(completeRad.begin());//ע��˴�ʼ��ΪcompleteRad�еĵ�һ��Ԫ�أ�����ǰ���ѭ��������ɾ��
							break;//����ѭ��
						}
						else
						{
							completeRad.erase(completeRad.begin());

						}
					}
				}			
			//Լ��Բ�����Ⱥϲ����
			//�������
				double ysyh=0.0;//����洢Լ��Բ���ı���
				for (int hdtj=0;hdtj<completeRad.size();hdtj++)
				{
					ysyh+=completeRad[hdtj].radian;
				}
				if (2*PI-ysyh>0.005)//�����������
				{
					for (int mj=0;mj<completeRad.size();mj++)
					{//������������ۼ�
						S1+=0.5*((indiv.Chromo[i].y+completeRad[mj].end_y)*(completeRad[mj].end_x-indiv.Chromo[i].x)+(indiv.Chromo[i].y+completeRad[mj].start_y)*(indiv.Chromo[i].x-completeRad[mj].start_x));
						
					}
					S2+=13*13*(2*PI-ysyh)/2.0;//������������ۼ�
				}

			//***ͳ�ƽ�����Ľڵ�******
				if (2*PI-ysyh>0.005) //��Ȼ�ڲ������������������
				{
					if ((indiv.Chromo[i].x<13)||(indiv.Chromo[i].x>87)||(indiv.Chromo[i].y<13)||(indiv.Chromo[i].y>87))
					{
						//��¼Բ��Բ��������
						for (int outp=0;outp<completeRad.size();outp++)
						{
							if ((completeRad[outp].start_x<=0)||(completeRad[outp].start_x>=100)||(completeRad[outp].start_y<=0)||(completeRad[outp].start_y>=100))
							{
								JeiYai tempoint;
								tempoint.x=completeRad[outp].start_x;
								tempoint.y=completeRad[outp].start_y;
								tempoint.Circ.push_back(indiv.Chromo[i]);
								circAbord.push_back(tempoint);
							}
							if ((completeRad[outp].end_x<=0)||(completeRad[outp].end_x>=100)||(completeRad[outp].end_y<=0)||(completeRad[outp].end_y>=100))
							{
								JeiYai tempoint;
								tempoint.x=completeRad[outp].end_x;
								tempoint.y=completeRad[outp].end_y;
								tempoint.Circ.push_back(indiv.Chromo[i]);
								circAbord.push_back(tempoint);
							}
						}							
					}
				}

            //�ڵ�ͳ�����

			} 
			else  //���û��Լ��Բ��
			{
				//�ۼ��������
				S2+=PI*13*13;
	
			}

			/////////////////һ���������ĸ�������������////////////////////

				if ((indiv.Chromo[i].x<13)||(indiv.Chromo[i].x>87)||(indiv.Chromo[i].y<13)||(indiv.Chromo[i].y>87))
				{
					if (indiv.Chromo[i].x<13)
					{
						if (indiv.Chromo[i].y<13)
						{
							JeiYai tempt1,tempt2,tempt3,tempt4;//�������ĸ�����
							tempt1.x=0;
							tempt1.y=indiv.Chromo[i].y+sqrt(13*13-pow(indiv.Chromo[i].x,2));
							tempt1.Circ.push_back(indiv.Chromo[i]);
							circAbord.push_back(tempt1);
							
							tempt2.y=indiv.Chromo[i].y-sqrt(13*13-pow(indiv.Chromo[i].x,2));
							if (tempt2.y>0)
							{
								tempt2.x=0;
								tempt2.Circ.push_back(indiv.Chromo[i]);
								circAbord.push_back(tempt2);
							}
							
							tempt3.x=indiv.Chromo[i].x+sqrt(13*13-pow(indiv.Chromo[i].y,2));
							tempt3.y=0;
							tempt3.Circ.push_back(indiv.Chromo[i]);
							circAbord.push_back(tempt3);
							
							tempt4.x=indiv.Chromo[i].x-sqrt(13*13-pow(indiv.Chromo[i].y,2));
							if (tempt4.x>0)
							{
								tempt4.y=0;
								tempt4.Circ.push_back(indiv.Chromo[i]);
								circAbord.push_back(tempt4);
							}
						}
						else if (indiv.Chromo[i].y>87)
						{
							JeiYai tempt1,tempt2,tempt3,tempt4;//�������ĸ�����
							tempt1.y=indiv.Chromo[i].y+sqrt(13*13-pow(indiv.Chromo[i].x,2));
							if (tempt1.y<100)
							{
								tempt1.x=0;
								tempt1.Circ.push_back(indiv.Chromo[i]);
								circAbord.push_back(tempt1);
							}
							
							tempt2.y=indiv.Chromo[i].y-sqrt(13*13-pow(indiv.Chromo[i].x,2));
							tempt2.x=0;
							tempt2.Circ.push_back(indiv.Chromo[i]);
							circAbord.push_back(tempt2);
							
							tempt3.x=indiv.Chromo[i].x-sqrt(13*13-pow(100-indiv.Chromo[i].y,2));
							if (tempt3.x>0)
							{
								tempt3.y=100;
								tempt3.Circ.push_back(indiv.Chromo[i]);
								circAbord.push_back(tempt3);
							}
							
							tempt4.x=indiv.Chromo[i].x+sqrt(13*13-pow(100-indiv.Chromo[i].y,2));
							tempt4.y=100;
							tempt4.Circ.push_back(indiv.Chromo[i]);
							circAbord.push_back(tempt4);
							
						} 
						else
						{
							JeiYai tempt1,tempt2;
							tempt1.x=0;
							tempt1.y=indiv.Chromo[i].y+sqrt(13*13-pow(indiv.Chromo[i].x,2));
							tempt1.Circ.push_back(indiv.Chromo[i]);
							circAbord.push_back(tempt1);
							
							tempt2.x=0;
							tempt2.y=indiv.Chromo[i].y-sqrt(13*13-pow(indiv.Chromo[i].x,2));
							tempt2.Circ.push_back(indiv.Chromo[i]);
							circAbord.push_back(tempt2);
							
						}

					}
					else if (indiv.Chromo[i].x>87)
					{
						if (indiv.Chromo[i].y<13)
						{
							JeiYai tempt1,tempt2,tempt3,tempt4;//�������ĸ�����
							tempt1.y=indiv.Chromo[i].y+sqrt(13*13-pow(100-indiv.Chromo[i].x,2));
							tempt1.x=100;
							tempt1.Circ.push_back(indiv.Chromo[i]);
							circAbord.push_back(tempt1);
							
							tempt2.y=indiv.Chromo[i].y-sqrt(13*13-pow(100-indiv.Chromo[i].x,2));
							if (tempt2.y>0)
							{
								tempt2.x=100;
								tempt2.Circ.push_back(indiv.Chromo[i]);
								circAbord.push_back(tempt2);
							}
							
							tempt3.x=indiv.Chromo[i].x-sqrt(13*13-pow(indiv.Chromo[i].y,2));
							tempt3.y=0;
							tempt3.Circ.push_back(indiv.Chromo[i]);
							circAbord.push_back(tempt3);
							
							tempt4.x=indiv.Chromo[i].x+sqrt(13*13-pow(indiv.Chromo[i].y,2));
							if (tempt4.x<100)
							{
								tempt4.y=0;
								tempt4.Circ.push_back(indiv.Chromo[i]);
								circAbord.push_back(tempt4);
							}
							
						}
						else if (indiv.Chromo[i].y>87)
						{
							JeiYai tempt1,tempt2,tempt3,tempt4;//�������ĸ�����
							tempt1.y=indiv.Chromo[i].y+sqrt(13*13-pow(100-indiv.Chromo[i].x,2));
							if (tempt1.y<100)
							{
								tempt1.x=100;
								tempt1.Circ.push_back(indiv.Chromo[i]);
								circAbord.push_back(tempt1);
							}
							
							tempt2.y=indiv.Chromo[i].y-sqrt(13*13-pow(100-indiv.Chromo[i].x,2));
							tempt2.x=100;
							tempt2.Circ.push_back(indiv.Chromo[i]);
							circAbord.push_back(tempt2);
							
							tempt3.x=indiv.Chromo[i].x-sqrt(13*13-pow(100-indiv.Chromo[i].y,2));
							tempt3.y=100;
							tempt3.Circ.push_back(indiv.Chromo[i]);
							circAbord.push_back(tempt3);
							
							tempt4.x=indiv.Chromo[i].x+sqrt(13*13-pow(100-indiv.Chromo[i].y,2));
							if (tempt4.x<100)
							{
								tempt4.y=100;
								tempt4.Circ.push_back(indiv.Chromo[i]);
								circAbord.push_back(tempt4);
							}
						} 
						else
						{
							JeiYai tempt1,tempt2;
							tempt1.x=100;
							tempt1.y=indiv.Chromo[i].y+sqrt(13*13-pow(100-indiv.Chromo[i].x,2));
							tempt1.Circ.push_back(indiv.Chromo[i]);
							circAbord.push_back(tempt1);

							tempt2.x=100;
							tempt2.y=indiv.Chromo[i].y-sqrt(13*13-pow(100-indiv.Chromo[i].x,2));
							tempt2.Circ.push_back(indiv.Chromo[i]);
							circAbord.push_back(tempt2);
							
						}
					} 
					else
					{
						if (indiv.Chromo[i].y<13)
						{
							JeiYai tempt1,tempt2;
							tempt1.x=indiv.Chromo[i].x+sqrt(13*13-pow(indiv.Chromo[i].y,2));
							tempt1.y=0;
							tempt1.Circ.push_back(indiv.Chromo[i]);
							circAbord.push_back(tempt1);
							tempt2.x=indiv.Chromo[i].x-sqrt(13*13-pow(indiv.Chromo[i].y,2));
							tempt2.y=0;
							tempt2.Circ.push_back(indiv.Chromo[i]);
							circAbord.push_back(tempt2);
						} 
						else
						{
							JeiYai tempt1,tempt2;
							tempt1.x=indiv.Chromo[i].x+sqrt(13*13-pow(100-indiv.Chromo[i].y,2));
							tempt1.y=100;
							tempt1.Circ.push_back(indiv.Chromo[i]);
							circAbord.push_back(tempt1);
							tempt2.x=indiv.Chromo[i].x-sqrt(13*13-pow(100-indiv.Chromo[i].y,2));
							tempt2.y=100;
							tempt2.Circ.push_back(indiv.Chromo[i]);
							circAbord.push_back(tempt2);
						}

					}
				}

			//###############################################################
		}
	}

	//ȥ��circAbord������ĵ�,���������Ӧ��Բ
	for (int ry1=0;ry1<circAbord.size();ry1++)
	{
		for (int ry2=ry1+1;ry2<circAbord.size();ry2++)
		{
			if ((pow(circAbord[ry1].x-circAbord[ry2].x,2)+pow(circAbord[ry1].y-circAbord[ry2].y,2))<0.1)
			{
				for (int yuan=0;yuan<circAbord[ry2].Circ.size();yuan++)
				{
					circAbord[ry1].Circ.push_back(circAbord[ry2].Circ[yuan]);
				}

				circAbord.erase(circAbord.begin()+ry2);
				ry2--;
			}
		}
	}
	//circAbordȥ�������
	//���߽���ĸ�����Ҳѹ��circAbord��
	JeiYai temp;
	temp.x=0;
	temp.y=0;
	circAbord.push_back(temp);

	temp.x=0;
	temp.y=100;
	circAbord.push_back(temp);

	temp.x=100;
	temp.y=100;
	circAbord.push_back(temp);

	temp.x=100;
	temp.y=0;
	circAbord.push_back(temp);
//��circAbord�еİ����ѡ��okpoint��
	for (int cab=0;cab<circAbord.size();cab++)
	{
		int sg=0;
		for (int mar=0;mar<margin.size();mar++)
		{
			if (sqrt(pow(circAbord[cab].x-margin[mar].x,2)+pow(circAbord[cab].y-margin[mar].y,2))<13.0)
			{
				sg=1;
				for (int yz=0;yz<circAbord[cab].Circ.size();yz++)
				{
					if ((circAbord[cab].Circ[yz].x==margin[mar].x)&&(circAbord[cab].Circ[yz].y==margin[mar].y))
					{
						sg=0;
					}
				}
				if (sg==1)
				{
					break;
				}
			}
		}
		if (sg==0)
		{
			double a=sqrt(pow(circAbord[cab].x-50.0,2)+pow(circAbord[cab].y-50.0,2));
			double c=sqrt(pow(circAbord[cab].x-100.0,2)+pow(circAbord[cab].y-50.0,2));		
			if(circAbord[cab].y>=50)
			{
				circAbord[cab].rad=acos((a*a+50*50-c*c)/(2*a*50.0));		
			} 
			else
			{
				circAbord[cab].rad=2*PI-acos((a*a+50*50-c*c)/(2*a*50.0));	
			}
			okPoint.push_back(circAbord[cab]);
		}

	}

	//��okPoint��ĵ㼯����������
	double totalS=0;//�洢�������
	for (int paixu1=0;paixu1<okPoint.size();paixu1++)
	{//���㰴���ȴ�С����
		for (int paixu2=paixu1+1;paixu2<okPoint.size();paixu2++)
		{
			if (okPoint[paixu1].rad>okPoint[paixu2].rad)
			{
				JeiYai tp;
				tp=okPoint[paixu2];
				okPoint[paixu2]=okPoint[paixu1];
				okPoint[paixu1]=tp;
			}
		}
		if (paixu1>=1)
		{
			totalS+=0.5*(okPoint[paixu1-1].y+okPoint[paixu1].y)*(okPoint[paixu1-1].x-okPoint[paixu1].x);
			int mark=0;//�ж��������Ƿ���ͬһԲ��
			vector<int>circ;
			int circNo;//��¼ͬ��Բ�ı��
			for (int ma1=0;ma1<okPoint[paixu1-1].Circ.size();ma1++)
			{
				
				for (int ma2=0;ma2<okPoint[paixu1].Circ.size();ma2++)
				{
					if ((okPoint[paixu1-1].Circ[ma1].x==okPoint[paixu1].Circ[ma2].x)&&(okPoint[paixu1-1].Circ[ma1].y==okPoint[paixu1].Circ[ma2].y))
					{
						mark=1;//��ͬһԲ��
						circ.push_back(ma2); //��ͬһ��Բ�洢������circz��
					}
				}
			}
			if (mark==1)
			{
				circNo=circ[0];//��circ�е�Բ���ҳ�����һ��
				for (int cir=1;cir<circ.size();cir++)
				{
					double d0=sqrt(pow(okPoint[paixu1].Circ[circNo].x-50.0,2)+pow(okPoint[paixu1].Circ[circNo].y-50.0,2));
					double dd=sqrt(pow(okPoint[paixu1].Circ[circ[cir]].x-50.0,2)+pow(okPoint[paixu1].Circ[circ[cir]].y-50.0,2));
					if(dd>d0)
					{
						circNo=circ[cir];
					}
				}
				double d=sqrt(pow(okPoint[paixu1-1].x-okPoint[paixu1].x,2)+pow(okPoint[paixu1-1].y-okPoint[paixu1].y,2));
				if (d>26.0)
				{
					d=26.0;
				}
				double r=acos((13*13+13*13-d*d)/(2*13*13.0));
				// �Ż��ӻ��б�(�ο����Ʊ���)
				double X2_X1=okPoint[paixu1-1].x-okPoint[paixu1].x;//X2-X1
				if (X2_X1*X2_X1>0.01)
				{
					double A=((okPoint[paixu1-1].y-okPoint[paixu1].y)/X2_X1);
					double B=(okPoint[paixu1].y*okPoint[paixu1-1].x-okPoint[paixu1-1].y*okPoint[paixu1].x)/X2_X1;
					double panbei=(okPoint[paixu1].Circ[circNo].y-A*okPoint[paixu1].Circ[circNo].x-B)*X2_X1;
					if (panbei>0)
					{
						totalS+=((13*13*(2*PI-r)/2.0)+(d*13*cos(r/2.0)/2.0));
					}
					else
					{
						totalS+=((13*13*r/2.0)-(d*13*cos(r/2.0)/2.0));

					}
				}
				else
				{
					totalS+=((13*13*r/2.0)-(d*13*cos(r/2.0)/2.0));
				}
				
				
				}
		}
	}

				totalS+=0.5*(okPoint[okPoint.size()-1].y+okPoint[0].y)*(okPoint[okPoint.size()-1].x-okPoint[0].x);
				int mark=0;//�ж��������Ƿ���ͬһԲ��
				vector<int>circ;//��¼ͬ��Բ�ı��
				int circNo;
				for (int ma1=0;ma1<okPoint[okPoint.size()-1].Circ.size();ma1++)
				{
					for (int ma2=0;ma2<okPoint[0].Circ.size();ma2++)
					{
						if ((okPoint[okPoint.size()-1].Circ[ma1].x==okPoint[0].Circ[ma2].x)&&(okPoint[okPoint.size()-1].Circ[ma1].y==okPoint[0].Circ[ma2].y))
						{
							mark=1;//��ͬһԲ��
							circ.push_back(ma2);
						}
					}
				}
				if (mark==1)
				{
					circNo=circ[0];//��circ�е�Բ���ҳ�����һ��
					for (int cir=1;cir<circ.size();cir++)
					{
						double d0=sqrt(pow(okPoint[0].Circ[circNo].x-50.0,2)+pow(okPoint[0].Circ[circNo].y-50.0,2));
						double dd=sqrt(pow(okPoint[0].Circ[circ[cir]].x-50.0,2)+pow(okPoint[0].Circ[circ[cir]].y-50.0,2));
						if(dd>d0)
						{
							circNo=circ[cir];
						}
					}
					double d=sqrt(pow(okPoint[okPoint.size()-1].x-okPoint[0].x,2)+pow(okPoint[okPoint.size()-1].y-okPoint[0].y,2));
					if (d>26.0)
					{
						d=26.0;
					}
					double r=acos((13*13+13*13-d*d)/(2*13*13.0));
					// �Ż��ӻ��б�(�ο����Ʊ���)
					double X2_X1=okPoint[okPoint.size()-1].x-okPoint[0].x;//X2-X1
					if (X2_X1*X2_X1>0.01)
					{
						double A=((okPoint[okPoint.size()-1].y-okPoint[0].y)/X2_X1);
						double B=(okPoint[0].y*okPoint[okPoint.size()-1].x-okPoint[okPoint.size()-1].y*okPoint[0].x)/X2_X1;
						double panbei=(okPoint[okPoint.size()-1].Circ[circNo].y-A*okPoint[0].Circ[circNo].x-B)*X2_X1;
						if (panbei>0)
						{
							totalS+=((13*13*(2*PI-r)/2.0)+(d*13*cos(r/2.0)/2.0));
						}
						else
						{
							totalS+=((13*13*r/2.0)-(d*13*cos(r/2.0)/2.0));
						}
					}
					else
					{
						totalS+=((13*13*r/2.0)-(d*13*cos(r/2.0)/2.0));

					}					
				}



	OutS=totalS-10000.0;
	double TOT=S1+S2-OutS;
	if (TOT>10000.0)
	{
		TOT=9980.0;
	}

	crate=(TOT)/10000.0;
	circAbord.clear();
	okPoint.clear();
	margin.clear();
////////////////////////////Բ��������㷨//////////////////////////////////////////////
	return crate;
}



//******ͳ�Ƽ���״̬�����������ĺ���**********
int CTabuGADlg::StatActNum(UnitGT indiv)
{
	int actvNum=0;
	for (int i=0;i<LocasNum;i++)
	{
		if (indiv.Chromo[i].chara==1)
		{
			actvNum++;
		}
	}
	return actvNum;

}

//*******��Ӧ�ȼ��㺯��*********************

double CTabuGADlg::CalcuFitness(UnitGT indiv)
{
	double tempfit=1.0;
	

	double d = 0;//ԽСԽ��
	//���������ܼ��̶ȵ�Ӱ�����
	for (int i = 0; i< LocasNum ; i++ )
	{
		if (indiv.Chromo[i].chara == 1)
		{
			int adj = 1;//�ܼ��ȸ��Ӵ���
			for (int j = 0; j < LocasNum ;j++ )
			{
				if ( i != j && indiv.Chromo[j].chara == 1)//����ͬһ������
				{
					//��������ж����ĵ�����Ƿ�С��R
					
					double dd = sqrt(pow(indiv.Chromo[i].x - indiv.Chromo[j].x,2) + pow(indiv.Chromo[i].y - indiv.Chromo[j].y,2));
					if ( dd < sR)
					{
						d = d + adj*1/dd;
						adj++;
					}
				}
			}
		}
	}



	if (indiv.CovRate>0.98)  //�������ʲ��ò�ͬ����Ӧ�Ⱥ���
	{
	//	tempfit=0.9+0.15*indiv.CovRate+0.3*30/indiv.activNum;
		tempfit=0.7+0.4*indiv.CovRate*N0/indiv.activNum +0.4*exp(-d/10.0);
	
	}
	else 
	{
	//	tempfit=0.9*indiv.CovRate+0.1*30/indiv.activNum; 
		tempfit=0.2*indiv.CovRate+0.2*N0*indiv.CovRate/indiv.activNum + 0.3*exp(-d/10.0);

	}	
	return tempfit;

}

//*****����SITE�Ż��㷨�Ż���Ⱥ**************
//��ѡ��һ�������ĸ��壬ȥ�����е�������򣬼ӿ������ٶ�

void CTabuGADlg::SITEoptim(UnitGT group[])
{
		vector<int>tempopt;//����һ���䳤���飬��¼��ѡ���Ż����ĸ���
	tempopt.reserve(20);//Ԥ���ռ䣬ע�⺯��������Ը���������
//	srand(time(NULL)); //
	for (int i=0;i<UnitNum*0.2;i++)
	{
			        //////////���ѡȡ�Ż�����/////////
		int num;       //��������������,��¼�������Ż���������
		int flg=1;     
		while (flg)    //�жϸø����Ƿ�ѡ���Ż���
		{
			num=rand()%UnitNum;  //��������� 
			if (tempopt.size()==0)    //������Ż��ĸ�����Ϊ0��
			{
				flg=0;            //��flg��0��ֹͣѡ���Ż�����
			} 
			else                 //�����ڼ�¼���в�ѯ
			{	int j;
				for (j=0;j<tempopt.size();j++)
				{
					if (num==tempopt[j])  //���˸����ѱ��Ż��������ѡ���Ż�����
						break;	    
				}
				if (j==tempopt.size())   //��û�б�ѡ�����ֹͣѡ������ѭ��
				{
					flg=0;
				}
			}
			
		}
		/////////////////////////////////////////////////
		tempopt.push_back(num);//����num ����������Ż��б���

		if (group[num].CovRate<0.96||group[num].activNum<N0)
		{
			for (int ad=0;ad<LocasNum;ad++)
			{
				if (group[num].Chromo[ad].chara==0)
				{
					double pp=(rand()%1000)/1000.0;
					if (pp<0.3)
					{
						group[num].Chromo[ad].chara=1;
					}
				}
			}

			group[num].activNum=StatActNum(group[num]);
			group[num].CovRate=CalCoverRate(group[num]);
			group[num].fit=CalcuFitness(group[num]);

		} 
		else
		{
			//////////�Ե�num������Ż�����///////////////////////////
			for (int k=0;k<LocasNum;k++)
			{
				if (group[num].Chromo[k].chara==1)
				{	
					double suiji=(rand()%100)/100.0;
					
					if (suiji<0.85)
					{
						int Xlef,Xrig,Ybot,Ytop;//�����¼��������֪Բ����ؾ���
						if (group[num].Chromo[k].x-sR<0) //���Բ���ǳ�������ʾ�������
						{
							Xlef=0;                   //���֪������ؾ�����߽�ȥ��ʾ������߽�
						} 
						else
						{
							Xlef=group[num].Chromo[k].x-sR;
						}
						if (group[num].Chromo[k].x+sR>HL) //�ұ߽�ѡ��
						{
							Xrig=HL;
						} 
						else
						{
							Xrig=group[num].Chromo[k].x+sR;
						}
						if (group[num].Chromo[k].y-sR<0)           //�±߽�ѡ��
						{
							Ybot=0;
						} 
						else
						{
							Ybot=group[num].Chromo[k].y-sR;
						}
						if (group[num].Chromo[k].y+sR>HL)  //�ϱ߽�ѡ��
						{
							Ytop=HL;
						} 
						else
						{
							Ytop=group[num].Chromo[k].y+sR;
						}//�߽�ѡ�����
						
						int statearea=0;//ͳ�ƴ������������������ܸ���
						int statpixel=0;//ͳ���ظ����ǵ����ظ���
						
						for (int p=Ybot;p<Ytop+1;p=p+2)
						{
							for (int q=Xlef;q<Xrig+1;q=q+2)
							{
								double d=pow(q-group[num].Chromo[k].x,2)/(sR*sR*1.0)+pow(p-group[num].Chromo[k].y,2)/(sR*sR*1.0);
								if (d<=1)
								{
									statearea++;
									for (int cf=0;cf<LocasNum;cf++)
									{
										if ((group[num].Chromo[cf].chara==1)&&(cf!=k))
										{
											double dd=pow(q-group[num].Chromo[cf].x,2)/(sR*sR*1.0)+pow(p-group[num].Chromo[cf].y,2)/(sR*sR*1.0);
											if (dd<=1)
											{
												statpixel++;
												break;
											}
										}
									}
									
								}
							}
						}
						
						if (statpixel>=0.97*statearea)  //��������ʴ���97%
						{
							group[num].Chromo[k].chara=0; //���ô��������ó�����״̬
					}
					}
				}
				
			}
			///////////////////////////////////////////////////////////////	
			group[num].activNum=StatActNum(group[num]);
			group[num].CovRate=CalCoverRate(group[num]);
			group[num].fit=CalcuFitness(group[num]);
		}		
	}
	tempopt.clear();//����Ż������¼���Է�����

}

//***************�Ŵ��㷨*******************

void CTabuGADlg::GA(UnitGT Group[])
{
	//***��ѡ�񣩲������̶ĵķ���ѡ���������********
	double totalFitness=0; //��¼��Ⱥ��Ӧ���ܺ�
	vector<UnitGT> tempSon1; //����һ����ʱ����Ⱥ����ѡ�񽻲������ʹ��
	vector<UnitGT> tempSon2;  //�ڱ��������ʹ��
	tempSon1.reserve(UnitNum);//ΪtempSonԤ���ռ䣬ע��ʹ�ú����
	tempSon2.reserve(UnitNum);

	for (int i=0;i<UnitNum;i++)
	{
		totalFitness=totalFitness+Group[i].fit;
	}
//	srand(time(NULL));
	for (int m=0;m<UnitNum;m++)
	{
		double rad=(rand()%100000)/100000.0;//��������5λС����0-1֮��������
		double addFitness=0;
		for (int n=0;n<UnitNum;n++)
		{
			addFitness+=Group[n].fit;   //���̶��ۼӲ���
			double odds=addFitness/totalFitness; //�������ֵ
			if (odds>rad)                       //����ڸ���������
			{
				Group[n].number=m; //������Ⱥ�еĸ�����ţ�ʹ���������±����һ��
				Son.push_back(Group[n]);        //���������ѡ���Ӵ�
				tempSon1.push_back(Group[n]);    //����ʱ�Ӵ���Ⱥ�б����Ӵ���Ⱥ��Ϣ
				tempSon2.push_back(Group[n]);
				break;
			}

		}
	}
//***************************************
//**********����********************
	for (int acr=0;acr<(AcrossOdds*UnitNum/2);acr++) //���ݽ������ÿ��ѡ��һ�Խ��н���
	{
		UnitGT acrUn1,acrUn2;//������ʱ�����洢���������������������
		int acrnum=rand()%tempSon1.size();//����һ��0��tempSon.size()-1�������
		acrUn1=tempSon1[acrnum];
		tempSon1.erase(tempSon1.begin()+acrnum);//��ѡ����ĸ������ʱ�Ӵ���Ⱥ�����

		acrnum=rand()%tempSon1.size(); //ͬ��ѡ���ڶ�������
		acrUn2=tempSon1[acrnum];
		tempSon1.erase(tempSon1.begin()+acrnum);

		Loca tempLoca;//����һ���洢��������ı���
		for (int brp=0;brp<3;brp++) //�����ϵ�
		{
			int acrpoint=(rand()%(LocasNum-2))+1;//��������1-69֮��Ļ��򽻻���
			for (int point=acrpoint;point<LocasNum;point++) //��������
			{
				tempLoca=acrUn1.Chromo[point];
				acrUn1.Chromo[point]=acrUn2.Chromo[point];
				acrUn2.Chromo[point]=tempLoca;
			}
		}

		Son[acrUn1.number]=acrUn1;    //�����򽻻���ĸ�������Ӵ���Ⱥ��
		Son[acrUn2.number]=acrUn2;

	}
	tempSon1.clear();//ʹ���������ռ�
	//****************************************
//*****************����************************
	for (int var=0;var<UnitNum*VarOdds;var++)
	{
			UnitGT varUnit;//
			int varnum=rand()%tempSon2.size();
			varUnit=tempSon2[varnum];
			tempSon2.erase(tempSon2.begin()+varnum);
			for (int varn=0;varn<2;varn++) //ÿ������ѡ��������λ����
			{
				int locan=rand()%LocasNum;
				//varUnit.Chromo[locan].x=(rand()%87)+7; //�����µĻ���
				//varUnit.Chromo[locan].y=(rand()%87)+7;
				//���ļ���״̬
				if (varUnit.Chromo[locan].chara==1)
				{
					varUnit.Chromo[locan].chara=0;
				}
				else
				{
					varUnit.Chromo[locan].chara=1;
				}
				
			}
			Son[varUnit.number]=varUnit;

	}
	tempSon2.clear();//ʹ���������ռ�
//*************************************************
//****������Ⱥ�еĸ������ݣ����򸲸��ʡ���Ӧ��ֵ�ȣ�****
	for (int seqn=0;seqn<UnitNum;seqn++)
	{
		Son[seqn].CovRate=CalCoverRate(Son[seqn]); //������
		Son[seqn].activNum=StatActNum(Son[seqn]);//����״̬��������Ŀ
		Son[seqn].fit=CalcuFitness(Son[seqn]);//��Ӧ��ֵ
	}
}

//*******�ı��������*******************


void CTabuGADlg::TextOut(UnitGT HistBest)//������Ÿ��崫��������
{
	int nn=0;
	aa+="\r\n";
	aa+="��ʷ���Ÿ������꣺\r\n";
	for (int i=0;i<LocasNum;i++)
	{
		if (HistBest.Chromo[i].chara==1)
		{
			nn++;
			aa+="   (";
			bb.Format("%d",HistBest.Chromo[i].x);
			aa+=bb;
			aa+=",";
			bb.Format("%d",HistBest.Chromo[i].y);
			aa+=bb;
			aa+="); ";
				if (nn%5==0)
				{
					aa+="\r\n";
				}
		}
	}

}

//***ѡȡ��ǰ���ź���ʷ���Ÿ���******

void CTabuGADlg::chooseBest(UnitGT Group[])
{
	NOWbest=Group[0];//�洢��ǰ���ŵĸ���
	for (int i=1;i<UnitNum;i++)
	{
		if (NOWbest.fit<Group[i].fit)
		{
			NOWbest=Group[i];
			nNowbest=i; //�洢��ǰ���Ÿ�������Ⱥ�еı��
		}
	}
	if (NOWbest.fit>HISTbest.fit)
	{
		HISTbest=NOWbest;
	}

	StatRes temp;//ͳ�Ƶ�ǰ���ź���ʷ����
	temp.NnActNum=NOWbest.activNum;
	temp.Nfitn=NOWbest.fit;
	temp.HnActNum=HISTbest.activNum;
	temp.Hfitn=HISTbest.fit;
	SR.push_back(temp);
}

void CTabuGADlg::OnBUTtest() 
{
	// TODO: Add your control notification handler code here

	srand(time(NULL));//�����������������

	t1=GetTickCount();
	Mainpro();
	t2=GetTickCount();
	m_time=t2-t1;

	TextOut(HISTbest);
	m_textout=aa;
	UpdateData(FALSE);
	Invalidate(FALSE);

	
}

void CTabuGADlg::DrawPIC()
{
	CWnd *pWin=GetDlgItem(IDC_PIC1);//��ȡPIC1��ͼ����ָ��
	pWin->GetClientRect(recPIC1);//�ѿؼ��ĳ����������Ϣ������recPIC1��
	CDC *pDC= pWin->GetDC();//��ȡ�ÿؼ��Ļ���
	Rx=sR*recPIC1.Width()/HL;  //������ʾ�����״�ʹ�С�����������ĸ���������Ϊ��Բ
	Ry=sR*recPIC1.Height()/HL;

	int rrx=sR*(recPIC1.Width()-2*Rx)/HL;
	int rry=sR*(recPIC1.Height()-2*Ry)/HL;

	CRect itemRC1(0,0,recPIC1.Width(),recPIC1.Height());
	CBrush brush(RGB(230,230,230));
	pDC->FillRect(itemRC1,&brush);

	CBrush brush1;
	brush1.CreateSolidBrush(RGB(255,255,255));
	CBrush *pOldBrush1=pDC->SelectObject(&brush1);
	pDC->Rectangle(Rx,Ry,recPIC1.Width()-Rx,recPIC1.Height()-Ry);
	pDC->SelectObject(pOldBrush1);
	brush1.DeleteObject();

	for (int i=0;i<LocasNum;i++)
	{
		if (HISTbest.Chromo[i].chara==1)
		{
			//���ݻ�ͼ�����������
			int px=Rx+(HISTbest.Chromo[i].x*(recPIC1.Width()-2*Rx)/HL);
			int py=recPIC1.Height()-Ry-HISTbest.Chromo[i].y*(recPIC1.Height()-2*Ry)/HL;

			CBrush brush;
			brush.CreateSolidBrush(RGB(100,100,255));
			CBrush *pOldBrush=pDC->SelectObject(&brush);
			pDC->Ellipse(px-rrx,py-rry,px+rrx,py+rry);
			pDC->SelectObject(pOldBrush);
			brush.DeleteObject();

			CPen pen1;
			pen1.CreatePen(PS_SOLID,3,RGB(255,0,0));
			CPen *pOldPen=pDC->SelectObject(&pen1);
			pDC->Ellipse(px-3,py-3,px+3,py+3);


			CString szText="(",tempText;
			tempText.Format("%d",HISTbest.Chromo[i].x);
			szText+=tempText;
			szText+=",";
			tempText.Format("%d",HISTbest.Chromo[i].y);
			szText+=tempText;
			szText+=")";
			pDC->SelectObject(pOldPen);
	 		pen1.DeleteObject();

			pDC->SetTextColor(RGB(255,0,0));//�����ı���ɫ
			pDC->SetBkMode(TRANSPARENT); //����͸���ı���ģʽ
			pDC->TextOut(px+7,py-7,szText);

		}
	}

	CPen Pen3(PS_SOLID, 3, RGB(0, 255, 0));
	pDC->SelectObject(&Pen3);
	
	pDC->MoveTo(Rx,Ry);
	pDC->LineTo(Rx,recPIC1.Height()-Ry);
	
	pDC->MoveTo(Rx, recPIC1.Height()-Ry);
	pDC->LineTo(recPIC1.Width()-Rx,recPIC1.Height()-Ry);
	
	pDC->MoveTo(recPIC1.Width()-Rx,recPIC1.Height()-Ry);
	pDC->LineTo(recPIC1.Width()-Rx, Ry);
	
	pDC->MoveTo(recPIC1.Width()-Rx, Ry);
 	pDC->LineTo(Rx,Ry);
}

void CTabuGADlg::Mainpro()
{
	CString sznInherit,szAcrossOdds,szVarOdds,szUnitNum,szLocasNum;//��ȡ�Ŵ��㷨����
	m_nIheritimes.GetWindowText(sznInherit);
	m_acrOdds.GetWindowText(szAcrossOdds);
	m_varodds.GetWindowText(szVarOdds);
	m_unitnum.GetWindowText(szUnitNum);
	m_sensnum.GetWindowText(szLocasNum);

	nInherit=atoi(sznInherit);
	sznInherit.ReleaseBuffer(0);
	AcrossOdds=atof(szAcrossOdds);
	szAcrossOdds.ReleaseBuffer(0);
	VarOdds=atof(szVarOdds);
	szVarOdds.ReleaseBuffer(0);
	UnitNum=atoi(szUnitNum);
	szUnitNum.ReleaseBuffer(0);
	LocasNum=atoi(szLocasNum);
	szLocasNum.ReleaseBuffer(0);

	CTABU fTabu; //����һ�����������
	CString szcandnum,sztabuLg,szcricTimes;//��ȡ�����㷨����
	m_candnum.GetWindowText(szcandnum);
	m_tabulg.GetWindowText(sztabuLg);
	m_circtimes.GetWindowText(szcricTimes);
	fTabu.candnum=atoi(szcandnum);
	szcandnum.ReleaseBuffer(0);
	fTabu.tabuLg=atoi(sztabuLg);
	sztabuLg.ReleaseBuffer(0);
	fTabu.circTimes=atoi(szcricTimes);
	szcricTimes.ReleaseBuffer(0);

	Father.reserve(20);
	Son.reserve(20);

	SR.clear();  //ÿ��ͳ��֮ǰ�����һ�ι��̵���������
	SR.reserve(nInherit+5);

	
	InitiGene();
	
	HISTbest=Father[0];//����ʷ���Ÿ���ֵΪ������һ������
	
	for (int i=0;i<Father.size();i++)  //���䳤���鸳ֵ����������
	{
		nFather[i]=Father[i];          //��Ϊ����ĺ�������ֱ����vector������Ϊ����ֱ�Ӵ���
	}
	chooseBest(nFather);//�õ���ʼ��Ⱥ��Ϣ

	aa="��ʼ��Ⱥ���Ÿ���(SITE�Ż�ǰ)��\r\n";
	aa+="     ������������";
	bb.Format("%d",HISTbest.activNum);
	aa+=bb;
	aa+=" �����ʣ�";
	bb.Format("%f",HISTbest.CovRate);
	aa+=bb;
	aa+=" ��Ӧ��ֵ��";
	bb.Format("%f",HISTbest.fit);
	aa+=bb;
	aa+="\r\n";

	SITEoptim(nFather);//�Գ�ʼ��Ⱥ����SITE�Ż�
	chooseBest(nFather);//�õ���ʼ��ǰ���ź���ʷ����

	aa+="��ʼ��Ⱥ���Ÿ��壨SITE�Ż��󣩣�\r\n";
	aa+="     ������������";
	bb.Format("%d",HISTbest.activNum);
	aa+=bb;
	aa+=" �����ʣ�";
	bb.Format("%f",HISTbest.CovRate);
	aa+=bb;
	aa+=" ��Ӧ��ֵ��";
	bb.Format("%f",HISTbest.fit);
	aa+=bb;
	aa+="\r\n";

	for (int yc=0;yc<nInherit;yc++)
	{
		GA(nFather);//�����Ŵ��㷨���õ��Ӵ�
		for (int j=0;j<Son.size();j++) //�䳤���鸳ֵ����������
		{
			nSon[j]=Son[j];
		}

		if ((yc+1)%(2+int(yc/30))==0)
		{
			SITEoptim(nSon);//���Ӵ���Ⱥ����SITE�Ż�
		}
		
		chooseBest(nSon);//���µ�ǰ���ź���ʷ����
		aa+="��";
		bb.Format("%d",yc+1);
		aa+=bb;
		aa+="����\r\n";
		aa+="     ��ǰ���ţ�";
		aa+="������������";
		bb.Format("%d",NOWbest.activNum);
		aa+=bb;
		aa+=";�����ʣ�";
		bb.Format("%f",NOWbest.CovRate);
		aa+=bb;
		aa+=";��Ӧ��ֵ��";
		bb.Format("%f",NOWbest.fit);
		aa+=bb;
		aa+="\r\n";

		aa+="     ��ʷ���ţ�";
		aa+="������������";
		bb.Format("%d",HISTbest.activNum);
		aa+=bb;
		aa+=";�����ʣ�";
		bb.Format("%f",HISTbest.CovRate);
		aa+=bb;
		aa+=";��Ӧ��ֵ��";
		bb.Format("%f",HISTbest.fit);
		aa+=bb;
		aa+="\r\n";
		 
		for (int StoF=0;StoF<UnitNum;StoF++)//���Ӵ���������
		{
			nFather[StoF]=nSon[StoF];
		}
	

		Father.clear();
		Son.clear();		
	}

}

void CTabuGADlg::DrawPIC2() //���������ͼ����
{
	CWnd *pWin=GetDlgItem(IDC_PIC2);//��ȡPIC1��ͼ����ָ��
	CRect recPIC2;
	pWin->GetClientRect(recPIC2);//�ѿؼ��ĳ����������Ϣ������recPIC1��
	CDC *pDC= pWin->GetDC();//��ȡ�ÿؼ��Ļ���

	CRect itemRC2(0,0,recPIC2.Width(),recPIC2.Height());
	CBrush brush(RGB(255,255,255));
	pDC->FillRect(itemRC2,&brush);

	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(0,0,255));
	CPen *pOldPen=pDC->SelectObject(&pen);
	pDC->Rectangle(30,30,recPIC2.Width()-30,recPIC2.Height()-40);//���ڲ����ο�
	if ((nf==0)&&(nA==1))
	{
		int zxActN=(LocasNum-20)/10-1;//�����м�̶ȸ���(����������)
		int zxJG=(recPIC2.Height()-70)/(zxActN+1);//�̶ȼ��
		for (int zx=1;zx<zxActN+1;zx++)//����������������̶ȺͿ̶�ֵ
		{
			CString text;
			text.Format("%d",20+zx*10);
			pDC->SetTextColor(RGB(0,0,255));//�����ı���ɫ
			pDC->SetBkMode(TRANSPARENT); //����͸���ı���ģʽ
			pDC->TextOut(10,recPIC2.Height()-50-zx*zxJG,text);
			pDC->MoveTo(30,recPIC2.Height()-45-zx*zxJG);
			pDC->LineTo(35,recPIC2.Height()-45-zx*zxJG);
			
		}
		
		CString szText="��������������";			
		pDC->SetTextColor(RGB(0,0,255));//�����ı���ɫ
		pDC->SetBkMode(TRANSPARENT); //����͸���ı���ģʽ
		pDC->TextOut(0,5,szText);
		szText.Format("%d",LocasNum);
		pDC->TextOut(10,20,szText);
		szText.Format("%d",20);
		pDC->TextOut(10,recPIC2.Height()-50,szText);
	}


	if ((nf==1)&&(nA==0))
	{	
		int zxfitJG=(recPIC2.Height()-70)/5;//��Ӧ��ֵ�̶ȼ��
		for (int zxft=1;zxft<5;zxft++)
		{
			CString textft;
			textft.Format("%.2f",0.4+zxft*0.2);
			pDC->SetTextColor(RGB(0,0,255));//�����ı���ɫ
			pDC->SetBkMode(TRANSPARENT); //����͸���ı���ģʽ
			pDC->TextOut(recPIC2.Width()-30,recPIC2.Height()-46-zxft*zxfitJG,textft);
			pDC->MoveTo(recPIC2.Width()-30,recPIC2.Height()-40-zxft*zxfitJG);
			pDC->LineTo(recPIC2.Width()-35,recPIC2.Height()-40-zxft*zxfitJG);
		}
		CString szText="��Ӧ��ֵ";
		pDC->TextOut(recPIC2.Width()-80,5,szText);
		szText.Format("%.2f",0.4);
		pDC->TextOut(recPIC2.Width()-30,recPIC2.Height()-46,szText);
		szText.Format("%.2f",1.4);
		pDC->TextOut(recPIC2.Width()-30,24,szText);
	}



	pDC->SelectObject(pOldPen);
	pen.DeleteObject();




	//����ͳ�ƵĴ��м���������
	for (int i=2;i<SR.size();i++)
	{
		//����ͼ���������ת����ʾ����
		int Nactn=recPIC2.Height()-40-(SR[i].NnActNum-20)*(recPIC2.Height()-70)/(LocasNum-20);
		int Hactn=recPIC2.Height()-40-(SR[i].HnActNum-20)*(recPIC2.Height()-70)/(LocasNum-20);

		double Nfit=recPIC2.Height()-40-(SR[i].Nfitn-0.4)*(recPIC2.Height()-70)/1.0;
		double Hfit=recPIC2.Height()-40-(SR[i].Hfitn-0.4)*(recPIC2.Height()-70)/1.0;

		float space=(recPIC2.Width()-10-60.0)/(SR.size()-2);//�����������

		if ((i-2>=0)&&((i-2)%((SR.size()-2)/10)==0))   //���ƺ�����
		{
			CPen hxpen;
			hxpen.CreatePen(PS_SOLID,1,RGB(0,0,255));
			CPen *poldhx=pDC->SelectObject(&hxpen);
			pDC->MoveTo(30+(i-2)*space,recPIC2.Height()-40);
			pDC->LineTo(30+(i-2)*space,recPIC2.Height()-45);
			CString hxtext;
			hxtext.Format("%d",i-2);
			pDC->SetTextColor(RGB(0,0,255));//�����ı���ɫ
			pDC->SetBkMode(TRANSPARENT); //����͸���ı���ģʽ
			pDC->TextOut(30+(i-2)*space,recPIC2.Height()-40,hxtext);
			hxtext="�Ŵ�����";
			pDC->TextOut(recPIC2.Width()/2-25,recPIC2.Height()-20,hxtext);
			pDC->SelectObject(poldhx);
			hxpen.DeleteObject();

		}

		if ((nf==1)&&(nA==0))
		{

			CPen Npen;//������Ƶ�ǰ���ŵĻ���
			Npen.CreatePen(PS_SOLID,2,RGB(0,0,255));
			CPen *pOldPenN=pDC->SelectObject(&Npen);
			//	pDC->Ellipse(30+i*space-2,Nactn-2,30+i*space+2,Nactn+2);
			pDC->Ellipse(30+(i-2)*space-2,Nfit-2,30+(i-2)*space+2,Nfit+2);
			pDC->SelectObject(pOldPenN);
			Npen.DeleteObject();
			
			CPen Hpen;//���������ʷ�������ŵĻ���
			Hpen.CreatePen(PS_SOLID,2,RGB(255,0,0));
			CPen *pOldPenH=pDC->SelectObject(&Hpen);
			//		pDC->Ellipse(30+i*space-2,Hactn-2,30+i*space+2,Hactn+2);
			pDC->Ellipse(30+(i-2)*space-2,Hfit-2,30+(i-2)*space+2,Hfit+2);
			pDC->SelectObject(pOldPenH);
			Hpen.DeleteObject();

			CString textTitle; //�������
			textTitle="��Ӧ��ֵ�仯ͼ";
			pDC->SetTextColor(RGB(0,0,255));//�����ı���ɫ
			pDC->SetBkMode(TRANSPARENT); //����͸���ı���ģʽ
			pDC->TextOut(recPIC2.Width()/2-45,10,textTitle);

		}
		if ((nf==0)&&(nA==1))
		{
			CPen Npen;//������Ƶ�ǰ���ŵĻ���
			Npen.CreatePen(PS_SOLID,2,RGB(0,0,255));
			CPen *pOldPenN=pDC->SelectObject(&Npen);
			pDC->Ellipse(30+(i-2)*space-2,Nactn-2,30+(i-2)*space+2,Nactn+2);
		//	pDC->Ellipse(30+i*space-2,Nfit-2,30+i*space+2,Nfit+2);
			pDC->SelectObject(pOldPenN);
			Npen.DeleteObject();
			
			CPen Hpen;//���������ʷ�������ŵĻ���
			Hpen.CreatePen(PS_SOLID,2,RGB(255,0,0));
			CPen *pOldPenH=pDC->SelectObject(&Hpen);
			pDC->Ellipse(30+(i-2)*space-2,Hactn-2,30+(i-2)*space+2,Hactn+2);
		//	pDC->Ellipse(30+i*space-2,Hfit-2,30+i*space+2,Hfit+2);
			pDC->SelectObject(pOldPenH);
			Hpen.DeleteObject();

			CString textTitle; //�������
			textTitle="�����������仯ͼ";
			pDC->SetTextColor(RGB(0,0,255));//�����ı���ɫ
			pDC->SetBkMode(TRANSPARENT); //����͸���ı���ģʽ
			pDC->TextOut(recPIC2.Width()/2-45,10,textTitle);
		}
	}	
}

void CTabuGADlg::OnBUTsN() 
{
	// TODO: Add your control notification handler code here
	nA=1;
	nf=0;
	Invalidate(FALSE);	
	char* pszFileName="datafile.txt";
	CStdioFile myfile;
	CFileException fileException;
	if (myfile.Open(pszFileName,CFile::typeText|CFile::modeCreate|CFile::modeReadWrite),&fileException)
	{
		int n=SR.size();
		for (int i=2;i<n;i++)
		{
			CString str1,str2,str3,str4;
			str1.Format("%d",SR[i].NnActNum);
			str1=str1+" ";
			myfile.WriteString(str1);
			str2.Format("%d",SR[i].HnActNum);
			str2=str2+" ";
			myfile.WriteString(str2);
			str3.Format("%f",SR[i].Nfitn);
			str3=str3+" ";
			myfile.WriteString(str3);
			str4.Format("%f",SR[i].Hfitn);
			str4=str4;
			myfile.WriteString(str4);
			myfile.WriteString("\n");
		}
		myfile.Close();
	} 
	else
	{
		TRACE("���ܴ��ļ� %s,error=%u\n",pszFileName,fileException.m_cause);
	}
}

void CTabuGADlg::OnBUTsF() 
{
	// TODO: Add your control notification handler code here
	nA=0;
	nf=1;
	Invalidate(FALSE);
	
}

void CTabuGADlg::OnBUTstatStab() 
{
	// TODO: Add your control notification handler code here
	srand(time(NULL));//�����������������
	int Nstatnum;
	CString Astatnum;
	m_statnum.GetWindowText(Astatnum);
	Nstatnum=atoi(Astatnum);
	Astatnum.ReleaseBuffer(0);

	statStab.clear();
	statStab.reserve(Nstatnum+1);

	t1=GetTickCount();
	for (int ns=0;ns<Nstatnum;ns++)
	{
		Mainpro();
		statStab.push_back(HISTbest);//ͳ��ÿһ�ε���ʷ����
	}
	t2=GetTickCount();


	aa="ͳ�ƹ��������\r\n";
	UnitGT bestInBest=statStab[0];//�����¼��ʷ���Ÿ����е����Ÿ���
	int nstab=0;//ͳ�ƴ������ܸ���

	for (int j=0;j<statStab.size();j++)
	{
		nstab=nstab+statStab[j].activNum; //�ۼӴ������ܸ���
		if (statStab[j].fit>bestInBest.fit) //ѡ��ͳ�ƹ����е�������
		{
			bestInBest=statStab[j]; 
		}

		aa+="��";
		bb.Format("%d",j+1);
		aa+=bb;
		aa+="�Σ�\r\n";
		aa+="     ������������";
		bb.Format("%d",statStab[j].activNum);
		aa+=bb;
		aa+=";  �����ʣ�";
		bb.Format("%f",statStab[j].CovRate);
		aa+=bb;
		aa+=";  ��Ӧ��ֵ";
		bb.Format("%f",statStab[j].fit);
		aa+=bb;
		aa+="\r\n";

	}

	m_time=t2-t1;
	m_avernum=nstab*1.0/statStab.size();
	HISTbest=bestInBest;//����ʷ���Ÿ�ֵΪ��ͳ����ʷ����



	int nn=0;
	aa+="\r\n";
	aa+="ͳ�ƹ��������Ÿ��壺\r\n";
	aa+="     ������������";
	bb.Format("%d",HISTbest.activNum);
	aa+=bb;
	aa+=";  �����ʣ�";
	bb.Format("%f",HISTbest.CovRate);
	aa+=bb;
	aa+=";  ��Ӧ��ֵ��";
	bb.Format("%f",HISTbest.fit);
	aa+=bb;
	aa+="\r\n";
	aa+="���Ÿ������꣺\r\n";

	for (int i=0;i<LocasNum;i++)
	{
		if (HISTbest.Chromo[i].chara==1)
		{
			nn++;
			aa+="   (";
			bb.Format("%d",HISTbest.Chromo[i].x);
			aa+=bb;
			aa+=",";
			bb.Format("%d",HISTbest.Chromo[i].y);
			aa+=bb;
			aa+="); ";
			if (nn%5==0)
			{
				aa+="\r\n";
			}
		}
	}
	m_textout=aa;
	UpdateData(FALSE);
	Invalidate(FALSE);

	
}

void CTabuGADlg::DrawPIC3()
{
	CWnd *pWin=GetDlgItem(IDC_PIC3);//��ȡPIC1��ͼ����ָ��
	CRect recPIC3;
	pWin->GetClientRect(recPIC3);//�ѿؼ��ĳ����������Ϣ������recPIC1��
	CDC *pDC= pWin->GetDC();//��ȡ�ÿؼ��Ļ���

	CRect itemRC3(0,0,recPIC3.Width(),recPIC3.Height());
	CBrush brush(RGB(255,255,255));
	pDC->FillRect(itemRC3,&brush);

	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(0,0,255));
	CPen *pOldPen=pDC->SelectObject(&pen);
	pDC->Rectangle(30,10,recPIC3.Width()-10,recPIC3.Height()-20);//���ڲ����ο�

	float zxJG=(recPIC3.Height()-30.0)/5;//����������
	CString gstext;
	for (int i=0;i<6;i++)
	{
		pDC->MoveTo(30,recPIC3.Height()-20-i*zxJG);
		pDC->LineTo(35,recPIC3.Height()-20-i*zxJG);
		gstext.Format("%d",30+2*i);
		pDC->SetTextColor(RGB(0,0,255));//�����ı���ɫ
		pDC->SetBkMode(TRANSPARENT); //����͸���ı���ģʽ
		pDC->TextOut(10,recPIC3.Height()-28-i*zxJG,gstext);
	}
	
	float hxJG=(recPIC3.Width()-40.0)/statStab.size();//���������
	for (int j=0;j<statStab.size();j++)
	{
		pDC->MoveTo(30+(j+1)*hxJG,recPIC3.Height()-20);
		pDC->LineTo(30+(j+1)*hxJG,recPIC3.Height()-26);
		gstext.Format("%d",j+1);
		pDC->SetTextColor(RGB(0,0,255));//�����ı���ɫ
		pDC->SetBkMode(TRANSPARENT); //����͸���ı���ģʽ
		pDC->TextOut(30+(j+1)*hxJG,recPIC3.Height()-18,gstext);
		CPen pen1;
		pen1.CreatePen(PS_SOLID,3,RGB(255,0,0));
		CPen *pOldPen1=pDC->SelectObject(&pen1);
		//���㻭ͼ���������������
		int htzx=recPIC3.Height()-20-(statStab[j].activNum-30)*(recPIC3.Height()-30)/10;
		pDC->Ellipse(30+(j+1)*hxJG-3,htzx-3,30+(j+1)*hxJG+3,htzx+3);
		pDC->SelectObject(pOldPen1);
		pen1.DeleteObject();
	}
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();

}



/*
	
*/
