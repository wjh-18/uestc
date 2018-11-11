#ifndef CLLog_H
#define CLLog_H

#include <pthread.h>
#include "CLStatus.h"

/*
�������ļ�LOG_FILE_NAME�У���¼��־��Ϣ
*/
class CLLog
{
public:
	static CLLog* GetInstance();

	static CLStatus WriteLogMsg(const char *pstrMsg, long lErrorCode);

	CLStatus WriteLog(const char *pstrMsg, long lErrorCode);

private:
	CLLog(const CLLog&);
	CLLog& operator=(const CLLog&);

	static pthread_mutex_t *InitializeMutex();

private:
	CLLog();
	~CLLog();

	int m_Fd;
	pthread_mutex_t *m_pMutexForFile;

	static CLLog * volatile  m_pLog;
	static pthread_mutex_t *m_pMutex;
};

#endif