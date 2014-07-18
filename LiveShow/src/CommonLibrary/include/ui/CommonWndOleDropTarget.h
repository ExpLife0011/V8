/**********************************************************
* ��Ȩ���� (C)2009, 51.com
*
* �ļ����ƣ�CommonWndOleDropTarget.h
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

#pragma once

#include "../Common.h"

namespace common { namespace ui
{

// CCommonWndOleDropTarget ����Ŀ��

/** CCommonWndOleDropTarget ���������קĿ�ķ���Ӧ��ק����
1.��Ӧ��CWnd�����ര�ڻ�ؼ�(���¼��ΪCWndDropTargetClient)ʵ��ICommonWndOleDropTarget�ӿ�(��׼����ק�ӿ�)��
2.CWndDropTargetClient�ж���һ��CCommonWndOleDropTarget���ͳ�Ա����m_commonWndDropTarget��
3.CWndDropTargetClient::OnCreate�е���m_commonWndDropTarget.Register(this);
4.CWndDropTargetClientͷ�ļ������б����У�
	DECLARE_DYNAMIC(CWndDropTargetClient)
	ʵ���ļ��б����У�
	IMPLEMENT_DYNAMIC(CWndDropTargetClient, COleDropTarget)
*/
class COMMON_INTERFACE CCommonWndOleDropTarget : public COleDropTarget
{
	DECLARE_DYNAMIC(CCommonWndOleDropTarget)
public:
	CCommonWndOleDropTarget();
	virtual ~CCommonWndOleDropTarget();

	virtual DROPEFFECT OnDragEnter(
		CWnd* pWnd, 
		COleDataObject* pDataObject,
		DWORD dwKeyState,
		CPoint point 
		);

	virtual DROPEFFECT OnDragOver(
		CWnd* pWnd, 
		COleDataObject* pDataObject, 
		DWORD dwKeyState, 
		CPoint point
		);

	virtual void OnDragLeave(CWnd* pWnd);               

	virtual BOOL OnDrop(
		CWnd* pWnd, 
		COleDataObject* pDataObject, 
		DROPEFFECT dropEffect, 
		CPoint point
		);
protected:
	DECLARE_MESSAGE_MAP()
};

/** ʵ��COleDropTarget�ı�׼�ӿ�
*/
class COMMON_INTERFACE ICommonWndOleDropTarget:public CObject 
{
	DECLARE_DYNAMIC(ICommonWndOleDropTarget)
public:
	virtual DROPEFFECT OnDragEnter(
		CWnd* pWnd, 
		COleDataObject* pDataObject,
		DWORD dwKeyState,
		CPoint point 
		) = 0;

	virtual DROPEFFECT OnDragOver(
		CWnd* pWnd, 
		COleDataObject* pDataObject, 
		DWORD dwKeyState, 
		CPoint point
		) = 0;

	virtual void OnDragLeave(
		CWnd* pWnd
		) = 0;               

	virtual BOOL OnDrop(
		CWnd* pWnd, 
		COleDataObject* pDataObject, 
		DROPEFFECT dropEffect, 
		CPoint point
		) = 0;
};

} } //namespace common::ui
