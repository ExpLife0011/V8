#include "stdafx.h"
#include "Analyser.h"
#include "Basic.h"
#include "AnalyserProc.h"
#include "FFTrans.h"
#include <atltypes.h>
#include <math.h>

namespace FFTWav
{
	enum OS_VERSION//�벻Ҫ����˳��
	{
		OS_UNKNOWN =    0,
		//OS_WIN95   =    1,
		//OS_WIN98   =    2,
		//OS_WIN98SE =    3,
		//OS_WINME   =    4,
		//OS_WINNT    =   5,
		OS_WIN2000 =    6,
		OS_WINXP   =    7,
		OS_WIN2003   =  8,
		//OS_WINXP64   =  9,
		OS_VISTA    =   10,
		OS_WIN2008 =11,
		OS_WIN2008R2 = 12,
		OS_WIN7    =    13,
	};


	/*
	* ��ȡϵͳ�汾����
	* @param [in] һ��OSVERSIONINFO�ṹ������
	* @return TRUE��ʾ�ɹ���FALSE��ʾʧ��
	*/
	BOOL GetOsVersion(OSVERSIONINFO & osInfo)
	{
		osInfo.dwOSVersionInfoSize = sizeof(osInfo);
		return GetVersionEx(&osInfo);
	}

	/*
	* �жϵ�ǰϵͳ�Ƿ����ĳ���汾
	* @param ��
	* @return OS_VERSIONö���е�һ��ֵ
	*/
	OS_VERSION GetOsVersion()
	{
		OSVERSIONINFO osVer;
		if(GetOsVersion(osVer)==TRUE)
		{
			DWORD majorVer=osVer.dwMajorVersion;
			DWORD minorVer=osVer.dwMinorVersion;

			if( majorVer == 5 && minorVer == 0)
			{
				return  OS_WIN2000;
			}
			else if( majorVer == 5 && minorVer == 1)
			{
				return OS_WINXP;
			}
			else if( majorVer == 5 && minorVer == 2)
			{
				return OS_WIN2003;
			}
			else if( majorVer == 6 && minorVer == 0)
			{
				return OS_VISTA;
			}
			else if(majorVer == 6 && minorVer == 1)
			{
				return OS_WIN7;
			}
			else
			{
				return OS_UNKNOWN;
			}
		}
		else
		{
			Assert(0);
			return OS_UNKNOWN;
		}
	}

	CAnalyser::CAnalyser(HWND hWnd)
	{
		m_nSampleSize = DEFAULT_SAMPLE_SIZE;//ÿ֡��Ƶ���ݴ�С
		m_nAudioDataBufferLength = DEFAULT_BUFFER_SIZE << 1; //��Ƶ���ݳ��� �ɼ�λ��16λ
		m_pAudioDataBuffer = new byte[m_nAudioDataBufferLength]; //��Ƶ������
		memset(m_pAudioDataBuffer,0,m_nAudioDataBufferLength);
		m_Left = new FLOAT[DEFAULT_SAMPLE_SIZE];
		m_Right = new FLOAT[DEFAULT_SAMPLE_SIZE];
		m_offset = 0;//����ƫ��
		m_DesiredFpsAsNS = 0x3B9ACA00L / DEFAULT_FPS; //������ˢ��ʱ�� 
		m_FpsAsNS = m_DesiredFpsAsNS; //�ӳټ���
		m_saFFTSampleSize = DEFAULT_SPECTRUM_ANALYSER_FFT_SAMPLE_SIZE;
		m_pFFT = new CFFTrans(m_saFFTSampleSize); //����Ҷ�任ʵ����
		m_saBands = DEFAULT_SPECTRUM_ANALYSER_BAND_COUNT;//����������
		m_saDecay = DEFAULT_SPECTRUM_ANALYSER_DECAY; //�̶��ӳ�
		m_saMultiplier = (FLOAT)((m_saFFTSampleSize / 2) / m_saBands);
		m_oldFFT = new FLOAT[m_saFFTSampleSize];
		m_width = DEFAULT_WIDTH;
		m_height = DEFAULT_HEIGHT;
		m_peaks = new INT[DEFAULT_SPECTRUM_ANALYSER_BAND_COUNT]; //�������Ӹ߶�
		m_peaksDelay = new INT[DEFAULT_SPECTRUM_ANALYSER_BAND_COUNT];//���������ӳ�
		m_peakDelay = DEFAULT_SPECTRUM_ANALYSER_PEAK_DELAY;

 		memset(m_peaks, 0, DEFAULT_SPECTRUM_ANALYSER_BAND_COUNT*sizeof(INT));
 		memset(m_peaksDelay, 0, DEFAULT_SPECTRUM_ANALYSER_BAND_COUNT*sizeof(INT));
		memset(m_oldFFT, 0, m_saFFTSampleSize*sizeof(FLOAT));
		m_hWnd = hWnd;
		m_hdcScreen = GetWindowDC(m_hWnd);
		m_hdcMem = CreateCompatibleDC(m_hdcScreen);
		m_hdcMem1 = CreateCompatibleDC(m_hdcScreen);
		m_hbmMem = CreateCompatibleBitmap(m_hdcScreen, m_width, m_height);
		m_hbmMem1 = CreateCompatibleBitmap(m_hdcScreen, m_width, m_height);
		m_hbrush = CreateSolidBrush(RGB(0, 0, 0));
		m_hbrush1 = CreateSolidBrush(RGB(0, 237, 255));//����������ɫ
		m_hOld = (HBITMAP)SelectObject(m_hdcMem, m_hbmMem);
		m_hOld1 = (HBITMAP)SelectObject(m_hdcMem1, m_hbmMem1);
		m_hbrushOld = (HBRUSH)SelectObject(m_hdcMem, m_hbrush);
		m_hbrushOld1 = (HBRUSH)SelectObject(m_hdcMem, m_hbrush1);

		m_peaksEnabled = TRUE; //��ʾ��������

		RECT rect = {0, 0, m_width, m_height};
		DWORD colors[] = {RGB(0,99,173),RGB(0,99,173), RGB(92,251,255), RGB(23,235,255)};
		DrawGradient(m_hdcMem1, &rect, colors, 4, GRADIENT_FILL_RECT_V);

// 		for(int i=m_height;i>=0;i--)
// 		{
// 			if(i % 2 == 0) continue;
// 
// 			MoveToEx(m_hdcMem1, 0, i, NULL);
// 			LineTo(m_hdcMem1, m_width, i);
// 		}
		
		m_bIsVistaOrWin7 = false;
		OS_VERSION ov = GetOsVersion();
		if (ov == OS_VISTA || ov == OS_WIN7)
		{
			m_bIsVistaOrWin7 = true;
		}
	}

