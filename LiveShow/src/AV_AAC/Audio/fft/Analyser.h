#pragma once
#include "51ktvtype.h"
namespace FFTWav
{
	//��Ƶ���ݼ�����
	class CAnalyserProcess;
	class CFFTrans;
	class CAnalyser
	{
	friend class CAnalyserProcess;
	public:
		CAnalyser(HWND hWnd);
		virtual ~CAnalyser(void);

	protected:
		//************���ݼ��㲿��
		int m_nSampleSize;//ÿ֡��Ƶ���ݴ�С  ��ǰ֡���ݴ�С
		DWORD m_nAudioDataBufferLength;//��Ƶ���ݻ�����
		byte* m_pAudioDataBuffer;//��Ƶ������
		FLOAT* m_Left; //������������������ٷֱ� - ռ������
		FLOAT* m_Right;//������������������ٷֱ�
		INT m_offset; //����ƫ��
		LONG m_FpsAsNS; //�����ӳ�
		LONG m_DesiredFpsAsNS; //�����ӳ�
		INT m_saFFTSampleSize;//����Ҷ�任��ʼ֡��С
		CFFTrans* m_pFFT; //����Ҷ�任ʵ����
		FLOAT m_saDecay;//�ӳ�ϵ��
		INT m_width; //���
		INT m_height;//�߶�
		INT m_saBands;//����������
		FLOAT m_saMultiplier;//
		FLOAT* m_oldFFT;//�ɵĸ���Ҷ�任����
		INT* m_peaks; //�������Ӹ߶�
		INT* m_peaksDelay;//���������ӳ�
		bool m_peaksEnabled; //�Ƿ���ʾ��������
		INT m_peakDelay;//���������ӳ�
		bool m_bIsVistaOrWin7;

		//��ͼ׼������
		HWND m_hWnd; //��Ƶ��ʾ�Ĵ��ھ��
		HDC m_hdcScreen;//��Ļ��ˢ
		HDC m_hdcMem;//�ڴ沨��ͼ��DC
		HDC m_hdcMem1;//һ��������ͼ�� 
		HBITMAP m_hbmMem;//�ڴ沨��ͼ����λͼ
		HBITMAP m_hbmMem1;//һ��������ͼ����λͼ
		HBITMAP m_hOld;//�ڴ沨��ͼ����ǰ��λͼ
		HBITMAP m_hOld1;//һ��������ͼ����λͼǰ����λͼ
		HBRUSH m_hbrush;//������ˢ  Ĭ�Ϻ�ɫ
		HBRUSH m_hbrush1;//�������� ��ˢ Ĭ�ϻҰ�
		HBRUSH m_hbrushOld; //ѡ�񱳾���ˢǰ���ϻ�ˢ
		HBRUSH m_hbrushOld1;//ѡ���������ӻ�ˢǰ���ϻ�ˢ
		
		
	protected:
		void drawSpectrumAnalyserBar(RECT* pRect, int pX, int pY, int pWidth, int pHeight, int band);
	public:
		void Process(float pFrameRateRatioHint);//ִ�м������
		void Draw(HWND hWnd,HDC hDc);
		void TransparentBlt2( HDC hdcDest,      // Ŀ��DC
			int nXOriginDest,   // Ŀ��Xƫ��
			int nYOriginDest,   // Ŀ��Yƫ��
			int nWidthDest,     // Ŀ����
			int nHeightDest,    // Ŀ��߶�
			HDC hdcSrc,         // ԴDC
			int nXOriginSrc,    // ԴX���
			int nYOriginSrc,    // ԴY���
			int nWidthSrc,      // Դ���
			int nHeightSrc,     // Դ�߶�
			UINT crTransparent  // ͸��ɫ,COLORREF����
			);
	};

}
