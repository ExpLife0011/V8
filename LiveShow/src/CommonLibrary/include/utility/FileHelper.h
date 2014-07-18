/*
@file:		FileHelper.h
@purpose:	�ļ��İ���������
@version:	1.0 2007.3.28 create zhangjb
*/

#pragma once

#include <string>
#include <vector>
#include "../Common.h"

#include "shlwapi.h"
#pragma comment(lib, "shlwapi.lib")

#include "winver.h"
#pragma comment(lib, "version.lib")

namespace common 
{
	namespace utility
	{
		namespace filehelper{
		/*
		/*function ���·���ϵ����һ���ļ�/Ŀ¼��
		/*@param [in] sPath  �����ȫ·��
		/*return ����ֵΪ�ļ����һ���ļ�/Ŀ¼��
		*/
		COMMON_INTERFACE std::wstring GetLastName(const std::wstring& sPath);

		/*
		/*function ��ȡ�ļ���չ��
		/*@param [in] sPath ������ļ�ȫ·��
		/*return �����ļ�����չ��
		*/
		COMMON_INTERFACE std::wstring GetFileExt(const std::wstring& sPath);

		
		/*
		/*function  ����ϼ���Ŀ¼
		/*@param [in] sPath ������ļ�ȫ·��
		/*@param [out] pCStringLastName �������һ���ļ���/Ŀ¼
		/*return �����ϼ�Ŀ¼��·��
		*/
		COMMON_INTERFACE std::wstring GetParentDir(const std::wstring& sPath, std::wstring* pCStringLastName = NULL);

		
		/*
		/*function ��õ�ǰ���̵�exe�ļ�·��
		/*@param [out] ���ص�ǰ���̵�exe���ļ���
		/*return ���ص�ǰ���̵�exe���ļ�·��
		*/
		COMMON_INTERFACE std::wstring GetCurPath(std::wstring* pCStringFileName = NULL);

		/*
		/*function ��õ�ǰ���̵�exe�ļ�����Ŀ¼
		/*@param [out] ���ص�ǰ���̵�exe���ļ���
		/*return ���ص�ǰ���̵�exe���ڵ�Ŀ¼
		*/
		COMMON_INTERFACE std::wstring GetCurDir(std::wstring* pCStringDirName = NULL);

		/*
		/*function �ļ�/Ŀ¼�Ƿ����
		/*@param [in] szFilePath �ļ�/Ŀ¼��·��
		/*return ���ڷ���TRUE����֮����FALSE
		*/
		COMMON_INTERFACE BOOL IsExist(LPCTSTR szFilePath);

		/*
		/*function Ŀ¼�Ƿ����
		/*@param [in] szFilePath Ŀ¼��·��
		/*return ���ڷ���TRUE����֮����FALSE
		*/
		COMMON_INTERFACE BOOL IsDirExist(LPCTSTR szFilePath);

		/*
		/*function �ļ��Ƿ����
		/*@param [in] szFilePath �ļ�·��
		/*return ���ڷ���TRUE����֮����FALSE
		*/
		COMMON_INTERFACE BOOL IsFileExist(LPCTSTR szFilePath);

		/*
		/*function ������·���ϵ�����Ŀ¼
		/*@param [in] strPath Ŀ¼·��
		/*return �����ɹ�����TRUE,��֮����FALSE
		*/
		COMMON_INTERFACE BOOL CreateAllDirectory(std::wstring strPath);

		//
		/*
		/*function ��ȡϵͳĿ¼��ʱ·����ע�⣬�Ƕ�·��
		/*@param void
		/*return ����ϵͳ��ʱĿ¼��·��
		*/
		COMMON_INTERFACE std::wstring GetSysTempDir();

		/*
		/*function ɾ��Ŀ¼������Ŀ¼�µ������ļ���Ŀ¼��
		/*@param [in] sDir ��Ҫɾ����Ŀ¼·��
		/*return ɾ���ɹ�����TRUE,��֮����FALSE
		*/
		COMMON_INTERFACE BOOL DeleteDir(const std::wstring& sDir);


