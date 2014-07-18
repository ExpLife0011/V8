#ifndef __PACKET_H__
#define __PACKET_H__
#ifdef _DEBUG
//#include <vld.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include "MyAssert.h"
#include "Common.h"

class COMMON_OUT_CLASS Packet
{
public:
	Packet(SInt32 iID, UInt32 iContentLen=0):
		  m_pPacketContent(NULL),
		  m_iPacketLen(iContentLen),
		  m_iID(iID),
		  m_iRemoteIP(0),
		  m_sRemotePort(0),
		  m_iOffset(0),
		  m_iRefCount(0)
	  {
		  if (0!=m_iPacketLen)
		  {
			  try
			  {
				  m_pPacketContent=new UInt8[m_iPacketLen];
			  }
			  catch (...)
			  {
				  LostTrace("Packet �����ڴ�ʧ��....���캯��\n");
			  }
		  }
	  }

	  virtual ~Packet()
	  {
		  SAFE_DELETEA(m_pPacketContent);
		  m_iPacketLen = 0;
		  m_iOffset    = 0;
		  m_iID        = -1;
		  m_iRemoteIP  = 0;
		  m_sRemotePort= 0;
		  m_iRefCount  = 0;
	  }

	  inline void	setContent(UInt8* pContent,UInt32 iContentLen)
	  {
		  SAFE_DELETEA(m_pPacketContent);
		  try
		  {
			  m_pPacketContent=new UInt8[iContentLen];
			  ::memcpy(m_pPacketContent,pContent,iContentLen);

			  m_iPacketLen  = iContentLen;
			  m_iOffset     = 0;
		  }
		  catch (...)
		  {
		  	 m_pPacketContent = NULL;
			 LostTrace("Packet setContent �����ڴ�ʧ��...\n");
		  }
	  }
	  
	  inline void   setContentPtr(UInt8* pContent,UInt32 iContentLen)
	  {
		  m_pPacketContent = pContent;
		  m_iPacketLen     = iContentLen;
		  m_iOffset        = 0;
	  }

	  inline SInt32	getSocketID()				{	return m_iID;	}
	  inline UInt8*	getPacketContent()			{   return m_pPacketContent; }
	  inline UInt32	getPacketLen()				{	return m_iPacketLen; }

	  //���õ��������ֽ���
	  inline void		setRemoteAddr(UInt32 iRemoteIP,UInt16 sRemotePort)  
	  { 
		  m_iRemoteIP=iRemoteIP;
		  m_sRemotePort=sRemotePort;	
	  }

	  //��ȡ���������ֽ���
	  inline void		getRemoteAddr(UInt32& iRemoteIP,UInt16& sRemotePort)
	  { 
		  iRemoteIP		=	m_iRemoteIP; 
		  sRemotePort	=	m_sRemotePort;	
	  }

	/******************���ߺ���*******************/
	inline  UInt8*		getPaddingContentPtr()			{ return m_pPacketContent+m_iOffset;}
	inline  UInt8*		getOriginalContentPtr()			{ return m_pPacketContent; }
	inline  UInt32		getCurOffset()					{ return m_iOffset;}
	inline  void		increaseOffset(UInt32 iLen)		{ m_iOffset+=iLen; }
	inline  void		setCurOffset(UInt32 iOffset)	{ m_iOffset=iOffset; }

	Bool				checkBytesLeft(UInt32 iLenLeft);
	void                writeUInt8(UInt8 cValue);
	UInt8               readUInt8();
	void				writeUInt16(UInt16 sValue);
	UInt16				readUInt16();
	void				writeUInt32(UInt32 iValue);
	UInt32				readUInt32();
	void				writeUInt64(UInt64 lValue);
	UInt64				readUInt64(); 
	void				writeByteArray(const UInt8* pData, UInt32 iDataLen);
	bool  				readByteArray(UInt8* pData, UInt32 iDataLen);


	//���ü�����1
	void                 AddReference();

	//���ü�����1, ����true��ʾ�ڴ���Ի��ջ��Ѿ����ͷ�
	void                 RemoveReference();

	SInt32				 GetReference()				 { return m_iRefCount; }
	
	void				 resetOffset()				 { m_iOffset=0; }
protected:

	UInt32		    m_iOffset;		  //���ڽ��й������ͽ�������ƫ����;
	UInt8*			m_pPacketContent; //ָ�����ݰ��ڴ��ַ��ָ��;
	UInt32			m_iPacketLen;     //���ݰ����ܳ���;

	SInt32			m_iID;            //�����ݰ������Ǹ�Socket ID�Ͻ����շ�;
	UInt32			m_iRemoteIP;	  //�����ߵ�IP��ַ��  //�����ֽ���
	UInt16			m_sRemotePort;	  //�����ߵĶ˿ںţ� //�����ֽ���

private:

	SInt32          m_iRefCount;
};

#define     BINARY_PACKET_HEADER_LEN	               4  

class COMMON_OUT_CLASS BinaryPacket
{
public:
	  BinaryPacket():
		  m_sVersion(0),
		  m_sPacketType(0)
	  {}

	  virtual ~BinaryPacket(){}
	  
	  static  Packet*       makePacket(SInt32 iID, UInt16 sVersion, UInt16 sPacketType, UInt32 iBodylen);
	  virtual Bool          parserPacket(Packet* pPacket);

	  inline  UInt16		getVersion()	{ return m_sVersion; }
	  inline  UInt16		getPacketType() { return m_sPacketType; }

protected:
	
	UInt16					m_sVersion;         //�汾��;                             2B
	UInt16					m_sPacketType;		//��������;                           2B
};
#endif //__PACKET_H__

