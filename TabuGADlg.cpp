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
	
	m_nIheritimes.SetWindowText("100");//遗传代数
	m_acrOdds.SetWindowText("0.8");//交叉概率
	m_varodds.SetWindowText("0.1");//变异概率
	m_unitnum.SetWindowText("20");//种群个数
	m_statnum.SetWindowText("5");
	m_sensnum.SetWindowText("80");
	
	m_circtimes.SetWindowText("200");//禁忌搜索总循环次数
	m_candnum.SetWindowText("10"); //禁忌搜索候选解个数
	m_tabulg.SetWindowText("10");//禁忌长度

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


//*********生成初始种群*************
void CTabuGADlg::InitiGene()
{
	//		srand(time(NULL));
	for (int i=0;i<UnitNum;i++)
	{//启发式初始布局
		UnitGT InitiTempUnit;       //定义个体临时对象
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
			InitiTempUnit.Chromo[y].chara=1;        //初始时每个传感器都设置为激活状态
		}
		
		for (int j=0;j<LocasNum;j++)
		{
			InitiTempUnit.Chromo[j].x=(rand()%101);
			InitiTempUnit.Chromo[j].y=(rand()%101);
			InitiTempUnit.Chromo[j].chara=1;        //初始时每个传感器都设置为激活状态
		}*/
		for ( int j=0;j<LocasNum;j++)
		{
			InitiTempUnit.Chromo[j].x=(rand()%int(HL));
			InitiTempUnit.Chromo[j].y=(rand()%int(HL));
			InitiTempUnit.Chromo[j].chara=1;        //初始时每个传感器都设置为激活状态
		}

		
		InitiTempUnit.number=i;//个体在种群中的序号
		
		InitiTempUnit.CovRate=CalCoverRate(InitiTempUnit); //获取个体覆盖率
		
		
		InitiTempUnit.activNum=StatActNum(InitiTempUnit); //获取个体被激活传感器的个数
		
		InitiTempUnit.fit=CalcuFitness(InitiTempUnit); //获取适应度
		Father.push_back(InitiTempUnit); //将个体压入初始父代种群中
	}

}


