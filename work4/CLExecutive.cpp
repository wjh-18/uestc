#include "CLExecutive.h"
#include "CLExecutiveFunctionProvider.h" //���Ӵ�Ҳ�ܱ���ͨ�������о��� ����֮

CLExecutive::CLExecutive(CLExecutiveFunctionProvider *pExecutiveFunctionProvider)
{
	m_pExecutiveFunctionProvider = pExecutiveFunctionProvider;
}

CLExecutive::~CLExecutive()
{
	delete m_pExecutiveFunctionProvider;
}
