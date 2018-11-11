#ifndef CLThreadForMsgLoop_H
#define CLThreadForMsgLoop_H

#include "CLStatus.h"

class CLMessageObserver;
class CLThread;


class CLThreadForMsgLoop
{
public:
	
	CLThreadForMsgLoop(CLMessageObserver *pMsgObserver, const char *pstrThreadName);
	CLThreadForMsgLoop(CLMessageObserver *pMsgObserver, const char *pstrThreadName, bool bWaitForDeath);
	virtual ~CLThreadForMsgLoop();

	
	CLStatus Run(void *pContext);

private:
	CLThreadForMsgLoop(const CLThreadForMsgLoop&);
	CLThreadForMsgLoop& operator=(const CLThreadForMsgLoop&);

private:
	CLThread *m_pThread;

	
	bool m_bWaitForDeath;
};

#endif
