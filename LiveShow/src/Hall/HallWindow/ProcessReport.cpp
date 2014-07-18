#include "stdafx.h"
#include "ProcessReport.h"
#include <algorithm>
#include "tlhelp32.h"
#include "..\Hall.h"


std::wstring CProcessReport::m_processWindows = _T("");
CProcessReport::CProcessReport()
{
	m_OpponentsProcessName.push_back(_T("yy.exe"));
	m_OpponentsProcessName.push_back(_T("9158.exe"));
	m_OpponentsProcessName.push_back(_T("sinashow.exe"));
	m_OpponentsProcessName.push_back(_T("chathall.exe"));
	m_OpponentsProcessName.push_back(_T("guagua.exe"));
	m_OpponentsProcessName.push_back(_T("eph.exe"));
	m_OpponentsProcessName.push_back(_T("99lover.exe"));
	m_OpponentsProcessName.push_back(_T("293show.exe"));

	m_OpponentsWindowsText.push_back(_T("���䷿�㳡"));
	m_OpponentsWindowsText.push_back(_T("xiu.56.com"));
	m_OpponentsWindowsText.push_back(_T("������"));
	m_OpponentsWindowsText.push_back(_T("������Ƶ����"));
	m_OpponentsWindowsText.push_back(_T("����show"));
	m_OpponentsWindowsText.push_back(_T("�ѹ�����"));
	m_OpponentsWindowsText.push_back(_T("ibo�㳡"));
	m_OpponentsWindowsText.push_back(_T("������Ƶ������"));
	m_OpponentsWindowsText.push_back(_T("�Ѻ��㳡"));
	m_OpponentsWindowsText.push_back(_T("5see�����㳡"));
	m_OpponentsWindowsText.push_back(_T("��������"));
	
}
//���Ͷ��ֽ�����������������
void CProcessReport::OnProcessReport()
{
	std::wstring strRunProcName = GetProcessName();  //��ѯ��ȡ�������еĶ��ֽ�����
	if(strRunProcName == _T(""))
	{
		return;
	}

	//�ϴ����ֽ�����������������

	core::ReportCollectInfoEvent *runProcEvent = new core::ReportCollectInfoEvent();	
	core::ReportCollectInfoEvent::Key2Value runProc;
	runProc.key = COLLECT_INFO_PROCESS;
	runProc.value = strRunProcName;
	runProcEvent->vecCollecInfo.push_back(runProc);

	Event _event = MakeEvent<MODULE_ID_HALL>()(core::EVENT_VALUE_CORE_REPORT_COLLECT_INFO, 
		MODULE_ID_CORE,0,0,0,runProcEvent);
	g_HallModule->m_pModuleManager->PushEvent(_event);
}

//��ȡ�������еĶ��ֽ�����
std::wstring CProcessReport::GetProcessName()
{
	std::wstring runProcName;
	runProcName = GetProcess(m_OpponentsProcessName,ProcessType::PROCESS_NAME );  //ʹ�ý������б�����������еĶ��ֽ���
	if(runProcName == _T("")) //δ�ҵ�
	{
		runProcName = GetProcess(m_OpponentsWindowsText,ProcessType::PROCESS_WINDOWS ); //ʹ�ô������б�����������еĶ��ִ��ڱ���
	}

	return runProcName;
}

std::wstring CProcessReport::GetProcess(std::vector<std::wstring> &processName,ProcessType pType)
{
	std::wstring procName;
	if(pType == PROCESS_WINDOWS)
	{
		procName = FindProcessWindowsText(&processName);
		return procName;
	}


	HANDLE toolhelp = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(toolhelp == NULL)
	{
		return procName;
	}

	PROCESSENTRY32 processinfo;
	processinfo.dwSize   =   sizeof(PROCESSENTRY32);
	BOOL start = Process32First(toolhelp, &processinfo); //��ȡ��һ���������еĽ���			

	while(start)
	{

		std::wstring runProcName = processinfo.szExeFile;
		std::transform(runProcName.begin(),runProcName.end(),runProcName.begin(),tolower);  //תСд


		vector<std::wstring>::iterator itfind;
		itfind = find(processName.begin(),processName.end(),runProcName);
		if(itfind != processName.end()) //�ҵ�
		{	
			procName = runProcName;
			break;
		}		

		start = Process32Next(toolhelp, &processinfo); //��һ���������еĽ���

	}

	CloseHandle(toolhelp);

	return procName;

}



std::wstring CProcessReport::FindProcessWindowsText(std::vector<std::wstring> *processName)
{
	//ö�����д��ڱ���
	std::wstring winName;
	m_processWindows = _T("");	
	EnumWindows(EnumWindowsProc,(LPARAM)processName);  //ö�����д���
	OutputDebugString(_T("FindProcessWindowsText"));
	OutputDebugString(m_processWindows.c_str());  

	return m_processWindows;

}

//ö�����д��ڻص�����
BOOL CProcessReport::EnumWindowsProc(HWND hwnd,LPARAM lparam)
{
	std::vector<std::wstring> *processName = (std::vector<std::wstring>*)lparam;
	TCHAR windowName[1024];
	memset(windowName, 0, 1024 * sizeof(TCHAR));
	GetWindowText(hwnd,windowName,1024);	//ȡ�ô��ڱ���
	std::wstring strName = windowName;
	std::wstring strProcessName;
	if(strName != _T(""))
	{
		std::transform(strName.begin(),strName.end(),strName.begin(),tolower);  //תСд

		for(int i=0;i<processName->size();i++)
		{
			strProcessName = processName->at(i);
			if(strName.find(strProcessName) != -1)  //���ֲ��Ҵ������а���ָ���������ı�����
			{
				m_processWindows = strProcessName;			
				return false;  //���ҵ��������ټ���ö��
			}
		}
	}	

	return true;  //����ö��

}
