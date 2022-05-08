// ControlView.cpp : 实现文件
//

#include "stdafx.h"
#include "MCA.h"
#include "ControlView.h"
#include "MCADoc.h"
#include "MainFrm.h"
#include <math.h>


// CControlView

IMPLEMENT_DYNCREATE(CControlView, CFormView)

CControlView::CControlView()
	: CFormView(CControlView::IDD)
	, m_nPeriod(0)
	, m_nHight(0)
	, m_bCheckAuto(FALSE)
{

}

CControlView::~CControlView()
{
}

void CControlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PERIOD, m_EditPeriod);
	DDX_Text(pDX, IDC_EDIT_PERIOD, m_nPeriod);
	DDX_Control(pDX, IDC_EDIT_HIGHT, m_EditHight);
	DDX_Text(pDX, IDC_EDIT_HIGHT, m_nHight);
	DDX_Control(pDX, IDC_BUTTON_PAINT, m_ButtonPaint);
	DDX_Control(pDX, IDC_BUTTON_CLEAR, m_ButtonClear);
	//  DDX_Check(pDX, IDC_CHECK_TIMER, m_bCheckAuto);
	DDX_Check(pDX, IDC_CHECK_TIMER, m_bCheckAuto);
}

BEGIN_MESSAGE_MAP(CControlView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_PAINT, &CControlView::OnBnClickedButtonPaint)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CControlView::OnBnClickedButtonClear)
	ON_COMMAND(ID_MENU_PAINT, &CControlView::OnMenuPaint)
	ON_COMMAND(ID_MENU_CLEAR, &CControlView::OnMenuClear)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_TIMER, &CControlView::OnBnClickedCheckTimer)
END_MESSAGE_MAP()


// CControlView 诊断

#ifdef _DEBUG
void CControlView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CControlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CControlView 消息处理程序


void CControlView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	m_nHight=10.0;
	m_nPeriod=0.1;
	UpdateData(FALSE);
	m_ButtonClear.EnableWindow(FALSE);
}


void CControlView::OnBnClickedButtonPaint()
{
	UpdateData( TRUE ) ; // 获取屏幕值至变量
	//设置按钮状态
	m_ButtonPaint.EnableWindow(FALSE);
	m_ButtonClear.EnableWindow(TRUE);
	//设置曲线值
	for (int i=0;i<512;i++)
	{
		((CMCADoc*)m_pDocument)->m_Dot[i]=m_nHight*(1+sin(m_nPeriod*i));
	}
	((CMCADoc*)GetDocument())->UpdateAllViews(NULL); //重画曲线
}


void CControlView::OnBnClickedButtonClear()
{
	//设置按钮状态
	m_ButtonPaint.EnableWindow(TRUE);
	m_ButtonClear.EnableWindow(FALSE);
	//设置曲线值
	for (int i=0;i<512;i++)
	{
		((CMCADoc*)m_pDocument)->m_Dot[i]=0;
	}
	//重画曲线
	((CMainFrame *)AfxGetApp()->m_pMainWnd)->GetActiveDocument()->UpdateAllViews( NULL ) ;
}


void CControlView::OnMenuPaint()
{
	//等同按下画图按钮
	OnBnClickedButtonPaint();
}


void CControlView::OnMenuClear()
{
	//等同按下清除按钮
	OnBnClickedButtonClear();
}


void CControlView::OnTimer(UINT_PTR nIDEvent)
{
	//自动循环增加曲线幅度
	m_nHight ++;
	if (m_nHight>30) m_nHight=10.0;
	//重新画图
	UpdateData(FALSE);
	OnBnClickedButtonPaint();
	CFormView::OnTimer(nIDEvent);
}


void CControlView::OnBnClickedCheckTimer()
{
	UpdateData(TRUE); //获取当前选中状态
	if (m_bCheckAuto)
	{
		SetTimer(1,500,NULL); //选中，设置自动更新
	}
	else
	{
		KillTimer(1); //不选中，取消自动更新
	}
}
