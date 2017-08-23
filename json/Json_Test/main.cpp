#include "TestObj.h"

int main()
{
	CTestObj objSrc;
	objSrc.m_chVal = 'A';
	objSrc.m_dVal = 1234.56;
	objSrc.m_iVal = 123456;
	objSrc.m_strVal = "abcdef";
	objSrc.m_listVal.push_back(10);
	objSrc.m_listVal.push_back(20);
	objSrc.m_listVal.push_back(30);

	objSrc.m_vecVal.push_back("abc");
	objSrc.m_vecVal.push_back("edf");
	objSrc.m_vecVal.push_back("ghi");

	objSrc.DisplayPropertys();
	std::string strVal = objSrc.Serialize();

	printf("\n %s \n", strVal.c_str());

	CTestObj objDest;
	if (objDest.DeSerialize(strVal.c_str()))
	{
		objDest.DisplayPropertys();
	}
	
	return 1;
}