	CAnalyser::~CAnalyser(void)
	{
		if (m_pFFT)
		{
			delete m_pFFT;
			m_pFFT = NULL;
		}
		if (m_pAudioDataBuffer)
		{
			delete []m_pAudioDataBuffer;
		}
		if(m_Left)
		{
			delete []m_Left;
			m_Left = NULL;
		}
		if (m_Right)
		{
			delete []m_Right;
			m_Right = NULL;
		}
		if(m_oldFFT)
		{
			delete [] m_oldFFT;
			m_oldFFT = NULL;
		}
		if (m_peaks)
		{
			delete[]m_peaks;
			m_peaks = NULL;
		}
		if (m_peaksDelay)
		{
			delete[] m_peaksDelay;
			m_peaksDelay = NULL;
		}

		SelectObject(m_hdcMem, m_hOld);
		SelectObject(m_hdcMem1, m_hOld1);
		SelectObject(m_hdcMem, m_hbrushOld);
		SelectObject(m_hdcMem, m_hbrushOld1);
		DeleteObject(m_hbmMem);
		DeleteObject(m_hbmMem1);
		DeleteObject(m_hbrush);
		DeleteObject(m_hbrush1);
		DeleteDC(m_hdcMem);
		DeleteDC(m_hdcMem1);
		ReleaseDC(m_hWnd,m_hdcScreen);
	}

	void CAnalyser::drawSpectrumAnalyserBar(RECT* pRect, int pX, int pY, int pWidth, int pHeight, int band)
	{
		BitBlt(m_hdcMem, pX, pY-pHeight, pWidth, pHeight, m_hdcMem1, pX, pY-pHeight, SRCCOPY); //����Ƶ���� 	
		if (m_peaksEnabled == TRUE) {
			if (pHeight > m_peaks[band]) {
				m_peaks[band] = pHeight;
				m_peaksDelay[band] = m_peakDelay;
			} else {
				m_peaksDelay[band]=m_peaksDelay[band]>m_peakDelay?m_peakDelay:m_peaksDelay[band];
				m_peaksDelay[band]--;
				m_peaksDelay[band]--;
				if (m_peaksDelay[band] < 0) {
					m_peaks[band]--;
					m_peaks[band]--;
				}
				if (m_peaks[band] < 0) {
					m_peaks[band] = 0;
				}
				if (m_peaks[band]>m_height)
				{
					m_peaks[band] = m_height;
				}
			}

			RECT rect = {0};
			rect.left = pX;
			rect.right = rect.left + pWidth;
			rect.top = pY - m_peaks[band];
			rect.bottom = rect.top + 1;
			FillRect(m_hdcMem, &rect, m_hbrush1);//haosl  �����������
		}
	}

