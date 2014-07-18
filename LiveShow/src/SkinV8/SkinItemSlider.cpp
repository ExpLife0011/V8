// SkinItemSlider.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SkinItem.h"
#include "ImageBase.h"
#include "SkinEngine.h"
#include "SkinItemSlider.h"


// CSkinItemSlider

IMPLEMENT_DYNCREATE(CSkinItemSlider, CSkinItem)
CSkinItemSlider::CSkinItemSlider()
{
	EnableAutomation();
	
	// Ϊ��ʹӦ�ó����� OLE �Զ��������ڻ״̬ʱ����
	//	���У����캯������ AfxOleLockApp��

	m_bTransparent = TRUE;
	
	m_pChannelImage = NULL;
	m_pThumbNormalImage = NULL;
	m_pThumbClickImage = NULL;
    m_pFullImage = NULL;
	m_lBarHeight = 5;
	m_lFullBegin = 0;

    m_bInThumbOrDrag = FALSE;
	m_bVeritySlider = FALSE;

	AfxOleLockApp();
}

CSkinItemSlider::~CSkinItemSlider()
{
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	// 	������������ AfxOleUnlockApp��
	
	AfxOleUnlockApp();
}

void CSkinItemSlider::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CSkinItem::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CSkinItemSlider, CSkinItem)
END_MESSAGE_MAP()


BEGIN_SKIN_DISPATCH_MAP(CSkinItemSlider, CSkinItem)
	SKINBASE_DISP_PROPERTIES(CSkinItemSlider)
	SKINITEM_DISP_PROPERTIES(CSkinItemSlider)

	SKIN_DISP_PROPERTY(CSkinItemSlider, channelImage, VT_BSTR)
	SKIN_DISP_PROPERTY(CSkinItemSlider, thumbNormalImage, VT_BSTR)
	SKIN_DISP_PROPERTY(CSkinItemSlider, thumbClickImage, VT_BSTR)
	SKIN_DISP_PROPERTY(CSkinItemSlider, fullImage, VT_BSTR)//DragonZ
	SKIN_DISP_PROPERTY(CSkinItemSlider, barHeight, VT_I4)//DragonZ
	SKIN_DISP_PROPERTY(CSkinItemSlider, fullBegin, VT_I4)//DragonZ
	SKIN_DISP_PROPERTY(CSkinItemSlider, veritySlider, VT_BOOL)//DragonZ

	SKIN_DISP_PROPERTY_ALIAS(CSkinItemSlider, thumbImage, thumbNormalImage, VT_BSTR)
	SKIN_DISP_PROPERTY_ALIAS(CSkinItemSlider, thumbImageClick, thumbClickImage, VT_BSTR)

END_SKIN_DISPATCH_MAP(CSkinItemSlider)

// ע��: ������� IID_ISkinItemSlider ֧��
//��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//���Ƚӿڵ� GUID ƥ�䡣

// {EE3ADE8C-C3DB-43A1-BE49-A76EBCDCBE3D}
static const IID IID_ISkinItemSlider =
{ 0xEE3ADE8C, 0xC3DB, 0x43A1, { 0xBE, 0x49, 0xA7, 0x6E, 0xBC, 0xDC, 0xBE, 0x3D } };

BEGIN_INTERFACE_MAP(CSkinItemSlider, CSkinItem)
	INTERFACE_PART(CSkinItemSlider, IID_ISkinItemSlider, Dispatch)
END_INTERFACE_MAP()

// {E7F24884-272E-4AB0-9E96-777FC927BCBE}
IMPLEMENT_OLECREATE(CSkinItemSlider, "Skin.SkinItemSlider", 0xe7f24884, 0x272e, 0x4ab0, 0x9e, 0x96, 0x77, 0x7f, 0xc9, 0x27, 0xbc, 0xbe)


// CSkinItemSlider ��Ϣ�������
BOOL CSkinItemSlider::GetPos(LONG& pos)
{
	ASSERT(::IsWindow(m_hWnd));
	if (!::IsWindow(m_hWnd))
		return FALSE;

	pos = (UINT)::SendMessage(m_hWnd, TBM_GETPOS, 0, 0);
	return TRUE;
}

