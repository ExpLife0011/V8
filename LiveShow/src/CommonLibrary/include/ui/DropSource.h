

#pragma once

#include "../Common.h"

namespace common { namespace ui
{

enum
{
	WM_DropSource_Canceled = WM_USER + 0x4291,
	WM_DropSource_Droped,
};

// CDropSource ����Ŀ��

/**
@class CDropSource
@brief ��קԴ��
*/
class COMMON_INTERFACE CDropSource : public COleDropSource
{
	DECLARE_DYNAMIC(CDropSource)

public:
    /**
    @fn CDropSource()
    @brief ���캯��
    */
	CDropSource();

    /**
    @fn ~CDropSource()
    @brief ��������
    */
	virtual ~CDropSource();

    /**
    @fn BOOL OnBeginDrag(CWnd* pWnd,CRect rcItem)
    @brief ��ʼ��ק
    @param [in] pWnd
    @param [in] rcItem
    @return 
    */
	virtual BOOL OnBeginDrag(CWnd* pWnd, CRect rcItem);

    /**
    @fn SCODE GiveFeedback(DROPEFFECT dropEffect)
    @brief 
    @param [in] dropEffect
    @return 
    */
	virtual SCODE GiveFeedback(DROPEFFECT /*dropEffect*/);

    /**
    @fn SCODE QueryContinueDrag(BOOL bEscapePressed, DWORD dwKeyState)
    @brief 
    @param [in] bEscapePressed
    @param [in] dwKeyState
    @return 
    */
	virtual SCODE QueryContinueDrag(BOOL bEscapePressed, DWORD dwKeyState);

    /**
    @fn void Register(CWnd* pWnd)
    @brief ע��
    @param [in] pWnd ע����ק�Ĵ���
    */
	void Register(CWnd* pWnd);

protected:
	DECLARE_MESSAGE_MAP()

private:
    BOOL m_bLBtnUp;
    CWnd* m_pwnd;
};

} } //namespace common::ui
