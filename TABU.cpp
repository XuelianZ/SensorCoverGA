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
	/////����ѡ���б��еĸ��������Ӧ��ֵ����////
	for (int num=0;num<candnum;num++)//ֻ��ǰcandnum(��ѡ�����)��
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
	
	/////�������׼�򣬻�ú�ѡ��////////
	if (candlist.size()==0)//���û�в�����ѡ��
	{
		nowBest=nowBest; //����һ�εĵ�ǰ���ż�����Ϊ��ǰ���ţ��������任
	} 
	else
	{
		for (int candit=0;candit<candnum;candit++)
		{
			int judge=0;//0�����ڽ��ɱ��У�1���ڽ��ɱ����Ҳ���������׼��
			//2:�ڽ��ɱ�������������׼��
			for (int ntb=0;ntb<tabulist.size();ntb++)
			{//����ڽ��ɱ���
			//	if (candlist[candit].chg1==tabulist[ntb].nGene||candlist[candit].chg2==tabulist[ntb].nGene)//
				if (candlist[candit].chg1==tabulist[ntb].nGene)
				{
					if (candlist[candit].fit>=hisBest.fit) //��Ӧ��ֵ������ʷ���ţ���������
					{
						nowBest=candlist[candit]; //���µ�ǰ����
						hisBest=candlist[candit];//������ʷ����
						judge=2;//�жϱ������Ϊ2
						break;//������ǰѭ��
					} 
					else //�����ڽ��ɱ����Ҳ���������׼��
					{
						judge=1;//���жϱ�־����Ϊ1
					}
				}
			}
			
			if (judge==0)  //������ڽ��ɱ���
			{
				nowBest=candlist[candit]; //�˺�ѡ��Ϊ��ǰ����
				if (nowBest.fit>hisBest.fit)
				{
					hisBest=nowBest;
				}
			}
			else if (judge==1) //����ڽ��ɱ����Ҳ���������
			{
				if (candit==candnum-1) //������к�ѡ�ⶼ����������
				{
					nowBest=nowBest;//����һ�εĵ�ǰ������Ȼ����Ϊ��ǰ����
					break;
				} 
				else
				{
					continue;//���������һ��ѭ��
				}
			} 
			else
			{
				break; //�������⣬����ѭ��
			}
		}
	}
	/////////////////////////////////////////////
	//////////////���½��ɱ�////////////////////
	TBList tempTb;//����һ����ʱ���ɶ���
	tempTb.nGene=nowBest.chg1;
	tempTb.ntime=tabuLg+1;
