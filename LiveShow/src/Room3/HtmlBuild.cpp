#include "stdafx.h"
#include "HtmlBuild.h"
#include "gift\GiftManager.h"
#include "userlist\ListIconManager.h"
#include "GlobalRoomDefine.h"
#include "GlobalManager.h"
#include "roomsetting\RoomOption.h"
#include "..\CommonLibrary\include\utility\SystemHelper.h"
#include "..\CommonLibrary\include\utility\StringHelper.h"
#include "..\CommonLibrary\include\utility\URLEncode.h"
#include "RoomDefine.h"
#include "RoomModule.h"
#include "globaluidefine.h"
#include "Room.h"
#include "HallDefine.h"
#include "RoomBusiness.h"
#include "personalsetting\PersonalConfig.h"
#include "autoreply\AutoReplyConfig.h"
#include "richlevel\RichLevelManager.h"
#include "sofa/SofaItem.h"

#define MAX_SHOW_179ID	999999

HtmlBuild::HtmlBuild( RoomBusiness* pRoomBusiness )
:m_pRoomBusiness( pRoomBusiness )
{

}

CString HtmlBuild::GetRequestP2PNotify( IUserItem* pSrcUserItem ) 
{
	CString strName ;	
	strName.Format( L"%s����������һ��һ��Ƶ������" ,GetNameAndID(pSrcUserItem) ) ;
	CString strAcceptHref ;
	strAcceptHref.Format( L"<a href=\"%s\" name=\"%s\" uuid=\"%d\" type=\"%d\">ͬ��</a>" ,
		L"" , pSrcUserItem->GetDecodeUserName().c_str() , pSrcUserItem->GetUserUIN() ,CLICK_TYPE_P2P_ACCEPT ) ;
	CString strRefuseHref ;
	strRefuseHref.Format( L"<a href=\"%s\" name=\"%s\" uuid=\"%d\" type=\"%d\">�ܾ�</a>" ,
		L"" , pSrcUserItem->GetDecodeUserName().c_str() , pSrcUserItem->GetUserUIN() , CLICK_TYPE_P2P_REFUSE ) ;

	return  GetPrivateTips( L"����ʾ���� " ,strName + L" " + strAcceptHref+L" ���� "+strRefuseHref+L"��" , COLOR_OPERATE  ) ;
}

CString HtmlBuild::GetOpenPrivateRspNoPermission() 
{
	CString strHref  ;
	strHref.Format( L"<a href=\"%s\" target=\"_blank\">��������<a>" , m_pRoomBusiness->GetUpdateVipUrl() ) ;
	
	return GetPrivateTips( L"����ʾ���� "  , L"��Ǹ��ֻ����ҫVIP�����û��ɹۿ�˽�� "+ strHref  , COLOR_OPERATE ) ; ;
}

CString HtmlBuild::GetOpenPrivateRspIsFull() 
{
	CString strHref  ;
	strHref.Format( L"<a href=\"%s\" target=\"_blank\">��������<a>" , m_pRoomBusiness->GetUpdateVipUrl() ) ;
	return GetPrivateTips( L"����ʾ���� "  , L"��Ǹ������ǰ�ɴ򿪵�˽�������Ѵ����� "+ strHref , COLOR_OPERATE ) ; ;
}

CString HtmlBuild::GetPublicStamp( IUserItem* pSrcUserItem ,IUserItem* pDstUserItem , uint16 unStampID ) 
{
	//������	
	CString strSrcNameHref = ChatUserItem( pSrcUserItem ) ;
	CString strDstNameHref = StampRightUserItem( pDstUserItem ) ;
	CString strImg ;
	IGiftItem* pGiftItem = GiftManager::GetInstance()->SearchStampByID( unStampID ) ;
	if ( pGiftItem != NULL )
	{
		strImg = Img( pGiftItem->GetSmallImagePath().c_str() ) ;
	}
	CString strTemp = Span( 12 , strSrcNameHref+L" ��Ƥ�ؼ��� "+strDstNameHref+L" Ϊ�� "+strImg )	;

	strTemp += L"</BR>" ;

	return strTemp ;
}

CString HtmlBuild::GetPrivateStamp( IUserItem* pSrcUserItem , uint16 unStampID ) 
{

	CString strImg ;
	//ͼƬ
	IGiftItem* pGiftItem = GiftManager::GetInstance()->SearchStampByID( unStampID ) ;
	if ( pGiftItem != NULL )
	{
		strImg = Img( pGiftItem->GetSmallImagePath().c_str() ) ;
	}
	CString strHref ;
	strHref.Format( _T("<a href=\"%s\" name=\"%s\" type=\"%d\" uuid=\"%d\">ӡ�µ���</a>") ,
		L"" ,pSrcUserItem->GetDecodeUserName().c_str() ,
		CLICK_TYPE_STAMP ,pSrcUserItem->GetUserUIN() ) ;
	return GetPrivateTips( L"����ʾ���� " , L"����"+ PrivateUserItem( pSrcUserItem ) +L"����Ϊ�� " +strImg +
		L" ������������Ҳ��ѡ��"+strHref+ L"�����ǻ�ȥ��" ,COLOR_GIFT) ;
}

CString HtmlBuild::GetPrivateMicNotify( IUserItem* pSrcUserItem  ) 
{
	CString strHref ;
	CString strName ;
	strName.Format( L"%s" ,GetNameAndID(pSrcUserItem) ) ;

	strHref.Format(_T("<a href=\"%s\" name=\"%s\" uuid=\"%d\" type=\"%d\" 179id=\"%u\" >����ۿ�</a>") ,
		L"" , pSrcUserItem->GetDecodeUserName().c_str() ,
		pSrcUserItem->GetUserUIN() , CLICK_TYPE_PRIVATEVIDEO , pSrcUserItem->GetUser179ID() ) ;

	return GetPrivateTips( L"����ʾ���� " , strName + L"����˽����ҫVIP�����û��� "+strHref ,COLOR_OPERATE ) ;
}


CString HtmlBuild::GetPrivateFireWork( IUserItem* pSrcUserItem ) 
{
	CString strHref , strInfo , strLinkInfo ;

	strInfo.Format( L" ��������Ա�������࣬Ϊ��%s���������й���Ա������һ���̻� "  ,m_pRoomBusiness->GetRoomOption()->GetRoomName().c_str() ) ;
	strLinkInfo.Format( L"%s��������Ա�������࣬Ϊ��%s���������й���Ա������һ���̻� " , GetNameAndID(pSrcUserItem) ,
		m_pRoomBusiness->GetRoomOption()->GetRoomName().c_str() ) ;
	strHref.Format( L"<a href=\"%s\" name=\"%s\" uuid=\"%d\" type=\"%d\">ת������ʱ����</a>" ,L"" ,strLinkInfo , 
		pSrcUserItem->GetUserUIN() , CLICK_TYPE_TEMP_NOTICE ) ;	

	return GetPrivateTips( L"����ʾ���� " ,ChatUserItem( pSrcUserItem )+strInfo+strHref , COLOR_GIFT)  ;
}

CString HtmlBuild::GetPrivateSlavo( IUserItem* pSrcUserItem ) 
{

	CString strHref , strInfo , strLinkInfo ;	
	 	
	strInfo.Format( L" �������£�Ϊ��%s�����������û�������һ������ "  ,m_pRoomBusiness->GetRoomOption()->GetRoomName().c_str() ) ;	
	strLinkInfo.Format( L"%s�������£�Ϊ��%s�����������û�������һ������ "  , GetNameAndID(pSrcUserItem) ,
		m_pRoomBusiness->GetRoomOption()->GetRoomName().c_str() ) ;	
	strHref.Format( L"<a href=\"%s\" name=\"%s\" uuid=\"%d\" type=\"%d\">ת������ʱ����</a>" ,L"" ,strLinkInfo , 
		pSrcUserItem->GetUserUIN() , CLICK_TYPE_TEMP_NOTICE ) ;

	return GetPrivateTips( L"����ʾ���� " ,ChatUserItem( pSrcUserItem )+ strInfo + strHref ,COLOR_GIFT)  ;
}

CString HtmlBuild::GetPublicFireWork( IUserItem* pSrcUserItem) 
{	
	CString strTemp ;
	strTemp.Format( L"%s ��������Ա�������࣬Ϊ��%s���������й���Ա������һ���̻�" , 
		ChatUserItem( pSrcUserItem ) , m_pRoomBusiness->GetRoomOption()->GetRoomName().c_str() ) ;
	return GetPublicTips( L"����ʾ���� " , strTemp ,COLOR_GIFT ) ;
}

CString HtmlBuild::GetPublicSlavo( IUserItem* pSrcUserItem ) 
{
	CString strTemp ;
	strTemp.Format( L"%s �������£�Ϊ��%s�����������û�������һ������" , 
		ChatUserItem( pSrcUserItem ) , m_pRoomBusiness->GetRoomOption()->GetRoomName().c_str() ) ;
	return GetPublicTips( L"����ʾ���� " , strTemp ,COLOR_GIFT ) ;
}

