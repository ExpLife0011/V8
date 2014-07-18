#pragma once

#ifdef GDIPLUS_BITMAP_SUPPORT

#include "imagebase.h"
#include "ImageTransformParam.h"

class CImageBaseImplBitmap :
	public CImageBase
{
public:
	CImageBaseImplBitmap(void);
	virtual ~CImageBaseImplBitmap(void);
public:
	static BOOL TransformColor(const CImageTransformParam* pParam, LONG color, LONG& transformColor);

	virtual BOOL LoadFromFile(LPCTSTR filePathName);
	virtual BOOL LoadFromData(const char* pzData, long size);
	virtual BOOL Transform(const CImageTransformParam* pParam);
	virtual BOOL Draw(HDC hDC, LPCRECT lpDstRect, LPRECT lpClipRect = NULL, const CImageTransformParam* pParam = NULL, 
        LONG clrTransparent = -1, BOOL bAlpha = FALSE, 
        BOOL bSideStretch = TRUE, LONG sideWidth = 0, LONG sideHeight = 0);
	virtual LONG Width();
	virtual LONG Height();
protected:
    Gdiplus::Bitmap* m_pOriBitmap;		//ԭʼͼ��
	Gdiplus::Bitmap* m_pTransformedBitmap;		//�任��ͼ�񣬰�����ֵ�任����ɫ�任
	CImageTransformParam m_transformParam;	//�任��ͼ��ı任����
};

#endif //GDIPLUS_BITMAP_SUPPORT
