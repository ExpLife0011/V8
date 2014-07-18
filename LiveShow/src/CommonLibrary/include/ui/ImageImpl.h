#pragma once

#include "../Common.h"
#include "./ClassDataMacro.h"

struct IImage;
struct tagANIMATEINFO;
struct tagFRAMEINFO;

namespace common { namespace ui
{

class IImageManager;

/**
@class CImageImpl
@brief IImage��ʵ��
*/
class COMMON_INTERFACE CImageImpl : 
    public IImage
{
public:
    /**
    @fn CImageImpl(IImageManager* pManager)
    @brief ���캯��
    @param [in] pManager ͼƬ�������
    */
    CImageImpl(IImageManager* pManager = NULL);

    /**
    @fn void Destroy()
    @brief ���ٺ���
    */
    void Destroy();

protected:
    /**
    @fn ~CImageImpl(void)
    @brief ����������Ϊ�������ʣ���ֹջ����
    */
    virtual ~CImageImpl(void);

    //for IUnknown and IImage
public:
    /** 
    @addtogroup IImage
    @brief  IImage ʵ�� 
    */ 
    //@{
    STDMETHOD_(ULONG, AddRef)();
    STDMETHOD_(ULONG, Release)();
    STDMETHOD(QueryInterface)(REFIID iid, void** ppvObject);
    STDMETHOD(get_Width)(UINT* pWidth);
    STDMETHOD(get_Height)(UINT* pHeight);
    STDMETHOD(Render)(HDC hDC, LPCRECT pDstRect, LPCRECT pSrcRect = NULL, LPCRECT pBoundRect = NULL);
    //@}

    /** 
    @addtogroup IAnimation
    @brief  IAnimation ʵ�� 
    */ 
    //@{
    STDMETHOD(GetNumFrames)(UINT* pNumFrames);
    STDMETHOD(GetAnimationInfo)(LPANIMATEINFO pAnimationInfo);
    STDMETHOD(GetFrameInfo)(UINT uFrame, LPFRAMEINFO pFrameInfo);
    STDMETHOD(RenderFrame)(HDC hDC, UINT uFrame, LPCRECT pDstRect);
    //@}

    /** 
    @addtogroup IImageEx
    @brief  IImageEx ʵ�� 
    */ 
    //@{
    STDMETHOD(RenderEx)(HDC hDC, LPCRECT pDstRect, VARIANT_BOOL bFrame);
    STDMETHOD(CreateHBITMAP)(HDC hDC, HBITMAP* pHBITMAP);
    //@}

private:
    /**
    @class XAnimation
    @brief IAnimation ��Ƕ��
    */
    class XAnimation : public IAnimation
    {
    public:
        STDMETHOD_(ULONG, AddRef)();
        STDMETHOD_(ULONG, Release)();
        STDMETHOD(QueryInterface)(REFIID iid, void** ppvObject);
        STDMETHOD(GetNumFrames)(UINT* pNumFrames);
        STDMETHOD(GetAnimationInfo)(LPANIMATEINFO pAnimationInfo);
        STDMETHOD(GetFrameInfo)(UINT uFrame, LPFRAMEINFO pFrameInfo);
        STDMETHOD(RenderFrame)(HDC hDC, UINT uFrame, LPCRECT pDstRect);
    };

    /**
    @class XImageEx
    @brief IImageEx ��Ƕ��
    */
    class XImageEx : public IImageEx
    {
    public:
        STDMETHOD_(ULONG, AddRef)();
        STDMETHOD_(ULONG, Release)();
        STDMETHOD(QueryInterface)(REFIID iid, void** ppvObject);
        STDMETHOD(RenderEx)(HDC hDC, LPCRECT pDstRect, VARIANT_BOOL bFrame);
        STDMETHOD(CreateHBITMAP)(HDC hDC, HBITMAP* pHBITMAP);
    };

public:
#ifdef _DEBUG
    /**
    @fn DWORD GetRefCount() const
    @brief ������ü��������ڵ���
    @return �������ü���
    */
    DWORD GetRefCount() const;
#endif

public:
    /**
    @fn BOOL Load(LPCTSTR lpzFileName)
    @brief ���ļ�����
    @param [in] lpzFileName �ļ�·����
    @return �Ƿ���سɹ�
    */
    BOOL Load(LPCTSTR lpzFileName);

    /**
    @fn BOOL Load(const char* pBuffer, long lBufSize)
    @brief ���ڴ����
    @param [in] pBuffer �ڴ�ָ��
    @param [in] lBufSize �ڴ泤��
    @return �Ƿ���سɹ�
    */
    BOOL Load(const char* pBuffer, long lBufSize);

    /**
    @fn BOOL Load(IStream* pStream)
    @brief ��IStream����
    @param [in] pSteam ISteamָ��
    @return �Ƿ���سɹ�
    */
    BOOL Load(IStream* pStream);

    /**
    @fn BOOL Load(HBITMAP hBitmap)
    @brief ��λͼ����
    @param [in] hBitmap λͼ
    @return �Ƿ���سɹ�
    */
    BOOL Load(HBITMAP hBitmap);

    /**
    @fn BOOL Load(HICON hIcon)
    @brief ��ͼ�����
    @param [in] hIcon ͼ��
    @return �Ƿ���سɹ�
    */
    BOOL Load(HICON hIcon);

    /**
    @fn BOOL Resample(UINT uWidth, UINT uHeight, int iMode = 1)
    @brief �ز���
    @param [in] uWidth ������Ŀ��
    @param [in] uHeight ������ĸ߶�
    @param [in] iMode ������ģʽ
    @return �Ƿ�����ɹ�
    */
    BOOL Resample(UINT uWidth, UINT uHeight, int iMode = 1);

    /**
    @fn BOOL Gray()
    @brief ��ͼ��ҶȻ�
    @return �Ƿ�ɹ�
    */
    BOOL Gray();

    /**
    @fn BOOL Copy(CImageImpl* pImage)
    @brief ����ͼ��
    @param [in] pImage ����Դͼ��
    @return �Ƿ񿽱��ɹ�
    */
    BOOL Copy(CImageImpl* pImage);

    /**
    @fn CImageImpl* Clone(IImageManager* pManager)
    @brief ��¡
    @param [in] pManager ͼƬ������ָ��
    @return �µ�ͼƬ����
    */
    CImageImpl* Clone(IImageManager* pManager);

    /**
    @fn IUnknown* GetUnknown()
    @brief ���IUnknownָ��
    @return ����IUnknownָ��
    */
    IUnknown* GetUnknown();

    /**
    @fn IImageManager* DetachImageManager()
    @brief ����ͼƬ����
    @return �����йܵ�ͼƬ�������
    */
    IImageManager* DetachImageManager();

protected:
    /**
    @fn void Clear()
    @brief ��ն���
    */
    void Clear();

private:
    XAnimation m_xAnimation;
    XImageEx m_xImageEx;
    DECLARE_CLASS_DATA(CImageImpl);
};

} } //namespace common::ui
