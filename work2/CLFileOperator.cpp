#include<fcntl.h>
#include<unistd.h>
#include<iostream>
#include<errno.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

#include"CLFileOperator.h"

using namespace std;
#define BUFFER_WRITE_SIZE 64 //写缓存大小，设置为 64
#define BUFFER_READ_SIZE 64 //读缓存大小，设置为 64

CLFileOperator::CLFileOperator(const char *FileName) {
//根据 _FileName 打开文件或创建文件，并进行初始化工作

	m_Fd=open(FileName,O_RDWR|O_APPEND|O_CREAT, S_IWUSR|S_IRUSR);
	//检查文件是否打开成功
	if(m_Fd==-1) {
		cout << "Open or create file " << FileName << " failed." << endl;
	}
	m_pWriteBuffer=new char[BUFFER_WRITE_SIZE];//创建读缓存区
	m_pReadBuffer=new char[BUFFER_READ_SIZE];//创建写缓存区
	m_nUsedBytesForWriteBuffer=0; //设置已用写缓存区大小为 0
	m_pMutex=new pthread_mutex_t; //创建互斥量对象
	m_readBufferSeek = 0;

	if(pthread_mutex_init(m_pMutex,0)!=0) {
		//初始化锁失败，释放资源
		delete m_pMutex;
		delete [] m_pWriteBuffer;
		delete [] m_pReadBuffer;
		close(m_Fd);
		cout << "Init mutx failed." << endl;
	}
	
	FlushRead(GetCurrentSeek());
}
CLFileOperator::~CLFileOperator() {
//关闭文件，并进行互斥量的撤销和缓存的回收
	if(m_Fd!=-1)
		close(m_Fd);
	if(m_pMutex!=0)
		delete m_pMutex;
	if(m_pWriteBuffer!=0)
		delete [] m_pWriteBuffer;
	if(m_pReadBuffer!=0)
		delete [] m_pReadBuffer;
}

int CLFileOperator::Write(const char *pstrMsg) {
	if(pstrMsg==0)
		return -1;
	if(strlen(pstrMsg)==0)
		return -1;
	if(m_pWriteBuffer==0)
		return -1;
	unsigned int len_strmsg=strlen(pstrMsg);//获取写入信息的大小
	unsigned int m_nleftroom=BUFFER_WRITE_SIZE-m_nUsedBytesForWriteBuffer;//剩余写缓存大小
	if(len_strmsg>BUFFER_WRITE_SIZE) {
//待写入信息长度大于缓存区大小时，先将原来的写缓写入文件，再将新的信息直接写入文件

		if(FlushWrite()==-1)
			return -1;
		if(m_Fd==-1) return -1;
		int w=WriteFile(pstrMsg,len_strmsg);
		if(w==-1)
			return -1;
		return w;
	}
	if(len_strmsg>m_nleftroom) {
//剩余缓存区不足时，刷新缓存
		if(FlushWrite()==-1)
			return -1;
	}
	memcpy(m_pWriteBuffer+m_nUsedBytesForWriteBuffer,pstrMsg,len_strmsg);//写入缓存
	m_nUsedBytesForWriteBuffer+=len_strmsg;

//修改已用缓存大小
	return 0;
}

int CLFileOperator::Read(char *buf, int position,int length) {

	//将数据从缓存中写回
	FlushWrite();

	if(m_Fd==-1) return -1;
	if(lseek(m_Fd,position,SEEK_SET)==-1)
		return -1;
	int r;
	if(length==0) {
		//不读出数据
		cout<<""<<endl;
		cout<<"you want to read nothing"<<endl;
	}
	if(length > BUFFER_READ_SIZE) {
		//读数据量大于缓存,则直接读出数据
		r=ReadFile(buf,length);
		//缓存读出数据以后的数据
		FlushRead(GetCurrentSeek());
	} else if(position+length > m_readBufferSeek+m_readBufferByte || position < m_readBufferSeek) {
		//读数据部分在缓存或全不在缓存，将数据读入缓存中
		ReadFile(m_pReadBuffer, length);
		memcpy(buf,m_pReadBuffer,length);
		buf[length] = '\0';
	} else {
		//所读数据全部都在缓存中,则将缓存中数据所在地址传给调用者
		memcpy(buf, m_pReadBuffer + position-m_readBufferSeek,length);
		buf[length] = '\0';
//		cout << "Read file from buffer "  << m_pReadBuffer << endl;
	}

	return 0;
}
int CLFileOperator::ReadFile(char *buf, int length) {
	//读文件
	//读之前进行加锁
	if(pthread_mutex_lock(m_pMutex)!=0)
		throw "pthread_mutex_lock failed......";
	m_readBufferByte= read(m_Fd,buf,length);
	
	cout << "Read file:  " << buf << "and byte" << m_readBufferByte << endl;
	if(m_readBufferByte==-1) {
		cout<<"read file failed."<<endl;
	} else if(m_readBufferByte == 0) {
		cout<<"read the end of the file."<<endl;
	}
	if(pthread_mutex_unlock(m_pMutex)!=0) throw "pthread_mutex_unlock failed......";
	return 0;
}
int CLFileOperator::WriteFile(const char *buf, int length) {
	//写文件
	//写之前进行加锁
//	cout<<m_pMutex<<endl;
	if(pthread_mutex_lock(m_pMutex)!=0)
	{
		throw "pthread_mutex_lock before lock failed......";
	}
	int r = write(m_Fd,buf,length);
	cout << "Write file:  " << buf << endl;
	if(r==-1) {
		cout<<"Write file failed."<<endl;
	}
	if(pthread_mutex_unlock(m_pMutex)!=0) throw "pthread_mutex_unlock after write failed......";
	return 0;
}

int CLFileOperator::FlushWrite() {
	//刷新函数
	if(m_pWriteBuffer==0)
		return -1;
	if(m_nUsedBytesForWriteBuffer==0)
		return -1;//缓存中无数据
	if(m_Fd==-1)
		return -1;
	int w = WriteFile(m_pWriteBuffer,m_nUsedBytesForWriteBuffer);//写入文件
	if(w==-1) return -1;
	m_nUsedBytesForWriteBuffer=0;//重新设置已用缓存区为 0
	return 0;//返回写入数据的长度
}
off_t CLFileOperator::GetCurrentSeek() {
	return lseek(m_Fd, 0, SEEK_CUR);
}
int CLFileOperator::FlushRead(int seek) {
	//判断读缓存是否已失效以及更新读缓存
	ReadFile(m_pReadBuffer, BUFFER_READ_SIZE);

	m_readBufferSeek = seek;
}
