#pragma once
#include <vector>
#include <list>

enum ProcessType 
{
	PROCESS_NAME,
	PROCESS_WINDOWS,
};

class CProcessReport
{
public:
	CProcessReport();
	~CProcessReport(){};

public:
	void OnProcessReport(); //���Ͷ��ֽ�����������������

private:
	std::wstring GetProcessName(); //��ȡ�������еĶ��ֽ�����
	std::wstring GetProcess(std::vector<std::wstring> &processName,ProcessType pType);  //
	std::wstring FindProcessWindowsText(std::vector<std::wstring> *processName);
	static BOOL CALLBACK EnumWindowsProc(HWND hwnd,LPARAM lparam); //ö�����д��ڻص�����

private:
	std::vector<std::wstring> m_OpponentsProcessName; //���ֽ������б�
	std::vector<std::wstring> m_OpponentsWindowsText; //���ֽ��̴������б�	
	static std::wstring m_processWindows;

};