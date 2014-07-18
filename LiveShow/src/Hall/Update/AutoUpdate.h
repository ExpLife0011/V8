#pragma once
#include "51ktv.h"
#include <map>
#include "../../include/ui/TrayMgr.h"
#include "UpdateGuideDlg.h"
#include "CheckUpdateDlg.h"

using namespace std;

#define UM_TRAY_ICON_NOTIFY_MESSAGE   WM_USER + 300   //����ʱ���̵���Ϣ
#define UM_DOWNLOAD_PROCESS_FULL      WM_USER + 301   //���ؽ�������
#define UM_UPDATE_TEXT			  WM_USER + 302   //������ʾ��Ϣ
#define UM_EXIT_AUTOUPDATE        WM_USER + 303   //�˳��Զ�����
#define UM_RES_UPDATE_SUCCESS     WM_USER + 304   //�����ļ��Զ����³ɹ�

#define VERDOWN_LOCAL_DIR _T("VersionDown")   //�°汾�������ı���Ŀ¼
#define VERSION_FILE_NEW  _T("NewVersion.ini")  //���°汾�����ļ�
#define VERSION_FILE_CUR  _T("CurVersion.ini")  //��ǰ�汾�����ļ�

#define INI_SIZE_16 16
#define INI_SIZE_280 280

//��ǰ״̬
#define STATE_AUTO 0   //׼����
#define STATE_NOUPDATE 1 //������
#define STATE_UPLOAD 2  //������
#define STATE_UPLOADEND 3 //���ؽ���
#define STATE_UPLOADERROR 4 //����ʧ��  
//��ǰ״̬

//������ʾ
enum UpdateText
{
	UPDATE_TEXT_AUTOUPDATE = 0, //������ʾ  _T("�������ظ��³���")
	UPDATE_TEXT_FAIL = 1, //������ʾ _T("����ʧ��")

};
enum VerUpdateType
{
	VER_NO = 0, //����Ҫ����
	VER_MAIN = 1, //���汾����   ��װ
	VER_CONFIG = 2, //�����ļ�����  ����
};

//�汾�ṹ
struct NewVersion
{
	CString m_sVerURl;//http�������°汾����url
	CString m_sVerLocal;  //����������Ŀ¼   
	CString m_sVerNum; //�汾��
	CString m_sVerFile; //�ļ���
};

//�汾��Ϣ
struct VersionInfo
{
	CString m_sCurMainVerNum  ;  //��ǰ�����
	CString m_sCurConfigVerNum ; //��ǰ���ð汾��

	NewVersion m_NewMain;    //�������汾��Ϣ
	NewVersion m_NewConfig;  //�������ð汾��Ϣ
};

//��������
struct webDownTask
{
	webDownTask()
	{
		m_nSeqNo = 0;
		m_uPercent = 0;
		m_uTotalLength = 0;
		m_uFinishedLength = 0;
		m_downEnd = false;
	}

	uint32	m_nSeqNo;		    		//	������������к�

	CString m_strDownUrl;               //  http����url
	CString m_strDownLocal;             //  ����������·��
	uint32	m_uPercent;					//	���ؽ��ȣ� 50 ��ʾ ���50%
	uint32	m_uTotalLength;				//	���ص��ܳ���
	uint32	m_uFinishedLength;			//	�Ѿ�������ϵ��ܳ���
	bool    m_downEnd;                  //  �Ƿ��������
};

//������������
struct TotalWebDownTask
{
	map<uint32,webDownTask> m_mapWebDown;  //������������
	uint32 m_uAllPercent;                  //�����ؽ��ȣ� 50 ��ʾ ���50%
	uint32 m_uAllTotalLength;              //�����س���
	uint32 m_uAllFinishedLength;           //�ܵ��Ѿ�������ϵĳ���

};

