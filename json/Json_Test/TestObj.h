#pragma once
#include "JsonObjectBase.h"

class CTestObj: public CJsonObjectBase
{
public:
	CTestObj();

	// 子类需要实现此函数，并且将相应的映射关系进行设置;   
	virtual void SetPropertys();

	void DisplayPropertys();

public:
	char			m_chVal;
	double			m_dVal;
	int				m_iVal;
	std::string		m_strVal;
	std::list<int>	m_listVal;
	std::vector<std::string> m_vecVal;
};