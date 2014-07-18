/*
@file:		JJEncrypt.h
@purpose:	����/���ܺ�����
@version:	1.0 2007.6.15 create danhq
*/

#pragma once

class TEAEncryptor
{
public:
	static BYTE DEF_KEY[16];

	/// TEA����
	/*
	@param	pInBuffer IN			Ҫ���ܵ�buffer
	@param	nInBufferLen IN			Ҫ���ܵ�buffer�ĳ���
	@param	pOutBuffer IN			��ż��ܽ����buffer
	@param	pnOutBufferLen IN OUT	��ż��ܽ����buffer�ĳ���(IN)�����ؼ��ܽ����ʵ�ʴ�С(OUT)
	@param	pKey IN					���ܵ�key,16byte
	@param	uRounds IN				TEA��������������Խ��ȫ��Խ�ߣ��������ٶ�Խ��
	@remark	���ܽ����ȼ���ǰ�ĳ��ȴ�1-8��byte,���Խ��� len(��ż��ܽ����buffer) = len(Ҫ���ܵ�buffer) + 8
	*/
	static BOOL TEAEncrypt(BYTE* pInBuffer, int nInBufferLen, BYTE* pOutBuffer, int* pnOutBufferLen, BYTE pKey[16] = DEF_KEY, UINT uRounds = 16);

	/// TEA����
	/*
	@param	pInBuffer		IN Ҫ���ܵ�buffer
	@param	nInBufferLen	IN Ҫ���ܵ�buffer�ĳ���
	@param	pOutBuffer		IN ��Ž��ܽ����buffer
	@param	pnOutBufferLen	IN OUT ��Ž��ܽ����buffer�ĳ���(IN)�����ؽ��ܽ����ʵ�ʴ�С(OUT)
	@param	pKey			IN ���ܵ�key,16byte,����ͼ���ʱ����ͬ
	@param	uRounds			IN ����,����ͼ���ʱ����ͬ
	@remark	��Ž��ܽ����buffer�ĳ��� ����Ҫ >= (Ҫ���ܵ�buffer�ĳ��� - 1)
	*/
	static BOOL TEADecrypt(BYTE* pInBuffer, int nInBufferLen, BYTE* pOutBuffer, int* pnOutBufferLen, BYTE pKey[16] = DEF_KEY, UINT uRounds = 16);

};
