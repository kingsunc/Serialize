#include "TestSimple.h"
#include "TestClass.h"
#include "TestCompatible.h"
#include "TestEnum.h"
#include "TestMyData.h"
#include "TestVector.h"
#include "TestSpeed1.h"
#include "TestSpeed2.h"
#include "TestSpeed2.h"
#include "TestServer.h"

int main()
{
	// һ������;
	TestSimple();

	// �Զ�������;
	TestClass();

	// ���ݼ���;
	TestCompatible();

	// ö������;
	TestEnum();

	// �Զ������ݸ�ʽ;
	TestMyData();

	// vector;
	TestVector();

	// ѹ��\��ѹ�ٶȲ���;
	TestSpeed1();
	TestSpeed2();

	//TestSpeed2();

	return 0;
}