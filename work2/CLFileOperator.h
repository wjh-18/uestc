#ifndef CLFILEOPERATOR_H
#define CLFILEOPERATOR_H
class CLFileOperator {
	public:
		CLFileOperator(const char *fileName); //构造析构函数
		~CLFileOperator();
//Read 和 Write 是该类对外提供的读写操作的接口.
		int Read(char *buf, int seek,int len);
		int Write(const char *pstrMsg);
	private:
		CLFileOperator();
		int ReadFile(char *buf, int len); //表示从给定位置(lseek)开始读出 len 长度的文件内容；
		int WriteFile(const char *pstrMsg, int len); //将 pstrMsg 指向的信息串写入到文件中.
		int FlushWrite(); //读操作之前和缓存不足时可调用 Flush 函数进行缓存的刷新.
		off_t GetCurrentSeek();//获取当前文件偏移量
		int FlushRead(int seek);//从文件偏移量seek处缓存数据
	private:
		const char *m_pFileName;//文件名
		int m_Fd;//文件标识符
		pthread_mutex_t *m_pMutex;//读写互斥量
		char *m_pWriteBuffer;//写缓存
		char *m_pReadBuffer;//读缓存
		off_t l_seek;//文件偏移量
		long m_fileSize;//文件长度
		unsigned int m_nUsedBytesForWriteBuffer;//未使用的写缓存
		int m_readBufferSeek;//读缓存数据所在文件偏移量
		int m_readBufferByte;
		//unsigned int m_nUsedBytesForReadBuffer;//未使用的读缓存
};
#endif