//�ڴ�ӳ������ݽṹ
typedef struct tagUpdateMap  //�ͻ����Զ�����ʱ���ͻ������Զ�����֮���ڴ�ӳ��ʱ��������ݽṹ
{	
	unsigned short  usUpdateType;  //��������  1-���汾����   2-�����ļ�����	
	WCHAR			DownPath[MAX_PATH];   //���ش��·��
	WCHAR			ClientPath[MAX_PATH];   //�ͻ������г���·��
	WCHAR           c179AppDataPath[MAX_PATH];  //�ͻ���������Դ·��
	HWND            CallUpdate_ClientHWnd;    //�����Զ����³���Ŀͻ��˾��
	HWND            DownLoad_ClientHWnd;      //�����Զ����³���Ŀͻ������ضԻ�����
	HWND            Update_Hwnd;             //�Զ����³�����
	NOTIFYICONDATA  trayNid;         //����ʱ������ͼ������
} UPDATEMAP, *PUPDATEMAP;
//
//==========================================================================================
// ��    ����CUpdateMap   �ڴ�ӳ����
// �����������������򿪻��ȡ�ڴ�ӳ���������
// �������ڣ�2012-1-5
// �޸����ڣ�
// ��    ����ʹ���ڴ�ӳ��ǰ���ȵ���CreateFileMap()��������ڴ�ӳ�䣬
//			 �ٵ���UseUpdateMapDateBeginLock() ��ʼʹ���ڴ�ӳ�����ݲ�����
//           ʹ����֮�����UseUpdateMapDateEndUnLock() ����ʹ���ڴ�ӳ�����ݲ�����			 
//           ������CloseFileMap()�ر��ڴ�ӳ��
//	         ע��UseUpdateMapDateBeginLock()һ��Ҫ��UseUpdateMapDateEndUnLock()�ɶ�ʹ��
// Ŀ    �أ����ڿͻ��˽������Զ�����������̼������ͨ��
//==========================================================================================

class CUpdateMap
{
public:
	CUpdateMap();
	virtual ~CUpdateMap();

	void CreateFileMap(CString MapName); //��������ڴ�ӳ��	
	bool UseUpdateMapDateBeginLock(PUPDATEMAP &pDate);  //��ʼʹ���ڴ�ӳ�����ݲ�����
	bool UseUpdateMapDateEndUnLock(PUPDATEMAP &pDate);  //����ʹ���ڴ�ӳ�����ݲ�����
	void CloseFileMap();  //�ر��ڴ�ӳ��

private:
	HANDLE m_hShareMem;
	void *m_pViewData;	//�ڴ�ӳ�������
	HANDLE m_DateMutex;  //�ڴ�ӳ�����ݵĻ�����   ���Ի���������ͬʱ�����ڴ�ӳ��

};

//==========================================================================================
// ��    ����CAutoUpdate   �Զ�������
// �����������Զ���web�������е�¼�ɹ�֮������������ļ���
//			 �������֮���Զ��ж��Ƿ���Ҫ�����ͻ���(�°汾��װ)������ļ�(���������ļ�)
//  	     ����Ҫ�������������������������°����Զ���������������а�װ�򸲸�
// �������ڣ�2012-1-10
// �޸����ڣ�
// ��    ����
// Ŀ    �أ��û��ͻ����Զ�����ʱ�ĸ��°�����
//==========================================================================================
class CUpdateGuideDlg;
class CAutoUpdate 
{
public:
	CAutoUpdate();
	CAutoUpdate(CString MapName);
	virtual ~CAutoUpdate();
	
