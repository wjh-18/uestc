#ifndef CLNonThreadProxy_H
#define CLNonThreadProxy_H

#include "CLStatus.h"

class CLMessageObserver;
class CLExecutiveFunctionProvider;

/*
�����������߳�ֱ�ӽ�����Ϣѭ���������Ǵ������߳�
*/
class CLNonThreadProxy
{
public:
	/*
	pMsgObserverӦ�Ӷ��з��䣬�Ҳ��ص���delete��pstrThreadName��������߳����Ʊ�����Ψһ��
	*/
	CLNonThreadProxy(CLMessageObserver *pMsgObserver, const char *pstrThreadName);
	virtual ~CLNonThreadProxy();

	CLStatus Run(void *pContext);

private:
	CLNonThreadProxy(const CLNonThreadProxy&);
	CLNonThreadProxy& operator=(const CLNonThreadProxy&);

private:
	CLExecutiveFunctionProvider *m_pFunctionProvider;
};

#endif