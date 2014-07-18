#pragma once
#include "afxwin.h"
#include <string>
#include "ItemBar.h"

///////////////////////////////////////////////////////////
//	����: CToolLevelItem
//  �๦��������
//  	Bar�е�Item��������51�ĵȼ���Ŀ

class CToolLevelItem	:
	public CToolItem
{
public:
	CToolLevelItem(void);
	CToolLevelItem( CToolLevelItem& barItem);
	CToolLevelItem( CToolLevelItem* pbarItem);
	virtual ~CToolLevelItem(void);


	/**
	@fn Draw( CDC* pDC)
	@brief Item�Ļ��ƽӿ�
	*/	
	virtual void	Draw( CDC* pDC) {} ;

	/**
	@fn ���õ�ǰItem�ĵȼ���Ŀ
	@brief �ȼ����ýӿ�
	@param [in] nLevel �ȼ�
	*/
	virtual	void	SetLevel( UINT nLevel) {};


private:

	std::wstring				m_strIconPath;		//	ͼ���·����Ŀǰ������PNG��ʽ
};