BOOL CSkinItemSlider::SetPos(LONG pos)
{
	ASSERT(::IsWindow(m_hWnd));
	if (!::IsWindow(m_hWnd))
		return FALSE;

	return (BOOL)::SendMessage(m_hWnd, TBM_SETPOS, 0, (LPARAM)pos);
}

BOOL CSkinItemSlider::GetMin(LONG& minValue)
{
	ASSERT(::IsWindow(m_hWnd));
	if (!::IsWindow(m_hWnd))
		return FALSE;

	minValue = (UINT)::SendMessage(m_hWnd, TBM_GETRANGEMIN, 0, 0);
	return TRUE;
}

BOOL CSkinItemSlider::SetMin(LONG minValue)
{
	ASSERT(::IsWindow(m_hWnd));
	if (!::IsWindow(m_hWnd))
		return FALSE;

	::SendMessage(m_hWnd, TBM_SETRANGEMIN, TRUE, (LPARAM)minValue);
	return TRUE;
}

BOOL CSkinItemSlider::GetMax(LONG& maxValue)
{
	ASSERT(::IsWindow(m_hWnd));
	if (!::IsWindow(m_hWnd))
		return FALSE;

	maxValue = (UINT)::SendMessage(m_hWnd, TBM_GETRANGEMAX, 0, 0);
	return TRUE;
}

BOOL CSkinItemSlider::SetMax(LONG maxValue)
{
	ASSERT(::IsWindow(m_hWnd));
	if (!::IsWindow(m_hWnd))
		return FALSE;

	::SendMessage(m_hWnd, TBM_SETRANGEMAX, TRUE, (LPARAM)maxValue);
	return TRUE;
}

BOOL CSkinItemSlider::GetThumbRect(RECT& thumbRect)
{
	ASSERT(::IsWindow(m_hWnd));
	if (!::IsWindow(m_hWnd))
		return FALSE;

	::SendMessage(m_hWnd, TBM_GETTHUMBRECT, 0, (LPARAM)(&thumbRect));
	return TRUE;
}

BOOL CSkinItemSlider::GetThumbImgRect(RECT& thumbRect)
{
	CImageBase * pImgThumb = m_pThumbNormalImage;
	RECT tempRect;
	GetThumbRect(tempRect);
	int nThumbWidth = tempRect.right - tempRect.left;
	int nThumbHeight = tempRect.bottom - tempRect.top;

	int nTemp = (pImgThumb->Width() - nThumbWidth)/2;
	thumbRect.left = tempRect.left - nTemp - 2;//��֣���ô��ƫ�����������ء������ѵ���ͼƬ������
	if (thumbRect.left < 0)
	{
		thumbRect.left = 0;
	}
	nTemp = (pImgThumb->Height() - nThumbHeight)/2;
	thumbRect.top = tempRect.top - nTemp;
	if (thumbRect.top < 0)
	{
		thumbRect.top = 0;
	}

	thumbRect.right = thumbRect.left + pImgThumb->Width();
	thumbRect.bottom = thumbRect.top + pImgThumb->Height();

	return TRUE;
}

BOOL CSkinItemSlider::GetChannelRect(RECT& channelRect)
{
	ASSERT(::IsWindow(m_hWnd));
	if (!::IsWindow(m_hWnd))
		return FALSE;
	RECT rcTemp;
	::SendMessage(m_hWnd, TBM_GETCHANNELRECT, 0, (LPARAM)(&rcTemp));
	if (!m_bVeritySlider)
	{
		channelRect = rcTemp;
	}else
	{
		RECT rcSlider;
		GetClientRect(m_hWnd, &rcSlider);
		channelRect.left = rcSlider.left + (rcSlider.right - rcSlider.left - (rcTemp.bottom - rcTemp.top) )/2;
		channelRect.right = channelRect.left + rcTemp.bottom - rcTemp.top;
		channelRect.top = rcSlider.top + (rcSlider.bottom - rcSlider.top - (rcTemp.right - rcTemp.left) )/2;;
		channelRect.bottom = channelRect.top + rcTemp.right - rcTemp.left;
	}
	return TRUE;
}
//DragonZ
BOOL CSkinItemSlider::GetFullRect(RECT& fullRect)
{
    RECT channelRc,thumbRc,fullRc;
	GetChannelRect(channelRc);
	GetThumbImgRect(thumbRc);
    fullRc = channelRc;
	if (!m_bVeritySlider)
	{
		fullRc.right = thumbRc.left;
	}else
	{
		fullRc.top = thumbRc.bottom; // �����������
		fullRc.bottom -= 2;
	}
	fullRect = fullRc;
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
BSTR CSkinItemSlider::GetchannelImage()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	return m_strChannelImage.AllocSysString();
}

