#pragma once

class CHueSaturationAdjuster
{
public:
    CHueSaturationAdjuster(void);
    ~CHueSaturationAdjuster(void);

public:
    //��ʼ��
    void Init(double hue, double sat, double light);
    //����
    RGBQUAD Adjust(RGBQUAD color);

protected:
    double m_aHue[7];
    double m_aSaturation[7];
    double m_aLightness[7];
    double m_fOverlap;

    int m_aHueTransfer[6][256];
    int m_aSaturationTransfer[6][256];
    int m_aLightnessTransfer[6][256];
};
