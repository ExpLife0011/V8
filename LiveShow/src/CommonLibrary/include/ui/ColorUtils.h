#pragma once

#include "../Common.h"
#include "ximage.h"

#define DEF_R	143
#define DEF_G	172
#define DEF_B	219

namespace common { namespace ui
{

/**
@fn double HuetoRGB(double m1, double m2, double h )
@brief Hueɫ��תRGB
@param [in] m1 m1
@param [in] m2 m2
@param [in] h
@return ת�����ֵ
*/
double COMMON_INTERFACE HuetoRGB(double m1, double m2, double h);

/**
@fn COLORREF HSLtoRGB( double H, double S, double L)
@brief HSL��ɫתRGB�ռ�
@param [in] H Hue
@param [in] S Saturation
@param [in] L Lightness
@return RGBֵ
*/
COLORREF COMMON_INTERFACE HSLtoRGB(double H, double L, double S);

/**
@fn void RGBtoHSL(COLORREF rgb, double *H, double *S, double *L)
@brief RGB�ռ���ɫתHSL�ռ���ɫ
@param [in] rgb RGB��ɫ
@param [out] H Hue
@param [out] S Saturation
@param [out] L Lightness
*/
void COMMON_INTERFACE RGBtoHSL(COLORREF rgb, double *H, double *S, double *L);

/**
@fn void Colorize(BYTE hue, BYTE sat, float blend, RGBQUAD& src, RGBQUAD& dst)
@brief ����ɫ��������Ƥ����ɫ
@param [in] hue ɫ������
@param [in] sat ���Ͷȵ���
@param [in] blend ���ȵ���
@param [in] src ����ǰRGB��ɫ
@param [out] dst ������RGB��ɫ
*/
void COMMON_INTERFACE Colorize(BYTE hue, BYTE sat, float blend, RGBQUAD& src, RGBQUAD& dst);

/**
@fn void Colorize(BYTE hue, BYTE sat, float blend, RGBQUAD& src, RGBQUAD& dst)
@brief ����ͼƬɫ��������Ƥ����ɫ
@param [in] pImage	��Ҫ������ͼƬ
@param [in] hue ɫ������
@param [in] sat ���Ͷȵ���
@param [in] blend ���ȵ���
@param [in] src ����ǰRGB��ɫ
@param [out] dst ������RGB��ɫ
*/
HBITMAP COMMON_INTERFACE Colorize(CxImage* pImage, BYTE bHue, BYTE bSat, float bBlend);

} } //namespace common::ui