CString HtmlBuild::GetGiftLucky( uint32 unSrcUIN ,uint32 src179ID ,CString& strSrcHead ,
								std::wstring strSrcName ,uint16 unGiftID , uint16 unLuckyTimes ,uint32 unLuckyMoney ) 
{
	IUserItem* pUserItem =  m_pRoomBusiness->GetUserManager()->SearchUserByUIN( unSrcUIN ) ;
	if ( pUserItem != NULL )
	{
		strSrcHead = GetUserHead( pUserItem ) ;
	}

	CString strTemp ;
	IUserItem* pSelfUserItem = m_pRoomBusiness->GetUserManager()->GetSelfUserItem() ;
	if ( pSelfUserItem == NULL )
	{
		return strTemp ;
	}

	IGiftItem* pGiftItem = GiftManager::GetInstance()->SearchGiftByID( unGiftID ) ;
	if ( pGiftItem == NULL )
	{
		return L"";
	}

	CString strCoin ;
	strCoin.Format( L"<B>%d</B>" , unLuckyMoney ) ;
	if ( unLuckyTimes >= 500 )
	{
		strCoin = Span( 16 , strCoin ) ;
	}
	CString strImgPath = Img( pGiftItem->GetSmallImagePath().c_str() );
	if ( unSrcUIN ==  pSelfUserItem->GetUserUIN() )
	{
		//�Լ��н�
		CString strInfo ;
		CString strMultipliPngPath = GetLuckyTimesPngPath( unLuckyTimes ) ;
		if ( strMultipliPngPath.IsEmpty() )
		{
			strInfo.Format( L"��ϲ�����ͳ��� %s%s �����˺��ˣ��õ�<B>%d</B>������%s�ң�" , pGiftItem->GetName().c_str() ,strImgPath ,
				unLuckyTimes , strCoin ) ;
		}
		else
		{
			strInfo.Format( L"��ϲ�����ͳ��� %s%s �����˺��ˣ��õ�%s������%s�ң�" , pGiftItem->GetName().c_str() ,strImgPath ,
				Img( strMultipliPngPath )  , strCoin ) ;
		}
		if ( ( pSelfUserItem->GetUserTitleLevel() > core::TITLELEVEL_TEMP_MANAGER) && unLuckyTimes >= 100  )
		{
			//����Ա
			CString strHref ;				
			//if ( pGiftItem->IsNeedTempNotice() )
			//{
				CString strHrefName ;
				CString strSrcNameAndID;
				if (src179ID > MAX_SHOW_179ID)
				{
					strSrcNameAndID = strSrcName.c_str();
				}
				else
				{
					strSrcNameAndID.Format(L"%s(%u)", strSrcName.c_str(), src179ID);
				}
				strHrefName.Format( L"��ϲ��%s�ͳ���%s�����˺��ˣ��õ�%d������%d�ң�" , strSrcNameAndID ,
					pGiftItem->GetName().c_str() ,unLuckyTimes ,unLuckyMoney ) ;
				strHref.Format( L"<a href=\"%s\" name=\"%s\" uuid=\"%u\" type=\"%d\">ת������ʱ����</a>" ,L"" ,strHrefName , 
					unSrcUIN , CLICK_TYPE_TEMP_NOTICE ) ;
			//}				

			strTemp = strInfo+strHref ;
		}
		else
		{
			strTemp = strInfo  ;
		}
	}
	else
	{			

		CString strName ;
		strName.Format( L"%s%s (%d)" , strSrcHead ,strSrcName.c_str() ,src179ID ) ;

		CString strInfo ;

		CString strMultipliPngPath = GetLuckyTimesPngPath( unLuckyTimes ) ;
		if ( strMultipliPngPath.IsEmpty() )
		{
			strInfo.Format( L"��ϲ��%s�ͳ� %s%s �����˺��ˣ��õ�<B>%d</B>������%s�ң��ͳ����������𷭱�����" ,strName ,
				pGiftItem->GetName().c_str() ,strImgPath , unLuckyTimes , strCoin ) ;
		}
		else
		{
			strInfo.Format( L"��ϲ��%s�ͳ� %s%s �����˺��ˣ��õ�%s������%s�ң��ͳ����������𷭱�����" ,strName ,
				pGiftItem->GetName().c_str() ,strImgPath , Img( strMultipliPngPath ) , strCoin ) ;

		}
		
		if ( (pSelfUserItem->GetUserTitleLevel() > core::TITLELEVEL_TEMP_MANAGER) && unLuckyTimes >= 100 && pGiftItem->IsNeedTempNotice() )
		{
			//����Ա
			CString strHref ;				
			CString strHrefName ;	
			CString strSrcNameAndID;
			if (src179ID > MAX_SHOW_179ID)
			{
				strSrcNameAndID = strSrcName.c_str();
			}
			else
			{
				strSrcNameAndID.Format(L"%s(%u)", strSrcName.c_str(), src179ID);
			}
			strHrefName.Format( L"��ϲ��%s�ͳ�%s�����˺��ˣ��õ�%d������%d�ң��ͳ����������𷭱�����" ,
				strSrcNameAndID, pGiftItem->GetName().c_str() , unLuckyTimes , unLuckyMoney) ;
			strHref.Format( L"<a href=\"%s\" name=\"%s\" uuid=\"%u\" type=\"%d\">ת������ʱ����</a>" ,L"" ,strHrefName , 
				unSrcUIN , CLICK_TYPE_TEMP_NOTICE ) ;
			strTemp = strInfo+strHref ;
			
		}
		else
		{
			strTemp = strInfo ;
		}
	}
	return GetPrivateTips( L"����ʾ���� " ,strTemp , COLOR_GIFT) ;
}

CString HtmlBuild::GetPrivateNormalGift( IUserItem* pSrcUserItem ,uint16 unGiftID , uint16 unCount ) 
{	
	CString strTemp ;
	IGiftItem* pGiftItem = GiftManager::GetInstance()->SearchGiftByID( unGiftID ) ;
	if ( pGiftItem != NULL )
	{	
		CString strCount ;
		strCount.Format(_T(" %d"),unCount) ;

		CString strImgPath = Img( pGiftItem->GetSmallImagePath().c_str() ) ;

		strTemp = GetPrivateTips(  L"����ʾ���� " , ChatUserItem(pSrcUserItem) + L" ���ι��͸��� "+CString(pGiftItem->GetName().c_str()) + 
			strImgPath +strCount + CString(pGiftItem->GetUnitName().c_str())  , COLOR_GIFT) ;
	}

	return strTemp ;
}

CString HtmlBuild::GetPublicNormalGift( GiftInfo& giftinfo , uint32 unGiftCount ) 
{
	IUserItem* pSrcUserItem =  m_pRoomBusiness->GetUserManager()->SearchUserByUIN( giftinfo.srcuin ) ;
	if ( pSrcUserItem != NULL )
	{
		giftinfo.strSrcHead = GetUserHead( pSrcUserItem ) ;
	}
	IUserItem* pDstUserItem =  m_pRoomBusiness->GetUserManager()->SearchUserByUIN( giftinfo.dstuin ) ;
	if ( pDstUserItem != NULL )
	{
		giftinfo.strDstHead = GetUserHead( pDstUserItem ) ;
	}

	CString strTemp ;
	IGiftItem* pGiftItem = GiftManager::GetInstance()->SearchGiftByID( giftinfo.unGiftid ) ;
	if ( pGiftItem != NULL )
	{	

		CString strGift ;
		strGift.Format( L" %s %s����%d%s" , pGiftItem->GetName().c_str() , 
			Img( pGiftItem->GetLargeImagePath().c_str() ) , unGiftCount , pGiftItem->GetUnitName().c_str() ) ;

		//����������
		CString strNameHrefLeft ;
		CString strSrcNameAndID;
		if (giftinfo.src179ID > MAX_SHOW_179ID)
		{
			strSrcNameAndID = giftinfo.strSrcName.c_str();
		}
		else
		{
			strSrcNameAndID.Format(L"%s(%u)", giftinfo.strSrcName.c_str(), giftinfo.src179ID);
		}
		strNameHrefLeft.Format(_T("<a href=\"%s\" name=\"%s\" uuid=\"%d\" type=\"%d\" title=\"%d\" class=\"user\" >%s</a>") , 
			L"" , giftinfo.strSrcName.c_str() ,
			giftinfo.srcuin , CLICK_TYPE_NAME ,giftinfo.src179ID ,
			strSrcNameAndID ) ;

		//������
		CString strNameHrefRight; 
		CString strDstNameAndID;
		if (giftinfo.dst179ID > MAX_SHOW_179ID)
		{
			strDstNameAndID = giftinfo.strDstName.c_str();
		}
		else
		{
			strDstNameAndID.Format(L"%s(%u)", giftinfo.strDstName.c_str(), giftinfo.dst179ID);
		}
		strNameHrefRight.Format(_T("<a href=\"%s\" name=\"%s\" uuid=\"%d\" type=\"%d\" title=\"%d\" class=\"user\" >%s</a>") , 
			L"" , giftinfo.strDstName.c_str() ,
			giftinfo.dstuin , CLICK_TYPE_NAME ,giftinfo.dst179ID ,
			strDstNameAndID ) ;

		strTemp = Font(L"����", COLOR_NORMAL ,Span(12,giftinfo.strSrcHead + strNameHrefLeft+L" �͸� "+giftinfo.strDstHead + strNameHrefRight+strGift) ) ;
		strTemp += L"<BR>" ;
	}

	return strTemp ;
}


CString HtmlBuild::GetPublicSheChiGift( IUserItem* pSrcUserItem ,IUserItem* pDstUserItem , uint16 unGiftID , uint32 unCount ) 
{
	CString strTemp ;
	IGiftItem* pGiftItem = GiftManager::GetInstance()->SearchGiftByID( unGiftID ) ;
	if ( pGiftItem != NULL )
	{		
		CString strGift ;
		//strGift.Format( L" %s %s����%d%s" , pGiftItem->GetName().c_str() , 
		//	Img( pGiftItem->GetLargeImagePath().c_str() ) , unCount , pGiftItem->GetUnitName().c_str() ) ;
		strGift.Format( L" %s %s����%d%s" , pGiftItem->GetRichName().c_str() , 
			Img( pGiftItem->GetLargeImagePath().c_str() ) , unCount , pGiftItem->GetUnitName().c_str() ) ;

		CString strChatLeft = ChatUserItem( pSrcUserItem  ) ;
		CString strChatRight = ChatUserItem(pDstUserItem  ) ;
		strTemp = Font( L"����" , COLOR_SHECHI , Span( 14 , strChatLeft+L" "+ CString(pGiftItem->GetStrSendDesc().c_str())+ L" "+strChatRight +strGift) ) ;
		strTemp += L"<BR>" ;
	}

	return strTemp ;
}

