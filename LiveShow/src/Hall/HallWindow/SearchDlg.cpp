// SearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SearchDlg.h"
#include "SearchEdit.h"
#include "../Hall.h"
#include "HallDlg.h"
#include "skin_i.h"
#include "SkinUtil.h"
#include "../SysSettingIni.h"
#include "../CommonLibrary/include/utility/StringHelper.h"
#include "../CommonLibrary/include/utility/json/json.h"
#include "webdefine.h"




// CSearchDlg dialog
#define DEFAULT_TEXT_COLOR RGB(133, 133, 133)
#define TEXT_COLOR RGB(0, 0, 0)
#define DEFAULT_TEXT  L"�����/������(��������5���ַ�)"
#define SKIN_ON_CLICK_SEARCH 1

#define SEARCH_RESULTS_ROOMITEM_ROOMID     "RoomID"    //�����
#define SEARCH_RESULTS_ROOMITEM_ROOMNAME   "RoomName"  //������
#define SEARCH_RESULTS_ROOMITEM_USERCOUNT   "UserCount"  //�����ѽ�����
#define SEARCH_RESULTS_PICITEM_NORMAL _T("resource\\halltree\\MyRoom1.png")      //�������ͼ����
#define SEARCH_RESULTS_PICITEM_SELECT _T("resource\\halltree\\MyRoom2.png")      //�������ͼ����
 
IMPLEMENT_DYNAMIC(CSearchDlg, CDialog)

CSearchDlg::CSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchDlg::IDD, pParent)
	, m_strEdit(DEFAULT_TEXT)
{
	m_pSkinEngine = NULL;
	::GetSkinEngine(&m_pSkinEngine);

	CString strXml = common::utility::systemhelper::Get179AppPath().c_str();
 
	m_pngNormal.Format(_T("%s%s"),strXml,SEARCH_RESULTS_PICITEM_NORMAL);	
	m_pngSelect.Format(_T("%s%s"),strXml,SEARCH_RESULTS_PICITEM_SELECT);
}


CSearchDlg::~CSearchDlg()
{
	
}

void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SEARCH, m_strEdit);
	DDX_Control(pDX, IDC_EDIT_SEARCH, m_editSearch);
}

BEGIN_MESSAGE_MAP(CSearchDlg, CDialog)
	ON_WM_SETFOCUS()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_SKIN_MESSAGE
END_MESSAGE_MAP()



BOOL CSearchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CSearchDlg::OnOK()
{
    OnSearchClick();
}

void CSearchDlg::OnCancel()
{

}

//������������
void CSearchDlg::EventResSearch(CString searchKey)
{
	CString sSearchUrl,sTemp;
	CSysSettingIni::GetWebInterfaceUrl(SYSSET_INI_KEYNAME_SEARCHROOM,sSearchUrl);  //����Ŀ¼���Ϸ��ķ�������url
	sTemp = AppendUrlParamet(sSearchUrl);

	std::wstring KeyEncode = common::utility::stringhelper::UrlUTF8EncodeW(std::wstring(searchKey)); //UTF-8 ��url��д
	sSearchUrl.Format(_T("%s&k=%s"),sTemp,KeyEncode.c_str());

	webinterface::get_http_url_event_req getHttpEvent;
	getHttpEvent.srcMId	=	MODULE_ID_HALL;
	getHttpEvent.desMId	=	MODULE_ID_WEBSERVICE;
	getHttpEvent.wstrUrl = sSearchUrl;
	getHttpEvent.nTimeout = 3;//3��
	IModuleManager* pModuleManager = g_HallModule->m_pModuleManager;
	if (pModuleManager != NULL)
	{
		m_nSeqNo = pModuleManager->CallService(getHttpEvent.eventValue,(param)&getHttpEvent);
		if(m_nSeqNo == 0)
		{
			::PostMessage(GetParent()->GetSafeHwnd(),WM_NOTIFY_HALL_CLICK_SEARCH,0,0);  //���ʹ����������
		}	
	}	
}

//�������󷵻���Ӧ����
void CSearchDlg::OnEventRespSearch(Event const& evt)
{
	if(m_nSeqNo == (uint32)evt.param2)
	{
		if( evt.param0 == webinterface::WEB_RET_SUCCESS)
		{
			webinterface::get_http_url_event_resp* phttpResp =(webinterface::get_http_url_event_resp* ) (evt.m_pstExtraInfo);
			ReleaseSearcTree(m_SearchNode);			
			ParserSearchTree(phttpResp->strBuffer);			
		}

		::PostMessage(GetParent()->GetSafeHwnd(),WM_NOTIFY_HALL_CLICK_SEARCH,0,0);  //���ʹ����������
	}
}

