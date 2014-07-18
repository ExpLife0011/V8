#pragma once

#include "FilePathName.h"

#include <map>
#include <set>

class CImageBase;
class CImageTransformParam;
/*
@brief ͼ���
*/
class CImageRepository
{
public:
	/*
	@brief ���캯��
	*/
	CImageRepository(void);

	/*
	@brief ��������
	*/
	virtual ~CImageRepository(void);

	/*
	@brief ���ļ�����ͼƬ
	@param filePathName �ļ���ȫ·����
	@return ʧ�ܷ���NULL
	*/
	virtual CImageBase* LoadImage(LPCTSTR filePathName);

	/*
	@brief ���ڴ��ļ�����ͼƬ
	@param filePathName �ļ���ȫ·����
	@param pzData �ļ�������ָ��
	@param size �ļ��ĳ���
	@return ʧ�ܷ���NULL
	*/
	virtual CImageBase* LoadImage(LPCTSTR filePathName, const char* pzData, long size);

	static BOOL TransformColor(const CImageTransformParam* pParam, LONG color, LONG& transformColor);

	/*
	@brief ����
	*/
	void TextOut(LPCTSTR textName);

	virtual BOOL GetRepositorySize(LONG& lNum, LONG& lSize) const;
protected:
	std::map<CFilePathName, CImageBase*> m_mapImageRepository;
};
