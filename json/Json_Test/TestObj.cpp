#include "TestObj.h"

CTestObj::CTestObj()
{
	SetPropertys();
}

void CTestObj::SetPropertys()
{
	SetProperty("chVal", asInt, (int*)&m_chVal);
	SetProperty("dVal", asDouble, &m_dVal);
	SetProperty("iVal", asInt, &m_iVal);
	SetProperty("strVal", asString, &m_strVal);
	SetProperty("listVal", asListArray, &m_listVal, asInt);
	SetProperty("vecVal", asVectorArray, &m_vecVal, asString);
}

void CTestObj::DisplayPropertys()
{
	printf("chVal : %c \n", m_chVal);
	printf("dVal : %f \n", m_dVal);
	printf("iVal : %d \n", m_iVal);
	printf("strVal : %s \n", m_strVal.c_str());

	printf("listVal (%d) : ", m_listVal.size());
	for (std::list<int>::iterator it = m_listVal.begin(); it != m_listVal.end(); it++)
	{
		printf("%d, ", *it);
	}
	printf("\n");

	int iVecSize = m_vecVal.size();
	printf("vecVal (%d) : ", iVecSize);
	for (int i = 0; i < iVecSize; i++)
	{
		printf("%s, ", m_vecVal[i].c_str());
	}
	printf("\n");
}