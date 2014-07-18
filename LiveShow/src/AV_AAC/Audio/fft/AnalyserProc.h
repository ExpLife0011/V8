#pragma once
#include "Basic.h"
#include "51ktvtype.h"
#include "RC.h"

namespace FFTWav
{
	//���Ʋ���ͼִ����
	class CAnalyser;
	class CAnalyserProcess:public RCObject
	{
	public:
		CAnalyserProcess(HWND hWnd);
		~CAnalyserProcess(void);
	protected:
		CAnalyser* m_Analyser;
		CCriticalSection cs;
		bool bNew;
		unsigned int iCount;
	protected:
		void processSamples(int nPosition);

	public:
		//ִ�в���
		void Process();
		//Ϊִ��Processǰ׼������ pBuf��Ƶ���� ��Ƶ���ݳ���byte
		void Prepare(byte* pBuf,int nLen);

		void Draw(HWND hWnd,HDC hDc);
	};

}
