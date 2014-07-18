#include "stdafx.h"
#include "../Hall.h"
#include "TrackerCtrl.h"
#include "..\src\CommonLibrary\include\ui\UIHelper.h"
#include "PicTracker.h"

#define  TRACKER_WIDTH      369    //����Ŀ����PicTracker.cpp����Ŀ�߶���4�����ش�С��ֻΪ�������
#define  TRACKER_HEIGHT     243

CTrackerCtrl::CTrackerCtrl(void)
{
	m_tracker.SetCtrl(this);
	m_hBmp = NULL;
	m_tracker.m_nStyle= CRectTracker::solidLine;
	m_bDrag = false;
	m_iStartx = 0;			//Ĭ��ͼƬ������ԭ�����
	m_iStarty = 0;
	m_PrePoint = CPoint(0,0);
	m_ZoomFactor = 1;
	m_bOriginal = false;
	m_bFullScreen = false;
	m_PreZoomFactor = 1;
}

CTrackerCtrl::~CTrackerCtrl(void)
{
	if( m_hBmp)
	{
		DeleteObject( m_hBmp);
		m_hBmp = NULL;
	}
}

bool CTrackerCtrl::Create(CWnd* pwndParent, CRect rc, UINT uId)
{
	//Tracker��СΪ  180*180
	m_tracker.m_rect.left = rc.Width()/2 - 90;//55;
	m_tracker.m_rect.right = rc.Width()/2 + 90;//55;
	m_tracker.m_rect.top = rc.Height()/2 - 90;//55;
	m_tracker.m_rect.bottom = rc.Height()/2 + 90;//55;
    //�������Сλ��
	CRect rectTrackerLimit;
	rectTrackerLimit = rc;
	rectTrackerLimit.left -= 12;
	rectTrackerLimit.right -= 15;
	rectTrackerLimit.top  -=  67;
	rectTrackerLimit.bottom -=  70;
	m_tracker.SetLimitRect(rectTrackerLimit);
	return CWnd::Create(AfxRegisterWndClass(0), NULL, WS_VISIBLE | WS_CHILD, rc, pwndParent, uId);
}

BEGIN_MESSAGE_MAP(CTrackerCtrl, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONUP()
	ON_MESSAGE(WM_TRACKER_MOVE,OnTrackerMove)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

LRESULT CTrackerCtrl::OnTrackerMove(WPARAM wParam,LPARAM lParam)
{
	Invalidate();
	return 0;
}

LRESULT CTrackerCtrl::OnMouseLeave(WPARAM wParam,LPARAM lParam)
{
	m_bDrag = false;
	return 0;
}

void CTrackerCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()
	common::ui::CClientRect rcThis(this);

	if (m_hBmp != NULL)
	{
		CBitmap bitmapmem;          
		CBitmap *pOldBit;
		CDC m_pMemDC;
		m_pMemDC.CreateCompatibleDC(&dc); 
		bitmapmem.CreateCompatibleBitmap(&dc, rcThis.Width(), rcThis.Height());
		pOldBit=m_pMemDC.SelectObject(&bitmapmem);

		CRect rect;
		GetWindowRect(&rect);
		ScreenToClient(&rect);
		HBRUSH bgBrush = ::CreateSolidBrush(RGB(255,255,255));
		FillRect(m_pMemDC,&rect,bgBrush);
		DeleteObject(bgBrush);
        //�ڶ�����������Ҫ�Ӹ��ţ�����Ϊ���ʾ��λ�ò��������m_pMemDC������ϵ
		imgRate.Draw(m_pMemDC,-m_iStartx,-m_iStarty,imgRate.GetWidth(),imgRate.GetHeight(),&rcThis,true);
		
		dc.BitBlt(rcThis.left,rcThis.top,rcThis.Width(),rcThis.Height(),&m_pMemDC,0,0,SRCCOPY); 
		m_pMemDC.SelectObject(pOldBit);
		pOldBit->DeleteObject();
		m_pMemDC.DeleteDC();
		bitmapmem.DeleteObject();

		CRect rectTracker;
		m_tracker.GetTrueRect(&rectTracker);
		rectTracker.left += m_iStartx;
		rectTracker.top += m_iStarty;
		rectTracker.right += m_iStartx;
		rectTracker.bottom += m_iStarty;

		imgSmall.Clear();
		CxImage imgTemp;
		imgRate.Crop(rectTracker,&imgTemp);//����ֱ��ʹ��imgSmall �������ּ��ж��������û�б������
		imgSmall = imgTemp;
		((CPicTracker*)GetParent())->m_picShowCtrl.SetBitmap(imgSmall.MakeBitmap());
		((CPicTracker*)GetParent())->m_picShowCtrl2.SetBitmap(imgSmall.MakeBitmap());
		if (rectTracker.left < 0)
		{
			((CPicTracker*)GetParent())->m_picShowCtrl.SetStartx(-rectTracker.left);
			((CPicTracker*)GetParent())->m_picShowCtrl2.SetStartx(-rectTracker.left);
		}
		else
		{
			((CPicTracker*)GetParent())->m_picShowCtrl.SetStartx(0);
			((CPicTracker*)GetParent())->m_picShowCtrl2.SetStartx(0);
		}
		if (rectTracker.top<0)
		{
			((CPicTracker*)GetParent())->m_picShowCtrl.SetStarty(-rectTracker.top);
			((CPicTracker*)GetParent())->m_picShowCtrl2.SetStarty(-rectTracker.top);
		}
		else
		{
			((CPicTracker*)GetParent())->m_picShowCtrl.SetStarty(0);
			((CPicTracker*)GetParent())->m_picShowCtrl2.SetStarty(0);
		}
		((CPicTracker*)GetParent())->m_picShowCtrl.Invalidate();
		((CPicTracker*)GetParent())->m_picShowCtrl2.Invalidate();
		m_tracker.Draw(&dc);
	}
}