CString HtmlBuild::GetChat( IUserItem* pSrcUserItem ,IUserItem* pDstUserItem ,
						   CString& strText ,MessageFont& stFont , bool bPublic , bool bReplaceSelf , bool bAutoMsg) 
{
	core::CurInfo myCurInfo = GetCurInfo() ; 
	CString strTemp ;

	CString strChatLeft = ChatUser( myCurInfo.unUIN , pSrcUserItem , bReplaceSelf ) ;
	CString strChatRight = ChatUser( myCurInfo.unUIN , pDstUserItem ,bReplaceSelf ) ;
	if ( bPublic )
	{
		if ( pDstUserItem == NULL )
		{
			//��������
			strTemp =Font( L"����",L"#000000" ,Span(12 ,strChatLeft + L" ˵��") +ChatMessage(strText,stFont,pSrcUserItem->GetUserUIN() ) ) ;
		}
		else
		{
			if ( strChatLeft == L"��" )
			{
				strTemp =Font( L"����",L"#000000" ,Span(12 ,strChatLeft + L"�� "+strChatRight+L" ˵��") +ChatMessage(strText,stFont,pSrcUserItem->GetUserUIN() ) ) ;
			}
			else if ( strChatRight == L"��")
			{
				strTemp =Font( L"����",L"#000000" ,Span(12 ,strChatLeft + L" ��"+strChatRight+L"˵��") +ChatMessage(strText,stFont,pSrcUserItem->GetUserUIN() ) ) ;
			}
			else
			{
				strTemp =Font( L"����",L"#000000" ,Span(12 ,strChatLeft + L" �� "+strChatRight+L" ˵��") +ChatMessage(strText,stFont,pSrcUserItem->GetUserUIN() ) ) ;
			}			
		}
		
	}
	else
	{
		if ( strChatLeft == L"��" )
		{
			strTemp =Font( L"����",L"#000000" ,Span(12,strChatLeft+L"�� "+strChatRight+L" ���ĵ�˵��"+ ChatMessage(strText,stFont,pSrcUserItem->GetUserUIN(),bAutoMsg))) ;
		}
		else if ( strChatRight == L"��" )
		{
			strTemp =Font( L"����",L"#000000" ,Span(12,strChatLeft+L" ��"+strChatRight+L"���ĵ�˵��"+ ChatMessage(strText,stFont,pSrcUserItem->GetUserUIN(),bAutoMsg))) ;
		}		
	}

	strTemp += L"<BR>" ;
	return strTemp ;
}

CString HtmlBuild::GetPrivateTips( const CString& strTitle , const CString& strValue ,  const CString& strColor )
{
	CString strTemp = Font( L"����" , strColor , Span(12,strTitle+strValue) ) ;
	strTemp += L"<BR>" ;
	return strTemp ;
}

CString HtmlBuild::GetPublicTips( const CString& strTitle , const CString& strValue ,  const CString& strColor ) 
{
	CString strTemp = Font( L"����" , strColor , Span(12,strTitle+strValue) ) ;
	strTemp += L"<BR>" ;
	return strTemp ;
}

CString HtmlBuild::GetOfficialNocice( CString& strValue ) 
{
	std::wstring strModulePath = common::utility::systemhelper::Get179AppPath();
	common::CURLEncode urlEncode;
	strModulePath = urlEncode.URLEncodeLocalPath(strModulePath);
	std::wstring strOfficeNoticePngPath = strModulePath + IMG_OFFICE_NOTICE_PNG_PATH;	

	CString strTemp = Img( strOfficeNoticePngPath.c_str() ) ;
	strTemp += Font( L"����" , COLOR_NORMAL ,Span(12 , L" "+strValue) ) ;
	strTemp += L"<BR>" ;
	return strTemp ;
}

CString HtmlBuild::GetNotice( const CString& strValue ) 
{
	std::wstring strModulePath = common::utility::systemhelper::Get179AppPath();
	common::CURLEncode urlEncode;
	strModulePath = urlEncode.URLEncodeLocalPath(strModulePath);
	std::wstring strNoticePngPath = strModulePath + IMG_NOTICE_PNG_PATH;	

	CString strTemp = Img( strNoticePngPath.c_str() ) ;
	strTemp += Font( L"����" , COLOR_NORMAL ,Span(12 , strValue) ) ;
	strTemp += L"<BR>" ;
	return strTemp ;
}

CString HtmlBuild::GetNotice(const CString& strValue ,MessageFont& stFont) 
{
	std::wstring strModulePath = common::utility::systemhelper::Get179AppPath();
	common::CURLEncode urlEncode;
	strModulePath = urlEncode.URLEncodeLocalPath(strModulePath);
	std::wstring strNoticePngPath = strModulePath + IMG_NOTICE_PNG_PATH;	

	CString strTemp = Img( strNoticePngPath.c_str() ) ;
	strTemp += Font( stFont.font_type.c_str() ,GetColorString(stFont.font_color) ,Span(stFont.font_size , strValue) ) ;
	strTemp += L"<BR>" ;
	return strTemp ;
}

CString HtmlBuild::GetTempNotice( uint32 un179ID ,CString strSrcDecodeName ,const CString& strValue , MessageFont& stFont ) 
{
	CString strName ;
	strName.Format( L"--��%s��(%u)����",strSrcDecodeName ,un179ID ) ;

	std::wstring strModulePath = common::utility::systemhelper::Get179AppPath();
	common::CURLEncode urlEncode;
	strModulePath = urlEncode.URLEncodeLocalPath(strModulePath);
	std::wstring strTempNoticePngPath = strModulePath + IMG_TEMPNOTICE_PNG_PATH;

	CString strTemp ;
	strTemp = Img( strTempNoticePngPath.c_str() ) ;
	strTemp += Font( stFont.font_type.c_str() ,GetColorString(stFont.font_color) ,Span(stFont.font_size ,  GetFontText( stFont , strValue ) ) ) ;
	strTemp += Font( L"����" ,COLOR_GIFT ,Span(12,strName)) ;
	strTemp += L"<BR>" ;

	return strTemp ;
}

CString HtmlBuild::GetEnterRoomGetUserList_Blink( IUserItem * pUserItem ) 
{
	CString strHtml ;
	//IGiftItem* pBlinkItem = GiftManager::GetInstance()->GetBlinkEnterItem() ;
	IGiftItem * pBlinkItem = GiftManager::GetInstance()->SearchBlinkEnterByID(pUserItem->GetBlinkEnterID());
	if ( pUserItem->IsBlinkEnter() && pBlinkItem != NULL )
	{
		CString strImgPath = Img( pBlinkItem->GetLargeImagePath().c_str());
		CString strTemp ;
		CString strCrestImgPath , strStampImgPath, strRichLevelImgPath = L"";	
		if ( pUserItem->GetUserStampID() != 0 )
		{
			//���� ͼƬ
			IGiftItem* pGiftItem = GiftManager::GetInstance()->SearchStampByID( pUserItem->GetUserStampID() ) ;
			if ( pGiftItem != NULL )
			{
				strStampImgPath = Img( pGiftItem->GetSmallImagePath().c_str() ) ;
			}
		}
		//if (pUserItem->GetUserRichLevel() > 0)
		//{
		//	std::wstring richLevelIconPath = RichLevelManager::GetRichLevelImgPath(pUserItem);
		//	if ( !richLevelIconPath.empty() )
		//	{
		//		strRichLevelImgPath = Img( richLevelIconPath.c_str() );
		//	}
		//}
		if ( pUserItem->GetUserVipLevel() >= core::VIPLEVEL_SILVER )
		{
			//�ʹ��û�/�ٷ����� ͼƬ
			std::wstring strIconPath = ListIconManager::GetOutputIcon(pUserItem) ;
			if ( !strIconPath.empty() )
			{
				strCrestImgPath = Img( strIconPath.c_str() );
			}	
			
			//����ͼƬ ��ͼ�� ������ �ǳ� �˺�
			strTemp.Format( L"%s%s��%s%s %s %s %s %s" ,strImgPath , pBlinkItem->GetStrSendDesc().c_str(), strStampImgPath ,
				strCrestImgPath , GetVipName( pUserItem->GetUserVipLevel() ) , strRichLevelImgPath , GetNameAndID(pUserItem), pBlinkItem->GetName().c_str() ) ;
		}
		else
		{
			strTemp.Format( L"%s%s��%s %s %s %s" ,strImgPath  , pBlinkItem->GetStrSendDesc().c_str(),
				strStampImgPath, strRichLevelImgPath , GetNameAndID(pUserItem), pBlinkItem->GetName().c_str() ) ;
		}

		strHtml = Font( L"����" , COLOR_GIFT ,Span( 12,Bold(strTemp) ) ) ;
		strHtml += L"<BR>" ;
	}
	return strHtml ;
}

//����ʹ�
CString HtmlBuild::GetEnterRoomGetUserList_VIPLevelTop( IUserItem* pUserItem ) 
{
	CString strHtml ;
	if (!pUserItem->IsBlinkEnter() && pUserItem->GetUserVipLevel() == core::VIPLEVEL_TOP )
	{
		strHtml = EnterMgr->GetEnterHtmlByVipLevel( pUserItem->GetUserVipLevel() ) ;
		if ( !strHtml.IsEmpty() )
		{
			CString strTemp ;
			strTemp.Format( L" %s "  , GetNameAndID(pUserItem) ) ;
			strHtml.Replace( L"VipImage" , GetUserItemHeadImg( pUserItem ) ) ;
			//strHtml.Replace( L"RichLevelImage" , GetUserItemRichLevelImg( pUserItem ) ) ;
			strHtml.Replace( L"name" , strTemp ) ;
			strHtml += L"<BR>" ;

		}
	}
	return strHtml ;
}

