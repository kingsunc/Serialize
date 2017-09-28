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
	// 一般类型;
	TestSimple();

	// 自定义类型;
	TestClass();

	// 数据兼容;
	TestCompatible();

	// 枚举类型;
	TestEnum();

	// 自定义数据格式;
	TestMyData();

	// vector;
	TestVector();

	// 压缩\解压速度测试;
	TestSpeed1();
	TestSpeed2();

	//TestSpeed2();

	return 0;
}