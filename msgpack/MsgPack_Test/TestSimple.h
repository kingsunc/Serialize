#pragma once
#include "msgpack.hpp"
#include <string>
#include <iostream>
#include <sstream>

void TestSimple()
{
	try
	{
		msgpack::type::tuple<int, bool, std::string> src(1, true, "example");
		std::stringstream buffer;
		// 序列化压缩;
		msgpack::pack(buffer, src);
		buffer.seekg(0);
		std::string str(buffer.str());

		// 发送过程...;

		// 反序列化的解压;
		msgpack::unpacked result;
		msgpack::unpack(result, str.data(), str.size());
		msgpack::object deserialized = result.get();
		// 转换msgpack: 对象实例为原始类型;
		// 如果类型不匹配，将抛出msgpack::type_error异常
		msgpack::type::tuple<int, bool, std::string> dst;
		deserialized.convert(&dst);

		// 单个类型取值方法为以下两种;
		{
			int iVal1			= msgpack::type::get<0>(dst);
			bool bVal2			= msgpack::type::get<1>(dst);
			std::string strVal3	= msgpack::type::get<2>(dst);
		}
		{
			//int iVal1			= dst.a0;
			//bool bVal2			= dst.a1;
			//std::string strVal3	= dst.a2;
		}

		// 输出;
		std::cout << deserialized << std::endl;
	}
	catch (...)
	{
		std::cout << "解析异常!" << std::endl;
	}

	return;
}