void CSkinItemSlider::SetchannelImage(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ�������Դ���������
    SetImageHelper(m_pChannelImage, m_strChannelImage, newVal);
}

BSTR CSkinItemSlider::GetthumbNormalImage()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	return m_strThumbNormalImage.AllocSysString();
}

void CSkinItemSlider::SetthumbNormalImage(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ�������Դ���������
    SetImageHelper(m_pThumbNormalImage, m_strThumbNormalImage, newVal);
}

BSTR CSkinItemSlider::GetthumbClickImage()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	return m_strThumbClickImage.AllocSysString();
}

void CSkinItemSlider::SetthumbClickImage(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ�������Դ���������
    SetImageHelper(m_pThumbClickImage, m_strThumbClickImage, newVal);
}

//���¼���DragonZ���
BSTR CSkinItemSlider::GetfullImage()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	return m_strFullImage.AllocSysString();
}

void CSkinItemSlider::SetfullImage(LPCTSTR newVal)
{ 
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: �ڴ�������Դ���������
	SetImageHelper(m_pFullImage, m_strFullImage, newVal);
}

LONG CSkinItemSlider::GetbarHeight()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return m_lBarHeight;
}

void CSkinItemSlider::SetbarHeight(LONG newVal)
{
	m_lBarHeight = newVal;
}

LONG CSkinItemSlider::GetfullBegin()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return m_lFullBegin;
}

void CSkinItemSlider::SetfullBegin(LONG newVal)
{
	m_lFullBegin = newVal;
}

void CSkinItemSlider::SetveritySlider( VARIANT_BOOL newVal )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (newVal != m_bVeritySlider)
	{
		m_bVeritySlider = newVal;
	}
}

VARIANT_BOOL CSkinItemSlider::GetveritySlider()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return m_bVeritySlider;
}

//////////////////////////////////////////////////////////////////////////
//����
//////////////////////////////////////////////////////////////////////////
void CSkinItemSlider::DrawBackground(CDC* pDC, LPRECT lpInvalidRect, CRgn* pInvalidRgn, BOOL bChildSkin)
{
	CSkinBase::DrawBackground(pDC, lpInvalidRect, pInvalidRgn);
	if (m_pChannelImage != NULL) {
		CRect channelRect = GetSkinAbsRect();
		GetChannelRect(channelRect);
		LONG lBarHeight = GetbarHeight();
		if (lBarHeight > 0)
		{
			if (!m_bVeritySlider)
			{
				channelRect.top = channelRect.top - (lBarHeight - channelRect.Height())/2;
				channelRect.bottom = channelRect.top + lBarHeight;
		    }else
			{
                channelRect.left = channelRect.left - (lBarHeight - channelRect.Width())/2;
				channelRect.right = channelRect.left + lBarHeight;
			}
		}
		m_pChannelImage->Draw(*pDC, &channelRect, NULL, GetImageParam(), GetTransformedTransparentColor());
	}
	
}


