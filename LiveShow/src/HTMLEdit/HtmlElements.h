#pragma once

#include <mshtml.h>
#include <afxtempl.h>

template<class THtmlElement> class CHtmlElements
{
	typedef CMap<LPDISPATCH, LPDISPATCH, THtmlElement*, THtmlElement*> CMapDispToHtmlElement;
	CMapDispToHtmlElement m_htmlElements;
	BOOL IsSiteConnected( LPDISPATCH pDisp )
	{
		THtmlElement *pElement;
		return m_htmlElements.Lookup( pDisp, pElement );
	}
public:
	CHtmlElements(void)
	{
	}
	~CHtmlElements(void)
	{
	}
public:
	void SetSite( LPDISPATCH pDisp )
	{
		if ( IsSiteConnected( pDisp ) ) //����Ա�������Sink
		{
			return;
		}
		THtmlElement *pElement = new THtmlElement; //ͨ��ģ�����ʹ�����Ӧ�����ʵ����������
		pElement->SetSite( pDisp );
		m_htmlElements.SetAt( pDisp, pElement );
	}

	//�ں��ʵĵط�����Clear�ͷ���������ڴ�

	void Clear(void)

	{

		POSITION pos = m_htmlElements.GetStartPosition();

		THtmlElement *pElement = NULL;

		LPDISPATCH pDisp = NULL;

		while (pos != NULL)

		{

			m_htmlElements.GetNextAssoc( pos, pDisp, pElement );

			m_htmlElements.RemoveKey( pDisp );

			delete pElement;

		}

	}

};
