

#include<pthread.h>


class FKXFileOp{
      public:
                   FKXFileOp(const char *_FileName);
                  ~FKXFileOp();
				  
				  
				  
                   void F_READ(int _position,int _length);
                   void F_WRITE(const char *pstrMsg);
      private:
	  
	  
	  
                   FKXFileOp();
				   
				   
				   
                   int ReadFile(int position,int length);
				   
				     
				   
				   
				   
                   int WriteFile(const char *pstrMsg);
                   int Flush();
                   const char *FileName;
                   int _fd;
                   pthread_mutex_t *m_pMutex;
                   char *m_pBuffer;
                  unsigned int m_nUsedBytesForBuffer;
};

