#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"LHYFileOp.h"

#include<fcntl.h>
#include<unistd.h>
#include<iostream>
#include<errno.h>
#include<pthread.h>



using namespace std;
#define BUFFER_SIZE 60  //缓存60


LHYFileOp::LHYFileOp(const char *_FileName){ //构造器
       _fd=open(_FileName,O_RDWR|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR);
       if(_fd==-1)
	   throw "打开文件错误";
       m_pBuffer=new char[BUFFER_SIZE];//创建缓存区
       m_nUsedBytesForBuffer=0;         //
       m_pMutex=new pthread_mutex_t;   //创建互斥量对象
	   
	   
       if(pthread_mutex_init(m_pMutex,0)!=0){ //缓存正在被访问，此次加锁失败
            delete m_pMutex;
            delete [] m_pBuffer;
            close(_fd);
            throw "构造器初始化失败";
       }  
}


LHYFileOp::~LHYFileOp(){  //析构
      if(_fd!=0) close(_fd);
      if(m_pMutex!=0)  delete m_pMutex;
      if(m_pBuffer!=0) delete  m_pBuffer;
}




int LHYFileOp::Flush(){ //刷新函数
      if(m_pBuffer==0)  return -1;
            if(m_nUsedBytesForBuffer==0) return -1;//缓存空
            if(pthread_mutex_lock(m_pMutex)!=0) return -1;
            if(_fd==-1)  return -1;
            int w=write(_fd,m_pBuffer,m_nUsedBytesForBuffer);//写入文件
            if(w==-1) return -1;
            m_nUsedBytesForBuffer=0;//重置缓存
            if(pthread_mutex_unlock(m_pMutex)!=0)  return -1;
            return w;//写入数据长度
}






void LHYFileOp::F_WRITE(const char *pstrMsg){ //写操作接口
      if(WriteFile(pstrMsg)==-1)  
            cout<<"写入失败"<<endl;
      else
            cout<<"写入成功"<<endl;
}


int LHYFileOp::WriteFile(const char *pstrMsg){ 
      if(pstrMsg==0)  return -1;//写入数据空
      if(strlen(pstrMsg)==0)  return -1;
      if(m_pBuffer==0)  return -1;//缓冲区空
      if(pthread_mutex_lock(m_pMutex)!=0)  return -1;
      unsigned int len_strmsg=strlen(pstrMsg);//写入数据容量
      unsigned int m_nleftroom=BUFFER_SIZE-m_nUsedBytesForBuffer;//空闲缓冲区大小
      if(len_strmsg>BUFFER_SIZE){//写入数据容量>缓存容量
         if(_fd==-1)  return -1;
         int w=write(_fd,pstrMsg,len_strmsg);//直接写文件
         if(w==-1)  return -1;
         return w;
     }
      if(len_strmsg>m_nleftroom){//剩余缓冲区不足，Flush
         if(Flush()==-1)  return -1;
      }       
memcpy(m_pBuffer+m_nUsedBytesForBuffer,pstrMsg,len_strmsg);
      m_nUsedBytesForBuffer+=len_strmsg;//更新缓存区剩余容量
      if(pthread_mutex_unlock(m_pMutex)!=0)  return -1;
      return 0;
}



void LHYFileOp::F_READ(int _position,int _length){//读操作接口
      if(ReadFile(_position,_length)==-1) 
             cout<<"读取失败"<<endl;
      else
             {   cout<<""<<endl;
                 cout<<"读取结果如上"<<endl;
            }
}


int LHYFileOp::ReadFile(int position,int length){
      Flush();//读取之前必须刷新，保证一致性
      if(pthread_mutex_lock(m_pMutex)!=0)
           throw "线程加锁失败";
      if(_fd==-1) return -1;
      if(lseek(_fd,position,SEEK_SET)==-1) return -1;
      int r;
      if(length==0){
	  cout<<""<<endl;
	  cout<<"没有读取数据"<<endl;
      }
      while(length>0){//读取容量>缓存容量，分段读取
               r=read(_fd,m_pBuffer,length);//读入
               if(r==-1){
                     cout<<"读取缓存失败"<<endl; break;
               }
              if(r==0) {
                   cout<<""<<endl;
                   cout<<"到达文件尾部"<<endl;
                   break;
              } 
             cout<<m_pBuffer;
             lseek(_fd,r,SEEK_CUR);//修改偏移量
             length=length-r;//剩余读数据长度
     }
      if(pthread_mutex_unlock(m_pMutex)!=0)
             throw "线程解锁失败";
      return 0;
}