//���������������������Ŀ¼��
void CSearchDlg::ParserSearchTree(std::string searchResp)
{
	try
	{
		Json::Reader reader;
		Json::Value root;
		if(!reader.parse(searchResp,root,false))
		{
			return ;
		}
		if(!root.isArray())
		{
			return;
		}

		std::string RoomID,RoomName,UserCount;		
		int rootsize = root.size();
		for(int i=0;i<rootsize;++i)
		{
			hallNode* newNode = new hallNode;
			
			RoomID = root[i][SEARCH_RESULTS_ROOMITEM_ROOMID].asString();
			RoomName = root[i][SEARCH_RESULTS_ROOMITEM_ROOMNAME].asString();			
			UserCount = root[i][SEARCH_RESULTS_ROOMITEM_USERCOUNT].asString();

			newNode->m_RoomID = atoi(RoomID.c_str());			
			newNode->m_Name.Format(_T("%s(%s)"),common::utility::stringhelper::UTF8ToUnicode(RoomName).c_str(),common::utility::stringhelper::UTF8ToUnicode(RoomID).c_str());	
			newNode->m_PeopleNum.Format(_T("%s��"),common::utility::stringhelper::UTF8ToUnicode(UserCount).c_str());			
			newNode->m_pngNormalExpand = m_pngNormal;
			newNode->m_pngSelectContract = m_pngNormal;
			m_SearchNode.push_back(newNode);
		}
	}
	catch (...)
	{
		return;
	}
	
	
}

//�ͷ�����Ŀ¼������
void CSearchDlg::ReleaseSearcTree(std::list<hallNode*> &RoomNode)
{
	std::list<hallNode*> ::iterator iter;

	iter = m_SearchNode.begin();
	while(iter != m_SearchNode.end())
	{	
		hallNode* curRoom = *iter;		
		if(curRoom->m_Child.size()>0)
		{	
			ReleaseSearcTree(curRoom->m_Child);

		}
		delete curRoom;
		iter++;

	}

	m_SearchNode.clear();
}

//�����ؼ����Ƿ���ȷ
bool CSearchDlg::IsSearchKeyOK()
{
	return m_searchKeyOK;
}

//��������ؼ���
void CSearchDlg::ClearSearchKey()
{
	//m_editSearch.SetWindowText(DEFAULT_TEXT);

}

HBRUSH CSearchDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    if (pWnd->GetSafeHwnd() == m_editSearch.GetSafeHwnd()) {
	    if (pDC && nCtlColor == CTLCOLOR_EDIT)
	    {
		    CString strText;
		    m_editSearch.GetWindowText(strText);
		    if (strText == DEFAULT_TEXT)
		    {
			    pDC->SetTextColor(DEFAULT_TEXT_COLOR);
		    }
		    else
		    {
			    pDC->SetTextColor(TEXT_COLOR);
		    }
	    }
        m_EditBrush.DeleteObject();
        m_EditBrush.CreateSolidBrush(RGB(255, 255, 255));
        return m_EditBrush;
    }

	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}

void CSearchDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

}

int CSearchDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	//Load Skin
	ASSERT(m_pSkinEngine != NULL);
	if (m_pSkinEngine != NULL){
		HRESULT result = m_pSkinEngine->LoadSkin(GetSafeHwnd(), L"search_bar");
		ASSERT(result == S_OK && __LINE__);
	}

	return 0;
}

LRESULT CSearchDlg::OnSkinMessage(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case SKIN_ON_CLICK_SEARCH:
		OnSearchClick();
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

void CSearchDlg::OnSearchClick()
{
	CString searchKey;
	m_editSearch.GetWindowText(searchKey);

	if(searchKey == DEFAULT_TEXT)
	{
		return;
	}

	::PostMessage(GetParent()->GetSafeHwnd(),WM_TREECTRL_CLEAR,0,0);
	CStringA searchKeyA(searchKey);	
	size_t KeySize = searchKeyA.GetLength();	
	if(KeySize >= 5)  
	{
		m_searchKeyOK = true;    //�����ؼ�����ȷ
	}
	else
	{
		m_searchKeyOK = false;   //�����ؼ��ֲ���ȷ  ����������5���ַ���
	}

	if(m_searchKeyOK)
	{
		EventResSearch(searchKey);  //������������	
		m_editSearch.SendBySel();
	}
	else
	{
		ReleaseSearcTree(m_SearchNode);
		::PostMessage(GetParent()->GetSafeHwnd(),WM_NOTIFY_HALL_CLICK_SEARCH,0,0);  //���ʹ����������
	}


	
}

void CSearchDlg::PostNcDestroy()
{
	ReleaseSearcTree(m_SearchNode);
	CDialog::PostNcDestroy();
}

void CSearchDlg::OnMove(int x, int y)
{

}

void CSearchDlg::OnLogOff()
{
	m_editSearch.SetWindowText(DEFAULT_TEXT);
}