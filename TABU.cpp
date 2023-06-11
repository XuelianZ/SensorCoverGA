// TABU.cpp: implementation of the CTABU class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TabuGA.h"
#include "TABU.h"
#include "TabuGADlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTABU::CTABU()
{

}

CTABU::~CTABU()
{

}

void CTABU::electNowBest()
{
	/////将候选解列表中的个体根据适应度值排序////
	for (int num=0;num<candnum;num++)//只排前candnum(候选解个数)个
	{
		UnitGT tempUnit;
		for (int i=num+1;i<candlist.size();i++)
		{
			if (candlist[num].fit<candlist[i].fit)
			{
				tempUnit=candlist[num];
				candlist[num]=candlist[i];
				candlist[i]=tempUnit;
			}
		}
	}
	////////////////////////////////////////////
	
	/////兼顾特赦准则，获得候选解////////
	if (candlist.size()==0)//如果没有产生候选解
	{
		nowBest=nowBest; //将上一次的当前最优继续作为当前最优，重新做变换
	} 
	else
	{
		for (int candit=0;candit<candnum;candit++)
		{
			int judge=0;//0：不在禁忌表中，1：在禁忌表中且不满足特赦准则
			//2:在禁忌表中且满足特赦准则
			for (int ntb=0;ntb<tabulist.size();ntb++)
			{//如果在禁忌表中
			//	if (candlist[candit].chg1==tabulist[ntb].nGene||candlist[candit].chg2==tabulist[ntb].nGene)//
				if (candlist[candit].chg1==tabulist[ntb].nGene)
				{
					if (candlist[candit].fit>=hisBest.fit) //适应度值大于历史最优，满足特赦
					{
						nowBest=candlist[candit]; //更新当前最优
						hisBest=candlist[candit];//更改历史最优
						judge=2;//判断标记设置为2
						break;//跳出当前循环
					} 
					else //否则在禁忌表中且不满足特赦准则
					{
						judge=1;//将判断标志设置为1
					}
				}
			}
			
			if (judge==0)  //如果不在禁忌表中
			{
				nowBest=candlist[candit]; //此候选解为当前最优
				if (nowBest.fit>hisBest.fit)
				{
					hisBest=nowBest;
				}
			}
			else if (judge==1) //如果在禁忌表中且不满足特赦
			{
				if (candit==candnum-1) //如果所有候选解都不满足特赦
				{
					nowBest=nowBest;//将上一次的当前最优仍然保留为当前最优
					break;
				} 
				else
				{
					continue;//否则继续下一个循环
				}
			} 
			else
			{
				break; //满足特赦，跳出循环
			}
		}
	}
	/////////////////////////////////////////////
	//////////////更新禁忌表////////////////////
	TBList tempTb;//定义一个临时禁忌对象
	tempTb.nGene=nowBest.chg1;
	tempTb.ntime=tabuLg+1;
/*	TBList tempTb1,tempTb2;//定义两个临时禁忌对象
	if (nowBest.chg1==nowBest.chg2)//如果做的是sleep操作
	{
		tempTb1.nGene=nowBest.chg1;
		tempTb1.ntime=tabuLg+1;//注意比禁忌长度多一次，后面会统一减一
		tabulist.push_back(tempTb1);//压入禁忌表
	} 
	else //如果做的是swap操作
	{
		tempTb1.nGene=nowBest.chg1;
		tempTb1.ntime=tabuLg+1;
		tempTb2.nGene=nowBest.chg2;
		tempTb2.ntime=tabuLg+1;
		tabulist.push_back(tempTb1);
		tabulist.push_back(tempTb2);
	}
*/	
	for (int ntabu=0;ntabu<tabulist.size();ntabu++)
	{
		if (tabulist[ntabu].ntime==1)//如果禁忌次数为1
		{
			tabulist.erase(tabulist.begin()+ntabu);//释放禁忌
			ntabu--;//清除之后紧邻位会填补这个数字
		}
		tabulist[ntabu].ntime--;//否则将禁忌次数减1
	}
	//////////////////////////////////////////////////	
	////////////////清空候选解列表///////////////////
	candlist.clear();

	CString temcs="选择当前最优函数运行；";
	cssc+=temcs;

}

