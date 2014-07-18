#pragma once

#include "afx.h"

// CColorEdit

class  CColorEdit : 
	public CEdit
{
	DECLARE_DYNAMIC(CColorEdit)

public:
	CColorEdit();
	virtual ~CColorEdit();


	/**
	@fn SetTextColor
	@brief ���ñ༭�����ı�����ɫ
	@param	[in] rgb	���õ��ı���ɫ
	**/
	void SetTextColor(COLORREF rgb);

	/**
	@fn GetTextColor
	@brief ��ȡ�༭�����ı�����ɫ
	@return	
	**/
	const COLORREF GetTextColor();

	/**
	@fn SetBackColor
	@brief ���ñ༭��ı���ɫ
	@param	[in] rgb	���õı�����ɫ
	**/
	void SetBackColor(COLORREF rgb);

	/**
	@fn GetBackColor
	@brief ��ȡ�༭��ı���ɫ
	@return	
	**/
	const COLORREF GetBackColor();

	/**
	@fn SetDisableBackColor( COLORREF rgb)
	@brief ���༭�򱻽��õ�ʱ��ı���ɫ
	@param	[in] rgb	���õĽ��ñ�����ɫ
	**/
	void SetDisableBackColor( COLORREF rgb);

	/**
	@fn SetRimColor( COLORREF rgb)
	@brief �༭��ı���ɫ
	@param	[in] rgb	���õı߿�ɫ
	**/
	void SetRimColor(COLORREF rgb)
	{
		m_crBorder = rgb;
	}

protected:

	COLORREF            m_crText;               //�ı���ɫ
	CBrush              m_brBackGnd;            //����ˢ��
	COLORREF            m_crBackGnd;            //������ɫ
	COLORREF			m_crBorder;
	COLORREF			m_crDisableBackGnd;		//����ʱ��ı���ɫ

	//{{AFX_MSG(CColorEdit)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void   OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
	virtual void PreSubclassWindow();
};


