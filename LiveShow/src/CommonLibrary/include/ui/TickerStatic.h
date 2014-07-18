#pragma once
#include <vector>
#include "51ktvtype.h"
#include "../Common.h"
using namespace std;

namespace common 
{
	namespace ui
	{
		
		struct tickerInfo
		{
			CString m_Message;
			CString m_Url;
		};

		struct tickerInfoRect
		{
			tickerInfo m_tickerInfo;
			CRect m_Rect;
		};

		//�����
		class COMMON_INTERFACE CTickerStatic : public CStatic
		{
			DECLARE_DYNAMIC(CTickerStatic)

		public:
			CTickerStatic();
			virtual ~CTickerStatic();
			 
		protected:
			DECLARE_MESSAGE_MAP()

		public:
			void RunTicker(vector<tickerInfo> &tickerVec,uint32 intervalTime = 150);  //���������
			void SetTickerFont(Gdiplus::Font &fontDefault,Gdiplus::Font &fontSelect);  //����Ĭ���������ͣʱ����   ����RunTicker֮ǰ����
			void SetTickerColor(COLORREF colorDefault,COLORREF colorSelect);  //����Ĭ��������ɫ����ͣʱ������ɫ  ����RunTicker֮ǰ����
			void SetPause(bool isPause = true); //���������ͣʱ�Ƿ���ͣ����   ����RunTicker֮ǰ����
			void SetClickTitle(bool isClick = true); //�����Ƿ����������򿪶�Ӧurl�¼�  ����RunTicker֮ǰ����
			void OnPostParentPaint(HDC hParentHDC);			

		private:
			virtual void PreSubclassWindow();
			afx_msg void OnPaint();
			afx_msg void OnTimer(UINT_PTR nIDEvent);
			afx_msg void OnMouseMove(UINT nFlags, CPoint point);
			afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam); //����뿪
			afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam); //�����ͣ
			afx_msg void OnLButtonUp(UINT nFlags, CPoint point);  //�����
			afx_msg void OnLButtonDown(UINT nFlags, CPoint point);  //�����
			afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
			afx_msg void OnSize(UINT nType, int cx, int cy);

			int GetCursorPointIndex();  //��ȡ��굱ǰpoint���ڵ��±�
			void SetCursourHead(bool head);  //������������� trueΪ���ͣ�falseΪ��׼��ͷ
		
		private:
			vector<tickerInfoRect> m_tickerVec;  //����������б�
			uint32 m_intervalTime;  //���ʱ��
			Gdiplus::Font *m_fontDefault;  //Ĭ������
			Gdiplus::Font *m_fontSelect;  //��ͣʱ����			
			Gdiplus::SolidBrush m_colorDefault;  //Ĭ��������ɫ
			Gdiplus::SolidBrush m_colorSelect;  //��ͣʱ������ɫ
			Gdiplus::SolidBrush m_colorDown;    //���ʱ������ɫ
			int m_intervallen; //�������
			int m_nScrollPos;  //�ı���ʾλ��
			bool m_bOver;	//���λ�ڿؼ�֮��ʱ��ֵΪtrue����֮Ϊflase
			bool m_bDown;	//�����ʱΪtrue����֮Ϊflase
			int m_curIndex; //��굱ǰpoint���ڵ��±�
			HCURSOR m_cursour; 
			bool m_isPause; //�����ͣʱ�Ƿ���ͣ����, trueΪ��ͣ������falseΪ��������
			bool m_isClick; //����Ƿ�ɵ�����⣬��ʹ��������򿪶�Ӧurl

			CDC m_dcBk;
			CBitmap m_bmpBk;
			CBitmap* m_pbmpOldBk;
			bool m_bNeedUpdate;
		};
	}
}