void CSkinItemSlider::DrawForeground(CDC* pDC, LPRECT lpInvalidRect, CRgn* pInvalidRgn)
{
	CImageBase* pImage = m_pThumbNormalImage;
	if (pImage == NULL)
		pImage = m_pThumbClickImage;
	if (pImage != NULL) {
		CRect thumbRect = GetSkinAbsRect();
		//GetThumbRect(thumbRect);
		GetThumbImgRect(thumbRect);
		pImage->Draw(*pDC, &thumbRect, NULL, GetImageParam(), GetTransformedTransparentColor(), true);

	}
	/////////////DragonZ/////////////////
	CImageBase* pFullImage = m_pFullImage;
	if (pFullImage == NULL)
		pFullImage = m_pFullImage;
	if (pFullImage != NULL) {
		CRect fullRect = GetSkinAbsRect();
		GetFullRect(fullRect);
		LONG lBarHeight = GetbarHeight();

		if (lBarHeight > 0)
		{
			if (!m_bVeritySlider)
			{
				fullRect.top = fullRect.top - (lBarHeight - fullRect.Height())/2;
				fullRect.bottom = fullRect.top + lBarHeight;
			}else
			{
				fullRect.left = fullRect.left + (fullRect.Width() - lBarHeight)/2;
				fullRect.right = fullRect.left + lBarHeight;
			}
		}

		LONG lFullBegin = GetfullBegin();
        if (lFullBegin > 0)
        {
			if (!m_bVeritySlider)
			{
				fullRect.left = fullRect.left + lFullBegin;
			}else
			{
				fullRect.bottom = fullRect.bottom - lFullBegin; // �����������
			}
        }

		pFullImage->Draw(*pDC, &fullRect, NULL, GetImageParam(), GetTransformedTransparentColor());
	}
	/////////////////////////////////////
}

void CSkinItemSlider::DrawFrame(CDC* pDC, LPRECT lpInvalidRect, CRgn* pInvalidRgn)
{
}

void CSkinItemSlider::Draw(CDC* pDC, LPRECT lpInvalidRect, CRgn* pInvalidRgn)
{
	DrawBackground(pDC, lpInvalidRect, pInvalidRgn);
	DrawForeground(pDC, lpInvalidRect, pInvalidRgn);
	DrawFrame(pDC, lpInvalidRect, pInvalidRgn);
}

//����Ƥ�����ԣ���Ƥ���¸��Ŵ���ʱ����
BOOL CSkinItemSlider::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* lpResult)
{
	*lpResult = 0;

	ASSERT(::IsWindow(m_hWnd));
	if (! ::IsWindow(m_hWnd) || ::IsIconic(m_hWnd))
		return FALSE;

	//׼��CWnd
	CWnd* pWnd = CWnd::FromHandle(m_hWnd);
	if (pWnd == NULL)
		return TRUE;

	//׼��DC
	CPaintDC dc(pWnd);

	//�����ؾ���
	CRect rcInvalid = dc.m_ps.rcPaint;

	//˫����
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap memBitmap;
	memBitmap.CreateCompatibleBitmap(&dc, GetWidth(), GetHeight());
	CBitmap* pOldBitmap = memDC.SelectObject(&memBitmap);

	//�ڻ����ϻ���
	Draw(&memDC, &rcInvalid, NULL);

	//���ƻ���DC����ʾDC
	dc.BitBlt(0, 0, GetWidth(), GetHeight(), &memDC, 0, 0, SRCCOPY);

	//�ָ�memDC
	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();

	memBitmap.DeleteObject();

	return !GetselfOnPaint();
}

BOOL CSkinItemSlider::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* lpResult)
{
    LONG x = GETXPARAM(lParam);
    LONG y = GETYPARAM(lParam);
    UINT flag = (UINT)wParam;
    CRect rect(0, 0, 0, 0);
    GetThumbRect(rect);
    if (rect.PtInRect(CPoint(x, y))
        || ::GetCapture() == m_hWnd) {
        m_bInThumbOrDrag = TRUE;
    } else {
        m_bInThumbOrDrag = FALSE;
    }

    return CSkinItem::OnMouseMove(uMsg, wParam, lParam, lpResult);
}

BOOL CSkinItemSlider::OnCaptureChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* lpResult)
{
    m_bInThumbOrDrag = FALSE;

    return CSkinItem::OnCaptureChanged(uMsg, wParam, lParam, lpResult);
}

BOOL CSkinItemSlider::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* lpResult)
{
    HCURSOR hCur = GetSkinCursor(NULL);
    if (m_bInThumbOrDrag && hCur != NULL) {
        ::SetCursor(hCur);
        return TRUE;
    }
    return CSkinItem::OnSetCursor(uMsg, wParam, lParam, lpResult);
}

