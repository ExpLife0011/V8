// TempAnnounceListCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\Room.h"
#include "TempAnnounceListCtrl.h"


// CTempAnnounceListCtrl

IMPLEMENT_DYNAMIC(CTempAnnounceListCtrl, CListCtrl)

CTempAnnounceListCtrl::CTempAnnounceListCtrl()
{

}

CTempAnnounceListCtrl::~CTempAnnounceListCtrl()
{
}


BEGIN_MESSAGE_MAP(CTempAnnounceListCtrl, CListCtrl)
END_MESSAGE_MAP()



// CTempAnnounceListCtrl ��Ϣ�������

BOOL CTempAnnounceListCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	switch( ((NMHDR*)lParam)->code )
	{
	case HDN_BEGINTRACKW:
	case HDN_BEGINTRACKA:
		*pResult = TRUE ;
		return TRUE ;
	}
	return CListCtrl::OnNotify( wParam ,lParam ,pResult ) ;
}