/*	TBList tempTb1,tempTb2;//����������ʱ���ɶ���
	if (nowBest.chg1==nowBest.chg2)//���������sleep����
	{
		tempTb1.nGene=nowBest.chg1;
		tempTb1.ntime=tabuLg+1;//ע��Ƚ��ɳ��ȶ�һ�Σ������ͳһ��һ
		tabulist.push_back(tempTb1);//ѹ����ɱ�
	} 
	else //���������swap����
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
		if (tabulist[ntabu].ntime==1)//������ɴ���Ϊ1
		{
			tabulist.erase(tabulist.begin()+ntabu);//�ͷŽ���
			ntabu--;//���֮�����λ����������
		}
		tabulist[ntabu].ntime--;//���򽫽��ɴ�����1
	}
	//////////////////////////////////////////////////	
	////////////////��պ�ѡ���б�///////////////////
	candlist.clear();

	CString temcs="ѡ��ǰ���ź������У�";
	cssc+=temcs;

}

void CTABU::CreatCandidate(UnitGT indiv)
{
		CTabuGADlg Dlg;//����һ���Ի��������
	/////////////////������ѡ��///////////////////////////
	UnitGT tempIndiv=indiv;
	if (tempIndiv.CovRate<0.95||tempIndiv.activNum<25)//��������ʹ�С��������پͼ������
	{
		for (int num1=0;num1<LocasNum;num1++)
		{
			if (tempIndiv.Chromo[num1].chara==0)
			{
				tempIndiv.Chromo[num1].chara=1;
				tempIndiv.chg1=num1;
				tempIndiv.CovRate=Dlg.CalCoverRate(tempIndiv);//����������
				tempIndiv.activNum=Dlg.StatActNum(tempIndiv);
				tempIndiv.fit=Dlg.CalcuFitness(tempIndiv);
				candlist.push_back(tempIndiv); //������ѹ���ѡ���б�

			}
		}
	} 
	else
	{
			for (int num=0;num<LocasNum;num++)
		{
		if (tempIndiv.Chromo[num].chara==1)
			{
			double p_c=(rand()%1000)/1000.0;//����һ���������
			if (p_c>0.5)//����0.5��������򽻻�
				{
				int Xlef,Xrig,Ybot,Ytop;//�����¼��������֪Բ����ؾ���
				if (tempIndiv.Chromo[num].x-13<0) //���Բ���ǳ�������ʾ�������
				{
					Xlef=0;                   //���֪������ؾ�����߽�ȥ��ʾ������߽�
				} 
				else
				{
					Xlef=tempIndiv.Chromo[num].x-13;
				}
				if (tempIndiv.Chromo[num].x+13>100) //�ұ߽�ѡ��
				{
					Xrig=100;
				} 
				else
				{
					Xrig=tempIndiv.Chromo[num].x+13;
				}
				if (tempIndiv.Chromo[num].y-13<0)           //�±߽�ѡ��
				{
					Ybot=0;
				} 
				else
				{
					Ybot=tempIndiv.Chromo[num].y-13;
				}
				if (tempIndiv.Chromo[num].y+13>100)  //�ϱ߽�ѡ��
				{
					Ytop=100;
				} 
				else
				{
					Ytop=tempIndiv.Chromo[num].y+13;
				}//�߽�ѡ�����
				tempIndiv.Chromo[num].x=Xlef+rand()%(Xrig-Xlef+1);
				tempIndiv.Chromo[num].y=Ybot+rand()%(Ytop-Ybot+1);
				tempIndiv.chg1=num;//��¼�����仯�Ļ���λ�����ڽ�������
				tempIndiv.CovRate=Dlg.CalCoverRate(tempIndiv);//����������
				tempIndiv.activNum=Dlg.StatActNum(tempIndiv);
				tempIndiv.fit=Dlg.CalcuFitness(tempIndiv);
				candlist.push_back(tempIndiv); //������ѹ���ѡ���б�

			} 
			else
			{
				tempIndiv.Chromo[num].chara=0;
				tempIndiv.chg1=num;
				tempIndiv.CovRate=Dlg.CalCoverRate(tempIndiv);//����������
				tempIndiv.activNum=Dlg.StatActNum(tempIndiv);
				tempIndiv.fit=Dlg.CalcuFitness(tempIndiv);
				candlist.push_back(tempIndiv); //������ѹ���ѡ���б�
			}
		/*	//*****�����ھӽڵ����************
			int len1=0,len2=0;//�������ڵ�num�ĵ�һ���ڶ����ھӽڵ����(���нڵ�)
			int actlen1=0,actlen2=0;//������ĵ�һ�ڶ����ھӽڵ�
			vector<int>sleepnb;  //��¼���ߵĵ�һ���ھӽڵ����
			for (int nb=0;nb<LocasNum;nb++)
			{
				//�ж��Ƿ�Ϊ��һ���ھӽڵ�
				double d2=pow((tempIndiv.Chromo[num].x-tempIndiv.Chromo[nb].x),2)/(13.0*13.0)+pow((tempIndiv.Chromo[num].y-tempIndiv.Chromo[nb].y),2)/(13.0*13.0);
				if (d2<1)
				{
					len1++;//��¼��һ���ھӽڵ�
					if (indiv.Chromo[nb].chara==1)
					{
						actlen1++;//��¼��һ�༤���ھӽڵ�
					} 
					else
					{
						sleepnb.push_back(nb);//��¼��һ���ھӽڵ��е����߽ڵ�
					}
				} 
				else
				{
					//�ж��Ƿ�Ϊ�ڶ����ھӵ�
					double d1=pow((tempIndiv.Chromo[num].x-tempIndiv.Chromo[nb].x),2)/(4*13.0*13.0)+pow((tempIndiv.Chromo[num].y-tempIndiv.Chromo[nb].y),2)/(4*13.0*13.0);
					if (d1<1)
					{
						len2++;//��¼�ڶ����ھӽڵ�
						if (tempIndiv.Chromo[nb].chara==1)
						{
							actlen2++; //��¼�ڶ��༤��ڵ�
						}
						
					}
				}
			}
		//***�������p_swap��p_sleep****
			double p_swap=(actlen1+1)*1.0/tempIndiv.activNum;//�����û�����
			double p_sleep=(actlen1+0.5*actlen2+1)/(len1+len2+1);//�������߸���
			

		//****swap����**************
			double p_sw=(rand()%1000)/1000.0;//�������һ������
			if (p_sw<p_swap)//�����û����������ڵ�һ�������ھӽڵ������ѡȡһ����״̬�û�
			{
				if (sleepnb.size()>0)
				{
					int sp=rand()%sleepnb.size();//ѡ��һ�����ߵ㽫�伤��
					int cg=sleepnb[sp];
					tempIndiv.Chromo[cg].chara=1;
					tempIndiv.Chromo[num].chara=0;//ʹ��ǰ����������
					tempIndiv.chg1=cg;  //��¼�����任�Ļ���λ�����ڽ��ɱ��ѯ
					tempIndiv.chg2=num;
					tempIndiv.CovRate=Dlg.CalCoverRate(tempIndiv);//����������
					tempIndiv.activNum=Dlg.StatActNum(tempIndiv);
					tempIndiv.fit=Dlg.CalcuFitness(tempIndiv);
					candlist.push_back(tempIndiv); //������ѹ���ѡ���б�
					continue;//��������ѭ��
				}
			
			}
			sleepnb.clear();
		//*********sleep����************** 
			if (tempIndiv.Chromo[num].chara==1)//���û��ִ��swap����
			{
				double p_sl=(rand()%1000)/1000.0;//�������һ������
				if (p_sl<p_sleep)
				{
					tempIndiv.Chromo[num].chara=0;
					double area=Dlg.CalCoverRate(tempIndiv);
					if (area>0.98)//�����Ӱ�츲���ʣ�������
					{
						tempIndiv.chg1=num;//��¼�����任�Ļ���λ
						tempIndiv.chg2=num;//�����������һ��
						tempIndiv.CovRate=area;
						tempIndiv.activNum=Dlg.StatActNum(tempIndiv);
						tempIndiv.fit=Dlg.CalcuFitness(tempIndiv);
						candlist.push_back(tempIndiv); //������ѹ���ѡ���б�

					}

				}
			} */