void CTABU::CreatCandidate(UnitGT indiv)
{
		CTabuGADlg Dlg;//定义一个对话框类对象
	/////////////////产生候选解///////////////////////////
	UnitGT tempIndiv=indiv;
	if (tempIndiv.CovRate<0.95||tempIndiv.activNum<25)//如果覆盖率过小或个数过少就激活传感器
	{
		for (int num1=0;num1<LocasNum;num1++)
		{
			if (tempIndiv.Chromo[num1].chara==0)
			{
				tempIndiv.Chromo[num1].chara=1;
				tempIndiv.chg1=num1;
				tempIndiv.CovRate=Dlg.CalCoverRate(tempIndiv);//计算个体参数
				tempIndiv.activNum=Dlg.StatActNum(tempIndiv);
				tempIndiv.fit=Dlg.CalcuFitness(tempIndiv);
				candlist.push_back(tempIndiv); //将个体压入候选解列表

			}
		}
	} 
	else
	{
			for (int num=0;num<LocasNum;num++)
		{
		if (tempIndiv.Chromo[num].chara==1)
			{
			double p_c=(rand()%1000)/1000.0;//产生一个随机概率
			if (p_c>0.5)//大于0.5则产生领域交换
				{
				int Xlef,Xrig,Ybot,Ytop;//定义记录传感器感知圆的外截矩形
				if (tempIndiv.Chromo[num].x-13<0) //如果圆覆盖超过了显示区域左边
				{
					Xlef=0;                   //则感知区域外截矩形左边界去显示区域左边界
				} 
				else
				{
					Xlef=tempIndiv.Chromo[num].x-13;
				}
				if (tempIndiv.Chromo[num].x+13>100) //右边界选择
				{
					Xrig=100;
				} 
				else
				{
					Xrig=tempIndiv.Chromo[num].x+13;
				}
				if (tempIndiv.Chromo[num].y-13<0)           //下边界选择
				{
					Ybot=0;
				} 
				else
				{
					Ybot=tempIndiv.Chromo[num].y-13;
				}
				if (tempIndiv.Chromo[num].y+13>100)  //上边界选择
				{
					Ytop=100;
				} 
				else
				{
					Ytop=tempIndiv.Chromo[num].y+13;
				}//边界选择完成
				tempIndiv.Chromo[num].x=Xlef+rand()%(Xrig-Xlef+1);
				tempIndiv.Chromo[num].y=Ybot+rand()%(Ytop-Ybot+1);
				tempIndiv.chg1=num;//记录产生变化的基因位，用于禁忌搜索
				tempIndiv.CovRate=Dlg.CalCoverRate(tempIndiv);//计算个体参数
				tempIndiv.activNum=Dlg.StatActNum(tempIndiv);
				tempIndiv.fit=Dlg.CalcuFitness(tempIndiv);
				candlist.push_back(tempIndiv); //将个体压入候选解列表

			} 
			else
			{
				tempIndiv.Chromo[num].chara=0;
				tempIndiv.chg1=num;
				tempIndiv.CovRate=Dlg.CalCoverRate(tempIndiv);//计算个体参数
				tempIndiv.activNum=Dlg.StatActNum(tempIndiv);
				tempIndiv.fit=Dlg.CalcuFitness(tempIndiv);
				candlist.push_back(tempIndiv); //将个体压入候选解列表
			}
		/*	//*****计算邻居节点个数************
			int len1=0,len2=0;//被操作节点num的第一、第二类邻居节点个数(所有节点)
			int actlen1=0,actlen2=0;//被激活的第一第二类邻居节点
			vector<int>sleepnb;  //记录休眠的第一类邻居节点序号
			for (int nb=0;nb<LocasNum;nb++)
			{
				//判断是否为第一类邻居节点
				double d2=pow((tempIndiv.Chromo[num].x-tempIndiv.Chromo[nb].x),2)/(13.0*13.0)+pow((tempIndiv.Chromo[num].y-tempIndiv.Chromo[nb].y),2)/(13.0*13.0);
				if (d2<1)
				{
					len1++;//记录第一类邻居节点
					if (indiv.Chromo[nb].chara==1)
					{
						actlen1++;//记录第一类激活邻居节点
					} 
					else
					{
						sleepnb.push_back(nb);//记录第一类邻居节点中的休眠节点
					}
				} 
				else
				{
					//判断是否为第二类邻居点
					double d1=pow((tempIndiv.Chromo[num].x-tempIndiv.Chromo[nb].x),2)/(4*13.0*13.0)+pow((tempIndiv.Chromo[num].y-tempIndiv.Chromo[nb].y),2)/(4*13.0*13.0);
					if (d1<1)
					{
						len2++;//记录第二类邻居节点
						if (tempIndiv.Chromo[nb].chara==1)
						{
							actlen2++; //记录第二类激活节点
						}
						
					}
				}
			}
		//***计算概率p_swap和p_sleep****
			double p_swap=(actlen1+1)*1.0/tempIndiv.activNum;//计算置换概率
			double p_sleep=(actlen1+0.5*actlen2+1)/(len1+len2+1);//计算休眠概率
			

		//****swap操作**************
			double p_sw=(rand()%1000)/1000.0;//随机产生一个概率
			if (p_sw<p_swap)//满足置换条件，则在第一类休眠邻居节点中随机选取一个作状态置换
			{
				if (sleepnb.size()>0)
				{
					int sp=rand()%sleepnb.size();//选中一个休眠点将其激活
					int cg=sleepnb[sp];
					tempIndiv.Chromo[cg].chara=1;
					tempIndiv.Chromo[num].chara=0;//使当前工作点休眠
					tempIndiv.chg1=cg;  //记录发生变换的基因位，用于禁忌表查询
					tempIndiv.chg2=num;
					tempIndiv.CovRate=Dlg.CalCoverRate(tempIndiv);//计算个体参数
					tempIndiv.activNum=Dlg.StatActNum(tempIndiv);
					tempIndiv.fit=Dlg.CalcuFitness(tempIndiv);
					candlist.push_back(tempIndiv); //将个体压入候选解列表
					continue;//跳出本次循环
				}
			
			}
			sleepnb.clear();
		//*********sleep操作************** 
			if (tempIndiv.Chromo[num].chara==1)//如果没有执行swap操作
			{
				double p_sl=(rand()%1000)/1000.0;//随机产生一个概率
				if (p_sl<p_sleep)
				{
					tempIndiv.Chromo[num].chara=0;
					double area=Dlg.CalCoverRate(tempIndiv);
					if (area>0.98)//如果不影响覆盖率，则休眠
					{
						tempIndiv.chg1=num;//记录发生变换的基因位
						tempIndiv.chg2=num;//两个标记设置一样
						tempIndiv.CovRate=area;
						tempIndiv.activNum=Dlg.StatActNum(tempIndiv);
						tempIndiv.fit=Dlg.CalcuFitness(tempIndiv);
						candlist.push_back(tempIndiv); //将个体压入候选解列表

					}

				}
			} */
//////////////////////////////////////////////////////////////
		}
	}
	}

/////////////////////////////////////////////////////////////
	CString temcs="候选解生成函数运行；";
	cssc+=temcs;

}

void CTABU::Tabu(UnitGT indiv)
{
	////////////////////////////////////////
	////禁忌长度、候选解个数、总循环次数等设置
	/////////////////////////////////////////
	cssc=" ";
	CTabuGADlg Dlg;//定义一个对话框类对象
	hisBest=indiv; //设置初始历史最优
	nowBest=indiv;//设置初始当前最优
	candlist.reserve(candnum);//预留空间
	tabulist.reserve(tabuLg);
	for (int i=0;i<circTimes;i++)
	{

		CreatCandidate(nowBest);
		electNowBest();
		if (hisBest.fit>=indiv.fit)//如果找到了一个比传入个体还好的个体
		{
			Dlg.NOWbest=hisBest;
			Dlg.nSon[Dlg.nNowbest]=hisBest;

			if (Dlg.NOWbest.fit>=Dlg.HISTbest.fit)
			{
				Dlg.HISTbest=Dlg.NOWbest;
			}		
		break; //则跳出循环,停止禁忌寻优
		}
	}
	tabulist.clear();//算法结束，清空禁忌表

	CString temcs="Tabu函数运行;";
	cssc+=temcs;

}
