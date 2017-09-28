#pragma once
#include "JsonObject.h"

class CSubTestObj : public CJsonObject
{
public:
	CSubTestObj()
	{
		InitPropertys();
	}

	// 子类需要实现此函数，并且将相应的映射关系进行设置;   
	virtual void InitPropertys()
	{
		AddProperty("chVal", asInt, &m_chVal);
		AddProperty("dVal", asDouble, &m_dVal);
		AddProperty("iVal", asInt, &m_iVal);
	}

public:
	char			m_chVal;
	double			m_dVal;
	int				m_iVal;
};

class CTestObj: public CJsonObject
{
public:
	CTestObj()
	{
		InitPropertys();
	}

	// 子类需要实现此函数，并且将相应的映射关系进行设置;   
	virtual void InitPropertys()
	{
		AddProperty("chVal", asInt, &m_chVal);
		AddProperty("dVal", asDouble, &m_dVal);
		AddProperty("iVal", asInt, &m_iVal);
		AddProperty("strVal", asString, &m_strVal);
		AddProperty("listVal", asListArray, &m_listVal, asInt);
		AddProperty("vecVal", asVectorArray, &m_vecVal, asString);
		AddProperty("bVal", asBool, &m_bVal);
		AddProperty("subObj", asJsonObj, &subObj);
	}

	void DisplayPropertys()
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

public:
	char			m_chVal;
	double			m_dVal;
	int				m_iVal;
	std::string		m_strVal;
	std::list<int>	m_listVal;
	std::vector<std::string> m_vecVal;
	bool			m_bVal;

	CSubTestObj		subObj;
};