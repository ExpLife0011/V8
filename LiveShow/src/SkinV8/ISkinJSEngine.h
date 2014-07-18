#pragma once

enum SKINJSENGINE_STATE
{
    SKINJSENGINE_CLOSE,
    SKINJSENGINE_NOTLOAD,
    SKINJSENGINE_LOAD,
    SKINJSENGINE_START,
    SKINJSENGINE_STOP,
};

class CSkinBase;

class ISkinJSEngine
{
public:
    ISkinJSEngine(void);

    //��������ջ�ϴ���
protected:
    virtual ~ISkinJSEngine(void);

    //��ʽ����������
public:
    void Destroy();

private:
    //��������
    explicit ISkinJSEngine(const ISkinJSEngine& other);
    ISkinJSEngine& operator = (const ISkinJSEngine& other);

public:
    //����
    virtual BOOL Create(CSkinBase* pBase) = 0;
    //����
    virtual BOOL Load(const char* pJS, LPCTSTR fileName = NULL) = 0;
    //��ʼ��ȫ�����ֿռ�
    virtual BOOL InitGlobalNamespace() = 0;
    //����
    virtual BOOL Start() = 0;
    //ֹͣ
    virtual BOOL Stop() = 0;
    //�ر�
    virtual BOOL Close() = 0;
    //�������״̬
    virtual SKINJSENGINE_STATE GetState() const = 0;
    //���JS����ֵ
    virtual HRESULT GetProperty(BSTR propName, VARIANT* pPropValue);
    //����JS����
    virtual HRESULT CallFunction(BSTR funcName, VARIANT* pVarResult, DISPPARAMS* pDispParams);
};