//��ʯ�ʹ�
CString HtmlBuild::GetEnterRoomGetUserList_VIPLevelDiamond( IUserItem* pUserItem ) 
{
	CString strHtml ;
	if (!pUserItem->IsBlinkEnter() && pUserItem->GetUserVipLevel() == core::VIPLEVEL_DIAMOND )
	{
		strHtml = EnterMgr->GetEnterHtmlByVipLevel( pUserItem->GetUserVipLevel() ) ;
		if ( !strHtml.IsEmpty() )
		{
			CString strTemp ;
			strTemp.Format( L" %s "  , GetNameAndID(pUserItem) ) ;
			strHtml.Replace( L"VipImage" , GetUserItemHeadImg( pUserItem ) ) ;
			//strHtml.Replace(L"RichLevelImage", GetUserItemRichLevelImg(pUserItem));
			strHtml.Replace( L"name" , strTemp ) ;
			strHtml += L"<BR>" ;
		}
	}
	return strHtml ;
}

//���û�
CString HtmlBuild::GetEnterRoomGetUserList_Crest( IUserItem * pUserItem ) 
{
	CString strHtml ;
	if (!pUserItem->IsBlinkEnter() && pUserItem->GetUserVipLevel() > core::VIPLEVEL_HONOR && pUserItem->GetUserVipLevel() < core::VIPLEVEL_DIAMOND)
	{
		strHtml = EnterMgr->GetEnterHtmlByVipLevel( pUserItem->GetUserVipLevel() ) ;
		if ( !strHtml.IsEmpty() )
		{
			CString strTemp ;
			strTemp.Format( L" %s "  , GetNameAndID(pUserItem) ) ;
			strHtml.Replace( L"VipImage" , GetUserItemHeadImg( pUserItem ) ) ;
			//strHtml.Replace( L"RichLevelImage" , GetUserItemRichLevelImg( pUserItem ) ) ;
			strHtml.Replace( L"name" , strTemp ) ;
			strHtml += L"<BR>" ;

		}
	}
	return strHtml ;
}


CString HtmlBuild::GetEnterRoomGetUserList_LuckyStar( IUserItem* pUserItem ) 
{
	return GetLuckyStarEnterRoom( pUserItem ) ;
}

CString HtmlBuild::GetGiftStar(IUserItem* pUserItem, uint16 unGiftID)
{
	CString strHtml ;
	room_user_info* userInfo = pUserItem->GetUserInfo();

	IGiftItem* pGiftItem = NULL;
	pGiftItem = GiftManager::GetInstance()->SearchGiftByID(unGiftID);
	if (pGiftItem)
	{
		CString strImgPath = Img( pGiftItem->GetLargeImagePath().c_str());
		CString strGiftName = pGiftItem->GetName().c_str();
		CString strTemp;
		strTemp.Format(L"%s%s֮�� %s ��ʶ�Ŀ�������������", strImgPath, strGiftName, GetNameAndID(pUserItem));
		strHtml = GetPublicTips( L"����ʾ���� " , strTemp ,COLOR_GIFT ); 
	}

	return strHtml ;
}

CString HtmlBuild::GetEnterRoom( IUserItem * pUserItem )
{
	//CString strHtml = GetLuckyStarEnterRoom( pUserItem );
	CString strHtml = L"";
	CString strTemp ;
	//IGiftItem* pBlinkItem = GiftManager::GetInstance()->GetBlinkEnterItem() ;
	IGiftItem * pBlinkItem = GiftManager::GetInstance()->SearchBlinkEnterByID(pUserItem->GetBlinkEnterID());
	if ( pUserItem->IsBlinkEnter() && pBlinkItem != NULL )
	{
		strHtml = GetLuckyStarEnterRoom(pUserItem);
		CString strImgPath = Img( pBlinkItem->GetLargeImagePath().c_str());	
		//std::wstring strRichLevelIcon = L"";
		CString strRichLevelPath = L"";
		//if (pUserItem->GetUserRichLevel() > 0)
		//{
		//	strRichLevelIcon = RichLevelManager::GetRichLevelImgPath(pUserItem);
		//	strRichLevelPath = Img(strRichLevelIcon.c_str());
		//}
		strTemp.Format( L"%s%s��%s%s %s%s" ,strImgPath , pBlinkItem->GetStrSendDesc().c_str(), GetUserItemHeadImg( pUserItem ), strRichLevelPath , GetNameAndID(pUserItem), pBlinkItem->GetName().c_str()) ;
		strHtml +=Font( L"����" , COLOR_GIFT ,Span(12 ,Bold(strTemp) )  ) ;
		strHtml += L"<BR>" ;
	}
	else
	{
		if ( pUserItem->GetUserVipLevel() >= VIPLEVEL_SILVER )
		{
			CString strHtmlVip = EnterMgr->GetEnterHtmlByVipLevel( pUserItem->GetUserVipLevel() ) ;
			if ( !strHtmlVip.IsEmpty() )
			{				 
				CString strTemp ;
				strTemp.Format( L" %s "  , GetNameAndID(pUserItem) ) ;
				strHtmlVip.Replace( L"VipImage" , GetUserItemHeadImg( pUserItem ) ) ;
				//strHtmlVip.Replace(L"RichLevelImage", GetUserItemRichLevelImg(pUserItem));
				strHtmlVip.Replace( L"name" , strTemp ) ;
				strHtmlVip += L"<BR>" ;
				strHtml += strHtmlVip ;
			}
		}
		else if ( m_pRoomBusiness->GetRoomOption()->IsShowUserInOut() && !CPersonalConfig::GetInstance()->GetIsBlockUserInOutMsg() )
		{			
			strTemp.Format( L"%s ���뷿��" , GetNameAndID(pUserItem) ) ;
			strHtml += GetPublicTips( L"����ʾ���� " , strTemp ,COLOR_GIFT ); 
		}
		strHtml += GetLuckyStarEnterRoom(pUserItem);
	}

	uint8 unEventEnterIndex = EventEnterMgr->GetEventIndex(pUserItem->GetUser179ID());
	if (unEventEnterIndex != 0)
	{
		strHtml += GetEnterRoomGetUserList_Event( pUserItem, unEventEnterIndex ) ;
	}

	std::vector<core::GiftStarInfo> vecInfo = pUserItem->GetGiftStarInfo();
    for (std::vector<core::GiftStarInfo>::iterator iter = vecInfo.begin(); iter != vecInfo.end(); ++iter)
    {
		IGiftItem* pGiftItem = NULL;
		pGiftItem = GiftManager::GetInstance()->SearchGiftByID(iter->unGiftID);
		if (pGiftItem)
		{
			CString strImgPath = Img( pGiftItem->GetLargeImagePath().c_str());
			strTemp.Format(L"%s%s֮�� %s ��ʶ�Ŀ�������������", strImgPath, pGiftItem->GetName().c_str(), GetNameAndID(pUserItem));
			strHtml += GetPublicTips( L"����ʾ���� " , strTemp ,COLOR_GIFT ); 
		}
	}

	return strHtml ;
}

CString HtmlBuild::GetLeaveRoom( IUserItem* pUserItem ) 
{

	CString strTemp ;
	strTemp.Format( L"%s %s �뿪������" , GetUserItemHeadImg( pUserItem ) , GetNameAndID(pUserItem) ) ;
	return GetPublicTips( L"����ʾ����  " , strTemp ,COLOR_GIFT );
}

CString HtmlBuild::ChatUser( uint32 nSelfUUID , IUserItem* pUserItem , bool bReplaceSelf  )
{
	CString strTemp ;
	if ( pUserItem == NULL )
	{
		return strTemp ;
	}
	else if ( pUserItem->GetUserUIN() == nSelfUUID && bReplaceSelf )
	{
		strTemp = L"��"  ;
	}
	else
	{
		strTemp = ChatUserItem( pUserItem  ) ;
	}

	return strTemp ;
}

CString HtmlBuild::ChatUserItem( IUserItem* pUserItem ) 
{
	CString strTemp ;
	if ( pUserItem != NULL )
	{
		strTemp = GetUserHead( pUserItem ) ;		
		CString strNameHref ;
		strNameHref.Format(_T("<a href=\"%s\" name=\"%s\" uuid=\"%d\" type=\"%d\" title=\"%d\" class=\"user\" >%s</a>") , 
			L"" , pUserItem->GetDecodeUserName().c_str() ,
			pUserItem->GetUserUIN() , CLICK_TYPE_NAME ,pUserItem->GetUser179ID() ,
			GetNameAndID(pUserItem) ) ;
		strTemp += strNameHref ;
	}
	return strTemp ;
}

CString HtmlBuild::StampRightUserItem( IUserItem* pUserItem ) 
{
	CString strTemp ;
	if (!pUserItem->IsOfficial())
	{
		std::wstring strVipPath = ListIconManager::GetVIPIcon(pUserItem);
		if ( !strVipPath.empty() )
		{
			strTemp += Img( strVipPath.c_str() ) ;
		}
	}

	if ( pUserItem->IsActor() || pUserItem->IsOfficial())
	{
		std::wstring strIconPath = ListIconManager::GetOutputIcon(pUserItem) ;
		if ( !strIconPath.empty() )
		{
			//�ʹ��û�/�ٷ����� ͼƬ
			strTemp += Img( strIconPath.c_str() ) ;
		}
	}
	//if ( pUserItem->GetUserRichLevel() > 0 )
	//{
	//	wstring strIcon = RichLevelManager::GetRichLevelImgPath(pUserItem);
	//	if ( !strIcon.empty() )
	//	{
	//		strTemp += Img( strIcon.c_str() ) ;
	//	}
	//}
	if ( pUserItem->GetUserTitleLevel() >= core::TITLELEVEL_TEMP_MANAGER && !(pUserItem->IsActor() || pUserItem->IsOfficial()))
	{
		wstring strIcon = ListIconManager::GetThirdColumnIcon( pUserItem ) ;
		if ( !strIcon.empty() )
		{
			strTemp += Img( strIcon.c_str() ) ;
		}
	}
	CString strNameHref ;
	strNameHref.Format(_T("<a href=\"%s\" name=\"%s\" uuid=\"%u\" type=\"%d\" title=\"%d\" class=\"user\" > %s</a>") , 
		L"" , pUserItem->GetDecodeUserName().c_str() ,
		pUserItem->GetUserUIN() , CLICK_TYPE_NAME ,pUserItem->GetUser179ID() ,
		GetNameAndID(pUserItem) ) ;
	strTemp += strNameHref ;

	return strTemp ;
}

