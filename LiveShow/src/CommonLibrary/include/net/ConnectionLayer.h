/**
* ConnectionLayer.h
* 
*
* @version 1.0 (06 ,04, 2008)
* @author plushu
*
*/
#pragma  once

#include "..\Common.h"
#include "ConnectionCommon.h"

namespace netlayer
{
	class ConnectionLayerImpl;

	class COMMON_INTERFACE ConnectionLayer
	{
	public:
		ConnectionLayer();
		virtual ~ConnectionLayer();

		/*
		* ����һ��ͨѶʵ��
		* @param [in] enType:��������
		* @param [in,out] oBuf:ѭ��buffer
		* @param [in] oAddr:Ŀ�ĵ�ַ
		* @param [in] oProxyAddr:�����ַ
		* @param [in] strName:�����û���
		* @param [in] strPass:��������
		* @param [in] strDomain:������
		* @return ����������ʾ (����0��ʾʧ��)
		*/

		unsigned int Create(COMM_TYPE enType, MSG_BUF& oBuf,
								const IpPort& oAddr = IpPort(), 
								const IpPort& oProxyAddr = IpPort(), 
								const std::string& strName = "", 
								const std::string& strPass = "",
								const std::string& strDomain = "");
		/*
		* ɾ��һ������
		* @param [in] uiID:Createʱ���ص����ӱ�ʾ
		*/

		void Delete(unsigned int uiID);

		/*
		* ��������
		* @param [in] uiID:Createʱ���ص����ӱ�ʾ
		* @param [in] oPacket:���͵İ�
		* @param [in] oAddr:Ŀ�ĵ�ַ
		* @return ���ط����Ƿ�ɹ�
		*/

		bool SendTo(unsigned int uiID, Packet& oPacket, const IpPort& oAddr = IpPort());

	private:

		ConnectionLayerImpl* m_pImpl;
	};
}; 