#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "ModuleManager.h"

class CMainApp : public CWinApp
{
public:
	CMainApp();

	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	void CMainApp::OnCycleTrigger(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	void CreatCycleWnd();
	void DestroyCycleWnd();

private:

	BOOL CheckSingleInstance();

	ModuleManagerImpl module_manager;
	HANDLE m_hMutex;
	HANDLE m_hMapFile;
};

extern CMainApp theApp;