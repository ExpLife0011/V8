
#pragma once

#include "SkinBaseDefine.h"
#include "XmlCmdTarget.h"

// CSkinTextStyle ����Ŀ��

class CSkinTextStyle : public CXmlCmdTarget
{
	DECLARE_DYNCREATE(CSkinTextStyle)

public:
	CSkinTextStyle();
	virtual ~CSkinTextStyle();
	CSkinTextStyle& operator = (const CSkinTextStyle& style);

	virtual void OnFinalRelease();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CSkinTextStyle)
	DECLARE_SKIN_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

protected:
	enum
	{
		SKIN_DISPID(CSkinTextStyle, color),
		SKIN_DISPID(CSkinTextStyle, bkColor),
		SKIN_DISPID(CSkinTextStyle, bkMode),
		SKIN_DISPID(CSkinTextStyle, fontSize),
		SKIN_DISPID(CSkinTextStyle, fontWeight),
		SKIN_DISPID(CSkinTextStyle, italic),
		SKIN_DISPID(CSkinTextStyle, underline),
		SKIN_DISPID(CSkinTextStyle, strikeOut),
		SKIN_DISPID(CSkinTextStyle, fontFamily),
		SKIN_DISPID(CSkinTextStyle, shadow),
		SKIN_DISPID(CSkinTextStyle, wordBreak),
		SKIN_DISPID(CSkinTextStyle, endEllipsis),
		SKIN_DISPID(CSkinTextStyle, noPrefix),
		SKIN_DISPID(CSkinTextStyle, singleLine),
		SKIN_DISPID(CSkinTextStyle, horizAlign),
		SKIN_DISPID(CSkinTextStyle, vertiAlign),
		SKIN_DISPID(CSkinTextStyle, beginLineMargin),
		SKIN_DISPID(CSkinTextStyle, lineMargin),
		SKIN_DISPID(CSkinTextStyle, endLineMargin),
		SKIN_DISPID(CSkinTextStyle, underlineMargin),
        SKIN_DISPID(CSkinTextStyle, ignoreCRLF),
	};

public:
	BOOL IsChanged();
	BOOL IsFontChanged();
	BOOL IsFormatChanged();
	UINT GetFormat();
	CFont* GetFont();
	UINT GetBkMode();
	BOOL UpdateFormat(HDC hDC);
	BOOL UpdateFont(HDC hDC);
	BOOL GetTextSize(HDC hDC, LPCTSTR strText, LONG& width, LONG& height);
	BOOL GetTextSize(HDC hDC, LPCTSTR strText, CSize& size);
	BOOL DrawText(HDC hDC, LPCTSTR lpzText, LPRECT lpDrawRect, LPRECT lpRealDrawRect = NULL);
    BOOL DrawTextEx(HDC hDC, LPCTSTR lpzText, LPRECT lpDrawRect, LONG clrText, LPRECT lpRealDrawRect = NULL);
    LONG HitTest(const CString& strText, LONG x, LONG y);

	static int GlideByReturn(const CString& str);

protected:
	BOOL InternalUpdateFont(HDC hDC);
	BOOL InternalUpdateFormat(HDC hDC);
	BOOL InternalGetTextSize(HDC hDC, LPCTSTR strText, LONG& width, LONG& height);

public:
	//////////////////////////////////////////////////////////////////////////
	//����
	//////////////////////////////////////////////////////////////////////////
	//��ɫ
	LONG Getcolor(void);
	void Setcolor(LONG newVal);
	//������ɫ
	LONG GetbkColor();
	void SetbkColor(LONG newVal);
	//����ģʽ
	BSTR GetbkMode(void);
	void SetbkMode(LPCTSTR newVal);
	//��С
	LONG GetfontSize(void);
	void SetfontSize(LONG newVal);
	//weight
	LONG GetfontWeight(void);
	void SetfontWeight(LONG newVal);
	//б��
	VARIANT_BOOL Getitalic(void);
	void Setitalic(VARIANT_BOOL newVal);
	//�»���
	VARIANT_BOOL Getunderline(void);
	void Setunderline(VARIANT_BOOL newVal);
	//ɾ����
	VARIANT_BOOL GetstrikeOut(void);
	void SetstrikeOut(VARIANT_BOOL newVal);
	//���壬��_T("����")
	BSTR GetfontFamily(void);
	void SetfontFamily(LPCTSTR newVal);
	//��Ӱ
	VARIANT_BOOL Getshadow(void);
	void Setshadow(VARIANT_BOOL newVal);
	//word break
	VARIANT_BOOL GetwordBreak(void);
	void SetwordBreak(VARIANT_BOOL newVal);
	//end ellipsis
	VARIANT_BOOL GetendEllipsis(void);
	void SetendEllipsis(VARIANT_BOOL newVal);
	//no prefix
	VARIANT_BOOL GetnoPrefix(void);
	void SetnoPrefix(VARIANT_BOOL newVal);
	//����
	VARIANT_BOOL GetsingleLine(void);
	void SetsingleLine(VARIANT_BOOL newVal);
	//ˮƽ����
	BSTR GethorizAlign(void);
	void SethorizAlign(LPCTSTR newVal);
	//��ֱ����
	BSTR GetvertiAlign(void);
	void SetvertiAlign(LPCTSTR newVal);
	//��һ�����ϱ߼��
	LONG GetbeginLineMargin(void);
	void SetbeginLineMargin(LONG newVal);
	//���е��м��
	LONG GetlineMargin(void);
	void SetlineMargin(LONG newVal);
	//���һ�����±߼��
	LONG GetendLineMargin(void);
	void SetendLineMargin(LONG newVal);
	//�»��������ֵļ��
	LONG GetunderlineMargin(void);
	void SetunderlineMargin(LONG newVal);
    //����\r\n
    VARIANT_BOOL GetignoreCRLF(void);
    void SetignoreCRLF(VARIANT_BOOL newVal);

protected:
	LOGFONT	m_lfFont;			//ʹ�õ�����ṹ
	BOOL	m_bUnderline;		//�Ի���»���
	HFONT	m_fFont;			//ʹ�õ�����
	LONG	m_clrColor;			//�ֵ���ɫ
	LONG	m_clrBkColor;		//��������ɫ
	LONG	m_iFontSize;		//����Ĵ�С
	UINT	m_uBkMode;			//����ģʽ��TRANSPARENT��OPAQUE
	UINT	m_uFormat;			//����ʾ�ĸ�ʽ
	LONG	m_nBeginLineMargin;	//��һ�����ϱ߼��
	LONG	m_nLineMargin;		//���е��м��
	LONG	m_nEndLineMargin;	//���һ�����±߼��
	LONG	m_nUnderlineMargin;	//�»��������ֵļ��
	BOOL	m_bShadow;			//��ʾ�ֵ���Ӱ
    BOOL    m_bIgnoreCRLF;      //����\r\n
	BOOL	m_bFontChanged;		//���屻�ı䣬������ʶ�Ƿ��ؽ�����
	BOOL	m_bFormatChanged;	//�����Ų���ʽ�ı�
};

