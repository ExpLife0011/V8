#pragma once

#include "stdafx.h"
#include "Common.h"
#include "afx.h"
#include <string>

using namespace std;

///////////////////////////////////////////////////////////
//	����: CTextLabel
//  �๦��������
//  	�ı���ǩ���������øñ�ǩ����ɫ��������
//		����һ������������ı�����������Զ�����ʡ�Դ���
//		����Ŀǰ���û�ͷ��tips�й㷺ʹ��


class COMMON_INTERFACE CTextLabel
{
public:
	CTextLabel();
	virtual ~CTextLabel();

	wstring GetSplitterString( wstring wstrText);

	/**
	@fn SetDC( CDC* pDC)
	@brief ���ñ�ǩ���ڵ�DC
	@param	[in] pDC	DC����
	**/
	void	SetDC( CDC* pDC) { m_pDC = pDC;}

	/**
	@fn SetFont( CFont* pFont)
	@brief ���ñ�ǩ���ı�����ɫ
	@param	[in] pDC	DC����
	**/
	void	SetFont( CFont* pFont) { m_pFont = pFont;}

	/**
	@fn SetText( wstring wstrText)
	@brief ���ñ�ǩ���ı�����
	@param	[in] wstrText	�ı�����
	**/
	void	SetText( wstring wstrText) { m_strText = wstrText;}

	/**
	@fn SetColor( COLORREF clrText)
	@brief ���ñ�ǩ���ı�����ɫ
	@param	[in] wstrText	�ı�����
	**/
	void	SetColor( COLORREF clrText) { m_clrText = clrText;}

	/**
	@fn SetUnderLine( BOOL bUnderline)
	@brief ���ñ�ǩ���ı��Ƿ���Ҫ����»���
	@param	[in] bUnderline	TRUE��ʾ��Ҫ�»��ߣ�FALSE������Ҫ
	**/
	void	SetUnderLine( BOOL bUnderline = TRUE) { m_bUnderline = bUnderline;}

	/**
	@fn SetLineSpace( UINT nLineSpace)
	@brief ����������֮��ļ�����룬Ĭ��Ϊ0
	@param	[in] nLineSpace	�о�
	**/
	void	SetLineSpace( UINT nLineSpace) { m_nLineSpace = nLineSpace;}

	/**
	@fn GetLineSpace()
	@brief ��ȡ������֮��ľ���
	@param	[in] nLineSpace	�о�
	**/
	UINT	GetLineSpace() { return m_nLineSpace;}

	/**
	@fn SetRect( CRect rect)
	@brief ���øñ�ǩ��ռ�ݵľ�������
	@param	[in] rect	�о�
	**/
	void	SetRect( CRect rect) { m_rcText = rect;}

	/**
	@fn Draw()
	@brief ����
	@param	[in] rect	�о�
	**/	
	void	Draw();

private:

	void	DrawLine( BOOL bDraw = TRUE);
	UINT	GetCharWidthInfo( wstring strText );
	UINT	GetCharHeightInfo( wstring strText);
	wstring	GetFittableStringFromFront( wstring wstrText, UINT nWidth, int nBeginIndex, int& nEndIndex);

	wstring		m_strText;			//	Label�е�����
	CRect		m_rcText;			//	Label�ľ�������
	CDC*		m_pDC;				//	���ڵ��豸����
	CFont*		m_pFont;			//	��������
	COLORREF	m_clrText;			//	���ֵ���ɫ
	BOOL		m_bUnderline;		//	�Ƿ�Ҫ�����»���
	UINT		m_nLineSpace;		//	������֮��ļ�࣬Ĭ��Ϊ0
};