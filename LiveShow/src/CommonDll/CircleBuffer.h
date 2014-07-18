#pragma once

#include "Common.h"
#include "MyAssert.h"

template<class T, UInt32 SIZE=256>
class CircleBuffer
{
public:

	//����������ڴ�ָ��(��VDATA)������һ����ʼ�������ٸı�
	explicit CircleBuffer(); 

	~CircleBuffer();

	inline UInt32   size()        { return SIZE;                           }  
	inline bool     empty()       { return m_iNextReadPos==m_iNextWritePos; } 


	/*
	* �����ݷ��뻺�壬
	* @param p Ҫ���뻺������������ʼָ��
	* @param len Ҫ���뻺���������ݳ���
	* @returnCode bool 
	*   true  : ����ɹ�
	*   false : ����ʧ�ܣ���������
	*/
	bool            push_back(T pData, UInt32 iLen, UInt32 iType);

	/*
	* ����������һ��Ҫ������ȡ����
	* @param p �������ݴ�ŵ���ʼָ��
	* @param len pָ�򻺳������ȣ��������ݳ���
	* @returnCode bool 
	*   true  : �����ɹ�
	*   false : ����ʧ�ܣ�p�����С�������߻���������
	*/
	bool            pop_front(T &pData, UInt32& iLen, UInt32& iType);

private:  

	typedef struct _VDATA
	{
		T        pData;
		UInt32   iDataLen;
		UInt32   iDataType;
	}VDATA;

	//�������ƺͿ�������
	CircleBuffer(CircleBuffer& cycleBufer);
	CircleBuffer&  operator=(CircleBuffer& cycleBufer);

private:
	UInt32          m_iNextReadPos;       //��һ��Ҫ������λ��
	UInt32          m_iNextWritePos;      //��һ��Ҫд����λ��
	VDATA           m_pVDATA[SIZE];       //��¼����ָ������
};

template<class T, UInt32 SIZE>
CircleBuffer<T, SIZE>::CircleBuffer()
                :m_iNextReadPos(0),
                 m_iNextWritePos(0)
{
}

template<class T, UInt32 SIZE>
CircleBuffer<T, SIZE>::~CircleBuffer()
{
}

template<class T, UInt32 SIZE>
bool  CircleBuffer<T, SIZE>::push_back(T pData, UInt32 iLen, UInt32 iType)
{
	if(  (m_iNextWritePos==SIZE-1 && 0==m_iNextReadPos) 
		|| (m_iNextWritePos==m_iNextReadPos-1) ) 
	{
		Assert(0);
		return false;
	}

	m_pVDATA[m_iNextWritePos].pData     = pData;
	m_pVDATA[m_iNextWritePos].iDataLen  = iLen;
	m_pVDATA[m_iNextWritePos].iDataType = iType;

	++m_iNextWritePos;
	if(m_iNextWritePos==SIZE) 
	{
		m_iNextWritePos = 0;  	
	}

	return true;
}

template<class T, UInt32 SIZE>
bool  CircleBuffer<T, SIZE>::pop_front(T& pData, UInt32& iLen, UInt32& iType)
{
	if(m_iNextWritePos==m_iNextReadPos) 
	{
		return false;
	}

	pData = m_pVDATA[m_iNextReadPos].pData;
	iLen  = m_pVDATA[m_iNextReadPos].iDataLen;
	iType = m_pVDATA[m_iNextReadPos].iDataType;

	++m_iNextReadPos;
	if (m_iNextReadPos==SIZE)
	{
		m_iNextReadPos=0;
	}

	return true;	
}