//********计算覆盖率函数***************
double CTabuGADlg::CalCoverRate(UnitGT indiv)
{

	//新方法
	double crate=0;   //定义覆盖率
	double S1=0;    //统计矢量多边形面积
	double S2=0;    //自由面积
	double OutS=0;  //界外面积
	vector<JeiYai>circAbord;//统计自由圆弧与边界的交点
	vector<JeiYai>okPoint;//统计最终包络点
	vector<Loca>margin;//记录边缘上的激活传感器，减少循环次数

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

			//计算每一个传感器的约束圆弧
			vector<cyclo>radArray;//定义每个圆存储约束圆弧的可变长数组
			radArray.reserve(5);//预留空间

			//统计约束圆弧////
			for (int j=0;j<LocasNum;j++)
			{
				if ((j!=i)&&(indiv.Chromo[j].chara==1))
				{
					//计算邻居节点的距离
					double dis=sqrt(pow(indiv.Chromo[i].x-indiv.Chromo[j].x,2)+pow(indiv.Chromo[i].y-indiv.Chromo[j].y,2));
					if (dis==0.0)//如果遇到两个圆重合则将重合的圆休眠
					{
						indiv.Chromo[j].chara=0;
						continue;//继续循环寻找下一个与圆i相交的圆
					}
					else if ((dis<26.0)&&(dis>0.0))//如果两圆有交集
					{
						cyclo tempRad;
						//计算圆j在圆i坐标系下的圆心极坐标角度
						double temdis=sqrt(pow(indiv.Chromo[j].x-(indiv.Chromo[i].x+13),2)+pow(indiv.Chromo[j].y-indiv.Chromo[i].y,2));
						double angleA;//反余弦公式计算得到角度
						if (indiv.Chromo[j].y>=indiv.Chromo[i].y)
						{
							angleA=acos((dis*dis+13*13-temdis*temdis)/(2*dis*13.0));
						}
						else
						{
							angleA=2*PI-acos((dis*dis+13*13-temdis*temdis)/(2*dis*13.0));
						}

						double angleB=acos((dis/2)/13.0);//得到相交弧度对应圆心角的一半
						tempRad.radian=2*angleB;

						if (angleA-angleB<0) //得到弧度起始角度
						{
							tempRad.start_angle=2*PI+(angleA-angleB);
						} 
						else
						{
							tempRad.start_angle=angleA-angleB;
						}
						tempRad.end_angle=tempRad.start_angle+2*angleB; //得到弧度结束角度

						tempRad.start_x=indiv.Chromo[i].x+13*cos(tempRad.start_angle);//计算起始点坐标
						tempRad.start_y=indiv.Chromo[i].y+13*sin(tempRad.start_angle);
						tempRad.end_x=indiv.Chromo[i].x+13*cos(tempRad.end_angle);//计算结束点坐标
						tempRad.end_y=indiv.Chromo[i].y+13*sin(tempRad.end_angle);
						radArray.push_back(tempRad);
					}
				}
			}
			//统计约束圆弧完成////


			if (radArray.size()>0) //如果有约束圆弧
			{
				//对radArray中的弧段按起点由小到大排序
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
				//排序完成////
				
				//合并约束圆弧弧度//确定起始点和结束点
				vector<cyclo>completeRad;//定义可变长数组用于存储合并后的约束圆弧弧度
				vector<cyclo>reviseRad;//用于修正最后一个合并圆弧的临时数组
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
				//如果存在两段以上的约束圆弧，且末段覆盖了前端段
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
							completeRad.erase(completeRad.begin());//注意此处始终为completeRad中的第一个元素，由于前面的循环不断在删除
							break;//跳出循环
						}
						else
						{
							completeRad.erase(completeRad.begin());

						}
					}
				}			
			//约束圆弧弧度合并完成
			//面积计算
				double ysyh=0.0;//定义存储约束圆弧的变量
				for (int hdtj=0;hdtj<completeRad.size();hdtj++)
				{
					ysyh+=completeRad[hdtj].radian;
				}
				if (2*PI-ysyh>0.005)//如果不是满弧
				{
					for (int mj=0;mj<completeRad.size();mj++)
					{//有向多边形面积累加
						S1+=0.5*((indiv.Chromo[i].y+completeRad[mj].end_y)*(completeRad[mj].end_x-indiv.Chromo[i].x)+(indiv.Chromo[i].y+completeRad[mj].start_y)*(indiv.Chromo[i].x-completeRad[mj].start_x));
						
					}
					S2+=13*13*(2*PI-ysyh)/2.0;//自由区域面积累加
				}

			//***统计界面外的节点******
				if (2*PI-ysyh>0.005) //仍然在不是满弧的情况下讨论
				{
					if ((indiv.Chromo[i].x<13)||(indiv.Chromo[i].x>87)||(indiv.Chromo[i].y<13)||(indiv.Chromo[i].y>87))
					{
						//记录圆与圆产生交点
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

            //节点统计完成

			} 
			else  //如果没有约束圆弧
			{
				//累加自由面积
				S2+=PI*13*13;
	
			}

			/////////////////一个传感器的覆盖面积计算完成////////////////////

				if ((indiv.Chromo[i].x<13)||(indiv.Chromo[i].x>87)||(indiv.Chromo[i].y<13)||(indiv.Chromo[i].y>87))
				{
					if (indiv.Chromo[i].x<13)
					{
						if (indiv.Chromo[i].y<13)
						{
							JeiYai tempt1,tempt2,tempt3,tempt4;//可能有四个交点
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
							JeiYai tempt1,tempt2,tempt3,tempt4;//可能有四个交点
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
							JeiYai tempt1,tempt2,tempt3,tempt4;//可能有四个交点
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
							JeiYai tempt1,tempt2,tempt3,tempt4;//可能有四个交点
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

	//去除circAbord中冗余的点,整理点所对应的圆
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
	//circAbord去冗余完成
	//将边界的四个顶点也压入circAbord中
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
//将circAbord中的包络点选入okpoint中
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

	//用okPoint里的点集计算界外面积
	double totalS=0;//存储整体面积
	for (int paixu1=0;paixu1<okPoint.size();paixu1++)
	{//将点按弧度从小到大
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
			int mark=0;//判断两个点是否在同一圆上
			vector<int>circ;
			int circNo;//记录同在圆的编号
			for (int ma1=0;ma1<okPoint[paixu1-1].Circ.size();ma1++)
			{
				
				for (int ma2=0;ma2<okPoint[paixu1].Circ.size();ma2++)
				{
					if ((okPoint[paixu1-1].Circ[ma1].x==okPoint[paixu1].Circ[ma2].x)&&(okPoint[paixu1-1].Circ[ma1].y==okPoint[paixu1].Circ[ma2].y))
					{
						mark=1;//在同一圆上
						circ.push_back(ma2); //将同一个圆存储与数组circz中
					}
				}
			}
			if (mark==1)
			{
				circNo=circ[0];//在circ中的圆，找出最靠外的一个
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
				// 优弧劣弧判别(参考本科毕设)
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
				int mark=0;//判断两个点是否在同一圆上
				vector<int>circ;//记录同在圆的编号
				int circNo;
				for (int ma1=0;ma1<okPoint[okPoint.size()-1].Circ.size();ma1++)
				{
					for (int ma2=0;ma2<okPoint[0].Circ.size();ma2++)
					{
						if ((okPoint[okPoint.size()-1].Circ[ma1].x==okPoint[0].Circ[ma2].x)&&(okPoint[okPoint.size()-1].Circ[ma1].y==okPoint[0].Circ[ma2].y))
						{
							mark=1;//在同一圆上
							circ.push_back(ma2);
						}
					}
				}
				if (mark==1)
				{
					circNo=circ[0];//在circ中的圆，找出最靠外的一个
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
					// 优弧劣弧判别(参考本科毕设)
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
////////////////////////////圆弧并面积算法//////////////////////////////////////////////
	return crate;
}



//******统计激活状态传感器个数的函数**********
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

//*******适应度计算函数*********************

double CTabuGADlg::CalcuFitness(UnitGT indiv)
{
	double tempfit=1.0;
	

	double d = 0;//越小越好
	//将传感器密集程度的影响加入
	for (int i = 0; i< LocasNum ; i++ )
	{
		if (indiv.Chromo[i].chara == 1)
		{
			int adj = 1;//密集度附加代价
			for (int j = 0; j < LocasNum ;j++ )
			{
				if ( i != j && indiv.Chromo[j].chara == 1)//不是同一个基因
				{
					//计算距离判断中心点距离是否小于R
					
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



	if (indiv.CovRate>0.98)  //按覆盖率采用不同的适应度函数
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

//*****运用SITE优化算法优化种群**************
//即选出一定比例的个体，去除其中的冗余基因，加快收敛速度

void CTabuGADlg::SITEoptim(UnitGT group[])
{
		vector<int>tempopt;//定义一个变长数组，记录已选择优化过的个体
	tempopt.reserve(20);//预留空间，注意函数结束后对该数组的清空
//	srand(time(NULL)); //
	for (int i=0;i<UnitNum*0.2;i++)
	{
			        //////////随机选取优化个体/////////
		int num;       //定义产生的随机数,记录即将被优化个体的序号
		int flg=1;     
		while (flg)    //判断该个体是否被选择优化过
		{
			num=rand()%UnitNum;  //产生随机数 
			if (tempopt.size()==0)    //如果已优化的个体数为0，
			{
				flg=0;            //则将flg置0，停止选择优化个体
			} 
			else                 //否则在记录表中查询
			{	int j;
				for (j=0;j<tempopt.size();j++)
				{
					if (num==tempopt[j])  //若此个体已被优化，则从新选择优化个体
						break;	    
				}
				if (j==tempopt.size())   //若没有被选择过则停止选择，跳出循环
				{
					flg=0;
				}
			}
			
		}
		/////////////////////////////////////////////////
		tempopt.push_back(num);//将第num 个体放入已优化列表中

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
			//////////对第num个体的优化操作///////////////////////////
			for (int k=0;k<LocasNum;k++)
			{
				if (group[num].Chromo[k].chara==1)
				{	
					double suiji=(rand()%100)/100.0;
					
					if (suiji<0.85)
					{
						int Xlef,Xrig,Ybot,Ytop;//定义记录传感器感知圆的外截矩形
						if (group[num].Chromo[k].x-sR<0) //如果圆覆盖超过了显示区域左边
						{
							Xlef=0;                   //则感知区域外截矩形左边界去显示区域左边界
						} 
						else
						{
							Xlef=group[num].Chromo[k].x-sR;
						}
						if (group[num].Chromo[k].x+sR>HL) //右边界选择
						{
							Xrig=HL;
						} 
						else
						{
							Xrig=group[num].Chromo[k].x+sR;
						}
						if (group[num].Chromo[k].y-sR<0)           //下边界选择
						{
							Ybot=0;
						} 
						else
						{
							Ybot=group[num].Chromo[k].y-sR;
						}
						if (group[num].Chromo[k].y+sR>HL)  //上边界选择
						{
							Ytop=HL;
						} 
						else
						{
							Ytop=group[num].Chromo[k].y+sR;
						}//边界选择完成
						
						int statearea=0;//统计传感器覆盖区域像素总个数
						int statpixel=0;//统计重复覆盖的像素个数
						
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
						
						if (statpixel>=0.97*statearea)  //如果覆盖率大于97%
						{
							group[num].Chromo[k].chara=0; //将该传感器设置成休眠状态
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
	tempopt.clear();//清空优化个体记录表，以防出错

}

//***************遗传算法*******************

void CTabuGADlg::GA(UnitGT Group[])
{
	//***（选择）采用轮盘赌的方法选择优秀个体********
	double totalFitness=0; //记录种群适应度总和
	vector<UnitGT> tempSon1; //定义一个临时子种群，在选择交叉过程中使用
	vector<UnitGT> tempSon2;  //在变异过程中使用
	tempSon1.reserve(UnitNum);//为tempSon预留空间，注意使用后清除
	tempSon2.reserve(UnitNum);

	for (int i=0;i<UnitNum;i++)
	{
		totalFitness=totalFitness+Group[i].fit;
	}
//	srand(time(NULL));
	for (int m=0;m<UnitNum;m++)
	{
		double rad=(rand()%100000)/100000.0;//产生具有5位小数的0-1之间的随机数
		double addFitness=0;
		for (int n=0;n<UnitNum;n++)
		{
			addFitness+=Group[n].fit;   //轮盘赌累加操作
			double odds=addFitness/totalFitness; //计算概率值
			if (odds>rad)                       //如果在概率区间内
			{
				Group[n].number=m; //更改种群中的个体序号，使其与数组下标序号一致
				Son.push_back(Group[n]);        //将优秀个体选入子代
				tempSon1.push_back(Group[n]);    //在临时子代种群中备份子代种群信息
				tempSon2.push_back(Group[n]);
				break;
			}

		}
	}
//***************************************
//**********交叉********************
	for (int acr=0;acr<(AcrossOdds*UnitNum/2);acr++) //根据交叉概率每次选出一对进行交叉
	{
		UnitGT acrUn1,acrUn2;//两个临时变量存储产生交叉操作的两个个体
		int acrnum=rand()%tempSon1.size();//产生一个0到tempSon.size()-1的随机数
		acrUn1=tempSon1[acrnum];
		tempSon1.erase(tempSon1.begin()+acrnum);//将选择过的个体从临时子代种群中清除

		acrnum=rand()%tempSon1.size(); //同理选出第二个个体
		acrUn2=tempSon1[acrnum];
		tempSon1.erase(tempSon1.begin()+acrnum);

		Loca tempLoca;//定义一个存储交换基因的变量
		for (int brp=0;brp<3;brp++) //三个断点
		{
			int acrpoint=(rand()%(LocasNum-2))+1;//产生处于1-69之间的基因交换点
			for (int point=acrpoint;point<LocasNum;point++) //交换基因
			{
				tempLoca=acrUn1.Chromo[point];
				acrUn1.Chromo[point]=acrUn2.Chromo[point];
				acrUn2.Chromo[point]=tempLoca;
			}
		}

		Son[acrUn1.number]=acrUn1;    //将基因交换后的个体存入子代种群中
		Son[acrUn2.number]=acrUn2;

	}
	tempSon1.clear();//使用完后清理空间
	//****************************************
//*****************变异************************
	for (int var=0;var<UnitNum*VarOdds;var++)
	{
			UnitGT varUnit;//
			int varnum=rand()%tempSon2.size();
			varUnit=tempSon2[varnum];
			tempSon2.erase(tempSon2.begin()+varnum);
			for (int varn=0;varn<2;varn++) //每个个体选两个基因位变异
			{
				int locan=rand()%LocasNum;
				//varUnit.Chromo[locan].x=(rand()%87)+7; //产生新的基因
				//varUnit.Chromo[locan].y=(rand()%87)+7;
				//更改激活状态
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
	tempSon2.clear();//使用完后清理空间
//*************************************************
//****生成种群中的个体数据（区域覆盖率、适应度值等）****
	for (int seqn=0;seqn<UnitNum;seqn++)
	{
		Son[seqn].CovRate=CalCoverRate(Son[seqn]); //覆盖率
		Son[seqn].activNum=StatActNum(Son[seqn]);//激活状态传感器数目
		Son[seqn].fit=CalcuFitness(Son[seqn]);//适应度值
	}
}

//*******文本输出函数*******************


void CTabuGADlg::TextOut(UnitGT HistBest)//输出最优个体传感器坐标
{
	int nn=0;
	aa+="\r\n";
	aa+="历史最优个体坐标：\r\n";
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

//***选取当前最优和历史最优个体******

void CTabuGADlg::chooseBest(UnitGT Group[])
{
	NOWbest=Group[0];//存储当前最优的个体
	for (int i=1;i<UnitNum;i++)
	{
		if (NOWbest.fit<Group[i].fit)
		{
			NOWbest=Group[i];
			nNowbest=i; //存储当前最优个体在种群中的标号
		}
	}
	if (NOWbest.fit>HISTbest.fit)
	{
		HISTbest=NOWbest;
	}

	StatRes temp;//统计当前最优和历史最优
	temp.NnActNum=NOWbest.activNum;
	temp.Nfitn=NOWbest.fit;
	temp.HnActNum=HISTbest.activNum;
	temp.Hfitn=HISTbest.fit;
	SR.push_back(temp);
}

void CTabuGADlg::OnBUTtest() 
{
	// TODO: Add your control notification handler code here

	srand(time(NULL));//设置随机数的种子数

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
	CWnd *pWin=GetDlgItem(IDC_PIC1);//获取PIC1绘图区域指针
	pWin->GetClientRect(recPIC1);//把控件的长宽、坐标等信息保存在recPIC1里
	CDC *pDC= pWin->GetDC();//获取该控件的画布
	Rx=sR*recPIC1.Width()/HL;  //根据显示框的形状和大小，将传感器的覆盖区域考虑为椭圆
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
			//根据绘图区域放缩坐标
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

			pDC->SetTextColor(RGB(255,0,0));//设置文本颜色
			pDC->SetBkMode(TRANSPARENT); //设置透明的背景模式
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
	CString sznInherit,szAcrossOdds,szVarOdds,szUnitNum,szLocasNum;//获取遗传算法参数
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

	CTABU fTabu; //定义一个禁忌类对象
	CString szcandnum,sztabuLg,szcricTimes;//获取禁忌算法参数
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

	SR.clear();  //每次统计之前清空上一次过程的遗留数据
	SR.reserve(nInherit+5);

	
	InitiGene();
	
	HISTbest=Father[0];//将历史最优赋初值为父代第一个个体
	
	for (int i=0;i<Father.size();i++)  //将变长数组赋值给定长数组
	{
		nFather[i]=Father[i];          //因为后面的函数不能直接用vector数组作为参数直接传入
	}
	chooseBest(nFather);//得到初始种群信息

	aa="初始种群最优个体(SITE优化前)：\r\n";
	aa+="     传感器个数：";
	bb.Format("%d",HISTbest.activNum);
	aa+=bb;
	aa+=" 覆盖率：";
	bb.Format("%f",HISTbest.CovRate);
	aa+=bb;
	aa+=" 适应度值：";
	bb.Format("%f",HISTbest.fit);
	aa+=bb;
	aa+="\r\n";

	SITEoptim(nFather);//对初始种群进行SITE优化
	chooseBest(nFather);//得到初始当前最优和历史最优

	aa+="初始种群最优个体（SITE优化后）：\r\n";
	aa+="     传感器个数：";
	bb.Format("%d",HISTbest.activNum);
	aa+=bb;
	aa+=" 覆盖率：";
	bb.Format("%f",HISTbest.CovRate);
	aa+=bb;
	aa+=" 适应度值：";
	bb.Format("%f",HISTbest.fit);
	aa+=bb;
	aa+="\r\n";

	for (int yc=0;yc<nInherit;yc++)
	{
		GA(nFather);//调用遗传算法，得到子代
		for (int j=0;j<Son.size();j++) //变长数组赋值给定长数组
		{
			nSon[j]=Son[j];
		}

		if ((yc+1)%(2+int(yc/30))==0)
		{
			SITEoptim(nSon);//对子代种群进行SITE优化
		}
		
		chooseBest(nSon);//更新当前最优和历史最优
		aa+="第";
		bb.Format("%d",yc+1);
		aa+=bb;
		aa+="代：\r\n";
		aa+="     当前最优：";
		aa+="传感器个数：";
		bb.Format("%d",NOWbest.activNum);
		aa+=bb;
		aa+=";覆盖率：";
		bb.Format("%f",NOWbest.CovRate);
		aa+=bb;
		aa+=";适应度值：";
		bb.Format("%f",NOWbest.fit);
		aa+=bb;
		aa+="\r\n";

		aa+="     历史最优：";
		aa+="传感器个数：";
		bb.Format("%d",HISTbest.activNum);
		aa+=bb;
		aa+=";覆盖率：";
		bb.Format("%f",HISTbest.CovRate);
		aa+=bb;
		aa+=";适应度值：";
		bb.Format("%f",HISTbest.fit);
		aa+=bb;
		aa+="\r\n";
		 
		for (int StoF=0;StoF<UnitNum;StoF++)//将子代赋给父代
		{
			nFather[StoF]=nSon[StoF];
		}
	

		Father.clear();
		Son.clear();		
	}

}

void CTabuGADlg::DrawPIC2() //过程输出绘图函数
{
	CWnd *pWin=GetDlgItem(IDC_PIC2);//获取PIC1绘图区域指针
	CRect recPIC2;
	pWin->GetClientRect(recPIC2);//把控件的长宽、坐标等信息保存在recPIC1里
	CDC *pDC= pWin->GetDC();//获取该控件的画布

	CRect itemRC2(0,0,recPIC2.Width(),recPIC2.Height());
	CBrush brush(RGB(255,255,255));
	pDC->FillRect(itemRC2,&brush);

	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(0,0,255));
	CPen *pOldPen=pDC->SelectObject(&pen);
	pDC->Rectangle(30,30,recPIC2.Width()-30,recPIC2.Height()-40);//画内部矩形框
	if ((nf==0)&&(nA==1))
	{
		int zxActN=(LocasNum-20)/10-1;//纵向中间刻度个数(传感器个数)
		int zxJG=(recPIC2.Height()-70)/(zxActN+1);//刻度间隔
		for (int zx=1;zx<zxActN+1;zx++)//画传感器个数坐标刻度和刻度值
		{
			CString text;
			text.Format("%d",20+zx*10);
			pDC->SetTextColor(RGB(0,0,255));//设置文本颜色
			pDC->SetBkMode(TRANSPARENT); //设置透明的背景模式
			pDC->TextOut(10,recPIC2.Height()-50-zx*zxJG,text);
			pDC->MoveTo(30,recPIC2.Height()-45-zx*zxJG);
			pDC->LineTo(35,recPIC2.Height()-45-zx*zxJG);
			
		}
		
		CString szText="传感器数（个）";			
		pDC->SetTextColor(RGB(0,0,255));//设置文本颜色
		pDC->SetBkMode(TRANSPARENT); //设置透明的背景模式
		pDC->TextOut(0,5,szText);
		szText.Format("%d",LocasNum);
		pDC->TextOut(10,20,szText);
		szText.Format("%d",20);
		pDC->TextOut(10,recPIC2.Height()-50,szText);
	}


	if ((nf==1)&&(nA==0))
	{	
		int zxfitJG=(recPIC2.Height()-70)/5;//适应度值刻度间隔
		for (int zxft=1;zxft<5;zxft++)
		{
			CString textft;
			textft.Format("%.2f",0.4+zxft*0.2);
			pDC->SetTextColor(RGB(0,0,255));//设置文本颜色
			pDC->SetBkMode(TRANSPARENT); //设置透明的背景模式
			pDC->TextOut(recPIC2.Width()-30,recPIC2.Height()-46-zxft*zxfitJG,textft);
			pDC->MoveTo(recPIC2.Width()-30,recPIC2.Height()-40-zxft*zxfitJG);
			pDC->LineTo(recPIC2.Width()-35,recPIC2.Height()-40-zxft*zxfitJG);
		}
		CString szText="适应度值";
		pDC->TextOut(recPIC2.Width()-80,5,szText);
		szText.Format("%.2f",0.4);
		pDC->TextOut(recPIC2.Width()-30,recPIC2.Height()-46,szText);
		szText.Format("%.2f",1.4);
		pDC->TextOut(recPIC2.Width()-30,24,szText);
	}



	pDC->SelectObject(pOldPen);
	pen.DeleteObject();




	//绘制统计的传感激个数过程
	for (int i=2;i<SR.size();i++)
	{
		//根据图像输出区域转化显示坐标
		int Nactn=recPIC2.Height()-40-(SR[i].NnActNum-20)*(recPIC2.Height()-70)/(LocasNum-20);
		int Hactn=recPIC2.Height()-40-(SR[i].HnActNum-20)*(recPIC2.Height()-70)/(LocasNum-20);

		double Nfit=recPIC2.Height()-40-(SR[i].Nfitn-0.4)*(recPIC2.Height()-70)/1.0;
		double Hfit=recPIC2.Height()-40-(SR[i].Hfitn-0.4)*(recPIC2.Height()-70)/1.0;

		float space=(recPIC2.Width()-10-60.0)/(SR.size()-2);//计算横坐标间隔

		if ((i-2>=0)&&((i-2)%((SR.size()-2)/10)==0))   //绘制横坐标
		{
			CPen hxpen;
			hxpen.CreatePen(PS_SOLID,1,RGB(0,0,255));
			CPen *poldhx=pDC->SelectObject(&hxpen);
			pDC->MoveTo(30+(i-2)*space,recPIC2.Height()-40);
			pDC->LineTo(30+(i-2)*space,recPIC2.Height()-45);
			CString hxtext;
			hxtext.Format("%d",i-2);
			pDC->SetTextColor(RGB(0,0,255));//设置文本颜色
			pDC->SetBkMode(TRANSPARENT); //设置透明的背景模式
			pDC->TextOut(30+(i-2)*space,recPIC2.Height()-40,hxtext);
			hxtext="遗传代数";
			pDC->TextOut(recPIC2.Width()/2-25,recPIC2.Height()-20,hxtext);
			pDC->SelectObject(poldhx);
			hxpen.DeleteObject();

		}

		if ((nf==1)&&(nA==0))
		{

			CPen Npen;//定义绘制当前最优的画笔
			Npen.CreatePen(PS_SOLID,2,RGB(0,0,255));
			CPen *pOldPenN=pDC->SelectObject(&Npen);
			//	pDC->Ellipse(30+i*space-2,Nactn-2,30+i*space+2,Nactn+2);
			pDC->Ellipse(30+(i-2)*space-2,Nfit-2,30+(i-2)*space+2,Nfit+2);
			pDC->SelectObject(pOldPenN);
			Npen.DeleteObject();
			
			CPen Hpen;//定义绘制历史最优最优的画笔
			Hpen.CreatePen(PS_SOLID,2,RGB(255,0,0));
			CPen *pOldPenH=pDC->SelectObject(&Hpen);
			//		pDC->Ellipse(30+i*space-2,Hactn-2,30+i*space+2,Hactn+2);
			pDC->Ellipse(30+(i-2)*space-2,Hfit-2,30+(i-2)*space+2,Hfit+2);
			pDC->SelectObject(pOldPenH);
			Hpen.DeleteObject();

			CString textTitle; //输出标题
			textTitle="适应度值变化图";
			pDC->SetTextColor(RGB(0,0,255));//设置文本颜色
			pDC->SetBkMode(TRANSPARENT); //设置透明的背景模式
			pDC->TextOut(recPIC2.Width()/2-45,10,textTitle);

		}
		if ((nf==0)&&(nA==1))
		{
			CPen Npen;//定义绘制当前最优的画笔
			Npen.CreatePen(PS_SOLID,2,RGB(0,0,255));
			CPen *pOldPenN=pDC->SelectObject(&Npen);
			pDC->Ellipse(30+(i-2)*space-2,Nactn-2,30+(i-2)*space+2,Nactn+2);
		//	pDC->Ellipse(30+i*space-2,Nfit-2,30+i*space+2,Nfit+2);
			pDC->SelectObject(pOldPenN);
			Npen.DeleteObject();
			
			CPen Hpen;//定义绘制历史最优最优的画笔
			Hpen.CreatePen(PS_SOLID,2,RGB(255,0,0));
			CPen *pOldPenH=pDC->SelectObject(&Hpen);
			pDC->Ellipse(30+(i-2)*space-2,Hactn-2,30+(i-2)*space+2,Hactn+2);
		//	pDC->Ellipse(30+i*space-2,Hfit-2,30+i*space+2,Hfit+2);
			pDC->SelectObject(pOldPenH);
			Hpen.DeleteObject();

			CString textTitle; //输出标题
			textTitle="传感器个数变化图";
			pDC->SetTextColor(RGB(0,0,255));//设置文本颜色
			pDC->SetBkMode(TRANSPARENT); //设置透明的背景模式
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
		TRACE("不能打开文件 %s,error=%u\n",pszFileName,fileException.m_cause);
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
	srand(time(NULL));//设置随机数的种子数
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
		statStab.push_back(HISTbest);//统计每一次的历史最优
	}
	t2=GetTickCount();


	aa="统计过程输出：\r\n";
	UnitGT bestInBest=statStab[0];//定义记录历史最优个体中的最优个体
	int nstab=0;//统计传感器总个数

	for (int j=0;j<statStab.size();j++)
	{
		nstab=nstab+statStab[j].activNum; //累加传感器总个数
		if (statStab[j].fit>bestInBest.fit) //选出统计过程中的最后个体
		{
			bestInBest=statStab[j]; 
		}

		aa+="第";
		bb.Format("%d",j+1);
		aa+=bb;
		aa+="次：\r\n";
		aa+="     传感器个数：";
		bb.Format("%d",statStab[j].activNum);
		aa+=bb;
		aa+=";  覆盖率：";
		bb.Format("%f",statStab[j].CovRate);
		aa+=bb;
		aa+=";  适应度值";
		bb.Format("%f",statStab[j].fit);
		aa+=bb;
		aa+="\r\n";

	}

	m_time=t2-t1;
	m_avernum=nstab*1.0/statStab.size();
	HISTbest=bestInBest;//将历史最优赋值为，统计历史最优



	int nn=0;
	aa+="\r\n";
	aa+="统计过程中最优个体：\r\n";
	aa+="     传感器个数：";
	bb.Format("%d",HISTbest.activNum);
	aa+=bb;
	aa+=";  覆盖率：";
	bb.Format("%f",HISTbest.CovRate);
	aa+=bb;
	aa+=";  适应度值：";
	bb.Format("%f",HISTbest.fit);
	aa+=bb;
	aa+="\r\n";
	aa+="最优个体坐标：\r\n";

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
	CWnd *pWin=GetDlgItem(IDC_PIC3);//获取PIC1绘图区域指针
	CRect recPIC3;
	pWin->GetClientRect(recPIC3);//把控件的长宽、坐标等信息保存在recPIC1里
	CDC *pDC= pWin->GetDC();//获取该控件的画布

	CRect itemRC3(0,0,recPIC3.Width(),recPIC3.Height());
	CBrush brush(RGB(255,255,255));
	pDC->FillRect(itemRC3,&brush);

	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(0,0,255));
	CPen *pOldPen=pDC->SelectObject(&pen);
	pDC->Rectangle(30,10,recPIC3.Width()-10,recPIC3.Height()-20);//画内部矩形框

	float zxJG=(recPIC3.Height()-30.0)/5;//计算纵向间隔
	CString gstext;
	for (int i=0;i<6;i++)
	{
		pDC->MoveTo(30,recPIC3.Height()-20-i*zxJG);
		pDC->LineTo(35,recPIC3.Height()-20-i*zxJG);
		gstext.Format("%d",30+2*i);
		pDC->SetTextColor(RGB(0,0,255));//设置文本颜色
		pDC->SetBkMode(TRANSPARENT); //设置透明的背景模式
		pDC->TextOut(10,recPIC3.Height()-28-i*zxJG,gstext);
	}
	
	float hxJG=(recPIC3.Width()-40.0)/statStab.size();//计算横向间隔
	for (int j=0;j<statStab.size();j++)
	{
		pDC->MoveTo(30+(j+1)*hxJG,recPIC3.Height()-20);
		pDC->LineTo(30+(j+1)*hxJG,recPIC3.Height()-26);
		gstext.Format("%d",j+1);
		pDC->SetTextColor(RGB(0,0,255));//设置文本颜色
		pDC->SetBkMode(TRANSPARENT); //设置透明的背景模式
		pDC->TextOut(30+(j+1)*hxJG,recPIC3.Height()-18,gstext);
		CPen pen1;
		pen1.CreatePen(PS_SOLID,3,RGB(255,0,0));
		CPen *pOldPen1=pDC->SelectObject(&pen1);
		//计算画图区域里的纵向坐标
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
