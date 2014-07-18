/*****************************************************************************
Module :     URLEncode.h
Notices:     Written 2002 by ChandraSekar Vuppalapati
Description: H URL Encoder
			URL Encode/Decode ��CURLEncode������ͷ�ļ�                                                    
			����URL Encode ������ո�ת��Ϊ %20��URL Decode���� �罫%20ת��Ϊ�ո� 
			֧��std::string��std::wstring�������͵Ĳ���.
*****************************************************************************/
#ifndef __CURLENCODE_H_
#define __CURLENCODE_H_

#include <string>
#include "../Common.h"

namespace common 
{
	/*
	* URL Encode/Decode ��CURLEncode
	* ����URL Encode ������ո�ת��Ϊ %20��URL Decode���� �罫%20ת��Ϊ�ո�
	* ֧��std::string��std::wstring�������͵Ĳ���.
	*/
	class COMMON_INTERFACE CURLEncode
	{
	public:
		CURLEncode() { };
		virtual ~CURLEncode() { };
		
		/*
		* �Դ���vData����URL Encode ������ո�ת��Ϊ %20
		* ��IE�������URLת������
		* @param [in] const std::string& vData ��ת�����ַ���
		* @return std::string ת������ַ���
		*/
		std::string URLEncode(const std::string& vData);

		/*
		* �Դ���vData����URL Encode ������ո�ת��Ϊ %20
		* ��IE�������URLת������
		* @param [in] const std::wstring& vData ��ת�����ַ���
		* @return std::wstring ת������ַ���
		*/
		std::wstring URLEncode(const std::wstring& vData);
		
		/*
		* �Դ���vData����URL Decode ������%20��ת��Ϊ �ո�
		* ��IE�������URLת������
		* @param [in] const std::wstring& vData ��ת�����ַ���
		* @return std::wstring ת������ַ���
		*/
		std::wstring URLDecode(const std::wstring& vData);
		
		/*
		* �Դ���vData����URL Decode ������%20��ת��Ϊ �ո�
		* ��IE�������URLת������
		* @param [in] const std::string& vData ��ת�����ַ���
		* @return std::string ת������ַ���
		*/
		std::string URLDecode(const std::string& vData);
		
		/** �Ա���·������URLEncode,��Ҫ����������еļ��ر���html��
		* ���ﲻ��Ҫ���������ַ���Encodeֻ��Ҫ���������ַ���Encode
		* ��:%,#��
		* @param [in] const std::wstring& vData ��ת�����ַ���
		* @return std::wstring.
		*/
		std::wstring URLEncodeLocalPath(const std::wstring& vData);

	private:
		static std::string csUnsafeString;
		std::string decToHex(const char &num, const int &radix);
		bool isUnsafe(const char &compareChar);
		std::string convert(const char &val);

		inline BYTE toHex(const BYTE &x){ return x > 9 ? x + 55: x + 48; }
		inline BYTE fromHex(const BYTE &x){ return x > 64 ? x - 55 : x - 48; }
	};
}

#endif //__CURLENCODE_H_