void CTrackerCtrl::SetBitmap(HBITMAP hBmp)
{
	if( m_hBmp)
	{
		DeleteObject( m_hBmp);
		m_hBmp = NULL;
	}

	m_hBmp = hBmp;
	img.CreateFromHBITMAP(m_hBmp);
	if (img.GetWidth()/img.GetHeight() > TRACKER_WIDTH/TRACKER_HEIGHT)//ͼƬ�Ƚ�"��"���������ͼƬ��Ƚ������ŵ�tracker��"���"��Ȼ��߶�ͬ��������
	{
		if (img.GetWidth()*MIN_ZOOM_FACTOR > TRACKER_WIDTH)
		{
			CxImage imgRate;
			int width = TRACKER_WIDTH*MAX_ZOOM_FACTOR;
			int height = (float)width*(float)(img.GetHeight())/(float)img.GetWidth();
			img.Resample2(width,height,CxImage::InterpolationMethod::IM_NEAREST_NEIGHBOUR,CxImage::OverflowMethod::OM_REPEAT,&imgRate);
			img = imgRate;
		}
	}
	else //ͼƬ�Ƚ�"��"�����,��ͼƬ�߶Ƚ������ŵ�tracker��"�߶�"��Ȼ����ͬ��������
	{
		if (img.GetHeight()*MIN_ZOOM_FACTOR > TRACKER_HEIGHT)
		{
			CxImage imgRate;
			int height = TRACKER_HEIGHT*MAX_ZOOM_FACTOR;
			int width = (float)height*(float)(img.GetWidth())/(float)img.GetHeight();
			img.Resample2(width,height,CxImage::InterpolationMethod::IM_NEAREST_NEIGHBOUR,CxImage::OverflowMethod::OM_REPEAT,&imgRate);
			img = imgRate;
		}
	}
	
	//���ؽ�����ʱ��Ӧ�ô���ȫ��״̬
	OnFullScreen();
}

void CTrackerCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bDrag = true;
	if(!m_tracker.Track(this,point,TRUE))
	{
		SetCapture();
	}
	m_PrePoint = point;
	CWnd::OnLButtonDown(nFlags, point);
}

void CTrackerCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//���ڼ��mouse leave
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(tme);
	tme.dwFlags  = TME_HOVER | TME_LEAVE;
	tme.hwndTrack = m_hWnd;
	tme.dwHoverTime = HOVER_DEFAULT;
	::_TrackMouseEvent(&tme);
	//end

	if (m_bDrag)
	{
		CRect rcThis;
		GetClientRect(&rcThis);
		if (imgRate.GetWidth()>=rcThis.Width())
		{
			if (point.x > m_PrePoint.x)
			{
				m_iStartx = (m_iStartx -(  point.x - m_PrePoint.x ))<0?m_iStartx:(m_iStartx -(  point.x - m_PrePoint.x ));
			}
			else
			{
				m_iStartx = (m_iStartx -(  point.x - m_PrePoint.x ) + rcThis.Width())>imgRate.GetWidth()?m_iStartx:(m_iStartx -(  point.x - m_PrePoint.x ));
			}
		}
		else
		{
			if (point.x < m_PrePoint.x)
			{
				m_iStartx = (m_iStartx -(  point.x - m_PrePoint.x ))>0?m_iStartx:(m_iStartx -(  point.x - m_PrePoint.x ));
			}
			else
			{
				m_iStartx = (m_iStartx -(  point.x - m_PrePoint.x ) + rcThis.Width())<imgRate.GetWidth()?m_iStartx:(m_iStartx -(  point.x - m_PrePoint.x ));
			}
		}

		if (imgRate.GetHeight()>=rcThis.Height())
		{
			if (point.y > m_PrePoint.y)
			{
				m_iStarty = (m_iStarty -(  point.y - m_PrePoint.y ))<0?m_iStarty:(m_iStarty -(  point.y - m_PrePoint.y ));
			}
			else
			{
				m_iStarty = (m_iStarty -(  point.y - m_PrePoint.y )  + rcThis.Height())>imgRate.GetHeight()?m_iStarty:(m_iStarty -(  point.y - m_PrePoint.y));
			}
		}
		else
		{
			if (point.y < m_PrePoint.y)
			{
				m_iStarty = (m_iStarty -(  point.y - m_PrePoint.y ))>0?m_iStarty:(m_iStarty -(  point.y - m_PrePoint.y ));
			}
			else
			{
				m_iStarty = (m_iStarty -(  point.y - m_PrePoint.y )  + rcThis.Height())<imgRate.GetHeight()?m_iStarty:(m_iStarty -(  point.y - m_PrePoint.y));
			}
		}
		m_PrePoint = point;
		Invalidate();
	}
	else
	{
		ReleaseCapture();
	}
	CWnd::OnMouseMove(nFlags, point);
}

BOOL CTrackerCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (pWnd == this && m_tracker.SetCursor(this, nHitTest))
		return TRUE;
	if (m_bDrag)
	{
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR1));
	}
	else
	{
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR2));
	}
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CTrackerCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bDrag = false;
	ReleaseCapture();
	CWnd::OnLButtonUp(nFlags, point);
}

void CTrackerCtrl::OnZoomOut()
{
	m_bOriginal = false;
	m_bFullScreen = false;

	if (m_ZoomFactor<=MIN_ZOOM_FACTOR) return;
	

	m_ZoomFactor /= ZOOM_FACTOR_PER_SLIDER_POS;
	CRect  rcThis;
	GetClientRect(rcThis);

	if (m_ZoomFactor<1)//��С
	{
		bool	bRet = img.Resample2(img.GetWidth()*m_ZoomFactor,img.GetHeight()*m_ZoomFactor,CxImage::InterpolationMethod::IM_NEAREST_NEIGHBOUR,CxImage::OverflowMethod::OM_REPEAT,&imgRate);
		if (bRet == false)
		{
			TRACE(_T("����ʧ��\n\r"));
			return;
		}
	}
	else//�Ŵ�
	{
		 bool	bRet = img.Resample(img.GetWidth()*m_ZoomFactor,img.GetHeight()*m_ZoomFactor,1,&imgRate);
		 if (bRet == false)
		 {
			 TRACE(_T("����ʧ��\n\r"));
			 return;
		 }
	}
	CRect rectTracker;
	m_tracker.GetTrueRect(&rectTracker);
	//����tracker�Ŀ��ǿ��϶������Դ�����ʱ���ǿ���tracker������Ľ������ŵģ�������������ġ����Լ���startx��startyʱҪע��
	float fStartx = (m_ZoomFactor/m_PreZoomFactor)*((rectTracker.left+rectTracker.right)/2 + m_iStartx) -  (rectTracker.left+rectTracker.right)/2;
	m_iStartx = fStartx>0?(fStartx*2+1)/2:(fStartx*2-1)/2;
	
	float fStarty = ((rectTracker.top + rectTracker.bottom)/2 + m_iStarty)*(m_ZoomFactor/m_PreZoomFactor) - (rectTracker.top + rectTracker.bottom)/2;
	m_iStarty = fStarty>0?(fStarty*2+1)/2:(fStarty*2-1)/2;
	m_PreZoomFactor = m_ZoomFactor;
	Invalidate();
}

