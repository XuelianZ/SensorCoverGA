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

	vector<UnitGT>candlist;//候选解列表
	UnitGT nowBest; //禁忌搜索当前最优
	UnitGT hisBest;//禁忌搜索历史最优
	vector<TBList>tabulist;//禁忌表
	int tabuLg;//禁忌长度
	int candnum;//候选解个数
	int circTimes;//算法总循环次数

	CString cssc;//测试输出
	int LocasNum;

};

#endif // !defined(AFX_TABU_H__31A3092A_341D_4967_B4C4_592CF6C73D73__INCLUDED_)
