#pragma once
#include "common.h"

namespace common{  namespace ui { namespace filedialoghelper {

	/// ��ʾ����ļ��жԻ��򣬷����û�ѡ����ļ��е�·��
	COMMON_INTERFACE CString BrowseForFolder(CString sTitle = L"", DWORD dwFlag = BIF_NEWDIALOGSTYLE, HWND hwndOwner = NULL);

	/// ��ʾ���ļ��Ի���
	COMMON_INTERFACE INT ShowOpenFileDlg(OUT CString& sFilePath, 
		IN OUT PBOOL pbReadOnly = NULL, 
		IN LPCTSTR lpszDefExt = NULL,
		IN LPCTSTR lpszFileName = NULL,
		IN LPCTSTR lpszFilter = NULL,	// eg: "ͼ���ļ�(*.bmp;*.jpg;*.gif)|*.bmp;*.jpg;*.gif|�����ļ�(*.*)|*.*||"
		IN DWORD dwFlags = OFN_ENABLESIZING,
		IN CWnd* pParentWnd = NULL
		);

	/// ��ʾ�����ļ��Ի���
	COMMON_INTERFACE INT ShowSaveFileDlg(OUT CString& sFilePath, 
		IN LPCTSTR lpszDefExt = NULL,
		IN LPCTSTR lpszFileName = NULL,
		IN LPCTSTR lpszFilter = NULL,	// eg: "ͼ���ļ�(*.bmp;*.jpg;*.gif)|*.bmp;*.jpg;*.gif|�����ļ�(*.*)|*.*||"
		IN DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		IN CWnd* pParentWnd = NULL
		);


}
}
}