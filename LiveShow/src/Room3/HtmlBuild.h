#pragma once
#include "coredefine.h"
#include "usermanager/useritem.h"
#include "GlobalRoomDefine.h"
using namespace core;

class RoomOption ;
class RoomBusiness ;
class CSofaItem ;
class HtmlBuild
{
public:	
	HtmlBuild( RoomBusiness* pRoomBusiness ) ;
	CString GetRequestP2PNotify( IUserItem* pSrcUserItem ) ;
	CString GetRequestPublicMicNotify( IUserItem * pSrcUserItem, uint8 unIndex );
	CString GetOpenPrivateRspNoPermission() ;
	CString GetOpenPrivateRspIsFull() ;
	CString GetPublicStamp( IUserItem* pSrcUserItem ,IUserItem* pDstUserItem , uint16 unStampID ) ;
	CString GetPrivateStamp( IUserItem* pSrcUserItem , uint16 unStampID ) ;
	CString GetPrivateStampRsp( IUserItem* pDstUserItem, uint16 unStampID );
	CString GetPrivateMicNotify( IUserItem* pSrcUserItem  ) ;
	CString GetPublicChangeVoice( IUserItem* pSrcUserItem ,IUserItem* pDstUserItem , uint16 unChangeVoiceID );
	CString GetPrivateChangeVoice( IUserItem* pSrcUserItem , uint16 unChangeVoiceID );
	CString GetPrivateChangeVoiceRsp( IUserItem* pDstUserItem, uint16 unChangeVoiceID );

	CString GetPrivateFireWork( IUserItem* pSrcUserItem ) ;
	CString GetPrivateSlavo( IUserItem* pSrcUserItem ) ;
	CString GetPublicFireWork( IUserItem* pSrcUserItem) ;
	CString GetPublicSlavo( IUserItem* pSrcUserItem ) ;
	CString GetGiftLucky( uint32 unSrcUIN ,uint32 src179ID ,CString& strSrcHead ,
		std::wstring strSrcName ,uint16 unGiftID , uint16	unLuckyTimes ,uint32 unLuckyMoney ) ;
	CString GetPrivateNormalGift( IUserItem* pSrcUserItem ,uint16 unGiftID , uint16 unCount ) ;

	CString GetPublicNormalGift( GiftInfo& giftinfo  , uint32 unGiftCount ) ;
	CString GetPublicSheChiGift( IUserItem* pSrcUserItem ,IUserItem* pDstUserItem , uint16 unGiftID , uint32 unCount ) ;

	CString GetChat(IUserItem* pSrcUserItem ,IUserItem* pDstUserItem ,
		CString& strText ,MessageFont& stFont , bool bPublic , bool bReplaceSelf , bool bAutoMsg = FALSE) ;	
	CString GetPrivateTips( const CString& strTitle , const CString& strValue , const CString& strColor=COLOR_NORMAL ) ;
	CString GetPublicTips( const CString& strTitle , const CString& strValue , const CString& strColor =COLOR_NORMAL ) ;
	CString GetOfficialNocice( CString& strValue ) ;
	CString GetNotice( const CString& strValue ) ;
	CString GetNotice(const CString& strValue , MessageFont& stFont) ;
	CString GetTempNotice( uint32 un179ID ,CString strSrcDecodeName ,const CString& strValue , MessageFont& stFont ) ;
	CString GetGiftStar(IUserItem* pUserItem, uint16 unGiftID);
	CString GetEnterRoomGetUserList_VIPLevelTop( IUserItem* pUserItem ) ;		//����ʹ�
	CString GetEnterRoomGetUserList_VIPLevelDiamond(IUserItem* pUserItem);    //��ʯ�ʹ�
	CString GetEnterRoomGetUserList_VIPLevelBlackDiamond(IUserItem * pUserItem);
	CString GetEnterRoomGetUserList_Crest( IUserItem * pUserItem ) ;
	CString GetEnterRoomGetUserList_Blink( IUserItem * pUserItem ) ;
	CString GetEnterRoomGetUserList_LuckyStar( IUserItem* pUserItem ) ;
	CString GetEnterRoomGetUserList_Event(IUserItem * pUserItem, uint8 unIndex);
	CString GetEnterRoom( IUserItem * pUserItem ) ;
	CString GetLeaveRoom( IUserItem* pUserItem ) ;
	CString GetVipName( uint8 nVipLevel ) ;
	CString GetTitleName( uint16 nTitleType ) ;
	CString GetSpeaker(CString& strText, MessageFont& stFont, SpeakerInfo& stInfo);
	CString GetSpeakerLucky( CString& strSrcName ,CString& strSrcLuckyHead , uint32  src179ID , 
		uint16	unLuckyTimes , uint32 unLuckyMoney ,uint16 unGiftid ) ;
	CString GetSpeakerLucky(CString& strText, SpeakerInfo& stInfo, uint16 unGiftID);
	CString GetSpeakerPlutusAward(CString& strText, SpeakerInfo& stInfo, uint16 unGiftID);
	CString GetSpeakerSystem(CString& strText);
	CString GetSpeakerGame(CString& strText);
	CString GetSpeakerLuxury(SpeakerInfo& stSrcInfo, SpeakerInfo& stDstInfo, CString& strRoomName, uint16 unGiftID, uint16 unCount);
	CString GetWelecomeWords( IUserItem* pOwnerItem , CString& strText , MessageFont& stFont ) ; //��������ʱ�Ļ�ӭ��
	CString GetActorAutoSpeakWords(IUserItem* pUserItem, CString& strText); //�����Զ����Դ�
	CString GetAgentAutoSpeakWords(IUserItem* pUserItem, CString& strText);//�����Զ����Դ�
	CString OnNotifyPlutusAward( uint32 srcuin , uint32 un179ID , std::wstring& strDecodeName  , 
		std::wstring strRoomName ,uint16 nSelfTitleLevel , int nNumber , uint16 unGiftID ) ;			//����
	CString GetUserHead( IUserItem* pUserItem ) ;			//��ȡ��ʾ����ǰ����Ϣ
	CString GetSpeakerFirework(CString& strText,SpeakerInfo& stInfo);
	CString GetSpeakerSalute(CString& strText, SpeakerInfo& stInfo);
	CString GetUserItemHeadImg( IUserItem* pUserItem , BOOL bStamp = TRUE ) ; //����û���ǰ���º͹�ͼƬ
	CString GetUserItemRichLevelImg(IUserItem* pUserItem); //����û��ĸ����ȼ�ͼ��
	CString GetAutoWelcome( IUserItem* pUserItem , CString& strText ) ;
	CString GetVisistorRegistor( IUserItem* pUserItem , CString& strText ) ;