		/*
		/*function �ļ��Ƿ�ɶ�(���Ƿ񱻱�ĳ���ռ��)
		/*@param [in] szFilePath �ļ�ȫ·��
		/*return �ļ��ɶ�����TRUE,��֮���� FALSE
		*/
		COMMON_INTERFACE BOOL IsFileReadable(LPCTSTR szFilePath);

		/*
		/*function �ļ��Ƿ��д(���Ƿ񱻱�ĳ���ռ��)
		/*@param [in] szFilePath �ļ�ȫ·��
		/*return �ļ���д����TRUE,��֮���� FALSE
		*/
		COMMON_INTERFACE BOOL IsFileWriteable(LPCTSTR szFilePath);

		/*
		/*function ��ȡ�ļ��Ĵ�С(��λ:�ֽڣ���ȡ�Ĵ�С��0xFFFFFFFF֮��)
		/*@param [in] szFilePath �ļ�·��
		/*@param [out] pdwHigh �ļ���С�ĸ߶˲���ֵ,����ΪNULL
		/*return �����ļ��Ĵ�С(��λ:�ֽ�)
		*/
		COMMON_INTERFACE DWORD GetFileSize(LPCTSTR szFilePath, DWORD* pdwHigh = NULL);

		/*
		/*function ��ȡĿ¼�Ĵ�С��Ŀ¼�������ļ���С�ĺͣ�
		/*@param [in] sDirPath Ŀ¼·��
		/*return ����Ŀ¼�Ĵ�С(��λ���ֽ�)
		*/
		COMMON_INTERFACE DWORD GetDirSize(const std::wstring& sDirPath);

		/*
		/*function ��ȡ�ļ��Ĵ���ʱ�䣬����޸�ʱ�䣬������ʱ�� 
		/*@param [in] �ļ�·��
		/*@param [out] lpCreateTime �ļ��Ĵ���ʱ��
		/*@param [out] lpLastAccessTime �ļ��ķ���ʱ��
		/*@param [out] lpLastWriteTime �ļ����޸�ʱ��
		/*return �ɹ�����TRUE,ʧ�ܷ���FALSE
		*/
		COMMON_INTERFACE BOOL  GetFileTime(const std::wstring& sPath, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime);

		/*
		/*function �����ļ��Ĵ���ʱ�䣬����޸�ʱ�䣬������ʱ�� 
		/*@param [in] �ļ�·��
		/*@param [in] lpCreateTime �ļ��Ĵ���ʱ��
		/*@param [in] lpLastAccessTime �ļ��ķ���ʱ��
		/*@param [in] lpLastWriteTime �ļ����޸�ʱ��
		/*return �ɹ�����TRUE,ʧ�ܷ���FALSE
		*/
		COMMON_INTERFACE BOOL  SetFileTime(const std::wstring& sPath, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime);

		/*
		/*function ��ȡ�ļ���ICONͼ�� 
		/*@param [in] �ļ�·��
		/*@param [in] �Ƿ���Ŀ¼
		/*return �ɹ������ļ�ICON�ľ����ʧ�ܷ���FALSE
		*/
		COMMON_INTERFACE HICON GetFileIcon(LPCTSTR szFilePath,BOOL bDir);

		/*
		/*function ������д���ļ�
		/*@param [in] pBuf ���ݵ��ڴ���ʼ��ַ
		/*@param [in] nBufLen ���ݵĳ���(��λ:�ֽ�)
		/*@param [in] sFile   �ļ�·��
		/*return �ɹ�����TRUE,ʧ�ܷ���FALSE
		*/
		COMMON_INTERFACE BOOL  WriteFile(BYTE* pBuf, int nBufLen, const std::wstring& sFile);


		//////////////////////////////////////////////////////////////////////////
		enum Mode
		{
			Exist=00,
			Write=02,
			Read=04,
			ReadWrite=06,
		};

		/*
		/*function �ж��ļ��Ƿ���е�ָ���ķ������� 
		/*@param [in] path �ļ�·��  (���ַ�)
		/*@param [in] mode �ļ���������
		/*return �������ָ�������ԣ�����true,��֮����false
		*/
		COMMON_INTERFACE bool FileAccessW(std::wstring const &path,int mode);
		
