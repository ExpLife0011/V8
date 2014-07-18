// EnterRoomGuide.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\Room.h"
#include "EnterRoomGuide.h"
#include "skin_i.h"
#include "SkinUtil.h"
#include "HallDefine.h"
#include "utility\SystemHelper.h"
#include "utility\StringHelper.h"
#include "..\SendEventManager.h"

#define SKIN_ON_CLICK_CLOSE   1

// CEnterRoomGuide �Ի���

IMPLEMENT_DYNAMIC(CEnterRoomGuide, CDialog)

CEnterRoomGuide::CEnterRoomGuide(CWnd* pParent /*=NULL*/)
	: CDialog(CEnterRoomGuide::IDD, pParent)
{
	 m_pSkinEngine = NULL;
	 ::GetSkinEngine(&m_pSkinEngine);
}

CEnterRoomGuide::~CEnterRoomGuide()
{
}

void CEnterRoomGuide::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEnterRoomGuide, CDialog)
	ON_WM_CREATE()
	ON_SKIN_MESSAGE
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CEnterRoomGuide ��Ϣ�������

int CEnterRoomGuide::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	ASSERT(NULL != m_pSkinEngine);
	if (NULL != m_pSkinEngine)
	{
		HRESULT hr = m_pSkinEngine->LoadSkin(GetSafeHwnd(),L"EnterRoomGuide");
		ASSERT(hr== S_OK && __LINE__);
	}

	return 0;
}

BOOL CEnterRoomGuide::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_htmlRecommendRoom.CreateFromStatic(IDC_HTML_GOTO_OTHER_ROOM,this);
	CComVariant var = (LONG)m_htmlRecommendRoom.GetSafeHwnd();
	m_pSkinEngine->SetSubSkinProp(GetSafeHwnd(),L"itemHtmlRecommendRoom",L"hwnd",var);
	InitGuideBrowser();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

BOOL CEnterRoomGuide::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if ( pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_ESCAPE:
		case VK_RETURN:

			return TRUE ;
		default: break;
		}	
	}

	return CDialog::PreTranslateMessage(pMsg);
}

LRESULT CEnterRoomGuide::OnSkinMessage(WPARAM wParam,LPARAM lParam)
{
	switch(wParam)
	{
	case SKIN_ON_CLICK_CLOSE:
		{
			ShowWindow(SW_HIDE);
		}
		break;
	default:break;
	}

	return TRUE;
}

void CEnterRoomGuide::InitGuideBrowser()
{
	Room_Get_Room_List roomList;
	g_RoomModule->m_pModuleManager->CallService(Room::SERVICE_ROOM_GET_ROOM_LIST, (param)&roomList);

	Hall::WebInterfaceUrl weburl;
	weburl.m_WebWithPara = false;
	weburl.m_WebInterfaceKeyName = SYSSET_INI_KEYNAME_ENTERROOM_GUIDE_RECROOM;
	g_RoomModule->m_pModuleManager->CallService(Hall::SERVICE_VALUE_HALL_GET_WEBINTERFACEURL, (param)&weburl);
	CString strRoomId, strUrl;
	strRoomId.Format(L"?roomid=");
	for (int i = 0; i < roomList.vecRoomList.size(); ++i)
	{
		CString roomId;
		if (i + 1 == roomList.vecRoomList.size())
		{
			roomId.Format(L"%u", roomList.vecRoomList[i]);
		}else
		{
			roomId.Format(L"%u,", roomList.vecRoomList[i]);
		}
		
		strRoomId.Append(roomId);
	}
	strUrl.Format(L"%s%s", weburl.m_WebInterfaceUrl.c_str(), strRoomId.GetBuffer());

	m_htmlRecommendRoom.SetUrl(std::wstring(strUrl.GetBuffer()), true);
	m_htmlRecommendRoom.UpdateURL();
}

void CEnterRoomGuide::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return;
	CDialog::OnClose();
}

void CEnterRoomGuide::OnClickRecommendRoom(uint32 roomID)
{
	if (roomID <= 0)
	{
		return;
	}

	CSendEventManager::SendEnterRoomRequest(roomID);
	ShowWindow(SW_HIDE);

}

LRESULT CEnterRoomGuide::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_MISSION_HYPERLINK_ENTERROOM:
		{
			OnClickRecommendRoom((uint32)wParam);
		}
		break;

	default:
		break;
	}

	return CDialog::WindowProc(message, wParam, lParam);
}
