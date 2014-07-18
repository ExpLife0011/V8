

#pragma once

#include "../Common.h"

namespace common { namespace ui
{

enum
{
	WM_OnDragOver = WM_USER + 0x2487,
	WM_OnDragEnd,
	WM_OnDragLeave,
};

// CDropTarget ����Ŀ��

/**
@class CDropTarget
@brief ��קĿ����
*/
class COMMON_INTERFACE CDropTarget : public COleDropTarget
{
	DECLARE_DYNAMIC(CDropTarget)

public:
    /**
    @class DragOverInfo
    @brief ��ק������Ϣ
    */
	struct DragOverInfo
	{
		CWnd* pWnd;
		COleDataObject* pDataObject;
		DWORD dwKeyState;
		CPoint point;

		DragOverInfo()
		{
			pWnd = NULL;
			pDataObject = NULL;
			dwKeyState = 0;
			point = CPoint(0, 0);
		}
	};

    /**
    @class DragEndInfo
    @brief ��ק������Ϣ
    */
	struct DragEndInfo
	{
		CWnd* pWnd;
		COleDataObject* pDataObject;
		DROPEFFECT dropEffect;
		CPoint point;

		DragEndInfo()
		{
			pWnd = NULL;
			pDataObject = NULL;
			dropEffect = DROPEFFECT_NONE;
			point = CPoint(0, 0);
		}
	};

    /**
    @fn CDropTarget()
    @brief ���캯��
    */
	CDropTarget();

    /**
    @fn ~CDropTarget()
    @brief ��������
    */
    virtual ~CDropTarget();

    /**
    @fn DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
    @brief ��ק������Ӧ
    @param [in] pWnd ����
    @param [in] pDataObject ��ק�����ݶ���
    @param [in] dwKeyState ����״̬
    @param [in] point �������
    @return ��ק����ֵ�������Ƿ���յ�
    */
	DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);

    /**
    @fn DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
    @brief ��ק������Ӧ
    @param [in] pWnd ����
    @param [in] pDataObject ��ק�����ݶ���
    @param [in] dwKeyState ����״̬
    @param [in] point �������
    @return ��ק����ֵ�������Ƿ���յ�
    */
	DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);

    /**
    @fn void OnDragLeave(CWnd* pWnd)
    @brief ��ק�뿪��Ӧ
    @param [in] pWnd ����
    */
	void OnDragLeave(CWnd* pWnd);               

    /**
    @fn BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point)
    @brief ������ק
    @param [in] pWnd ����
    @param [in] pDataObject ��ק�����ݶ���
    @param [in] dwKeyState ����״̬
    @param [in] point �������
    @return 
    */
	BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);

protected:
	DECLARE_MESSAGE_MAP()
};

} } //namespace common::ui
