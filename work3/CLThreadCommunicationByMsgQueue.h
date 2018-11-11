#ifndef CLThreadCommunicationByMsgQueue_H
#define CLThreadCommunicationByMsgQueue_H

#include "CLExecutiveCommunication.h"
#include "CLStatus.h"

class CLMessage;
class CLMessageQueue;

class CLThreadCommunicationByMsgQueue : public CLExecutiveCommunication
{
public:
	
	CLThreadCommunicationByMsgQueue(CLMessageQueue *pMsgQueue);
	virtual ~CLThreadCommunicationByMsgQueue();

	virtual CLStatus PostExecutiveMessage(CLMessage *pMessage);

private:
	CLThreadCommunicationByMsgQueue(const CLThreadCommunicationByMsgQueue&);
	CLThreadCommunicationByMsgQueue& operator=(const CLThreadCommunicationByMsgQueue&);

private:
	CLMessageQueue *m_pMsgQueue;
};

#endif
