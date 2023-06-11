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

//***********��ӵ�ͷ�ļ�**************
#include "vector"
#include <math.h>
#include <time.h>
using namespace std;
//**************************************

 //int const LocasNum=80;//����λ��
 double const PI=3.141592653;

struct Loca    // ÿ������Ľṹ��
{ 
	int x,y;   //��Ӧÿ��������������
	int chara;  //��Ӧ�������ļ���״̬
};
struct UnitGT     //ÿ������Ľṹ��
{
	Loca Chromo[300];  //����Ļ������ Ⱦɫ��
	int activNum; //�������ĸ���
	double fit;      //��Ӧ��ֵ
	double CovRate; //������
//	int pixel[2][2]; //���ڴ洢�������ظ���״̬
	int number;//���ڴ洢��������Ⱥ�е����
	int chg1,chg2;//���ڽ��������У���¼���ɺ�ѡ��ʱ�����˱任�Ļ���λ���

};
struct TBList
{
	int nGene;//�����ɵĻ������
	int ntime;//���ɴ���
};

struct StatRes//ͳ�����ݽ���Ļ�����
{
	int NnActNum;//��ǰ���ż����������
	int HnActNum;//��ʷ���Ŵ���������
	double Nfitn;//��ǰ������Ӧ��ֵ
	double Hfitn;//��ʷ������Ӧ��ֵ
};

struct cyclo    //����洢Բ���������ݵĽṹ��
{
	float start_x,start_y; //������ʼ��
	float start_angle;  //��㼫����Ƕ�
	float end_x,end_y; //�����յ�
	float end_angle;  //�յ㼫����Ƕ�
	float radian;//����
	};

struct JeiYai //�������ڵ�洢�ṹ��
{
	double x,y;//������
	vector<Loca>Circ;//��¼�����Ӧ��Բ
	double rad;//�������������Ļ���
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__275E305F_40F7_4705_9BB6_005ED5FDA8E2__INCLUDED_)
