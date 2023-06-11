// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__275E305F_40F7_4705_9BB6_005ED5FDA8E2__INCLUDED_)
#define AFX_STDAFX_H__275E305F_40F7_4705_9BB6_005ED5FDA8E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//***********添加的头文件**************
#include "vector"
#include <math.h>
#include <time.h>
using namespace std;
//**************************************

 //int const LocasNum=80;//基因位数
 double const PI=3.141592653;

struct Loca    // 每个基因的结构体
{ 
	int x,y;   //对应每个传感器的坐标
	int chara;  //对应传感器的激活状态
};
struct UnitGT     //每个个体的结构体
{
	Loca Chromo[300];  //个体的基因组成 染色体
	int activNum; //激活基因的个数
	double fit;      //适应度值
	double CovRate; //覆盖率
//	int pixel[2][2]; //用于存储区域像素覆盖状态
	int number;//用于存储个体在种群中的序号
	int chg1,chg2;//用于禁忌搜索中，记录生成候选解时产生了变换的基因位序号

};
struct TBList
{
	int nGene;//被禁忌的基因序号
	int ntime;//禁忌次数
};

struct StatRes//统计数据结果的机构体
{
	int NnActNum;//当前最优激活传感器个数
	int HnActNum;//历史最优传感器个数
	double Nfitn;//当前最优适应度值
	double Hfitn;//历史最优适应度值
};

struct cyclo    //定义存储圆弧弧段数据的结构体
{
	float start_x,start_y; //弧段起始点
	float start_angle;  //起点极坐标角度
	float end_x,end_y; //弧端终点
	float end_angle;  //终点极坐标角度
	float radian;//弧度
	};

struct JeiYai //定义界外节点存储结构体
{
	double x,y;//点坐标
	vector<Loca>Circ;//记录交点对应的圆
	double rad;//相对于中心区域的弧度
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__275E305F_40F7_4705_9BB6_005ED5FDA8E2__INCLUDED_)
