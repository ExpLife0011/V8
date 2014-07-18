#pragma  once
#include "coredefine.h"

namespace room
{
	enum ENM_GIFT_SENDTYPE
	{
		SENDTYPE_NONE			= 0x00,	//��Ҫ��������´��ڲ���
		SENDTYPE_OTHERSINGLE	= 0x01,	//�Ե���������ʹ��
		SENDTYPE_OTHERALL		= 0x02,	//�Է�����������ʹ�ã������˻������й���Ա��
		SENDTYPE_SELF			= 0x03,	//ֻ�ܶ��Լ�ʹ��
	};

	struct gift_info
	{
		uint16 unID;
		uint16 unIndex;
		std::wstring strName;
		std::wstring strRichName;		//�������������ݳ��������õ�
		std::wstring strDesc;
		std::wstring strUnitName;
		uint32 unPrice;
		uint32 unDstEarn;
		std::wstring strSmallImagePath;
		std::wstring strLargeImagePath;
		uint8 unGiftType;				//ENM_GiftType
		uint8 unSendType;				//ENM_GIFT_SENDTYPE
		bool bTempNotice;
		bool bGiftWords;
		uint8 unDstType;				//ENM_GiftDstType
		std::wstring strCatalog;
		std::wstring strType;			//�����е������ַ�����һ�㲻��
		std::wstring strSendBtn;		//Tip�ϵ�ʹ�ð�ť����
		std::wstring strPrescription;	//ʱЧ����
		std::wstring strSendDesc;		//��������
		std::wstring strGiftWords;
		CTime tmBeginTime;				//��Ч�ڿ�ʼʱ��
		CTime tmEndTime;				//��Ч�ڽ���ʱ��
		bool bInUse;					//�Ƿ��ϼ�

		gift_info() : strSendBtn(L"�������"), strPrescription(L""), strSendDesc(L"����"), bGiftWords(false), strGiftWords(L""), tmBeginTime(1970,1,1,12,0,0),tmEndTime(2100,1,1,0,0,0),bInUse(true)
		{

		}
	};
}

struct IGiftItem
{
	virtual uint16 GetID()							= 0;
	virtual uint16 GetIndex()						= 0;
	virtual std::wstring GetName()					= 0;
	virtual std::wstring GetRichName()				= 0;
	virtual std::wstring GetDesc()					= 0;
	virtual std::wstring GetUnitName()				= 0;
	virtual uint32 GetPrice()						= 0;
	virtual uint32 GetDstEarn()						= 0;
	virtual std::wstring GetSmallImagePath()		= 0;
	virtual std::wstring GetLargeImagePath()		= 0;
	virtual uint8 GetGiftType()						= 0;
	virtual uint8 GetSendType()						= 0;
	virtual void SetGiftInfo(room::gift_info & giftinfo)	= 0;
	virtual bool IsNeedTempNotice()					= 0;
	virtual bool IsNeedGiftWords()					= 0;
	virtual std::wstring GetCatalogName()			= 0;
	virtual std::wstring GetStrType()				= 0;
	virtual uint8 GetDstType()						= 0;
	virtual std::wstring GetStrSendBtn()			= 0;
	virtual std::wstring GetStrPrescription()		= 0;
	virtual std::wstring GetStrSendDesc()			= 0;
	virtual std::wstring GetStrGiftWords()			= 0;
	virtual CTime GetBeginTime()					= 0;
	virtual CTime GetEndTime()						= 0;
	virtual bool IsInUse()							= 0;
};