#pragma once

namespace Hall
{
	enum 
	{
		MESSAGE_VALUE_HALL_MODULE_BEGIN = MESSAGE_VALUE_HALL_BEGIN,

		MESSAGE_VALUE_HALL_OPENSOUND,//�Ƿ������  param0:  1:������  0;�ر�����
		MESSAGE_VALUE_HALL_HEAD_IMAGE_UPDATE,  //����ͷ��ͼƬ  param0: unUIN
		MESSAGE_VALUE_HALL_RES_UPDATE, //�����ļ��Ѹ���

		MESSAGE_VALUE_HALL_MODULE_END,
	};

	enum
	{
		SERVICE_VALUE_HALL_MODULE_BEGIN = SERVICE_VALUE_HALL_BEGIN,

		SERVICE_VALUE_HALL_GET_WEBINTERFACEURL,  //&WebInterfaceUrl
		SERVICE_VALUE_HALL_GET_TOKEN_URL,  //&std::wstring
		SERVICE_VALUE_HALL_OPEN_TOKEN_URL,  //&std::wstring
		SERVICE_MSGBOX_SHOW,  //&MsgBox179 
		SERVICE_VALUE_HALL_GET_HEAD_IMAGE_PATH,  //&HeadImage    ע��HeadImage.m_isGuestΪtrueʱ HeadImage.m_unUIN��HeadImage.m_bMan��Ч���ɲ��� 
		SERVICE_VALUE_HALL_UPDATE_HEAD_IMAGE_PATH,  //&HeadImage ע��HeadImage.m_isGuestΪtrueʱ HeadImage.m_unUIN��HeadImage.m_bMan��Ч���ɲ��� 

		SERVICE_VALUE_HALL_END,

	};

	enum E_HallEventValue
	{

		event_value_hall_module_begin = EVENT_VALUE_HALL_BEGIN,

		EVENT_VALUE_HALL_CREATEANDSHOW, //��������

		EVENT_VALUE_HALL_ENTER_ROOM_REQUEST,  //������� param0: roomId
		EVENT_VALUE_HALL_HEAD_UPLOAD,         //ͷ���ϴ� param0: &HeadSetting
		EVENT_VALUE_HALL_ACTIVATE_SHOW,       //����������ʾ
		EVENT_VALUE_HALL_InLineURL_SHOW,      //�����Ҳ����Ƕ����  (�����Ҳ���Ƕҳ��)  param0: &InLineUrl

		EVENT_VALUE_HALL_END,
	};
		

	struct WebInterfaceUrl
	{
		//SERVICE_VALUE_HALL_GET_WEBINTERFACEURL

		std::wstring m_WebInterfaceKeyName;  //�����web�ӿڼ�������  ��ο�SysSet.ini��[WebInterfaceUrl]�¼�������
		bool m_WebWithPara;   //�Ƿ���web�ӿ�֮�����,  trueΪ����(url֮��Ӳ���uin,tokentype,token)   �� falseΪ����
		std::wstring m_WebInterfaceUrl;  //���ص�url , 
		WebInterfaceUrl():m_WebWithPara(true)
		{
		}
	};

	struct HeadImage
	{
		//SERVICE_VALUE_HALL_GET_HEAD_IMAGE_PATH
		//SERVICE_VALUE_HALL_UPDATE_HEAD_IMAGE_PATH

		uint32 m_unUIN;   //����ͷ��ͼƬ��unUIN
		bool m_bMan;      //����ͷ��ͼƬ���û��Ա�  trueΪ��  falseΪŮ
		bool m_isGuest;   //�Ƿ�Ϊ�ο�
		std::wstring m_HeadImagePath;  //���ص�ͷ��ͼƬ·��
	};	
	
	struct MsgBox179
	{
		//SERVICE_MSGBOX_SHOW		

		enum  BoxStyle
		{
			//��ͼ��ļ������� 
			MSGBOX_OK_ONE_STRING                    = 50,  //һ�����֣�ȷ��
			MSGBOX_OK_TWO_STRING,                         //�������֣�ȷ��
			MSGBOX_OK_ONE_STRING_WITH_LINK,				  //һ�����֣�һ�����ӣ�ȷ��
			MSGBOX_OK_TWO_STRING_WITH_LINK,				  //�������֣�һ�����ӣ�ȷ��
			//��ͼ��ļ�������
			MSGBOX_ICO_OK_ONE_STRING,					  //ͼ�꣬һ�����֣�ȷ��
			MSGBOX_ICO_OK_TWO_STRING,					  //ͼ�꣬�������֣�ȷ��
			MSGBOX_ICO_OK_CANCEL_ONE_STRING,			  //ͼ�꣬һ�����֣�ȷ����ȡ��
			MSGBOX_ICO_OK_CANCEL_TWO_STRING,			  //ͼ�꣬�������֣�ȷ����ȡ��
			//�οͲ�����ʾ����
			MSGBOX_GUEST_OPERATE,						  //�οͲ�����ʾ���ձ���ʽ
			//��©����ʽ������ӽ���
			MSGBOX_OK_THREE_STRING,                       //�������֣�ȷ��
			MSGBOX_OK_THREE_STRING_WITH_LINK,             //�������֣�һ�����ӣ�ȷ��
		};

		enum BoxICO
		{
			//ͼ��ļ�������
			ICONTYPE_WARNING                = 80,          //����ͼ��
			ICONTYPE_BINGO,								   //��ͼ��
			ICONTYPE_ERROR,								   //����ͼ��
		};

		std::wstring m_sMessage1;  //��ʾ����
		std::wstring m_sMessage2;  //��ʾ����   (��ʾ������Ϊ��2��ʱ��Ч)
		std::wstring m_sMessage3;  //��ʾ����   (��ʾ������Ϊ��3��ʱ��Ч)
		std::wstring m_linkText;  //��������   (��ʾ������Ϊ������ʱ��Ч)
		std::wstring m_linkLocal; //���ӵ�ַ   (��ʾ������Ϊ������ʱ��Ч)			
		BoxStyle m_boxStype; //��ʾ������
		BoxICO m_boxICO;     //��ʾ��ͼ��  (��ʾ������Ϊ��ͼ��ʱ��Ч)
		std::wstring m_sTitle;    //��ʾ�����
	};

	struct HeadSetting : public ExtraInfo
	{
		//EVENT_VALUE_HALL_HEAD_UPLOAD

		HWND m_parentHwnd;
	};

	struct InLineUrl : public ExtraInfo
	{
		//EVENT_VALUE_HALL_InLineURL_SHOW
		std::wstring m_InLineUrl;    //�����Ҳ����Ƕ����url
	};
	
};