CString HtmlBuild::PrivateUserItem( IUserItem* pUserItem , BOOL bStamp ) 
{
	CString strTemp ,strTitleImg;
	if ( pUserItem->GetUserTitleLevel() >= core::TITLELEVEL_TEMP_MANAGER && !(pUserItem->IsActor() || pUserItem->IsOfficial()))
	{
		wstring strIcon = ListIconManager::GetThirdColumnIcon( pUserItem ) ;
		if ( !strIcon.empty() )
		{
			strTitleImg += Img( strIcon.c_str() ) ;
		}
	}
	strTemp.Format( L"%s%s%s %s " , GetUserItemHeadImg( pUserItem , bStamp ) ,GetUserItemRichLevelImg(pUserItem) , strTitleImg, GetNameAndID(pUserItem) ) ;
	return strTemp ;
}

CString HtmlBuild::GetUserItemHeadImg( IUserItem* pUserItem , BOOL bStamp ) //����û���ǰ���º͹�ͼƬ
{
	CString strTemp ;
	if ( pUserItem != NULL )
	{
		if ( bStamp && pUserItem->GetUserStampID() != 0 )
		{
			//���� ͼƬ
			IGiftItem* pGiftItem = GiftManager::GetInstance()->SearchStampByID( pUserItem->GetUserStampID() ) ;
			if ( pGiftItem != NULL )
			{
				strTemp += Img( pGiftItem->GetSmallImagePath().c_str() ) ;
			}
		}

		if (!pUserItem->IsOfficial())
		{
			std::wstring strVipPath = ListIconManager::GetVIPIcon(pUserItem);
			if ( !strVipPath.empty() )
			{
				strTemp += Img( strVipPath.c_str() ) ;
			}
		}

		if ( pUserItem->IsActor() || pUserItem->IsOfficial() )
		{
			std::wstring strIconPath = ListIconManager::GetOutputIcon(pUserItem) ;
			if ( !strIconPath.empty() )
			{
				//�ʹ��û�/�ٷ����� ͼƬ
				strTemp += Img( strIconPath.c_str() ) ;
			}
		}
	}
	return strTemp ;
}

CString HtmlBuild::GetUserItemRichLevelImg(IUserItem* pUserItem) //����û������ȼ�ͼ��
{
	return L"";
	//CString strTemp ;
	//if ( pUserItem != NULL )
	//{
	//	if ( pUserItem->GetUserRichLevel() > 0 )
	//	{
	//		std::wstring strIconPath = RichLevelManager::GetRichLevelImgPath(pUserItem);
	//		if (!strIconPath.empty())
	//		{
	//			strTemp += Img(strIconPath.c_str());
	//		}
	//	}
	//}
	//return strTemp ;
}

CString HtmlBuild::GetAutoWelcome( IUserItem* pUserItem , CString& strText ) 
{
	MessageFont stFont ;
	stFont.font_type = L"����" ;
	stFont.font_color = 0 ;
	stFont.font_size = 12 ;
	stFont.font_style = core::FONTSTYLETYPE_NONE ;

	CString strTemp =Font( L"����", COLOR_NORMAL ,Span( 12 , ChatUserItem( pUserItem )+ L" ˵�� ") + ChatMessage(strText,stFont,pUserItem->GetUserUIN()) ) ;
	strTemp += L"<BR>" ;

	return strTemp ;
}

CString HtmlBuild::GetVisistorRegistor( IUserItem* pUserItem , CString& strText ) 
{

	MessageFont stFont ;
	stFont.font_type = L"����" ;
	stFont.font_color = 0 ;
	stFont.font_size = 12 ;
	stFont.font_style = core::FONTSTYLETYPE_NONE ;

	CString strTemp =Font( L"����", COLOR_NORMAL ,Span( 12 , ChatUserItem( pUserItem )+ L" �������ĵ�˵�� ") + ChatMessage(strText,stFont,pUserItem->GetUserUIN()) ) ;
	strTemp += L"<BR>" ;

	return strTemp ;
}

CString HtmlBuild::ChatMessage( CString& strText , MessageFont& stFont , uint32 srcUin, bool bAutoMsg) 
{
	CString strTemp ;
	if ( stFont.font_style == FONTSTYLETYPE_COLORTEXT )
	{
		//����
		CaiZiItem *pCaiZiItem = CaiZiMgr->GetCaiZiItemByIndex( _wtoi( strText ) ) ;
		if ( pCaiZiItem != NULL )
		{
			strTemp = Span( 12 , pCaiZiItem->GetCaiZiHtml().c_str() ) ;
		}
	}
	else
	{
		strTemp = Font( stFont.font_type.c_str() ,GetColorString(stFont.font_color) ,Span(stFont.font_size , GetFontText( stFont , strText ) ) ) ;
		CString strNoRemind;
		if (bAutoMsg)
		{
			strNoRemind.Format( L"<SPAN> <a href=\"%s\" name=\"%s\" type=\"%d\" uuid=\"%d\" >��������</a></SPAN>",L"" ,L"autoReply", CLICK_TYPE_NO_REMIND,srcUin);
			strTemp += strNoRemind;
		}
		strTemp += Span( 12 , _T("#333333") ,GetCurrentTimeString() ) ;
	}
	return strTemp ;
}

CString HtmlBuild::Img( CString strImgPath ) 
{
	CString strTemp ;
	strTemp.Format( L"<IMG src=\"%s\">" ,strImgPath ) ;
	return strTemp ;
}

CString HtmlBuild::ItaLic( const CString& strValue ) 
{
	CString strTemp ;
	strTemp.Format(_T("<I>%s</I>") , strValue ) ;
	return strTemp ;
}

CString HtmlBuild::UnderLine(const CString& strValue )
{
	CString strTemp ;
	strTemp.Format(_T("<U>%s</U>") , strValue ) ;
	return strTemp ;
}

CString HtmlBuild::Bold(const CString& strValue ) 
{
	CString strTemp ;
	strTemp.Format(_T("<B>%s</B>") , strValue ) ;
	return strTemp ;
}

CString HtmlBuild::Span(int nFontSize , const CString& strColor ,const CString& strValue ) 
{
	CString strTemp ;
	strTemp.Format(_T("<SPAN style=FONT-SIZE:%dpx;color:%s>%s</SPAN>"),nFontSize ,strColor,strValue) ;
	return strTemp ;
}

CString HtmlBuild::Span(int nFontSize ,const CString& strValue ) 
{
	CString strTemp ;
	strTemp.Format(_T("<SPAN style=FONT-SIZE:%dpx>%s</SPAN>") ,nFontSize , strValue ) ;
	return strTemp ;
}

CString HtmlBuild::Font(const CString& strFont , const CString& strColor , const CString& strValue ) 
{
	CString strTemp ;
	strTemp.Format(_T("<FONT face=%s color=%s>%s</FONT>"),strFont , strColor , strValue ) ;
	return strTemp ;
}

CString HtmlBuild::Marquee(const CString& strValue ) 
{
	CString strTemp ;
	strTemp.Format(_T("<marquee id=content direction=left scrollamount=6 onmouseover=this.stop() onmouseout=this.start()>%s</marquee>") ,strValue ) ;
	return strTemp ;
}

//��ɫת�����ַ���
CString HtmlBuild::GetColorString( COLORREF cf ) 
{
	CString strColor ;
	strColor.Format( _T("#%02X%02X%02X") , GetRValue(cf),GetGValue(cf) , GetBValue(cf) ) ;
	return strColor ;
}

//�õ�ʱ��
CString HtmlBuild::GetCurrentTimeString() 
{
	CString strTime ;
	CTime mtime = CTime::GetCurrentTime() ;
	strTime.Format( L" (%.2d:%.2d:%.2d)" , mtime.GetHour() , mtime.GetMinute() , mtime.GetSecond() ) ;
	return strTime ;
}

CString HtmlBuild::GetGiftDateString( uint32 unTime ) 
{
	CString strTime ;
	time_t szTime = unTime ;
	struct tm *pTime = localtime( &szTime ) ;
	if ( pTime != NULL )
	{
		strTime.Format( L"��%.2d.%.2d %.2d:%.2d��" ,pTime->tm_mon+1 ,pTime->tm_mday , pTime->tm_hour ,pTime->tm_min ) ;
	}
	return strTime ;
}

CString HtmlBuild::GetFontText( MessageFont& stFont ,const CString& strText ) 
{
	CString strTextTemp = strText ;
	if(stFont.font_style & core::FONTSTYLETYPE_BOLD)
	{
		strTextTemp = Bold( strTextTemp ) ;
	}
	if( stFont.font_style & core::FONTSTYLETYPE_ITALICS)
	{
		strTextTemp = ItaLic( strTextTemp ) ;
	}
	if(stFont.font_style & core::FONTSTYLETYPE_UNDERLINE)
	{
		strTextTemp = UnderLine( strTextTemp ) ;
	}
	return strTextTemp ;
}

