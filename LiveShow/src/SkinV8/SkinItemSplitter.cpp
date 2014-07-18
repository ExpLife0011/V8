// SkinItemSplitter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SkinItem.h"
#include "SkinItemSplitter.h"


// CSkinItemSplitter

IMPLEMENT_DYNCREATE(CSkinItemSplitter, CSkinItem)
CSkinItemSplitter::CSkinItemSplitter()
{
	EnableAutomation();
	
	// Ϊ��ʹӦ�ó����� OLE �Զ��������ڻ״̬ʱ����
	//	���У����캯������ AfxOleLockApp��

	m_bTransparent = TRUE;

	AfxOleLockApp();
}

CSkinItemSplitter::~CSkinItemSplitter()
{
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	// 	������������ AfxOleUnlockApp��
	
	AfxOleUnlockApp();
}


void CSkinItemSplitter::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CSkinItem::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CSkinItemSplitter, CSkinItem)
END_MESSAGE_MAP()


BEGIN_SKIN_DISPATCH_MAP(CSkinItemSplitter, CSkinItem)
	SKINBASE_DISP_PROPERTIES(CSkinItemSplitter)
	SKINITEM_DISP_PROPERTIES(CSkinItemSplitter)

END_SKIN_DISPATCH_MAP(CSkinItemSplitter)

// ע��: ������� IID_ISkinItemSplitter ֧��
//��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//���Ƚӿڵ� GUID ƥ�䡣

// {A0BD99BE-1C40-46FB-AA24-652423F6DCF8}
static const IID IID_ISkinItemSplitter =
{ 0xA0BD99BE, 0x1C40, 0x46FB, { 0xAA, 0x24, 0x65, 0x24, 0x23, 0xF6, 0xDC, 0xF8 } };

BEGIN_INTERFACE_MAP(CSkinItemSplitter, CSkinItem)
	INTERFACE_PART(CSkinItemSplitter, IID_ISkinItemSplitter, Dispatch)
END_INTERFACE_MAP()

// {FA66128A-44E0-4192-A535-10C10DC26CA7}
IMPLEMENT_OLECREATE_FLAGS(CSkinItemSplitter, "Skin.SkinItemSplitter", afxRegApartmentThreading, 0xfa66128a, 0x44e0, 0x4192, 0xa5, 0x35, 0x10, 0xc1, 0xd, 0xc2, 0x6c, 0xa7)


// CSkinItemSplitter ��Ϣ�������
void CSkinItemSplitter::DrawBackground(CDC* pDC, LPRECT lpInvalidRect, CRgn* pInvalidRgn, BOOL bChildSkin)
{
	CSkinBase::DrawBackground(pDC, lpInvalidRect, pInvalidRgn);
}

void CSkinItemSplitter::DrawForeground(CDC* pDC, LPRECT lpInvalidRect, CRgn* pInvalidRgn)
{

}

void CSkinItemSplitter::DrawFrame(CDC* pDC, LPRECT lpInvalidRect, CRgn* pInvalidRgn)
{

}

void CSkinItemSplitter::Draw(CDC* pDC, LPRECT lpInvalidRect, CRgn* pInvalidRgn)
{
	DrawBackground(pDC, lpInvalidRect, pInvalidRgn);
	DrawForeground(pDC, lpInvalidRect, pInvalidRgn);
	DrawFrame(pDC, lpInvalidRect, pInvalidRgn);
}

BOOL CSkinItemSplitter::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* lpResult)
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

    //����dc������dc
    memDC.BitBlt(0, 0, GetWidth(), GetHeight(), &dc, 0, 0, SRCCOPY);

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