void CTrackerCtrl::OnZoomIn()//���㷽������OnZoomOut()
{
	m_bOriginal = false;
	m_bFullScreen = false;

	if (m_ZoomFactor>=MAX_ZOOM_FACTOR) return;
	
	m_ZoomFactor*=ZOOM_FACTOR_PER_SLIDER_POS;
	CRect  rcThis;
	GetClientRect(rcThis);
	CxImage imgTemp;

	if (m_ZoomFactor<1)
	{
		bool	bRet = img.Resample2(img.GetWidth()*m_ZoomFactor,img.GetHeight()*m_ZoomFactor,CxImage::InterpolationMethod::IM_NEAREST_NEIGHBOUR,CxImage::OverflowMethod::OM_REPEAT,&imgRate);
		if (bRet == false)
		{
			TRACE(_T("����ʧ��\n\r"));
			return;
		}
	}
	else
	{
		bool	bRet = img.Resample(img.GetWidth()*m_ZoomFactor,img.GetHeight()*m_ZoomFactor,1,&imgRate);
		if (bRet == false)
		{
			TRACE(_T("����ʧ��\n\r"));
			return;
		}
	}
	CRect rectTracker;
	m_tracker.GetTrueRect(&rectTracker);
	//���㹫ʽ�� (a-x)/(a-b) = k;
	float fStartx = (m_ZoomFactor/m_PreZoomFactor)*((rectTracker.left+rectTracker.right)/2 + m_iStartx) -  (rectTracker.left+rectTracker.right)/2;
	m_iStartx = fStartx>0?(fStartx*2+1)/2:(fStartx*2-1)/2;

	float fStarty = ((rectTracker.top + rectTracker.bottom)/2 + m_iStarty)*(m_ZoomFactor/m_PreZoomFactor) - (rectTracker.top + rectTracker.bottom)/2;
	m_iStarty = fStarty>0?(fStarty*2+1)/2:(fStarty*2-1)/2;

	m_PreZoomFactor = m_ZoomFactor;
	Invalidate();
}

void CTrackerCtrl::OnOriginal()
{
	CRect  rcThis;
	GetClientRect(rcThis);

	m_bOriginal = true;
	m_bFullScreen = false;
	m_ZoomFactor  = 1;
	m_PreZoomFactor = 1;
	bool	bRet = img.Resample(img.GetWidth()*m_ZoomFactor,img.GetHeight()*m_ZoomFactor,1,&imgRate);
	m_iStartx = imgRate.GetWidth() - rcThis.Width();
	m_iStartx /= 2;
	m_iStarty = imgRate.GetHeight() - rcThis.Height();
	m_iStarty /= 2;
	Invalidate();
}

