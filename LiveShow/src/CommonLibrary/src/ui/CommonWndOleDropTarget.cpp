/**********************************************************
* ��Ȩ���� (C)2009, 51.com
*
* �ļ����ƣ�CommonWndOleDropTarget.cpp
* ����ժҪ����קCOleDropTarget��չ�࣬����ʵ������קĿ�ķ�ʵ����ק����
* ����˵����
* ��ǰ�汾��
* ��    �ߣ��»���
* ������ڣ�2009-10-29
*
* �޸ļ�¼1��
*    �޸����ڣ�
*    �� �� �ţ�
*    �� �� �ˣ�
*    �޸����ݣ�
**********************************************************/
// CommonWndOleDropTarget.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "../../include/ui/CommonWndOleDropTarget.h"

namespace common { namespace ui
{

//////////////////////////////////////////////////////////////////////////
/// CCommonWndOleDropTarget��ʵ�ִ���

IMPLEMENT_DYNAMIC(CCommonWndOleDropTarget, COleDropTarget)

CCommonWndOleDropTarget::CCommonWndOleDropTarget()
{
}

CCommonWndOleDropTarget::~CCommonWndOleDropTarget()
{
}

BEGIN_MESSAGE_MAP(CCommonWndOleDropTarget, COleDropTarget)
END_MESSAGE_MAP()

/// CCommonWndOleDropTarget ��Ϣ�������

DROPEFFECT CCommonWndOleDropTarget::OnDragEnter(
	CWnd* pWnd, 
	COleDataObject* pDataObject, 
	DWORD dwKeyState, 
	CPoint point 
	)
{
	/**����ʹ����MFC��IsKindOf��RTTI��dynamic_cast����������ʶ��
	1.����IsKindOf(ʹ��IMPLEMENT_DYNAMIC)��֧�ֶ��ؼ̳У��ж��ؼ̳�ʱIsKindOf��ʧ�ܴ�ʱ�Ͳ���RTTI������ʶ���ˡ�
	*/
	DROPEFFECT deResult = DROPEFFECT_NONE;
	if (NULL != pWnd 
		&& NULL != m_hWnd 
		&& (pWnd->IsKindOf(RUNTIME_CLASS(ICommonWndOleDropTarget)) || dynamic_cast<ICommonWndOleDropTarget *>(pWnd))
		)
	{
#ifdef _CPPRTTI 
		ICommonWndOleDropTarget *ptrCommonWndDropTarget = dynamic_cast<ICommonWndOleDropTarget *>(pWnd);
#else
		ICommonWndOleDropTarget *ptrCommonWndDropTarget = (ICommonWndOleDropTarget *)pWnd;
#endif
		if (NULL != ptrCommonWndDropTarget)
		{
			deResult = ptrCommonWndDropTarget->OnDragEnter(pWnd, pDataObject, dwKeyState, point);
		}
	}
	else
	{
		deResult = __super::OnDragEnter(pWnd, pDataObject, dwKeyState, point);
	}

	return deResult;
}

DROPEFFECT CCommonWndOleDropTarget::OnDragOver(
	CWnd* pWnd, 
	COleDataObject* pDataObject, 
	DWORD dwKeyState, 
	CPoint point 
	)
{
	DROPEFFECT deResult = DROPEFFECT_NONE;
	if (NULL != pWnd 
		&& NULL != m_hWnd 
		&& (pWnd->IsKindOf(RUNTIME_CLASS(ICommonWndOleDropTarget)) || dynamic_cast<ICommonWndOleDropTarget *>(pWnd))
		)
	{
#ifdef _CPPRTTI 
		ICommonWndOleDropTarget *ptrCommonWndDropTarget = dynamic_cast<ICommonWndOleDropTarget *>(pWnd);
#else
		ICommonWndOleDropTarget *ptrCommonWndDropTarget = (ICommonWndOleDropTarget *)pWnd;
#endif
		if (NULL != ptrCommonWndDropTarget)
		{
			deResult = ptrCommonWndDropTarget->OnDragOver(pWnd, pDataObject, dwKeyState, point);
		}
	}
	else
	{
		deResult = __super::OnDragOver(pWnd, pDataObject, dwKeyState, point);
	}

	return deResult;
}

void CCommonWndOleDropTarget::OnDragLeave(CWnd* pWnd)
{
	//DROPEFFECT deResult = DROPEFFECT_NONE;
	if (NULL != pWnd 
		&& NULL != m_hWnd 
		&& (pWnd->IsKindOf(RUNTIME_CLASS(ICommonWndOleDropTarget)) || dynamic_cast<ICommonWndOleDropTarget *>(pWnd))
		)
	{
#ifdef _CPPRTTI 
		ICommonWndOleDropTarget *ptrCommonWndDropTarget = dynamic_cast<ICommonWndOleDropTarget *>(pWnd);
#else
		ICommonWndOleDropTarget *ptrCommonWndDropTarget = (ICommonWndOleDropTarget *)pWnd;
#endif
		if (NULL != ptrCommonWndDropTarget)
		{
			ptrCommonWndDropTarget->OnDragLeave(pWnd);
		}
	}
	else
	{
		__super::OnDragLeave(pWnd);
	}
}

BOOL CCommonWndOleDropTarget::OnDrop(
	CWnd* pWnd,
	COleDataObject* pDataObject,
	DROPEFFECT dropEffect, 
	CPoint point 
	)
{
	//DROPEFFECT deResult = DROPEFFECT_NONE;
	BOOL bResult = FALSE;
	if (NULL != pWnd 
		&& NULL != m_hWnd 
		&& (pWnd->IsKindOf(RUNTIME_CLASS(ICommonWndOleDropTarget)) || dynamic_cast<ICommonWndOleDropTarget *>(pWnd))
		)
	{
#ifdef _CPPRTTI 
		ICommonWndOleDropTarget *ptrCommonWndDropTarget = dynamic_cast<ICommonWndOleDropTarget *>(pWnd);
#else
		ICommonWndOleDropTarget *ptrCommonWndDropTarget = (ICommonWndOleDropTarget *)pWnd;
#endif
		if (NULL != ptrCommonWndDropTarget)
		{
			bResult = ptrCommonWndDropTarget->OnDrop(pWnd, pDataObject, dropEffect, point);	
		}
	}
	else
	{
		bResult = __super::OnDrop(pWnd, pDataObject, dropEffect, point);
	}

	return bResult;
}

//////////////////////////////////////////////////////////////////////////
///ICommonWndOleDropTarget��ʵ�ִ���
IMPLEMENT_DYNAMIC(ICommonWndOleDropTarget, CObject)

} } //namespace common::ui