	CString GetGiftDateString( uint32 unTime ) ;
	CString GetPublicFlyText( IUserItem * pUserItem, CString strText);
	CString GetLuckyStarEnterRoom( IUserItem* pUserItem ) ;
	CString GetLuckyStarBirth() ; //���������ǵ���
	CString GetSofaUserHead(CSofaItem * pSofaItem);
	CString ChatUserItem( IUserItem* pUserItem ) ;
	CString ChatSofaUserItem(CSofaItem * pSofaItem);
	CString GetNameAndID(IUserItem * pUserItem);			//�û���+179ID��179ID����6λ����ʾ
	CString GetRoomMidInputDefaultText(CString& strDefault);
	CString GetMarkInvite(CString & strSongerName);
	CString GetMarkTips( const CString& strTitle , const CString& strValue , const CString& strColor=COLOR_NORMAL ) ;
private:
	CString ChatUser( uint32 nSelfUUID , IUserItem* pUserItem , bool bReplaceSelf  ) ;
	//CString ChatUserItem( IUserItem* pUserItem ) ;
	CString StampRightUserItem( IUserItem* pUserItem ) ;	
	CString PrivateUserItem( IUserItem* pUserItem , BOOL bStamp = TRUE ) ;
	CString ChatMessage( CString& strText , MessageFont& stFont , uint32 srcUin, bool bAutoMsg = FALSE) ;
	CString Img( CString strImgPath ) ;
	CString ItaLic( const CString& strValue ) ;
	CString UnderLine(const CString& strValue ) ;
	CString Bold(const CString& strValue ) ;
	CString Span(int nFontSize , const CString& strColor ,const CString& strValue ) ;
	CString Span(int nFontSize ,const CString& strValue ) ;
	CString Font(const CString& strFont , const CString& strColor , const CString& strValue ) ;
	CString Marquee(const CString& strValue ) ;
	CString SpeakerUserItem( CString& strSrcName , CString& strSrcHead , uint32 un179ID ,COLORREF cf = RGB(0,153,255) ) ;
	CString SpeakerUserItem( SpeakerInfo& stInfo, COLORREF cf = RGB(0,153,255) ) ;
	CString SpeakerMessage( CString& strText , MessageFont& stFont );
	CString SpeakerSystemMessage( CString& strText );
	CString SpeakerLuckyMessage( CString& strText );
	CString SystemMessageTitle();
	CString SpeakerFireworkTitle();
	CString SpeakerSaluteTitle();

	CString GetColorString( COLORREF cf ) ;			//��ɫת�����ַ���
	CString GetCurrentTimeString() ;				//�õ�ʱ��

	CString GetFontText( MessageFont& stFont ,const CString& strText ) ; 
	CString GetLuckyTimesPngPath( uint16 unLuckyTimes ) ;
	RoomBusiness* m_pRoomBusiness ;
};