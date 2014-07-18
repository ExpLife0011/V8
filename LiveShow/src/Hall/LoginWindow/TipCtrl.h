#pragma once

#include "afx.h"
#include "afxtempl.h"
#include "../CommonLibrary/include/ui/SimpleTipCtrl.h"

using namespace common::ui;

#define RB_INFINITE	-1	

class  CTipCtrl : 
	public CSimpleTipCtrl
{
public:
	CTipCtrl();
	virtual ~CTipCtrl();

	/**
	@fn SetIcon
	@brief ���úͻ�ȡͼ
	@param	[in] hIcon	���õ�ͼ��
	@param	[in] iconSize	ͼ��Ĵ�С��Ĭ��Ϊ16,16
	**/
	void	SetIcon( HICON hIcon, CSize iconSiz = (16,16));

	/**
	@fn SetShowIcon
	@brief �Ƿ���ʾͼ��
	@param	[in] bShowIcon	true����Ҫ��ʾͼ�꣬false������Ҫ��ʾͼ��
	**/
	void	SetShowIcon( BOOL bShowIcon) { m_bShowIcon = bShowIcon;}

	/**
	@fn SetLeft
	@brief ������ʾ�ĵ׶˼�ͷƫ����ƫ��
	@param	[in] bLeft		ΪTRUEΪƫ����ʾ
	**/
	void	SetLeft(BOOL bLeft);

	/**
	@fn SetButtonText
	@brief ���ð�ť���ı�
	@param	[in] strText		��ť���ı���Ϊ����û����ʾ��ť
	**/
	void	SetButtonText(CString strText);

	/**
	@fn GetButtonText
	@brief ��ȡ��ť���ı�
	**/
	const CString   GetButtonText();

	/**
	@fn SetClickClose
	@brief �����ʱ���Ƿ�ر�
	@param	[in] strText		��ť���ı���Ϊ����û����ʾ��ť
	**/
	void	SetClickClose(BOOL bClose);
    const BOOL   GetClickClose();

	/**
	@fn SetAssociateWnd
	@brief �������tip�����Ĵ���
	@param	[in] strText		��ť���ı���Ϊ����û����ʾ��ť
	*/
	void	SetAssociateWnd( CWnd* pAssociateWnd);

	/**
	@fn GetAssociateWnd
	@brief ��ȡ���tip�����Ĵ���
	@param	[in] strText		��ť���ı���Ϊ����û����ʾ��ť
	*/
	const CWnd*   GetAssociateWnd();

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
	typedef struct
	{
		CString	szText;						//	Tooltip text
		HICON	hIcon;						//	Tooltip icon

	} TipToolInfo;

	CString     m_strButtonText;			//	���Tips����ʾbutton����Ϊbutton������
    BOOL        m_bClickClose;              //  �����ʱ���Ƿ���ʧ
	HICON		m_hIcon;					//	Tips�ϵ�ͼ��
	CSize		m_IconSize;					//	ͼ��Ĵ�С
	BOOL		m_bShowIcon;				//	�Ƿ���ʾͼ��
	BOOL		m_bLeft;					//	��ͷ�Ƿ������

	CFont*		m_pFont;
	CWnd*		m_pAssociateWnd;			//	�����ÿؼ��Ĵ���
};