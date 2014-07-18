#pragma once

#include "MixerChannel.h"
#include "MixerDefine.h"

class CMixerManager
{
public:
	CMixerManager(void);
	~CMixerManager(void);

	//��ʼ��  �����ʼ���ſ��Խ�����������
	void Init(HWND hWnd);
	
	//��ȡ��ǰ�������Ƿ����
	bool GetMixerControlTotalEnable();
	//��ȡ�����Ƿ����
	bool GetMixerControlWavoutEnable();
	//��ȡ���������е���˷��Ƿ����
	bool GetMixerControlOutmicEnable();
	//��ȡ�����������Ƿ����
	bool GetMixerControlMixerEnable();
	//��ȡ��Ƶ�����豸��������С
	bool GetMixerControlInmicEnable();
	//��ȡ������˷�������С�Ƿ����
	bool GetMixerControlWavInEnable();

	//�������� 0 ~ 255 
	//����������
	bool SetMixerControlTotalVolume(unsigned int nVolume);
	//��ȡ������
	bool GetMixerControlTotalVolume(unsigned int& nVolume);
	//���ð���
	bool SetMixerControlWavoutVolume(unsigned int nVolume);
	//��ȡ��������
	bool GetMixerControlWavoutVolume(unsigned int& nVolume);
	//�������������е���˷�
	bool SetMixerControlOutmicVolume(unsigned int nVolume);
	//��ȡ���������е���˷�����
	bool GetMixerControlOutmicVolume(unsigned int& nVolume);

	//¼������0~255
	//����������
	bool SetMixerControlMixerVolume(unsigned int nVolume);
	//��ȡ��������������
	bool GetMixerControlMixerVolume(unsigned int& nVolume);
	//¼�������е���˷�
	bool SetMixerControlInmicVolume(unsigned int nVolume);
	//��ȡ¼�������е���˷�����
	bool GetMixerControlInmicVolume(unsigned int& nVolume);

	//������Ƶ�����豸������С
	bool SetMixerControlWavInVolume(unsigned int nVolume);
	//������Ƶ�����豸������С
	bool GetMixerControlWavInVolume(unsigned int& nVolume);


	//��������
	//��������������
	bool SetMixerControlTotalMute(bool bEnable);    //������
	//��ȡ�������Ƿ���
	bool GetMixerControlTotalMute(bool& bEnable);
	//���ð�������
	bool SetMixerControlWavoutMute(bool bEnable);   //����
	//��ȡ�����Ƿ���
	bool GetMixerControlWavoutMute(bool& bEnable);
	//�������������е���˷�ľ���
	bool SetMixerControlOutmicMute(bool bEnable);   //���������
	//��ȡ���������е���˷�ľ���
	bool GetMixerControlOutmicMute(bool& bEnable);
	//���������֧���벻֧��ѡ��
	//��������������
	bool SetMixerControlMixerMute(bool bEnable);   //����·����
	//��ȡ��������Ӧ�Ƿ���
	bool GetMixerControlMixerMute(bool& bEnable);
	//����¼�������е���˷羲��
	bool SetMixerControlInmicMute(bool bEnable);   //����˷�
	//��ȡ¼�������е���˷��Ƿ���
	bool GetMixerControlInmicMute(bool& bEnable);

	//�жϿ������� ѡ�� ���� ���������� �Դ����ж�ϵͳ֧����������
	bool IsMixerControlSelect(bool& bSel);

	//���ó���
	bool SetMixerControlSingMode();
	//��ȡ�Ƿ��ڳ���ģʽ
	bool GetMixerControlSingMode(bool& bEnable);
	//������������
	bool SetMixerControlChatMode();
	//��ȡ�Ƿ���������ģʽ
	bool GetMixerControlChatMode(bool& bEnable);
	//�����ϷŸ�
	bool SetMixerControlPlayMode();
	//��ȡ�Ƿ������ϷŸ�ģʽ
	bool GetMixerControlPlayMode(bool& bEnable);
	//��ȡ��ǰ������ģʽ
	bool GetMixerControlMode(EnMixerControlMode& eMode);

	/**********************************************************
	һ������֧��������������� ����������Ϊ��ѡ�񡢷�ѡ��
	1.����ģʽ ���������� Ҳ������˷���������
	  ����������		ѡ��     
	  ����				�Ǿ���
	  ���������˷�	�Ǿ���
    2.�������� ������������ ����������˷�����
	  ���������        ѡ��
	  ����              ����
	  ���������˷�    �Ǿ���
    3.�����ϷŸ� ���������� �������û�˵������
	  ����������        ѡ��
	  ����              �Ǿ���
	  ���������˷�    ����
	��������֧��������������� ����������Ϊ���������Ǿ�����
	1.����ģʽ ������������ Ҳ������˷���������
	  ����������        �Ǿ���
	  ����              �Ǿ���
	  ���������        �Ǿ���
    2.��������ģʽ ������������ ����������˷��û�˵������
	  ����������        �Ǿ���
	  ����              ����
	  ���������        �Ǿ���
	3.�����ϷŸ� ������������ �������û���˷�˵������
	  ����������        �Ǿ���
	  ����              �Ǿ���
	  ���������        ����
	  ************************************************************/
protected:
	//��ȡ�����ؼ�����
	void GetMixerLineParam(EnMixerControlType sType,StrucMixerParam& sMixerParam);
	//��������ϳ�������
	bool SetMixerControlSoftMute(bool bEnable);
	//��ȡ����ϳ����Ƿ���
	bool GetMixerControlSoftMute(bool& bEnable);
	//����ǰ�����뾲��
	bool SetMixerControlFrontMute(bool bEnable);
	//��ȡǰ�������Ƿ���
	bool GetMixerControlFontMute(bool& bEnable);
	//������������������
	bool SetMixerControlTreeMute(bool bEnable);
	//��ȡ�����������Ƿ���
	bool GetMixerControlTreeMute(bool& bEnable);
	//��ȡ����ϵͳ����
	EnOsType GetOsType();
	//��ȡ�Ƿ�Ϊvista Or Win7����ϵͳ
	bool GetOsVistaOrWin7();

protected:
	CMixerChannel* m_pMixerChannel;
};