// TABU.h: interface for the CTABU class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABU_H__31A3092A_341D_4967_B4C4_592CF6C73D73__INCLUDED_)
#define AFX_TABU_H__31A3092A_341D_4967_B4C4_592CF6C73D73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
using namespace std;

class CTABU  
{
public:
	void Tabu(UnitGT indiv);
	void CreatCandidate(UnitGT indiv);
	void electNowBest();
	CTABU();
	virtual ~CTABU();

	vector<UnitGT>candlist;//��ѡ���б�
	UnitGT nowBest; //����������ǰ����
	UnitGT hisBest;//����������ʷ����
	vector<TBList>tabulist;//���ɱ�
	int tabuLg;//���ɳ���
	int candnum;//��ѡ�����
	int circTimes;//�㷨��ѭ������

	CString cssc;//�������
	int LocasNum;

};

#endif // !defined(AFX_TABU_H__31A3092A_341D_4967_B4C4_592CF6C73D73__INCLUDED_)
