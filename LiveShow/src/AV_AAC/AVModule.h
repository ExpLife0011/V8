#pragma once
#include "51ktv.h"
#include "imodule.h"
#include "CircleBuffer.h"
#include "Audio\\mixer\\MixerManager.h"
#include "AVManager.h"

class AVModule :
	public IModule
{
public:
	AVModule(void){}
	~AVModule(void){}

	virtual void Load(IModuleManager *);
	virtual void Unload();
	virtual wchar_t const * const  GetModuleName();
	
	//ģ����֪ͨģ����һ���¼������¼�����Ϊ�첽
	virtual void ProcessEvent(Event const&);	
	//��ʹ�øýӿ�֪ͨ��Ϣ��������Ϊһ���첽����Event�ķ�����Model��------->ModelManager
	virtual void ProcessMessage(Message const&);
	//����һ����Ϣ���Լ����Է�����Ϣ�Ĵ�������Ϊʵʱ
	virtual int32 Invoke(ServiceValue const serviceValue, param);
	//�ṩ���첽���õķ����¼��Ľӿڣ��Ȱ��¼�����BUF Ȼ��ͳһ����m_pModuleManager����   Model��------->ModelManager
	bool   sendEvent(void* pEvent, uint32 iType);
	
	IModuleManager*	GetModuleManager(){return m_pModuleManager;}

private:
	void   processCircleBuffer();

	IModuleManager* m_pModuleManager;
	CircleBuffer<void*>  m_CircleBuffer;

	AVManager	  m_avManager;
	CMixerManager m_mixerManager;
};