	void CAnalyser::Process(float pFrameRateRatioHint)//ִ�м������
	{	
		if(IsIconic(m_hWnd) == TRUE) //�����Ƿ���С��
			return;

		for (int a = 0; a < m_nSampleSize; a++) { //�����ֵ
			m_Left[a] = (m_Left[a] + m_Right[a]) / 2.0f;
		} 

		float c = 0;
		float pFrrh = pFrameRateRatioHint; //����
		float* wFFT = m_pFFT->Calculate(m_Left, m_nSampleSize);//����Ҷ����
		float wSadfrr = m_saDecay * pFrrh; //�ӳ�ʱ��m_saDecay
		//float wBw = ((float) m_width / (float) m_saBands); //����ÿ��������
		float wBw = 2.0f;

		RECT rect;
		rect.left = 0;	
		rect.top = 0;
		rect.right = rect.left + m_width;
		rect.bottom = rect.top + m_height;
		FillRect(m_hdcMem, &rect, m_hbrush); //��䱳�� ����

		for (int a = 0,  bd = 0; bd < m_saBands; a += (INT)m_saMultiplier, bd++) {
			float wFs = 0;
			for (int b = 0; b < (INT)m_saMultiplier; b++) {
				wFs += wFFT[a + b];
			}

			wFs = (wFs * (float) log(bd + 2.0F));

			if(wFs > 0.005F && wFs < 0.009F)
				wFs *= 9.0F * PI;
			else if(wFs > 0.01F && wFs < 0.1F)
				wFs *= 3.0F * PI;
			else if(wFs > 0.1F && wFs < 0.5F)
				wFs *= PI; 

			if (wFs > 1.0F) {
				wFs = 0.9F;
			}

			if (wFs >= (m_oldFFT[a>=m_saFFTSampleSize?m_saFFTSampleSize-1:a] - wSadfrr)) {
				m_oldFFT[a>=m_saFFTSampleSize?m_saFFTSampleSize-1:a] = wFs;
			} else {
				m_oldFFT[a>=m_saFFTSampleSize?m_saFFTSampleSize-1:a] -= wSadfrr;
				if (m_oldFFT[a>=m_saFFTSampleSize?m_saFFTSampleSize-1:a] < 0) {
					m_oldFFT[a>=m_saFFTSampleSize?m_saFFTSampleSize-1:a] = 0;
				}
				wFs = m_oldFFT[a>=m_saFFTSampleSize?m_saFFTSampleSize-1:a];
			}
			
			wFs = wFs>1.0?1.0:wFs;
			drawSpectrumAnalyserBar(&rect, (int) c, m_height, (int) wBw - 1, (int) (wFs * m_height), bd);
			c += wBw;
		}
	}

	void CAnalyser::Draw(HWND hWnd,HDC hDc)
	{
		if (hWnd && ::IsWindow(hWnd))
		{
			CRect rc;
			int x,y;
			::GetWindowRect(hWnd,&rc);
			x = rc.Width()-m_width;
			y = m_height-16;
			if (m_bIsVistaOrWin7)
			{
				TransparentBlt2(hDc,x, y, m_width, m_height, m_hdcMem,0,0,m_width, m_height,RGB(0,0,0));
			}
			else
			{
				TransparentBlt(hDc,x, y, m_width, m_height, m_hdcMem,0,0,m_width, m_height,RGB(0,0,0));
			}
		}
	}

	void CAnalyser::TransparentBlt2( HDC hdcDest,      // Ŀ��DC
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
		)
	{
		HBITMAP hOldImageBMP, hImageBMP = CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest); // ��������λͼ
		HBITMAP hOldMaskBMP, hMaskBMP = CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);   // ������ɫ����λͼ
		HDC  hImageDC = CreateCompatibleDC(hdcDest);
		HDC  hMaskDC = CreateCompatibleDC(hdcDest);
		hOldImageBMP = (HBITMAP)SelectObject(hImageDC, hImageBMP);
		hOldMaskBMP = (HBITMAP)SelectObject(hMaskDC, hMaskBMP);

		// ��ԴDC�е�λͼ��������ʱDC��
		if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
			BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, SRCCOPY);
		else
			StretchBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, 
			hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, SRCCOPY);

		// ����͸��ɫ
		SetBkColor(hImageDC, crTransparent);

		// ����͸������Ϊ��ɫ����������Ϊ��ɫ������λͼ
		BitBlt(hMaskDC, 0, 0, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCCOPY);

		// ����͸������Ϊ��ɫ���������򱣳ֲ����λͼ
		SetBkColor(hImageDC, RGB(0,0,0));
		SetTextColor(hImageDC, RGB(255,255,255));
		BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

		// ͸�����ֱ�����Ļ���䣬�������ֱ�ɺ�ɫ
		SetBkColor(hdcDest,RGB(255,255,255));
		SetTextColor(hdcDest,RGB(0,0,0));
		BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

		// "��"����,��������Ч��
		BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCPAINT);

		// �����ָ� 
		SelectObject(hImageDC, hOldImageBMP);
		DeleteDC(hImageDC);
		SelectObject(hMaskDC, hOldMaskBMP);
		DeleteDC(hMaskDC);
		DeleteObject(hImageBMP);
		DeleteObject(hMaskBMP);
	}

}