void CTrackerCtrl::OnFullScreen()
{
	CRect  rcThis;
	GetClientRect(rcThis);
	m_bFullScreen = true;
	m_bOriginal = false;
	
	float rate = (float)(img.GetWidth())/(float)(img.GetHeight());
	float fClient = (float)(rcThis.Width())/(float)(rcThis.Height());
	float hScale = (float)(img.GetHeight())/(float)(rcThis.Height());
	float wScale = (float)(img.GetWidth())/(float)(rcThis.Width());
	if (hScale<=1&&wScale<=1)
	{
		//���ԭʼͼƬ�����С����ԭʼ����
		OnOriginal();
		return;
	}
	//��������SetBitmap()��һ���������
	if(rate < fClient)//ͼƬ�Ƚ�"��"�����,��ͼƬ�߶Ƚ������ŵ�tracker�ĸ߶ȣ�Ȼ����ͬ��������
	{
		img.Resample2(img.GetWidth()/hScale,img.GetHeight()/hScale,CxImage::InterpolationMethod::IM_NEAREST_NEIGHBOUR,CxImage::OverflowMethod::OM_REPEAT,&imgRate);
		m_ZoomFactor  = m_PreZoomFactor = 1/hScale;
	}
	else//ͼƬ�Ƚ�"��"���������ͼƬ��Ƚ������ŵ�tracker�Ŀ�ȣ�Ȼ��߶�ͬ��������
	{
		img.Resample2(img.GetWidth()/wScale,img.GetHeight()/wScale,CxImage::InterpolationMethod::IM_NEAREST_NEIGHBOUR,CxImage::OverflowMethod::OM_REPEAT,&imgRate);
		m_ZoomFactor  = m_PreZoomFactor = 1/wScale;
	}
	m_iStartx = imgRate.GetWidth() - rcThis.Width();
	m_iStartx/=2;

	m_iStarty = imgRate.GetHeight() - rcThis.Height();
	m_iStarty/=2;
	Invalidate();
}

BOOL CTrackerCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return TRUE;
}

void CTrackerCtrl::SetDrag(bool bDrag)
{
	m_bDrag = bDrag;
}

float CTrackerCtrl::GetZoomFactor()
{
	return m_ZoomFactor;
}

void CTrackerCtrl::SetZoomFactor(int pos)
{
	if (pos == 50)//ԭʼ��С
	{
		m_ZoomFactor = 1;
	}
	else if (pos<50)
	{
		m_ZoomFactor = 1;
		for (int i=0; i<50 - pos; i++)
		{
			m_ZoomFactor /= ZOOM_FACTOR_PER_SLIDER_POS;
		}
	}
	else 
	{
		m_ZoomFactor = 1;
		for ( int i=0; i<pos - 50; i++)
		{
			m_ZoomFactor *= ZOOM_FACTOR_PER_SLIDER_POS;
		}
	}
	CRect  rcThis;
	GetClientRect(rcThis);
	//DragonZ:���µ�if-else�Ĵ������ԭ��(from Rainbow)����һģһ���ģ���֮
//ԭ�棺
	/*if (m_ZoomFactor<1)
	{   
		bool	bRet = img.Resample(img.GetWidth()*m_ZoomFactor,img.GetHeight()*m_ZoomFactor,1,&imgRate);
		if (bRet == false)
		{
			TRACE(_T("����ʧ��\n\r"));
			return;
		}
	}
	else
	{
		bool	bRet = img.Resample(img.GetWidth()*m_ZoomFactor,img.GetHeight()*m_ZoomFactor,1,&imgRate);
		if (bRet == false)
		{
			TRACE(_T("����ʧ��\n\r"));
			return;
		}
	}*/

	//DragonZ:
	bool bRet = img.Resample(img.GetWidth()*m_ZoomFactor,img.GetHeight()*m_ZoomFactor,1,&imgRate);
	//bool bRet = true;
	if (bRet == false)
	{
		TRACE(_T("����ʧ��\n\r"));
		return;
	}

	CRect rectTracker;
	m_tracker.GetTrueRect(&rectTracker);
	float fStartx = (m_ZoomFactor/m_PreZoomFactor)*((rectTracker.left+rectTracker.right)/2 + m_iStartx) -  (rectTracker.left+rectTracker.right)/2;
	m_iStartx = fStartx>0?(fStartx*2+1)/2:(fStartx*2-1)/2;

	float fStarty = ((rectTracker.top + rectTracker.bottom)/2 + m_iStarty)*(m_ZoomFactor/m_PreZoomFactor) - (rectTracker.top + rectTracker.bottom)/2;
	m_iStarty = fStarty>0?(fStarty*2+1)/2:(fStarty*2-1)/2;
	m_PreZoomFactor = m_ZoomFactor;
	Invalidate();
}