CString HtmlBuild::GetLuckyTimesPngPath( uint16 unLuckyTimes ) 
{
	std::wstring strModulePath = common::utility::systemhelper::Get179AppPath();
	common::CURLEncode urlEncode;
	strModulePath = urlEncode.URLEncodeLocalPath(strModulePath);
	std::wstring strMultiplePngPath ;
	switch( unLuckyTimes )
	{
	case 100:
		{
			strMultiplePngPath = strModulePath + IMG_100MULTIPLE_GIF_PATH;
		}
		break;
	case 500:
		{
			strMultiplePngPath = strModulePath + IMG_500MULTIPLE_GIF_PATH;	
		}
		break;
	case 800:
		{
			strMultiplePngPath = strModulePath + IMG_800MULTIPLE_PNG_PATH;	
		}
		break;
	case 1000:
		{
			strMultiplePngPath = strModulePath + IMG_1000MULTIPLE_GIF_PATH;	
		}
		break;
	case 1500:
		{
			strMultiplePngPath = strModulePath + IMG_1500MULTIPLE_PNG_PATH;	
		}
		break;
	case 2000:
		{
			strMultiplePngPath = strModulePath + IMG_2000MULTIPLE_PNG_PATH ;
		}
		break;
	case 2500:
		{
			strMultiplePngPath = strModulePath + IMG_2500MULTIPLE_PNG_PATH;	
		}
		break;
	case 3000:
		{
			strMultiplePngPath = strModulePath + IMG_3000MULTIPLE_PNG_PATH;	
		}
		break;
	case 5000:
		{
			strMultiplePngPath = strModulePath + IMG_5000MULTIPLE_GIF_PATH;				
		}
		break;
	default:break ;
	}	
	return strMultiplePngPath.c_str() ;
}


CString HtmlBuild::GetVipName( uint8 nVipLevel ) 
{
	CString strVipName ;
	switch( nVipLevel )
	{
	case core::VIPLEVEL_VIP:
		{
			strVipName = L"VIP" ;
		}
		break;
	case core::VIPLEVEL_HONOR:
		{
			strVipName = L"��ҫVIP" ;
		}
		break;
	case core::VIPLEVEL_SILVER:
		{
			strVipName = L"��ɫ�ʹ�" ;
		}
		break;
	case core::VIPLEVEL_GOLDEN:
		{
			strVipName = L"��ɫ�ʹ�" ;
		}
		break;
	case core::VIPLEVEL_CRYSTAL:
		{
			strVipName = L"ˮ���ʹ�" ;
		}
		break;
	case core::VIPLEVEL_DIAMOND:
		{
			strVipName = L"��ʯ�ʹ�" ;
		}
		break;
	case core::VIPLEVEL_BLACKDIAMOND:
		{
			strVipName = L"����ʹ�" ;
		}
		break;
	case core::VIPLEVEL_TOP:
		{
			strVipName = L"����ʹ�" ;
		}
		break;
	default:break;
	}

	return strVipName ;
}

CString HtmlBuild::GetTitleName( uint16 nTitleType ) 
{
	CString strTitle ;
	switch( nTitleType )
	{
	case core::TITLELEVEL_TEMP_MANAGER:
		{
			strTitle = L"��ʱ����Ա" ;
		}
		break; 
	case core::TITLELEVEL_MANAGER:
		{
			strTitle = L"����Ա" ;
		}
		break;
	case core::TITLELEVEL_SECOND_OWNER:
		{
			strTitle = L"������" ;
		}
		break;
	case core::TITLELEVEL_OWNER:
		{
			strTitle = L"����" ;
		}
		break;
	case core::TITLELEVEL_SUPER_MANAGER:
		{
			strTitle = L"��������Ա" ;
		}
		break;
	default: break;
	}
	return strTitle ;
}

CString HtmlBuild::GetSpeaker( CString& strText, MessageFont& stFont, SpeakerInfo& stInfo )
{
	return SpeakerUserItem(stInfo) + L":<BR>" + SpeakerMessage(strText, stFont);
}

//��������ʱ�Ļ�ӭ��
CString HtmlBuild::GetWelecomeWords( IUserItem* pOwnerItem , CString& strText , MessageFont& stFont ) 
{
	CString strTemp = Font( L"����" ,COLOR_NORMAL , Span(12 ,ChatUserItem(pOwnerItem)+
		L" �������ĵ�˵�� "+ChatMessage(strText,stFont,pOwnerItem->GetUserUIN()) ) ) ;
	strTemp += L"<BR>" ;
	return strTemp ;
}

CString HtmlBuild::GetActorAutoSpeakWords(IUserItem* pUserItem, CString& strText)
{
	CString strTemp = Font( L"����" , L"#000000" , Span(12, ChatUserItem(pUserItem) + L" �������ĵ�˵�� " + strText) ) ;
	strTemp += L"<BR>" ;
	return strTemp ;
}

CString HtmlBuild::GetAgentAutoSpeakWords(IUserItem* pUserItem, CString& strText)
{
	CString strTemp = Font( L"����" , L"#000000" , Span(12, ChatUserItem(pUserItem) + L" �������ĵ�˵�� " + strText) ) ;
	strTemp += L"<BR>" ;
	return strTemp ;
}

CString HtmlBuild::OnNotifyPlutusAward( uint32 srcuin , uint32 un179ID , 
									   std::wstring& strDecodeName ,std::wstring strRoomName ,
									   uint16 nSelfTitleLevel , int nNumber ,uint16 unGiftID ) 
{
	CString strTemp ;
	if ( nSelfTitleLevel > core::TITLELEVEL_TEMP_MANAGER )
	{
		//����Ա		
		CString strHref ;
		IGiftItem* pGiftItem = GiftManager::GetInstance()->SearchGiftByID( unGiftID ) ;
		if ( pGiftItem != NULL )
		{
			CString strImgPath = Img( pGiftItem->GetSmallImagePath().c_str() ) ;

			CString strNameAndID;
			if (un179ID > MAX_SHOW_179ID)
			{
				strNameAndID = strDecodeName.c_str();
			}
			else
			{
				strNameAndID.Format(L"%s(%u)", strDecodeName.c_str(), un179ID);
			}

			CString strHrefName ;
			strHrefName.Format( L"%s%s�ĳ��ĸж��˲���10�������·��ɷ�Ԫ����ÿ�˶���%d�λ���ʹ͵Ļ��ᣬ�ƽ����أ�����������" ,
				strRoomName.c_str(),strNameAndID ,nNumber ) ;
			strHref.Format( L"<a href=\"%s\" name=\"%s\" uuid=\"%u\" type=\"%d\">ת������ʱ����</a>" ,
				L"" ,strHrefName , srcuin , CLICK_TYPE_TEMP_NOTICE) ;

			CString strInfo ;
			strInfo.Format( L"%s%s�ĳ��ĸж��� ����%s��10�������·��ɷ�Ԫ����ÿ�˶���%d�λ���ʹ͵Ļ��ᣬ�ƽ����أ�����������" ,
				strRoomName.c_str() ,strNameAndID ,strImgPath ,nNumber ) ;
			strTemp = Font( L"����" ,COLOR_GIFT ,Span(12,L"����ʾ���� ")+Span( 12,strInfo)+ Span(12 ,strHref)  ) ;
			strTemp += L"<BR>" ;
		}
	}
	else
	{		
		//�ǹ���Ա
		CString strInfo ;
		CString strImgPath ;
		IGiftItem* pGiftItem = GiftManager::GetInstance()->SearchGiftByID( unGiftID ) ;
		if ( pGiftItem != NULL )
		{

			CString strNameAndID;
			if (un179ID > MAX_SHOW_179ID)
			{
				strNameAndID = strDecodeName.c_str();
			}
			else
			{
				strNameAndID.Format(L"%s(%u)", strDecodeName.c_str(), un179ID);
			}
			strInfo.Format( L"%s�ĳ��ĸж��� ����%s��10�������·��ɷ�Ԫ����ÿ�˶���%d�λ���ʹ͵Ļ��ᣬ�ƽ����أ�����������" ,
				strNameAndID, strImgPath, nNumber ) ;
			strTemp = Font( L"����" ,COLOR_GIFT , Span(12,L"����ʾ���� "+strInfo) ) ;
			strTemp += L"<BR>" ;
		}
	}
	return strTemp ;
}

//��ȡ��ʾ����ǰ����Ϣ
CString HtmlBuild::GetUserHead( IUserItem* pUserItem ) 
{
	CString strTemp = GetUserItemHeadImg( pUserItem ) ;	

	//if ( pUserItem->GetUserRichLevel() > 0 )
	//{
	//	wstring strIcon = RichLevelManager::GetRichLevelImgPath(pUserItem);
	//	if ( !strIcon.empty() )
	//	{
	//		strTemp += Img( strIcon.c_str() ) ;
	//	}
	//}

	if ( pUserItem->GetUserTitleLevel() >= core::TITLELEVEL_TEMP_MANAGER && !(pUserItem->IsActor() || pUserItem->IsOfficial()))
	{
		wstring strIcon = ListIconManager::GetThirdColumnIcon( pUserItem ) ;
		if ( !strIcon.empty() )
		{
			strTemp += Img( strIcon.c_str() ) ;
		}
	}
	strTemp +=L" " ;
	return strTemp ;
}

CString HtmlBuild::SpeakerUserItem( CString& strSrcName , CString& strSrcHead , uint32 un179ID ,COLORREF cf ) 
{
	CString strTemp = L"";
	CString strName ;
	
	IUserItem* pUserItem = m_pRoomBusiness->GetUserManager()->SearchUserBy179ID(un179ID);
	//if (pUserItem != NULL && !pUserItem->IsOfficial())
	//{
	//	std::wstring strRichLevelImg = RichLevelManager::GetRichLevelImgPath(pUserItem);
	//	strTemp = Img(strRichLevelImg.c_str());
	//}
	CString strSrcNameAndID;
	if (un179ID > MAX_SHOW_179ID)
	{
		strSrcNameAndID = strSrcName;
	}
	else
	{
		strSrcNameAndID.Format(L"%s(%u)", strSrcName, un179ID);
	}
	strName.Format( L"%s%s" ,strTemp, strSrcNameAndID ) ;
	strName = Font(_T("����") ,GetColorString(cf), Span(13,strName) );
	return strSrcHead + strName ;
}