//////////////////////////////////////////////////////////////
		}
	}
	}

/////////////////////////////////////////////////////////////
	CString temcs="��ѡ�����ɺ������У�";
	cssc+=temcs;

}

void CTABU::Tabu(UnitGT indiv)
{
	////////////////////////////////////////
	////���ɳ��ȡ���ѡ���������ѭ������������
	/////////////////////////////////////////
	cssc=" ";
	CTabuGADlg Dlg;//����һ���Ի��������
	hisBest=indiv; //���ó�ʼ��ʷ����
	nowBest=indiv;//���ó�ʼ��ǰ����
	candlist.reserve(candnum);//Ԥ���ռ�
	tabulist.reserve(tabuLg);
	for (int i=0;i<circTimes;i++)
	{

		CreatCandidate(nowBest);
		electNowBest();
		if (hisBest.fit>=indiv.fit)//����ҵ���һ���ȴ�����廹�õĸ���
		{
			Dlg.NOWbest=hisBest;
			Dlg.nSon[Dlg.nNowbest]=hisBest;

			if (Dlg.NOWbest.fit>=Dlg.HISTbest.fit)
			{
				Dlg.HISTbest=Dlg.NOWbest;
			}		
		break; //������ѭ��,ֹͣ����Ѱ��
		}
	}
	tabulist.clear();//�㷨��������ս��ɱ�

	CString temcs="Tabu��������;";
	cssc+=temcs;

}
