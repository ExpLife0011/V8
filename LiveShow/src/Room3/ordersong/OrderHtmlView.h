#pragma once
#include "..\..\CommonLibrary/include/ui/MLHtmlView.h"

enum ENM_ListType
{
	LISTTYPE_SONG,			//��ǰ�����������б�
	LISTTYPE_ORDER,			//��ǰ���ѵ�����б�
	LISTTYPE_MARK,			//��ǰ�����۸����б�
};

class COrderHtmlView : public CMLHtmlView
{
	DECLARE_DYNCREATE(COrderHtmlView)
	DECLARE_DISPATCH_MAP()

public:
	COrderHtmlView(void);
	virtual ~COrderHtmlView(void);

	void SetType(ENM_ListType enmType);

protected:
	BOOL Invoke_SaveSongList(int nSongerID, LPCTSTR lpszParam);		//����赥
	BOOL Invoke_AddSong(int nSongerID, LPCTSTR lpszSong);			//��Ӹ���
	BOOL Invoke_ClearSongList(int nSongerID);						//��ո赥
	BOOL Invoke_OrderSong(int nSongerID, LPCTSTR lpszSong);			//�û����
	BOOL Invoke_OrderPriority(int nSongerID, LPCTSTR lpszSong);		//�û��岥
	BOOL Invoke_SongListChange(int nChange);						//�赥�Ƿ���
	BOOL Invoke_DecideSong(int nOrderID, int nStat);				//����������
	BOOL Invoke_DecideEvaluate(int nOrderID, int nStat);			//���۸���
	BOOL Invoke_OpenOrderSong();									//�򿪵�����

protected:
	virtual void DocumentComplete(LPDISPATCH pDisp, VARIANT* URL);

private:
	ENM_ListType m_enmType;
};
