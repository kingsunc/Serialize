#pragma once
#include "JsonObjectBase.h"

class CTestObj: public CJsonObjectBase
{
public:
	CTestObj();

	// ������Ҫʵ�ִ˺��������ҽ���Ӧ��ӳ���ϵ��������;   
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