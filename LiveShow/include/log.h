#pragma once

#include "log_impl.h"

#define EXTERN_LOG()				extern CLogHelper g_ModuleLog;
#define INSTANCE_LOG(Module_Name)	CLogHelper		  g_ModuleLog(Module_Name);
#define LOG_TRACE(lpszFormat, ...)  g_ModuleLog.OutputTraceInfo(lpszFormat, __VA_ARGS__);
#define LOG_WARN(lpszFormat, ...)	g_ModuleLog.OutputWarnInfo(lpszFormat, __VA_ARGS__);
#define LOG_ERROR(lpszFormat, ...)  g_ModuleLog.OutputErrorInfo(lpszFormat, __VA_ARGS__);

//����ļ�����
#define LOG_FILE_CACHE(lpszFormat, ...)  g_ModuleLog.Output2FileCache(lpszFormat, __VA_ARGS__);
//����д���ļ�
#define LOG_FLUSH_CACHE				g_ModuleLog.FlushCache2File();
//����ļ�����
#define LOG_CLEAR_CACHE				g_ModuleLog.ClearFileCache();
