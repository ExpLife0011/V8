#pragma once

class CRenderEngine
{
private:
    CRenderEngine(){};
    ~CRenderEngine(){};

public:
    //////////////////////////////////////////////////////////////////////////
    //��������
    //////////////////////////////////////////////////////////////////////////
    //����Բ�Ǿ���
    static HRGN CreateRountRectRgn(long left, long top, long right, long bottom, long diameter, bool bNULL = true);
    //��������Բ�ǰ뾶�ɷֱ����õ�����
    static HRGN CreateUpDownRoundRectRgn(long left, long top, long right, long bottom, long upDiameter, long downDiameter, bool bNULL = true);
    //��������Բ�ǰ뾶�ɷֱ����õ�����
    static HRGN CreateUpDownRoundRectRgn(long width, long height, long upDiameter, long downDiameter, bool bNULL = true);

    //////////////////////////////////////////////////////////////////////////
    //������
    //////////////////////////////////////////////////////////////////////////
    //����ֱ��
    static BOOL RenderLine(HDC hDC, const POINT& start, const POINT& end, LONG lineColor, LONG lineWidth = 1);
    //���ƾ���
    static BOOL RenderRect(HDC hDC, const RECT& rect, LONG color, LONG lineWidth = 1);
    //���ƾ���
    static BOOL Render3DRect(HDC hDC, const RECT& rect, LONG topLeftColor, LONG bottomRightColor);
    //���ƽ������
    static BOOL RenderFocusRect(HDC hDC, const RECT& rect);
    //��������
    static BOOL RenderRgn(HDC hDC, HRGN hRgn, LONG color, LONG lineWidth = 1);

    //////////////////////////////////////////////////////////////////////////
    //���
    //////////////////////////////////////////////////////////////////////////
    //������
    static BOOL FillRect(HDC hDC, const RECT& rect, LONG color);
    //�����Ӱ����
    static BOOL FillShadowRect(HDC hDC, const RECT& rect, LONG diameter, LONG centerColor = 0xFF000000, LONG surroundColor = 0x00FFFFFF);
    //�������
    static BOOL FillRgn(HDC hDC, HRGN hRgn, LONG color);
};
