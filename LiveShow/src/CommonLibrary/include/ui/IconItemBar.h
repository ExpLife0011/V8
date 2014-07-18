#pragma once
#include "afxwin.h"
#include <vector>
#include <string>
#include "../Common.h"
#include "../../include/ui/ItemBar.h"

namespace common { namespace ui
{

///////////////////////////////////////////////////////////
//	����: CToolIconItem
//  �๦��������
//  	Bar�е�ÿһ��Item��һ��ͼ��

class COMMON_INTERFACE CToolIconItem	:
	public CToolItem
{
public:
	CToolIconItem(void);
	virtual ~CToolIconItem(void){};

	/**
	@fn Draw( CDC* pDC)
	@brief Item�Ļ��ƽӿ�
	*/	
	virtual void	Draw( CDC* pDC);

	/**
	@fn ���õ�ǰItem��Icon
	@brief Item�Ļ��ƽӿ�
	@param [in] strIconPath Iconͼ���ļ���·��
	*/
	virtual	void	SetIcon( std::wstring strIconPath) ;

	/**
	@fn ��ȡ��ǰItem��Ӧ��ͼ��·��
	@brief Item�Ļ��ƽӿ�
	@return Iconͼ���ļ���·��
	*/
	std::wstring	GetIconPath(){return m_strIconPath;}


protected:

	std::wstring				m_strIconPath;		//	ͼ���·����Ŀǰ������PNG��ʽ
};

}}