		/*
		/*function �ж��ļ��Ƿ���е�ָ���ķ������� 
		/*@param [in] path �ļ�·�� 
		/*@param [in] mode �ļ���������
		/*return �������ָ�������ԣ�����true,��֮����false
		*/
		COMMON_INTERFACE bool FileAccessA(std::string const &path,int mode);


		/*
		/*function ���ļ��ж�ȡ����
		/*@param [in] name �ļ�·��
		/*@param [out] vec ������ݵ����� ,ע��:Ҫ��ȡ���ݵĳ���=vec.size()
		/*@param [out] realRead ʵ�ʶ�ȡ���ݵĴ�С(��λ���ֽ�)
		/*@param [in] offset  �ļ����ݵ���ʼλ��(��λ:�ֽ�)
		/*return �ɹ�����COMMON_SUCCESS ��ʧ�ܷ���COMMON_FAILED
		*/
		COMMON_INTERFACE CommonResult ReadFileW(std::wstring const & name,std::vector<char> & vec,DWORD & realRead,uint32 offset=0);
		
		/*
		/*function д�����ݵ��ļ�
		/*@param [in] name �ļ�·��
		/*@param [in] vec ������ݵ����� ��ע�⣺Ҫд�����ݵĳ���=vec.size()
		/*@param [out] realRead ʵ��д�����ݵĴ�С(��λ���ֽ�)
		/*@param [in] offset  �ļ����ݵ���ʼλ��(��λ:�ֽ�)
		/*return �ɹ�����COMMON_SUCCESS ��ʧ�ܷ���COMMON_FAILED
		*/
		COMMON_INTERFACE CommonResult WriteFileW(std::wstring const & name,std::vector<char> const & vec,DWORD & realWrite,uint32 offset=0);
		
		/*
		/*function ���ļ��ж�ȡ����
		/*@param [in] hFile �ļ����
		/*@param [out] vec ������ݵ����� ,ע��:Ҫ��ȡ���ݵĳ���=vec.size()
		/*@param [out] realRead ʵ�ʶ�ȡ���ݵĴ�С(��λ���ֽ�)
		/*@param [in] offset  �ļ����ݵ���ʼλ��(��λ:�ֽ�)
		/*return �ɹ�����COMMON_SUCCESS ��ʧ�ܷ���COMMON_FAILED
		*/
		COMMON_INTERFACE CommonResult ReadFileH(HANDLE hFile,std::vector<char> & vec,DWORD & realRead,uint32 offset);
		
		/*
		/*function д�����ݵ��ļ�
		/*@param [in] hFile �ļ����
		/*@param [in] vec ������ݵ�����,ע�⣺Ҫд�����ݵĳ���=vec.size() 
		/*@param [out] realRead ʵ��д�����ݵĴ�С(��λ���ֽ�)
		/*@param [in] offset  �ļ����ݵ���ʼλ��(��λ:�ֽ�)
		/*return �ɹ�����COMMON_SUCCESS ��ʧ�ܷ���COMMON_FAILED
		*/
		COMMON_INTERFACE CommonResult WriteFileH(HANDLE hFile,std::vector<char> const & vec,DWORD & realWrite,uint32 offset);
		
		/*
		/*function ��ȡ�ļ��������Ϣ
		/*@param [in] name �ļ�·��
		/*@param [out] BY_HANDLE_FILE_INFORMATION_ �ļ�����Ϣ
		/*return  �ɹ�����COMMON_SUCCESS ��ʧ�ܷ���COMMON_FAILED
		*/
		COMMON_INTERFACE CommonResult GetFileInformationW(std::wstring name ,BY_HANDLE_FILE_INFORMATION & BY_HANDLE_FILE_INFORMATION_);

		COMMON_INTERFACE CommonResult GetFileInformationH(HANDLE hFile, BY_HANDLE_FILE_INFORMATION & BY_HANDLE_FILE_INFORMATION_);

		COMMON_INTERFACE bool CreateUnicodeFile(LPCTSTR szFilePath,bool arways = false);

		//FILETIME ת time_t
		COMMON_INTERFACE void FileTimeToUinxTime(LPFILETIME pft,time_t *t); 

	    //time_t ת FILETIME
	    COMMON_INTERFACE void UinxTimeToFileTime(time_t t,LPFILETIME pft);

	}
	}
}

