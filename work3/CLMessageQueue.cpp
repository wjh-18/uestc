#include "CLMessageQueue.h"
#include "CLCriticalSection.h"
#include "CLMessage.h"
#include "CLLogger.h"

CLMessageQueue::CLMessageQueue() : m_Event(true)
{
}

CLMessageQueue::~CLMessageQueue()
{
	while(true)
	{
		CLMessage *pMsg = Pop();  
		if(pMsg == 0)  
			break;
        delete pMsg;   
	}
}

CLStatus CLMessageQueue::PutMessage(CLMessage * pMessage)
{
	CLStatus s = Push(pMessage);
	if(!s.IsSuccess())
	{
		CLLogger::WriteLogMsg("In CLMessageQueue::PutMessage(), Push error", 0);
		return CLStatus(-1, 0);
	}

	CLStatus s2 = m_Event.Set();
	if(!s2.IsSuccess())
	{
		CLLogger::WriteLogMsg("In CLMessageQueue::PutMessage(), m_Event.Set error", 0);
		return CLStatus(-1, 0);
	}
	return CLStatus(0, 0);
}

CLMessage* CLMessageQueue::GetMessage()
{
	CLStatus s = m_Event.Wait();
	if(!s.IsSuccess())
	{
		CLLogger::WriteLogMsg("In CLMessageQueue::GetMessage(), m_Event.Wait error", 0);
		return 0;
	}
    return Pop();
}

CLStatus CLMessageQueue::Push(CLMessage * pMessage)
{
	try
	{
		CLCriticalSection cs(&m_Mutex);
        my_MessageQueue.Push(pMessage);
	}
	catch(const char* str)
	{
		CLLogger::WriteLogMsg("In CLMessageQueue::Push(), exception arise", 0);
		delete pMessage;
		return CLStatus(-1, 0);
	}
    return CLStatus(0, 0);
}

CLMessage* CLMessageQueue::Pop()
{
	try
	{
		CLCriticalSection cs(&m_Mutex);
        if(my_MessageQueue.IsEmpty())
			return 0;
        CLMessage *p = my_MessageQueue.Pop();
		return p;
	}
	catch(const char* str)
	{
		CLLogger::WriteLogMsg("In CLMessageQueue::Pop(), exception arise", 0);
		return 0;
	}
}
