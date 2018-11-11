#include <iostream>
struct CLNode{		
    int data;
    struct CLNode *next;
};
class CLMyQueue
{
private:
    struct CLNode *QueueHead;//��ͷ
    struct CLNode *QueueTail;//��β	
public:
    CLMyQueue();
    ~CLMyQueue(); 
    void Push(int data);  //���
    int Pop();            //����
    bool IsEmpty();
  };
CLMyQueue::CLMyQueue()	//��������ʼ��
{
    QueueHead = NULL;
    QueueTail = NULL;
}
CLMyQueue::~CLMyQueue()	//����
{
    while (QueueHead != NULL) 
    {
        struct CLNode *t = QueueHead;
        QueueHead = QueueHead->next;
        delete t;
    }
}

bool CLMyQueue::IsEmpty()//�����п�
{
    if (QueueHead == NULL) //����ͷָ��Ϊ��ʱ������Ϊ��
    {
        return true;
    }
    return false;
}



void CLMyQueue::Push(T data)//���
{
    if (IsEmpty())//�Կգ�����βָ��ָ��ͬһ�ڵ�
    {
        QueueHead = new struct CLNode();
        QueueHead->data = data;
        QueueTail = QueueHead;
        return;
    }
	//��βд
    struct CLNode *newNode = new struct CLNode();
    newNode->data = data;
    newNode->next = NULL;
    QueueTail->next = newNode;
    QueueTail = newNode;
}
 CLMyQueue::Pop()	//����
{
    if (IsEmpty())//�п�
    {
        return NULL;
    } 
    int data = QueueHead->data;//����
    struct CLNode*t = QueueHead;
    QueueHead = QueueHead->next;
    delete t;
    return data;
}
