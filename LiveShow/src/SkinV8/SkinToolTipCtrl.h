#pragma once

#include "SkinTextStyle.h"

// CSkinToolTipCtrl

class CImageBase;

class CSkinToolTipCtrl : public CWnd
{
	DECLARE_DYNCREATE(CSkinToolTipCtrl)

public:
	CSkinToolTipCtrl();
	virtual ~CSkinToolTipCtrl();

    BOOL Create(CWnd* pParent);

public:
    CImageBase* GetBackImage();
    void SetBackImage(CImageBase* pImage);
    CImageBase* GetIconImage();
    void SetIconImage(CImageBase* pImage);

    CString GetCaption();
    void SetCaption(LPCTSTR lpzCaption);
    CString GetText();
    void SetText(LPCTSTR lpzText);
    CString GetButtonText();
    void SetButtonText(LPCTSTR lpzText);

    LONG GetMaxWidth();
    void SetMaxWidth(LONG lMaxWidth);
    LONG GetMaxHeight();
    void SetMaxHeight(LONG lMaxHeight);

    POINT GetPos();
    void SetPos(POINT pt);

    BOOL GetLeftPreferred();
    void SetLeftPreferred(BOOL bLeft);
    BOOL GetTopPreferred();
    void SetTopPreferred(BOOL bTop);

protected:
    SIZE Layout();

protected:
	DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnPaint();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);

protected:
    //�ͻ������С
    CSize m_szClient;

    //����
    CImageBase* m_pBackImage;

    //ͼ��
    CImageBase* m_pIconImage;
    CRect m_rcIcon;

    //����
    CString m_strCaption;
    CSkinTextStyle m_styleCaption;
    CRect m_rcCaption;

    //����
    CString m_strText;
    CSkinTextStyle m_styleText;
    CRect m_rcText;

    //��ť
    CString m_strButton;
    CSkinTextStyle m_styleButton;
    CRect m_rcButton;

    //����Ⱥ͸߶ȣ�-1Ϊ����
    LONG m_nMaxWidth;
    LONG m_nMaxHeight;

    //ָʾ��
    CPoint m_ptPos;

    //����λ��ƫ��
    BOOL m_bLeftPreferred;  //��ƫ��
    BOOL m_bTopPreferred;   //��ƫ��

    //���
    LONG m_lHorizMargin;
    LONG m_lVertiMargin;
};

