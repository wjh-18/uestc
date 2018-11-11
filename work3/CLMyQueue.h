
#ifndef CLMyQueue_H
#define	CLMyQueue_H

#include <iostream>

template <class T>
struct CLNode		
{
    T data;
    struct CLNode *next;
};

template <class T>
class CLMyQueue
{
private:
    struct CLNode<T> *QueueHead;
    struct CLNode<T> *QueueTail;
	
public:
    CLMyQueue();
    ~CLMyQueue();
    
    void Push(T data);  
    T Pop();           
    bool IsEmpty();
  };


template <class T>
CLMyQueue<T>::CLMyQueue()	
{
    QueueHead = NULL;
    QueueTail = NULL;
}

template <class T>
CLMyQueue<T>::~CLMyQueue()	
{
    while (QueueHead != NULL)  
    {
        struct CLNode<T> *t = QueueHead;
        QueueHead = QueueHead->next;
        delete t;
    }
}

template <class T>
void CLMyQueue<T>::Push(T data)
{
    if (IsEmpty())
    {
        QueueHead = new struct CLNode<T>;
        QueueHead->data = data;
        QueueTail = QueueHead;
        return;
    }
    
	
    struct CLNode<T> *newNode = new struct CLNode<T>;
    newNode->data = data;
    newNode->next = NULL;
    QueueTail->next = newNode;
    QueueTail = newNode;
}

template <class T>
T CLMyQueue<T>::Pop()	
{
    if (IsEmpty())
    {
        return NULL;
    }
    
    T data = QueueHead->data;
    struct CLNode<T> *t = QueueHead;
    QueueHead = QueueHead->next;
    delete t;
    return data;
}

template <class T>
bool CLMyQueue<T>::IsEmpty()
{
    if (QueueHead == NULL) 
    {
        return true;
    }
    return false;
}


#endif	

