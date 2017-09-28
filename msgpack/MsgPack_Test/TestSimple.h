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
		// ���л�ѹ��;
		msgpack::pack(buffer, src);
		buffer.seekg(0);
		std::string str(buffer.str());

		// ���͹���...;

		// �����л��Ľ�ѹ;
		msgpack::unpacked result;
		msgpack::unpack(result, str.data(), str.size());
		msgpack::object deserialized = result.get();
		// ת��msgpack: ����ʵ��Ϊԭʼ����;
		// ������Ͳ�ƥ�䣬���׳�msgpack::type_error�쳣
		msgpack::type::tuple<int, bool, std::string> dst;
		deserialized.convert(&dst);

		// ��������ȡֵ����Ϊ��������;
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

		// ���;
		std::cout << deserialized << std::endl;
	}
	catch (...)
	{
		std::cout << "�����쳣!" << std::endl;
	}

	return;
}