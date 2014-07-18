#pragma once

#include "../Common.h"
#include "afx.h"
#include "afxtempl.h"

namespace common { namespace ui
{

class COMMON_INTERFACE CSimpleTipCtrl 
	: public CWnd
{
public:

	typedef struct
	{
		CString	szText;						//	Tooltip text

	} TipToolInfo;

	enum
	{
		timerShow			= 100,
		timerHide			= 101
	};

public:
	CSimpleTipCtrl();
	virtual ~CSimpleTipCtrl();

	/**
	@fn Show(CString szText, CWnd* pParent, CPoint *pt)
	@brief ��ָ����λ�õ���ʾTips
	@param	[in] szText	Tips������
	@param	[in] pt	����tips��λ�ã����ΪNULL��������Ϊ��굱ǰλ��
	@param	[in] nWidth	��Tips�Ŀ��
	@return 
	**/
	virtual void	Show(CString szText, CWnd* pParent, CPoint *pt = NULL, UINT nWidth = 60);

	/**
	@fn BeHide
	@brief ָ����ǰtips�Ƿ�����
	@return 
	**/
	BOOL	BeHide() ;

	/**
	@fn Hide
	@brief ����
	@return 
	**/
	virtual void	Hide();

	void	TerminateTimer( UINT nTimerId) { KillTimer( nTimerId);}

	/**
	@fn SetShowDelay(int nDelay)
	@brief ������ƶ������������Ϻ��ӳ���ʾTips��ʱ��
	@param	[in] nDelay		�ӳ�ʱ��
	**/
	void	SetShowDelay(int nDelay) { m_nShowDelay = nDelay; };

	/**
	@fn GetShowDelay
	@brief ��ȡ����ƶ������������Ϻ��ӳ���ʾTips��ʱ��
	@return	�ӳ�ʱ��
	**/
	const int	GetShowDelay() { return m_nShowDelay;}

	/**
	@fn SetHideDelay
	@brief ��Tips�������Զ���ʧ���ӳ�ʱ��
	@param	[in] nDelay		�ӳ�ʱ��, RB_INFINITE Ϊ���Զ���ʧ
	@return	�ӳ�ʱ��
	**/
	void	SetHideDelay(int nDelay) { m_nHideDelay = nDelay; };

	/**
	@fn GetHideDelay
	@brief ��ȡ��ʧ���ӳ�ʱ��
	@return	��ʧ�ӳ�ʱ��
	**/
	const int	GetHideDelay() { return m_nHideDelay;}

	/**
	@fn SetBkgColor
	@brief ��ȡTip�ı�����ɫ
	@param	[in] clrBkg		���õı���ɫ
	**/
	void	SetBkgColor( COLORREF clrBkg);

	/**
	@fn GetBkgColor
	@brief ��ȡTip�ı�����ɫ
	**/	
	const COLORREF	GetBkgColor();

	/**
	@fn SetBorderColor
	@brief ���úͻ�ȡTip�ı߿���ɫ
	@param	[in] clrBorder	���õı߽���ɫ
	**/
	void	SetBorderColor( COLORREF clrBorder);

	/**
	@fn GetBorderColor
	@brief ��ȡTip�ı߽���ɫ
	**/	
	const COLORREF	GetBorderColor();

	/**
	@fn SetTextColor
	@brief ��ȡTip��������ɫ
	@param	[in] clrText	���õ�������ɫ
	**/
	void	SetTextColor( COLORREF clrText);

	/**
	@fn GetTextColor
	@brief ��ȡTip�ı߽���ɫ
	**/	
	const COLORREF	GetTextColor();

	/**
	@fn SetTipsText
	@brief ����Tip����ʾ����
	@param	[in] strText	��ʾ����
	**/
	void	SetTipsText( CString strText);

	/**
	@fn GetTipsText
	@brief ��ȡTip����ʾ����
	@return	Tips����ʾ����
	**/
	const CString	GetTipsText();

	/**
	@fn SetFont
	@brief ����Tip�ϵ���������
	@param	[in] hFont	����
	**/
	void	SetFont( HFONT hFont);

	/**
	@fn GetFont
	@brief ��ȡTip�ϵ���������
	**/
	const LOGFONT	GetFont();

	/**
	@fn SetFont
	@brief ����Tip�ϵ���������
	@param	[in] hFont	����
	**/
	void	SetFitted( BOOL bFitted){m_bFitted = bFitted;}

	/**
	@fn GetFont
	@brief ��ȡTip�ϵ���������
	**/
	const BOOL 	GetFitted() { return m_bFitted;}
protected:
	BOOL			GetWindowRegion(CDC *pDC, HRGN* hRegion, CSize* Size = NULL);
	BOOL			Create(CWnd *parent);

	afx_msg void	OnPaint();
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnTimer(UINT nIDEvent);
	afx_msg void	OnDestroy();
	afx_msg void	OnLButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

protected:
	UINT		m_nTimer;					//	��ʱ��

	int			m_nShowDelay;				//	�ӳ���ʾʱ��
	int			m_nHideDelay;				//	�ӳ���ʧ��ʱ�䣬���Ϊ-1�����Զ���ʧ
	CString		m_strText;					//	��ʾ����
	CRect       m_rcButtonRect;
	CPoint		m_ptStartPos;				//	��������

	/**�����ɫ����*/
	COLORREF	m_clrBkg;					//	������ɫ
	COLORREF	m_clrBorder;				//	�߿���ɫ
	COLORREF	m_clrText;					//	��ʾ���������ɫ
	BOOL		m_bHide;					//	�Ƿ�������״̬
	LOGFONT		m_stLogFont;				//	�����������Ϣ

	UINT		m_nWidth;					//	Tips�Ŀ��
	BOOL		m_bFitted;					//	����Ƿ���Ҫ�޶��ڸ����Ŀ��m_nWidth֮�ڣ�Ĭ������Ҫ�޶�
};

}}