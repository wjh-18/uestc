#ifndef CLThreadProxy_H
#define CLThreadProxy_H

#include "CLStatus.h"

class CLMessageObserver;
class CLThread;

/*
�������ڴ���һ���̣߳�����õ�ͨ�Ż�����CLMessageQueue��
*/
class CLThreadProxy
{
public:
	/*
	pMsgObserverӦ�Ӷ��з��䣬�Ҳ��ص���delete��pstrThreadName��������߳����Ʊ�����Ψһ��
	Ĭ�������bWaitForDeathΪfalse����Ϊtrue����������������еȴ����߳�����
	*/
	CLThreadProxy(CLMessageObserver *pMsgObserver, const char *pstrThreadName);
	CLThreadProxy(CLMessageObserver *pMsgObserver, const char *pstrThreadName, bool bWaitForDeath);
	virtual ~CLThreadProxy();

	/*
	Run�������۷�����ȷ�������ֻ�ɵ���һ�Ρ�������һ��CLThreadProxy����
	*/
	CLStatus Run(void *pContext);
	
private:
	CLThreadProxy(const CLThreadProxy&);
	CLThreadProxy& operator=(const CLThreadProxy&);

private:
	CLThread *m_pThread;
	
	bool m_bWaitForDeath;
};

#endif