#include "../../StdAfx.h"
#pragma once

#include "..\..\include\ui\AppBarImpl.h"
#include "AppBar.h"

#define HM_NONE     0   //������
#define HM_TOP      1   //��������
#define HM_BOTTOM   2   //��������
#define HM_LEFT     3   //��������
#define HM_RIGHT    4   //��������
#define DETASTEP 10
#define INTERVAL    20  //����ճ��ʱ�������Ļ�߽����С���,��λΪ����
#define INFALTE     10  //��������ʱ����봰�ڱ߽����С���,��λΪ����
/*
Ĭ�Ϲ��캯����һ��ΪCWnd
@void �޹��캯��
�޷���ֵ
*/
namespace common { namespace ui
{
template<typename TBaseWnd>
CAppBarImpl<TBaseWnd>::CAppBarImpl(void):public TBaseWnd
{
	m_appbar = new CAppBar();
	g_bDlgStatus = 0;
	m_hideMode = CAppBar::APPBAR_DOCKING_NONE;

}

/*
���ع��캯����һ��ΪCDialogΪ���������
@UINT  [in]  nIDTemplate �޹��캯��
@CWnd* [in]  pParent �޹��캯��
�޷���ֵ
*/
template<typename TBaseWnd>
CAppBarImpl<TBaseWnd>::CAppBarImpl(UINT nIDTemplate,CWnd* pParent):TBaseWnd(nIDTemplate,pParent)
{
	m_appbar = new CAppBar();
	g_bDlgStatus = 0;
	m_hideMode = CAppBar::APPBAR_DOCKING_NONE;
}
//template<>
//CAppBarImpl<CDialog>::CAppBarImpl(UINT nIDTemplate,CWnd* pParent):CDialog(nIDTemplate,pParent)
//{
//	m_appbar = new CAppBar();
//	g_bDlgStatus = 0;
//}
/*
Ĭ�����캯��
@void �޹��캯��
�޷���ֵ
*/
template<typename TBaseWnd>
CAppBarImpl<TBaseWnd>::~CAppBarImpl(void)
{
	if (m_appbar)
		delete m_appbar;
}
BEGIN_TEMPLATE_MESSAGE_MAP(CAppBarImpl,TBaseWnd,TBaseWnd)
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_ACTIVATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_NCHITTEST()
	ON_WM_TIMER()
	ON_MESSAGE(APPBAR_CALLBACK, OnAppBarNotify)
	ON_WM_SHOWWINDOW()
	ON_WM_NCLBUTTONUP()
	ON_WM_MOVING()
	ON_WM_SYSCOMMAND()
	ON_WM_SIZING()
	ON_WM_CREATE()
	ON_MESSAGE(WM_SLIDEOUT_END, OnSlideoutEnd)
	ON_MESSAGE(WM_SLIDEIN_END, OnSlideinEnd)
END_MESSAGE_MAP()

/*
����λ�øı��׼��Ϣ��Ӧ����
@WINDOWPOS*  [in|out]  nIDTemplate ����λ����Ϣ
@return void ����ֵΪ��
*/
template<typename TBaseWnd>
void CAppBarImpl<TBaseWnd>::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	__super::OnWindowPosChanged(lpwndpos);
	m_appbar->OnWindowPosChanged(lpwndpos);
}

/*
����״̬�����׼��Ϣ��Ӧ����
@UINT  [in] nState       ״̬���ֵ
@CWnd* [in] pWndOther    ʧȥ����Ĵ���
@BOOL  [in] bMinimized   �����Ƿ���С��
@return void ����ֵΪ��
*/
template<typename TBaseWnd>
void CAppBarImpl<TBaseWnd>::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	__super::OnActivate(nState, pWndOther, bMinimized);
	m_appbar->OnActivate(nState, pWndOther, bMinimized);
}

/*
��������갴�±�׼��Ϣ��Ӧ����
@UINT   [in] nFlags       ״̬���ֵ
@CPoint [in] point        ��ǰ���ͻ���λ��
@return void ����ֵΪ��
*/
template<typename TBaseWnd>
void CAppBarImpl<TBaseWnd>::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SetCapture();
	m_appbar->OnLButtonDown(nFlags, point);
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,0);	
	__super::OnLButtonDown(nFlags, point);
}

/*
����������ɿ���׼��Ϣ��Ӧ����
@UINT   [in] nFlags       ״̬���ֵ
@CPoint [in] point        ��ǰ���ͻ���λ��
@return void ����ֵΪ��
*/
template<typename TBaseWnd>
void CAppBarImpl<TBaseWnd>::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_appbar->OnLButtonUp(nFlags, point);
	ReleaseCapture();
	__super::OnLButtonUp(nFlags, point);
}

