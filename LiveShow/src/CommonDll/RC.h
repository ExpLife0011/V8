#pragma once

#include "Mutex.h"
#include "Cond.h"

class COMMON_OUT_CLASS RCObject
{
public:
	RCObject():m_iRefCount(0){}
	RCObject(const RCObject&):m_iRefCount(0){}
	RCObject& operator=(const RCObject& rhs){return *this;}

	virtual ~RCObject()=0;

	//���ü�����1
	void                 AddReference();

	//���ü�����1, ����true��ʾ�ڴ���Ի��ջ��Ѿ����ͷ�
	void                 RemoveReference();

	//��ȡ���ú�
	unsigned int		 GetReference();

	//�������ü���
	void				 SetReference(unsigned int iref);

	//�ж϶����Ƿ񱻶������
	bool                 isShared();

	//�ȴ��������߳��ͷ�
	void                 WaitUnshared();

private:
	
	Mutex             m_RCMutex;     //��������Ļ�����
	Cond              m_Cond;

	SInt32            m_iRefCount;    //��������ü���
};

//����ָ��
template <class T>
class RCPtr
{
public:
	RCPtr(T* realPtr = NULL):pointee(realPtr)    {   init();  }
	RCPtr(const RCPtr& rhs):pointee(rhs.pointee) {   init();  }
	RCPtr& operator = (const RCPtr& rhs)
	{
		if (pointee!=rhs.pointee)
		{
			if (pointee) 
			{
				pointee->RemoveReference();
			}

			pointee = rhs.pointee;
	
			init();
		}
		return *this;
	}

	~RCPtr()
	{
		if (pointee) 
		{
			pointee->RemoveReference();
		}
	}

	T* operator->() const  { return pointee; }
	T& operator*()  const  { return *pointee; }
	operator bool() const  { if (pointee) return true; return false;}

private:

	T* pointee;

	void init()
	{
		if (NULL==pointee ) 
		{
			return;
		}
		pointee->AddReference();
	}
};

