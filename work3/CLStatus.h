#ifndef CLSTATUS_H
#define CLSTATUS_H

/*
用于保存函数的处理结果
*/
class CLStatus
{
public:
	
	CLStatus(long lReturnCode, long lErrorCode);
	CLStatus(const CLStatus& s);
	virtual ~CLStatus();

public:
	bool IsSuccess();

public:
	const long& m_clReturnCode;
	const long& m_clErrorCode;

private:
	long m_lReturnCode;
	long m_lErrorCode;
};

#endif
