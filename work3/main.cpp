#include "CLExecutiveFunctionProvider.h"
#include "CLExecutiveFunctionForMsgLoop.h"
#include "CLExecutiveNameServer.h"
#include "CLThread.h"
#include "CLThreadForMsgLoop.h"
#include "CLMessageQueue.h"
#include "CLMessage.h"
#include "CLMsgLoopManagerForMsgQueue.h"
#include "CLMessageObserver.h"
#include <iostream>
using namespace std;
#define HELLO_MSG 0    
#define QUIT_MSG 1 
class CLMessageProvider;
class CLSHelloMessage : public CLMessage//继承CLMessage
{
private:
    public:
    	friend class CLMessageProvider;
    CLSHelloMessage():CLMessage(HELLO_MSG)//构造器
	{	
	}
	virtual ~CLSHelloMessage()
	{
	}
  };
  class CLQuitMessage : public CLMessage  //继承CLMessage的退出消息
 {
  public:
    CLQuitMessage() : CLMessage(QUIT_MSG)
    {
	}
	virtual ~CLQuitMessage()
	{
	}
  };
  class CLMessageProvider : public CLMessageObserver//CLMessageProvider继承 
 //CLMessageObserver，是线程执行体
{
public:
	CLMessageProvider()
	{
	}
	virtual ~CLMessageProvider()
	{
	}
	virtual CLStatus Initialize(CLMessageLoopManager *pMessageLoop, void* pContext)
	{
		//向系统注册回调函数
		pMessageLoop->Register(HELLO_MSG, (CallBackForMessageLoop)(&CLMessageProvider::Do_HelloMsg));
		pMessageLoop->Register(QUIT_MSG, (CallBackForMessageLoop)(&CLMessageProvider::Do_QuitMsg));
		return CLStatus(0, 0);
	}
	
	
	CLStatus Do_HelloMsg(CLMessage *pM)
	{
		CLSHelloMessage *pHelloMsg = (CLSHelloMessage *)pM;
		cout<<"Hello"<<endl; //输出
		return CLStatus(0, 0);
	}	
	CLStatus Do_QuitMsg(CLMessage *pM)
	{
		cout << "quit..." << endl;//退出消息
		return CLStatus(QUIT_MESSAGE_LOOP, 0);
	}
};
int main()
{	
	CLThreadForMsgLoop myTthread(new CLMessageProvider, "childThread", true);//子线程创建
	myTthread.Run(0);
	CLExecutiveNameServer::PostExecutiveMessage("childThread", new CLSHelloMessage());//向子线程发送消息
	CLExecutiveNameServer::PostExecutiveMessage("childThread", new CLQuitMessage());
	return 0;
}
