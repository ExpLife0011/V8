// SkinProgress.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageBase.h"
#include "SkinEngine.h"
#include "SkinItemDialog.h"
#include "SkinProgress.h"
#include ".\skinprogress.h"


// CSkinProgress

IMPLEMENT_DYNCREATE(CSkinProgress, CSkinBase)

CSkinProgress::CSkinProgress()
{
	EnableAutomation();
	
	// Ϊ��ʹӦ�ó����� OLE �Զ��������ڻ״̬ʱ����
	//	���У����캯������ AfxOleLockApp��
	
	m_nRange = 100;
	m_nPos = 0;
	m_pBackImage = NULL;
    m_strBackImage;
	m_pPosImage = NULL;
    m_strPosImage;

	AfxOleLockApp();
}

CSkinProgress::~CSkinProgress()
{
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	// 	������������ AfxOleUnlockApp��
	AfxOleUnlockApp();
}

void CSkinProgress::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CSkinProgress, CSkinBase)
END_MESSAGE_MAP()


BEGIN_SKIN_DISPATCH_MAP(CSkinProgress, CSkinBase)
	SKINBASE_DISP_PROPERTIES(CSkinProgress)

	SKIN_DISP_PROPERTY(CSkinProgress, range, VT_I4)
	SKIN_DISP_PROPERTY(CSkinProgress, pos, VT_I4)
	SKIN_DISP_PROPERTY(CSkinProgress, backimage, VT_BSTR)
	SKIN_DISP_PROPERTY(CSkinProgress, posimage, VT_BSTR)

END_SKIN_DISPATCH_MAP(CSkinProgress)

// ע��: ������� IID_ISkinProgress ֧��
//��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//���Ƚӿڵ� GUID ƥ�䡣

// {8A397DD1-9D50-4E05-A2C7-41106310F836}
static const IID IID_ISkinProgress =
{ 0x8A397DD1, 0x9D50, 0x4E05, { 0xA2, 0xC7, 0x41, 0x10, 0x63, 0x10, 0xF8, 0x36 } };

BEGIN_INTERFACE_MAP(CSkinProgress, CSkinBase)
	INTERFACE_PART(CSkinProgress, IID_ISkinProgress, Dispatch)
END_INTERFACE_MAP()

// {35ED3931-2447-4FE6-9370-3455521426C8}
IMPLEMENT_OLECREATE_FLAGS(CSkinProgress, "Skin.SkinProgress", afxRegApartmentThreading, 0x35ed3931, 0x2447, 0x4fe6, 0x93, 0x70, 0x34, 0x55, 0x52, 0x14, 0x26, 0xc8)


// CSkinProgress ��Ϣ�������
BSTR CSkinProgress::Getbackimage(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return m_strBackImage.AllocSysString();
}

void CSkinProgress::Setbackimage(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
    SetImageHelper(m_pBackImage, m_strBackImage, newVal);
}

BSTR CSkinProgress::Getposimage(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return m_strPosImage.AllocSysString();
}

void CSkinProgress::Setposimage(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
    SetImageHelper(m_pPosImage, m_strPosImage, newVal);
}

LONG CSkinProgress::Getrange(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return m_nRange;
}

void CSkinProgress::Setrange(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (newVal < 0 || newVal == m_nRange){
		return;
	}
	m_nRange = newVal;
	if (m_nRange < m_nPos){
		m_nPos = m_nRange;
	}
	InvalidateRect();
}

LONG CSkinProgress::Getpos()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return m_nPos;
}

void CSkinProgress::Setpos(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (newVal == m_nPos)
		return;
	if (newVal < 0){
		newVal = 0;
	}else if (newVal > newVal){
		newVal = m_nRange;
	}
	m_nPos = newVal;
	InvalidateRect();
}

void CSkinProgress::Draw(CDC* pDC, LPRECT lpInvalidRect, CRgn* pInvalidRgn)
{
	const int nWidth = m_rcSkinRect.Width();
	const int nHeight = m_rcSkinRect.Height();
	if (m_pBackImage != NULL){
		m_pBackImage->Draw(*pDC, &m_rcSkinRect, NULL, GetImageParam(), GetTransformedTransparentColor());
	}
	if (m_pPosImage != NULL){
		const int nWidth2 = m_rcSkinRect.Width() * m_nPos / m_nRange;
		const int imgWidth = m_pPosImage->Width();
		const int imgHeight = m_pPosImage->Height();
		const int imgDrawNum = nWidth2 / imgWidth;
		int i;
		CRect rcDraw = m_rcSkinRect;
		rcDraw.right = rcDraw.left + imgWidth;
		for (i=0; i<imgDrawNum; i++){
			m_pPosImage->Draw(*pDC, &rcDraw, NULL, GetImageParam(), GetTransformedTransparentColor());
			rcDraw.OffsetRect(imgWidth, 0);
		}
		const int widthLeft = nWidth2 % imgWidth;	//ʣ�µ�δ���ƵĿ��
		if (widthLeft > 0){
			CRect dcRect;
			dcRect.left = m_rcSkinRect.left + i * imgWidth;
			dcRect.top = m_rcSkinRect.top;
			dcRect.right = dcRect.left + widthLeft;
			dcRect.bottom = dcRect.top + nHeight;
			CRect dibRect(0, 0, widthLeft, imgHeight);
			m_pPosImage->Draw(*pDC, &dcRect, NULL, GetImageParam(), GetTransformedTransparentColor());
		}
	}
}