CString HtmlBuild::SpeakerUserItem( SpeakerInfo& stInfo, COLORREF cf/* = RGB(0,99,255)*/ )
{
	CString strTemp ;

	if ( stInfo.unStampID != 0 )
	{
		//���� ͼƬ
		IGiftItem* pGiftItem = GiftManager::GetInstance()->SearchStampByID( stInfo.unStampID ) ;
		if ( pGiftItem != NULL )
		{
			strTemp += Img( pGiftItem->GetSmallImagePath().c_str() ) ;
		}
	}
	if ( (core::ENM_VipLevel)stInfo.unVipLevel>= core::VIPLEVEL_SILVER)
	{
		strTemp += Img( ListIconManager::GetIconPathByVipLevel(stInfo.unVipLevel).c_str() );
	}	

	//if (stInfo.unRichLevel > 0 )
	//{
	//	std::wstring strIcon = RichLevelManager::GetRichLevelImgPathByLevel(stInfo.unRichLevel);
	//	if ( !strIcon.empty())
	//	{
	//		strTemp += Img( strIcon.c_str() ) ;
	//	}
	//}
	//����������
	CString strName;
	CString strTitleName;
	if (stInfo.un179ID > MAX_SHOW_179ID)
	{
		strTitleName = common::utility::stringhelper::XMLEncode(stInfo.strName).c_str();
	}
	else
	{
		strTitleName.Format(L"%s(%u)", common::utility::stringhelper::XMLEncode(stInfo.strName).c_str(), stInfo.un179ID);
	}
	strName.Format(L"%s", strTitleName);
	strName = Font(_T("����") ,GetColorString(cf), Span(13,strName) );
	strTemp += strName ;

	return strTemp ;
}

CString HtmlBuild::SpeakerMessage( CString& strText , MessageFont& stFont )
{
	CString strTemp;
	strTemp = Font( stFont.font_type.c_str() ,GetColorString(stFont.font_color) ,Span(stFont.font_size , strText) ) ;
	strTemp += L"<BR>" ;

	return strTemp;
}

CString HtmlBuild::SpeakerSystemMessage( CString& strText )
{
	CString strTemp;
	strTemp = Font( L"����" , _T("#0000FF"), Span(13, strText) ) ;
	strTemp += L"<BR>" ;

	return strTemp;
}

CString HtmlBuild::SpeakerLuckyMessage( CString& strText )
{
	CString strTemp;
	strTemp = Font( L"����" , _T("#FF0000"), Span(12, strText) ) ;
	strTemp += L"<BR>" ;

	return strTemp;
}

CString HtmlBuild::GetSpeakerLucky( CString& strSrcName ,CString& strSrcLuckyHead , uint32 src179ID ,
								   uint16	unLuckyTimes , uint32 unLuckyMoney ,uint16 unGiftid ) 
{
	IUserItem* pUserItem =  m_pRoomBusiness->GetUserManager()->SearchUserBy179ID( src179ID ) ;
	if ( pUserItem != NULL )
	{
		strSrcLuckyHead = GetUserItemHeadImg( pUserItem ) ;
	}
	CString strTemp , strGiftName ;
	IGiftItem* pGiftItem = GiftManager::GetInstance()->SearchGiftByID( unGiftid ) ;
	if (pGiftItem != NULL)
	{
		strGiftName = pGiftItem->GetName().c_str();
	}
	strTemp.Format( L"�ͳ��� %s Ϊ��Ӯȡ��<B>%u</B>������<B>%u</B>��" ,strGiftName , unLuckyTimes , unLuckyMoney ) ;
	return SystemMessageTitle() + SpeakerUserItem( strSrcName ,strSrcLuckyHead ,src179ID ) + SpeakerLuckyMessage(strTemp) ;
}


CString HtmlBuild::GetSpeakerLucky( CString& strText, SpeakerInfo& stInfo, uint16 unGiftID )
{
	CString strTimes, strMoney, strName;
	int nPos = strText.Find(L",");
	strTimes = strText.Left(nPos);
	strMoney = strText.Right(strText.GetLength() - nPos - 1);
	IGiftItem* pGiftItem = GiftManager::GetInstance()->SearchGiftByID( unGiftID ) ;
	if (pGiftItem != NULL)
	{
		strName = pGiftItem->GetName().c_str();
	}
	CString strTemp;
	strTemp.Format(L"�ͳ��� %s Ϊ��Ӯȡ��<B>%s</B>������<B>%s</B>��", strName, strTimes, strMoney);
	return SystemMessageTitle() + SpeakerUserItem(stInfo) + SpeakerLuckyMessage(strTemp);
}

CString HtmlBuild::GetSpeakerPlutusAward(CString& strText, SpeakerInfo& stInfo, uint16 unGiftID)
{
	int nPos = strText.Find( L"," ) ;
	CString strRoomName = strText.Left( nPos );
	strText = strText.Right( strText.GetLength() - nPos -1 ) ;
	nPos = strText.Find( L",") ;
	CString strRoomID = strText.Left( nPos ) ;
	CString strNumber = strText.Right( strText.GetLength() - nPos - 1 );
	CString strTemp ;
	strTemp.Format( L"�ĳ��ĸж��� ����<B>��%s(%s)��</B>��ÿ�˶���%s�λ���ʹ͵Ļ��ᣬ�ƽ����أ�������ѽ��" , strRoomName , strRoomID , strNumber ) ;
	return SystemMessageTitle() + SpeakerUserItem(stInfo) + SpeakerLuckyMessage(strTemp);
}

CString HtmlBuild::GetSpeakerSystem( CString& strText )
{
	return SpeakerSystemMessage(strText);
}

CString HtmlBuild::SystemMessageTitle()
{
	CString strTemp;
	strTemp = Img( ListIconManager::GetIconPathByIndex(USERLIST_ICON_SYSTEMMSG).c_str() );
	strTemp += L"<BR>";

	return strTemp;
}

CString HtmlBuild::GetSpeakerFirework( CString& strText,SpeakerInfo& stInfo )
{
	CString strTemp;
	strTemp.Format(L"Ϊ\"%s\"�������й���Ա������һ�� �̻���\"%s\"��������̺죬����ʤ��", strText, strText);

	return  SpeakerFireworkTitle() + SpeakerUserItem(stInfo) + SpeakerLuckyMessage(strTemp);
}

CString HtmlBuild::GetSpeakerSalute( CString& strText, SpeakerInfo& stInfo )
{
	CString strTemp;
	strTemp.Format(L"Ϊ\"%s\"���������û�������һ�� ���ڣ�\"%s\"�����������ң�ʢ����ǰ", strText, strText);

	return SpeakerSaluteTitle() + SpeakerUserItem(stInfo) + SpeakerLuckyMessage(strTemp);
}

CString HtmlBuild::SpeakerFireworkTitle()
{
	return Img( ListIconManager::GetIconPathByIndex(USERLIST_ICON_SMALLSPEAKER).c_str()) + Img( ListIconManager::GetIconPathByIndex(USERLIST_ICON_FIREWORK).c_str());

}

CString HtmlBuild::SpeakerSaluteTitle()
{
	return Img( ListIconManager::GetIconPathByIndex(USERLIST_ICON_SMALLSPEAKER).c_str()) + Img( ListIconManager::GetIconPathByIndex(USERLIST_ICON_SALUTE).c_str());
}

CString HtmlBuild::GetPublicChangeVoice( IUserItem* pSrcUserItem ,IUserItem* pDstUserItem , uint16 unChangeVoiceID )
{
	IGiftItem* pGiftItem = GiftManager::GetInstance()->SearchGiftByID( unChangeVoiceID ) ;
	CString strGiftNameAndImg ;
	if ( pGiftItem != NULL )
	{
		strGiftNameAndImg = pGiftItem->GetName().c_str();
		strGiftNameAndImg += Img( pGiftItem->GetLargeImagePath().c_str() ) ;
	}

	CString strTemp = Font( L"����" ,COLOR_NORMAL ,Span(12, ChatUserItem( pSrcUserItem ) +L" ʹ�á�����֮������ "+ChatUserItem( pDstUserItem )+L" ��ɣ�" + strGiftNameAndImg) ) ;
	strTemp += L"</BR>" ;
	
	return strTemp ;
}

CString HtmlBuild::GetPrivateChangeVoice( IUserItem* pSrcUserItem , uint16 unChangeVoiceID )
{
	CString strGiftName ;
	//ͼƬ
	IGiftItem* pGiftItem = GiftManager::GetInstance()->SearchGiftByID( unChangeVoiceID ) ;
	if ( pGiftItem != NULL )
	{
		strGiftName =  pGiftItem->GetName().c_str();
	}
	CString strHref ;
	strHref.Format( _T("<a href=\"%s\" name=\"%s\" type=\"%d\" uuid=\"%d\">������</a>") ,
		L"" , pSrcUserItem->GetDecodeUserName().c_str() , CLICK_TYPE_VOICE, pSrcUserItem->GetUserUIN() ) ;
	return GetPrivateTips( L"����ʾ���� " , L"����"+PrivateUserItem( pSrcUserItem)+L"���"+strGiftName+
		L"�ˣ��˳𲻱��Ǿ��ӣ�ѡ��"+strHref+L"�����~" ,COLOR_GIFT) ;
}

CString HtmlBuild::GetPublicFlyText( IUserItem * pUserItem, CString strText )
{
	return GetPublicTips( L"", ChatUserItem(pUserItem)+L" ʹ�÷���˵��"+strText+GetCurrentTimeString() );
}

