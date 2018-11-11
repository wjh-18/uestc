#ifndef CLSTATUS_H
#define CLSTATUS_H

/*
���ڱ��溯���Ĵ�����
*/
class CLStatus
{
public:
	/*
	lReturnCode >=0��ʾ�ɹ�������ʧ��
	*/
	CLStatus(long lReturnCode, long lErrorCode);
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
