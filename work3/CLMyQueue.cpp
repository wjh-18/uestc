#include <iostream>
struct CLNode{		
    int data;
    struct CLNode *next;
};
class CLMyQueue
{
private:
    struct CLNode *QueueHead;//队头
    struct CLNode *QueueTail;//队尾	
public:
    CLMyQueue();
    ~CLMyQueue(); 
    void Push(int data);  //入队
    int Pop();            //出队
    bool IsEmpty();
  };
CLMyQueue::CLMyQueue()	//构造器初始化
{
    QueueHead = NULL;
    QueueTail = NULL;
}
CLMyQueue::~CLMyQueue()	//析构
{
    while (QueueHead != NULL) 
    {
        struct CLNode *t = QueueHead;
        QueueHead = QueueHead->next;
        delete t;
    }
}

bool CLMyQueue::IsEmpty()//队列判空
{
    if (QueueHead == NULL) //当队头指针为空时，队列为空
    {
        return true;
    }
    return false;
}



void CLMyQueue::Push(T data)//入队
{
    if (IsEmpty())//对空，则首尾指针指向同一节点
    {
        QueueHead = new struct CLNode();
        QueueHead->data = data;
        QueueTail = QueueHead;
        return;
    }
	//队尾写
    struct CLNode *newNode = new struct CLNode();
    newNode->data = data;
    newNode->next = NULL;
    QueueTail->next = newNode;
    QueueTail = newNode;
}
 CLMyQueue::Pop()	//出队
{
    if (IsEmpty())//判空
    {
        return NULL;
    } 
    int data = QueueHead->data;//出队
    struct CLNode*t = QueueHead;
    QueueHead = QueueHead->next;
    delete t;
    return data;
}