/*
����������ƶ���׼��Ϣ��Ӧ����
@UINT   [in] nFlags       ״̬���ֵ
@CPoint [in] point        ��ǰ���ͻ���λ��
@return void ����ֵΪ��
*/
template<typename TBaseWnd>
void CAppBarImpl<TBaseWnd>::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//    m_appbar->OnMouseMove(nFlags, point);
	__super::OnMouseMove(nFlags, point);
}

/*
���ڻ��в��Ա�׼��Ϣ��Ӧ����
@CPoint [in] point        ��ǰ���ͻ���λ��
@return void ����ֵΪ��
*/
template<typename TBaseWnd>
LRESULT CAppBarImpl<TBaseWnd>::OnNcHitTest(CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_appbar->OnNcHitTest(CDialog::OnNcHitTest(point));
	return __super::OnNcHitTest(point);
}

/*
������Ϣ�����׼��Ϣ��Ӧ����
@UINT_PTR [in] nIDEvent        ��ϢID���ֵ
@return void ����ֵΪ��
*/
template<typename TBaseWnd>
void CAppBarImpl<TBaseWnd>::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nIDEvent>TIMER_BASE)
		m_appbar->OnTimer(nIDEvent);
	__super::OnTimer(nIDEvent);
}

/*
����������ƶ���׼��Ϣ��Ӧ����
@WPARAM   [in] wParam       ��ϢID���
@LPARAM   [in] lParam       ��Ϣ�����ṹָ��
@return LRESULT ����ֵΪ��
*/
template<typename TBaseWnd>
LRESULT CAppBarImpl<TBaseWnd>::OnAppBarNotify( WPARAM wParam, LPARAM lParam/*bHandled*/)
{
	BOOL isFinsih = TRUE;
	m_appbar->OnAppBarNotify(0,wParam,lParam,isFinsih);
	return 0;

}

/*
����������ƶ���׼��Ϣ��Ӧ����
@BOOL   [in] bShow       ��ϢID���
@UINT   [in] nStatus     ��Ϣ�����ṹָ��
@return LRESULT ����ֵΪ��
*/
template<typename TBaseWnd>
void CAppBarImpl<TBaseWnd>::OnShowWindow(BOOL bShow, UINT nStatus)
{
	__super::OnShowWindow(bShow, nStatus);
}

/*
���ڱ�������굯���׼��Ϣ��Ӧ����
@UINT   [in] nHitTest     ����״̬���ֵ
@CPoint [in] point        ��ǰ���ͻ���λ��
@return void ����ֵΪ��
*/
template<typename TBaseWnd>
void CAppBarImpl<TBaseWnd>::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//m_appbar->m_bDraging = false;
	LRESULT rs =  OnNcHitTest(point);
	m_appbar->SliderWindow(m_hideMode);
	__super::OnNcLButtonUp(nHitTest, point);
}