	void ShowCheckUpdateDlg(CWnd *pHall); //��ʾ�����¶Ի��򣬲���ʼ������°汾
	void OnEventRespWebDown(Event const& e);  //web�������ʱ�ķ��غ���,  e.param2��ʾ ��������ϵ����к�
	bool GetTatalDownProcess(uint32 &nTotalTime,uint32 &nFinishTime,uint32 &nProcess); //��ȡ�ܵ����ؽ���	
	static CString GetCurVersionInfo();  //�������ļ��л�ȡ��ǰ��ʾ�汾��
	void LoadTrayUpdate();  //���ظ���ʱ������ͼ�꣬ �����ʱ������ͼ���Ƕ�̬�ģ��ɶ��ico��ɣ���˸ú���Ӧ���ڶ�ʱ����
	static CString GetAppTip(); //��ȡNewVersion.ini�ļ���AppTip��tipֵ
	void ExitAutoUpdate();

private:
	void InitAutoUpdate(HWND clickHWND);  //��ʼ�����Լ���web�������°汾�ļ�	
	void DownNewPackage();  //��������������°�
	void UpdateBegin();    //�����Զ���������ʼ�������汾�������������ļ��ĸ���

	CString GetNewVersionInfo();  //�����������ļ��л�ȡ������ʾ�汾��
	int32 SendWebDown(CString formUrl, CString ToLocal, int nTimeOut=0,BOOL bResumable = FALSE);  //����web�������󣬴�formUrl��url��ַ����������ToLocal��ַ�����ظ�������������к�, nTimeOut:��
	CString GetNameFormUrl(CString Url); //��url��ַ�л�ȡ�ļ���
	void ClearDir(CString deleteDir);  //ɾ��ָ��Ŀ¼��Ŀ¼�µ������ļ�
	void OpenDirectory(CString PositionDir); //�򿪱���ָ��Ŀ¼����û�и�Ŀ¼���Զ�����
	bool FindWebDownTask(uint32 nSeqNo,webDownTask &downTask);  //�����������к��ּ��ֲ�ѯ��������
	bool FindSeqNoInDownTask(uint32 nSeqNo); //��ѯnSeqNo���к��Ƿ�������������
	void SetWebDownEnd(uint32 nSeqNo);   //����nSeqNo���к������������
	bool IsWebDownTotalEnd();  //�������������Ƿ����������
	void GetVersionInfo(); //��NewVersion.ini���°汾�����ļ���CurVersion.ini��ǰ�汾�����ļ��л�ȡ�汾��Ϣ
	VerUpdateType IsMainConfigUpdate();  //�ж������汾���������ļ�����	

	void InitTrayUpdate();  //���汾����ʱ�ĳ�ʼ������ͼ��
	void ReleaseTrayUpdate();  //���汾����ʱ���ͷ�����ͼ��	
	void ShowUpdateGuideDlg(); //��ʾ������
	void CloseCheckUpdateDlg(bool isShowHall); //���������֮��Ĺرռ����¶Ի���

private:
	PUPDATEMAP m_MapDate179;  //�ͻ������Զ�����֮����ڴ�ӳ������ָ��
	CString m_strMapName; //�ͻ������Զ�����֮����ڴ�ӳ����
	CUpdateMap m_Map179; //�ڴ�ӳ��
	VersionInfo m_VerInfo;  //�汾��Ϣ
	TotalWebDownTask  m_downTask; //������������
	uint32 m_NewVersionNSeqNO; //NewVersion.ini���°汾�����ļ����������к�
	int m_iAutoState;//�Զ�����״̬��0-׼���� 1-������  2-������  3-���ؽ���  4-����ʧ�� 
	CString m_strNewVerFile; //NewVersion.ini���°汾�����ļ�·��
	CString m_strCurVerFile; //CurVersion.ini��ǰ�汾�����ļ�·��	
	CString m_NewVersionDownDir;  //�°汾����������Ŀ¼
	CTrayMgr m_trayMgrUpdate; //����ʱ������
	vector<HICON> m_trayUpdatePath;  //����ʱ�Ķ�̬����ͼ���ַ
	int m_trayUpdateCur;  //����ʱ�Ķ�̬����ͼ�굱ǰ�±�
	VerUpdateType m_updatetype;
	CUpdateGuideDlg updateGudie;  //������
	CCheckUpdateDlg m_checkUpdateDlg;  //�����¶Ի���

public:
	HWND m_clickHWND;  //�ͻ��˴���


};