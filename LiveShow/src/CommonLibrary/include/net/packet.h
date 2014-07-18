/**
* packet.h
* ���������ֽ���ת��
*
* @version 1.0 (06 ,10, 2008)
* @author reinhardt ken
*
*/
#pragma once

#include "..\Common.h"
#include <string>
#include <vector>
#include "..\include\utility\StringHelper.h"

namespace common
{
	namespace net
	{
		class COMMON_INTERFACE Packet
		{
		public:
			enum origin
			{
				from_cur,
				from_begin,
				from_end,
			};
		public:

			/*
			* ����buffer����һ��packet
			*/

			Packet(ByteBuf &buf) :data(buf.second), dataSize((uint32)buf.first)
			{
				cursor = data;
			}
			
			/*
			* ����buffer����һ��packet
			*/

			void Construct(ByteBuf &buf)
			{
				data=buf.second;
				dataSize=(uint32)buf.first;
				cursor = data;
			}

			/*
			* ����buffer
			*/

			byte const *Data() 
			{
				return data;
			}

			/*
			* �����α��ƶ�����
			*/

			uint32 Size() 
			{
				return (uint32)(cursor - data);
			}

			/*
			* �����α�ʣ���ƶ�����
			*/

			uint32 FreeSize()
			{
				return (uint32)(data + dataSize - cursor);
			}

			/*
			* �ƶ��α�
			* @param [in] off:�ֶ�origin_��ƫ��
			* @param [in] origin_:ƫ����ʼλ��
			*/

			void MoveCur(int off, origin origin_);

			/*
			* packһ��string (utf-8)
			*/

			Packet &operator <<(std::string &str) 
			{
				return operator <<(str.c_str());
			}

			/*
			* packһ��wstring
			*/

			Packet &operator <<(std::wstring &str)
			{
				std::string des = common::utility::stringhelper::UnicodeToUTF8(str);
				operator <<(des.c_str());
				return *this;
			}

			/*
			* packһ��uint8
			*/

			Packet &operator <<(uint8 b);

			/*
			* packһ��uint16
			*/

			Packet &operator <<(uint16 w);

			/*
			* packһ��uint32
			*/

			Packet &operator <<(uint32 dw);

			/*
			* packһ��uint64
			*/

			Packet &operator <<(uint64 ddw);

			/*
			* packһ��char*
			*/

			Packet &operator <<(char const *str);

			/*
			* packһ����byte��vector
			*/

			Packet &operator<<(std::vector<byte>& vec)
			{
				*this<<(uint16)(vec.size()+1);
					for(uint32 i=0;i<vec.size();i++)
						*this<<vec[i];
					*this<<(uint8)0;
					return *this;
			}

			/*
			* pack��size��С��buffer
			*/

			void WriteData(byte const  *buf, uint32 size);

			/*
			* unpackһ��uint8
			*/

			Packet &operator >>(uint8 &b);

			/*
			* unpackһ��uint16
			*/

			Packet &operator >>(uint16 &w);

			/*
			* unpackһ��uint32
			*/

			Packet &operator >>(uint32 &dw);

			/*
			* unpackһ��uint64
			*/

			Packet &operator >>(uint64 &ddw);

			/*
			* unpack�ַ���
			*/

			Packet &operator >>(char const *&str);

			/*
			* unpack�ַ���
			*/

			Packet &operator >>(unsigned char const *&str);

			/*
			* unpack�ַ���
			*/

			Packet &operator >>(char *str);

			/*
			* unpack�ַ�����string (utf-8)
			*/

			Packet &operator >>(std::string &str);

			/*
			* unpack�ַ�����wstring
			*/

			Packet &operator >>(std::wstring &str) 
			{
				std::string temp;
				operator >>(temp);
				str = common::utility::stringhelper::UTF8ToUnicode(temp);
				return *this;
			}

			/*
			* unpack�ַ�����byte��vector
			*/

			Packet &operator >>(std::vector<byte>& vec);

			/*
			* ����cursor
			* @param n:ʣ��size
			*/

			byte const* GetCursor();

			/*
			* ����buffer��С
			*/

			void SetDataSize(uint32 size);

		protected:
			byte *data;
			byte *cursor;
			uint32 dataSize;
		};

		#define MAX_PACKET_SIZE 65535

		class COMMON_INTERFACE OutPacket : public Packet
		{
		public:
			OutPacket():Packet(ByteBuf(sizeof(realData),realData)){}

		protected:
			byte realData[MAX_PACKET_SIZE];
		};

		class COMMON_INTERFACE InPacket : public Packet
		{
		public:
			InPacket(ByteBuf &buf):Packet(buf){}
		};
	}
}