/*
�����ƶ�ʱ��׼��Ϣ��Ӧ����
@UINT   [in] nHitTest     ����״̬���ֵ
@CPoint [in] point        ��ǰ���ͻ���λ��
@return void ����ֵΪ��
*/
template<typename TBaseWnd>
void CAppBarImpl<TBaseWnd>::OnMoving(UINT fwSide, LPRECT pRect)
{
	FixMoving(fwSide,  pRect);   
	__super::OnMoving(fwSide, pRect);
	if((!m_appbar->GetDragContent())&&(m_hideMode == CAppBar::APPBAR_DOCKING_NONE)
		||m_appbar->GetDragContent())
		m_appbar->SliderWindow(m_hideMode);
	// TODO: �ڴ˴������Ϣ����������

}
template<typename TBaseWnd>
BOOL CAppBarImpl<TBaseWnd>::AdjustPos(CRect* lpRect)
{//�Զ�����
	int iSX=GetSystemMetrics(SM_CXFULLSCREEN);
	int iSY=GetSystemMetrics(SM_CYFULLSCREEN);
	RECT rWorkArea;
	BOOL bResult = SystemParametersInfo(SPI_GETWORKAREA,  
		sizeof(RECT),
		&rWorkArea,
		0);    
	CRect rcWA;
	if(!bResult)
	{//������ò��ɹ�������GetSystemMetrics��ȡ��Ļ���
		rcWA=CRect(0,0,iSX,iSY);
	}
	else
		rcWA=rWorkArea;

	int iX=lpRect->left;
	int iY=lpRect->top;

	if(iX < rcWA.left + DETASTEP && iX!=rcWA.left)
	{//������
		//pWnd->SetWindowPos(NULL,rcWA.left,iY,0,0,SWP_NOSIZE);
		lpRect->OffsetRect(rcWA.left-iX,0);

		g_bDlgStatus=1;
		AdjustPos(lpRect);
		return TRUE;
	}
	if(iY < rcWA.top + DETASTEP && iY!=rcWA.top)
	{//������
		//pWnd->SetWindowPos(NULL ,iX,rcWA.top,0,0,SWP_NOSIZE);
		lpRect->OffsetRect(0,rcWA.top-iY);

		g_bDlgStatus=2;
		AdjustPos(lpRect);
		return TRUE;
	}
	if(iX + lpRect->Width() > rcWA.right - DETASTEP && iX !=rcWA.right-lpRect->Width())
	{//������
		//pWnd->SetWindowPos(NULL ,rcWA.right-rcW.Width(),iY,0,0,SWP_NOSIZE);
		lpRect->OffsetRect(rcWA.right-lpRect->right,0);

		g_bDlgStatus=3;
		AdjustPos(lpRect);
		return TRUE;
	}
	if(iY + lpRect->Height() > rcWA.bottom - DETASTEP && iY !=rcWA.bottom-lpRect->Height())
	{//������
		//pWnd->SetWindowPos(NULL ,iX,rcWA.bottom-rcW.Height(),0,0,SWP_NOSIZE);

		g_bDlgStatus=4;	
		lpRect->OffsetRect(0,rcWA.bottom-lpRect->bottom);
		return TRUE;
	}
	//	

	UINT uFlag = CAppBar::APPBAR_DOCKING_NONE;
	switch(g_bDlgStatus)	
	{
	case 1:
		uFlag = CAppBar::APPBAR_DOCKING_LEFT;
		break;
	case 2:
		uFlag = CAppBar::APPBAR_DOCKING_TOP;
		break;
	case 3:
		uFlag = CAppBar::APPBAR_DOCKING_RIGHT;
		break;
	case 4:
		uFlag = CAppBar::APPBAR_DOCKING_BOTTOM;
		break;
	}
	m_appbar->SliderWindow(uFlag);
	return FALSE;
}
template<typename TBaseWnd>
void  CAppBarImpl<TBaseWnd>::FixBorderSizing(UINT fwSide, LPRECT pRect)
{
	INT screenHeight = GetSystemMetrics(SM_CYSCREEN);
	INT screenWidth  = GetSystemMetrics(SM_CXSCREEN);
	INT height = pRect->bottom - pRect->top;
	INT width  = pRect->right - pRect->left;
	int Interval = 1;
	if (pRect->top <= Interval)
	{   //ճ�����ϱ�
		//		pRect->bottom = height - m_edgeHeight;
		//		pRect->top = -m_edgeHeight;
		m_hideMode = CAppBar::APPBAR_DOCKING_TOP;
	}
	else if(pRect->bottom >= (screenHeight - Interval ))
	{   //ճ�����±�
		//		pRect->top = screenHeight - height;
		//		pRect->bottom = screenHeight;
		m_hideMode = CAppBar::APPBAR_DOCKING_BOTTOM;
	}
	else if (pRect->left < Interval)
	{	//ճ�������	
		if(!m_isSizeChanged)
		{
			CRect tRect;
			GetWindowRect(tRect);
			//			m_oldWndHeight = tRect.Height();			
		}
		//		pRect->right = width;
		//		pRect->left = 0;

		//		m_isSizeChanged = TRUE;
		m_hideMode = CAppBar::APPBAR_DOCKING_LEFT;
	}
	else if(pRect->right >= (screenWidth - Interval))
	{   //ճ�����ұ�
		if(!m_isSizeChanged)
		{
			CRect tRect;
			GetWindowRect(tRect);
			//			m_oldWndHeight = tRect.Height();						
		}
		//		pRect->left = screenWidth - width;
		//		pRect->right = screenWidth;

		//		m_isSizeChanged = TRUE;
		m_hideMode = CAppBar::APPBAR_DOCKING_RIGHT;
	}
	else
	{   //��ճ��
		m_hideMode = CAppBar::APPBAR_DOCKING_NONE;

	}
};
template<typename TBaseWnd>
void  CAppBarImpl<TBaseWnd>::FixMoving(UINT fwSide, LPRECT pRect,BOOL bIsMoving)
{

	POINT curPos;
	GetCursorPos(&curPos);
	int Interval = 0;
	if (bIsMoving)
		Interval = INTERVAL;

	INT screenHeight = GetSystemMetrics(SM_CYSCREEN);
	INT screenWidth  = GetSystemMetrics(SM_CXSCREEN);
	INT height = pRect->bottom - pRect->top;
	INT width  = pRect->right - pRect->left;

	if (curPos.y <= Interval)
	{   //ճ�����ϱ�
		pRect->bottom = height - m_edgeHeight;
		pRect->top = -m_edgeHeight;
		m_hideMode = CAppBar::APPBAR_DOCKING_TOP;
	}
	else if(curPos.y >= (screenHeight - Interval ))
	{   //ճ�����±�
		pRect->top = screenHeight - height;
		pRect->bottom = screenHeight;
		m_hideMode = CAppBar::APPBAR_DOCKING_BOTTOM;
	}
	else if (curPos.x < Interval)
	{	//ճ�������	
		if(!m_isSizeChanged)
		{
			CRect tRect;
			GetWindowRect(tRect);
			//			m_oldWndHeight = tRect.Height();			
		}
		pRect->right = width;
		pRect->left = 0;

		m_isSizeChanged = TRUE;
		m_hideMode = CAppBar::APPBAR_DOCKING_LEFT;
	}
	else if(curPos.x >= (screenWidth - Interval))
	{   //ճ�����ұ�
		if(!m_isSizeChanged)
		{
			CRect tRect;
			GetWindowRect(tRect);
			//			m_oldWndHeight = tRect.Height();						
		}
		pRect->left = screenWidth - width;
		pRect->right = screenWidth;

		m_isSizeChanged = TRUE;
		m_hideMode = CAppBar::APPBAR_DOCKING_RIGHT;
	}
	else
	{   //��ճ��
		m_hideMode = CAppBar::APPBAR_DOCKING_NONE;

	}
	//m_appbar->SliderWindow(m_hideMode);
}
template<typename TBaseWnd>
void CAppBarImpl<TBaseWnd>::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	__super::OnSysCommand(nID, lParam);
	if( (nID & 0xFFF0) == SC_MOVE )
	{
		PostMessage(WM_NCLBUTTONUP, HTCAPTION, lParam);
	}
}
template<typename TBaseWnd>
void CAppBarImpl<TBaseWnd>::OnSizing(UINT fwSide, LPRECT pRect)
{
	__super::OnSizing(fwSide, pRect);
	if(m_appbar->m_uCurrentDockingSide == CAppBar::APPBAR_DOCKING_NONE)
	{
		FixBorderSizing( fwSide,  pRect);
		m_appbar->SliderWindow(m_hideMode);
	}
	else 
	{
		FixSizing( fwSide,  pRect);
		if(m_hideMode != CAppBar::APPBAR_DOCKING_NONE)
			m_appbar->SliderWindow(m_hideMode);
		else 
			m_appbar->m_uCurrentDockingSide = CAppBar::APPBAR_DOCKING_NONE;

	}

	// TODO: �ڴ˴������Ϣ����������
}
template<typename TBaseWnd>
void  CAppBarImpl<TBaseWnd>::FixSizing(UINT fwSide, LPRECT pRect)
{
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int screenWidth  = GetSystemMetrics(SM_CXSCREEN);
	if(pRect->left>INTERVAL&&pRect->top>INTERVAL&&
		pRect->right<screenWidth-INTERVAL&&pRect->bottom<screenHeight-INTERVAL )
	{
		m_hideMode = CAppBar::APPBAR_DOCKING_NONE;
		//	 MessageBox(L"hehe");
	}
	return;
}
template<typename TBaseWnd>
int CAppBarImpl<TBaseWnd>::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_appbar->SetHwnd(m_hWnd);
	m_appbar->InitAppBar(CAppBar::APPBAR_DOCKING_ALL, true);
	m_appbar->SetKeepSize(true);
	m_appbar->SetAutoHide(true);
	m_edgeHeight = GetSystemMetrics(SM_CYEDGE);
	m_edgeWidth  = GetSystemMetrics(SM_CXFRAME);

	SystemParametersInfo(SPI_GETDRAGFULLWINDOWS,TRUE,NULL,0) ;   //drag window not just a rect
	return 0;
}
template<typename TBaseWnd>
 BOOL CAppBarImpl<TBaseWnd>::IsAppWndHanging()
{
	if (m_appbar)
	{
		return m_appbar->IsAppWndHanging();
	}
	return TRUE;
}
template<typename TBaseWnd>
 LRESULT CAppBarImpl<TBaseWnd>::OnSlideoutEnd(WPARAM w, LPARAM l)
 {
	 OnBarSlideredOut();
	 return 0;
 }

 template<typename TBaseWnd>
 LRESULT CAppBarImpl<TBaseWnd>::OnSlideinEnd(WPARAM w, LPARAM l)
 {
     OnBarSlideredIn();
	 return 0;
 }

 }}