CString HtmlBuild::GetLuckyStarEnterRoom( IUserItem* pUserItem ) 
{
	CString strHtml = L"";
	if ( pUserItem->IsLuckyStar() )
	{
		std::wstring strModulePath = common::utility::systemhelper::Get179AppPath();
		common::CURLEncode urlEncode;
		strModulePath = urlEncode.URLEncodeLocalPath(strModulePath);
		std::wstring strLuckyStarGifPath = strModulePath + IMG_LUCKYSTAR_GIF_PATH;
		CString strTemp ;
		strTemp.Format( L"%s�����������ǡ� %s ������������ٱ����䡣" ,
			Img( strLuckyStarGifPath.c_str() ) , GetNameAndID(pUserItem) ) ;
		strHtml = Font( L"����" , COLOR_GIFT , Span(12, Bold(L"����ʾ���� "+strTemp)) ) ;
		strHtml += L"<BR>" ;
	}
	return strHtml ;
}

//���������ǵ���
CString HtmlBuild::GetLuckyStarBirth() 
{	
	return GetPrivateTips( L"����ʾ���� " , L"��ϲ���ٻ񡰳��������ǡ��ƺţ�ϵͳ���͸������Ž�����Ч����ȥ�����ɣ�" ,COLOR_GIFT )  ;
}

CString HtmlBuild::GetPrivateChangeVoiceRsp( IUserItem* pDstUserItem, uint16 unChangeVoiceID )
{
	CString strTemp = L"��ʹ�á�����֮������ " ;
	strTemp += PrivateUserItem( pDstUserItem ) ;
	strTemp += L" ���" ;

	IGiftItem* pGiftItem = GiftManager::GetInstance()->SearchGiftByID( unChangeVoiceID ) ;
	if ( pGiftItem != NULL )
	{
		strTemp += pGiftItem->GetName().c_str();
		strTemp += Img( pGiftItem->GetLargeImagePath().c_str() ) ;
	}

	return GetPrivateTips( L"����ʾ���� " , strTemp , COLOR_GIFT ) ;
}

CString HtmlBuild::GetPrivateStampRsp( IUserItem* pDstUserItem, uint16 unStampID )
{

	IGiftItem* pGiftItem = GiftManager::GetInstance()->SearchStampByID( unStampID ) ;
	CString strImg ;
	if ( pGiftItem != NULL )
	{
		strImg = Img( pGiftItem->GetSmallImagePath().c_str() ) ;
	}
	return GetPrivateTips( L"����ʾ���� " , L"������ "+ PrivateUserItem(pDstUserItem,FALSE) + L" Ϊ��"+ strImg  ,COLOR_GIFT ) ;
}

CString HtmlBuild::GetRequestPublicMicNotify( IUserItem * pSrcUserItem, uint8 unIndex )
{
	CString strName ;	
	strName.Format( L"%s�������Ϲ�������" ,GetNameAndID(pSrcUserItem) ) ;
	CString strAcceptHref ;
	strAcceptHref.Format( L"<a href=\"%s\" name=\"%s\" uuid=\"%d\" uindex=\"%d\" type=\"%d\">ͬ��</a>" ,
		L"" , pSrcUserItem->GetDecodeUserName().c_str() , pSrcUserItem->GetUserUIN() , unIndex, CLICK_TYPE_PUBLIC_ACCEPT ) ;
	CString strRefuseHref ;
	strRefuseHref.Format( L"<a href=\"%s\" name=\"%s\" uuid=\"%d\" uindex=\"%d\" type=\"%d\">�ܾ�</a>" ,
		L"" , pSrcUserItem->GetDecodeUserName().c_str() , pSrcUserItem->GetUserUIN() , unIndex, CLICK_TYPE_PUBLIC_REFUSE ) ;

	return  GetPrivateTips( L"����ʾ���� " ,strName + L" " + strAcceptHref+L" ���� "+strRefuseHref+L"��" , COLOR_OPERATE  ) ;
}

CString HtmlBuild::GetSofaUserHead( CSofaItem * pSofaItem )
{
	CString strVip = ListIconManager::GetIconPathByVipLevel(pSofaItem->GetLastVipLevel()).c_str();
	if (!strVip.IsEmpty())
	{
		strVip = Img(strVip);
	}

	CString strRich = L"";
	if (pSofaItem->GetLastRichLevel() > 0)
	{
		strRich = RichLevelManager::GetRichLevelImgPathByLevel(pSofaItem->GetLastRichLevel()).c_str();
		if (!strRich.IsEmpty())
		{
			strRich = Img(strRich);
		}
	}
	return strVip + strRich;
}

CString HtmlBuild::ChatSofaUserItem( CSofaItem * pSofaItem )
{
	CString strTemp ;
	if ( pSofaItem != NULL )
	{
		strTemp = GetSofaUserHead( pSofaItem ) ;		
		CString strNameHref ;
		CString strSofaNameAndID;
		if (pSofaItem->GetLast179ID() > MAX_SHOW_179ID)
		{
			strSofaNameAndID = common::utility::stringhelper::XMLEncode(pSofaItem->GetLastUserName()).c_str();
		}
		else
		{
			strSofaNameAndID.Format(L"%s(%u)", common::utility::stringhelper::XMLEncode(pSofaItem->GetLastUserName()).c_str(), pSofaItem->GetLast179ID());
		}
		strNameHref.Format(_T("<a href=\"%s\" name=\"%s\" uuid=\"%d\" type=\"%d\" title=\"%d\" class=\"user\" >%s</a>") , 
			L"" , common::utility::stringhelper::XMLEncode(pSofaItem->GetLastUserName()).c_str() ,
			pSofaItem->GetLastUserUIN() , CLICK_TYPE_NAME ,pSofaItem->GetLast179ID() ,
			strSofaNameAndID ) ;
		strTemp += strNameHref ;
	}
	return strTemp ;
}

CString HtmlBuild::GetEnterRoomGetUserList_Event( IUserItem * pUserItem, uint8 unIndex )
{
	CString strHtml ;
	strHtml = EventEnterMgr->GetEnterHtmlByIndex(unIndex);
	if ( !strHtml.IsEmpty() )
	{
		CString strTemp ;
		strTemp.Format( L" %s "  , GetNameAndID(pUserItem) ) ;
		strHtml.Replace( L"name" , strTemp ) ;
		strHtml += L"<BR>" ;

	}

	return strHtml ;
}

CString HtmlBuild::GetNameAndID( IUserItem * pUserItem )
{
	CString strTemp;
	if (pUserItem->GetUser179ID() > MAX_SHOW_179ID)
	{
		strTemp = pUserItem->GetDecodeUserName().c_str();
	}
	else
	{
		strTemp.Format(L"%s(%u)", pUserItem->GetDecodeUserName().c_str(), pUserItem->GetUser179ID());
	}

	return strTemp;
}

CString HtmlBuild::GetEnterRoomGetUserList_VIPLevelBlackDiamond( IUserItem * pUserItem )
{
	CString strHtml ;
	if (!pUserItem->IsBlinkEnter() && pUserItem->GetUserVipLevel() == core::VIPLEVEL_BLACKDIAMOND )
	{
		strHtml = EnterMgr->GetEnterHtmlByVipLevel( pUserItem->GetUserVipLevel() ) ;
		if ( !strHtml.IsEmpty() )
		{
			CString strTemp ;
			strTemp.Format( L" %s "  , GetNameAndID(pUserItem) ) ;
			strHtml.Replace( L"VipImage" , GetUserItemHeadImg( pUserItem ) ) ;
			//strHtml.Replace(L"RichLevelImage", GetUserItemRichLevelImg(pUserItem));
			strHtml.Replace( L"name" , strTemp ) ;
			strHtml += L"<BR>" ;
		}
	}
	return strHtml ;
}

CString HtmlBuild::GetSpeakerGame( CString& strText )
{
	CString strTemp;
	strTemp = Font( L"����" , _T("#0000FF"), Span(13, strText) ) ;
	strTemp += L"<BR>" ;

	return SystemMessageTitle() + strTemp;
}

CString HtmlBuild::GetRoomMidInputDefaultText( CString& strDefault )
{
	CString strTemp = Font( L"����" , L"#C2C2C2" , Span(12, strDefault) ) ;
	return strTemp ;
}

CString HtmlBuild::GetMarkInvite( CString & strSongerName )
{
	CString strTitle = Font( L"����" , L"#EF427B" , Span(13, Bold(CString(L"��������ۡ� "))) ) ;
	CString strHref;
	strHref.Format( L"<a href=\"%s\" name=\"%s\" uuid=\"%d\" type=\"%d\">ȥ����</a>" ,L"" ,strSongerName , GetCurInfo().unUIN, CLICK_TYPE_MARK );

	CString strTemp;
	strTemp.Format(L"����%s�����������ݳ��������� ", strSongerName);
	CString strRet = Font( L"����" , L"#EF427B" , Span(13, strTemp + strHref) ) ;

	return strTitle + strRet; 
}

CString HtmlBuild::GetMarkTips( const CString& strTitle , const CString& strValue , const CString& strColor/*=COLOR_NORMAL */ )
{
	CString strTemp = Font( L"����" , strColor , Span(13,Bold(strTitle)+strValue) ) ;
	strTemp += L"<BR>" ;
	return strTemp ;
}

CString HtmlBuild::GetSpeakerLuxury( SpeakerInfo& stSrcInfo, SpeakerInfo& stDstInfo, CString& strRoomName, uint16 unGiftID, uint16 unCount )
{
	IGiftItem * pGiftItem = GiftManager::GetInstance()->SearchGiftByID(unGiftID);
	if (pGiftItem != NULL)
	{
		CString strGiftName = pGiftItem->GetName().c_str();
		CString strUnit = pGiftItem->GetUnitName().c_str();

		CString strMessage;
		strMessage.Format(L"%d%s%s", unCount, strUnit, strGiftName);

		CString strRoom;
		strRoom.Format(L"\"%s\"�����", strRoomName);

		return SystemMessageTitle() + SpeakerLuckyMessage(strRoom) + SpeakerUserItem(stSrcInfo) 
			+ SpeakerLuckyMessage(CString(L"�͸�")) + SpeakerUserItem(stDstInfo) + SpeakerLuckyMessage(strMessage);
	}

	return L"";
}