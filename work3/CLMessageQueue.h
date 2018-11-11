#ifndef CLMessageQueue_H
#define CLMessageQueue_H

#include "CLMyQueue.h"
#include "CLStatus.h"
#include "CLMutex.h"
#include "CLEvent.h"

class CLMessage;


class CLMessageQueue
{
private:
	CLMyQueue<CLMessage*> my_MessageQueue;
	CLMutex m_Mutex;
	CLEvent m_Event;
	
public:
	CLMessageQueue();
	virtual ~CLMessageQueue();

public:
	CLStatus PutMessage(CLMessage * pMessage);  
	CLMessage* GetMessage(); 

private:
	CLStatus Push(CLMessage * pMessage);
	CLMessage* Pop();
};

#endif
