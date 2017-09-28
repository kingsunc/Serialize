#pragma once
#include <msgpack.hpp>
#include <string>
#include <iostream>
#include <sstream>

struct MyData
{
	MyData() {}
	MyData(const std::string& k, const std::string& v) : strKey(k), strValue(v){}

	std::string	strKey;
	std::string	strValue;
	MSGPACK_DEFINE(strValue, strKey);
};
typedef std::vector<MyData> MultiMyData;

void TestMyData()
{
	std::stringstream stream;

	// send MultiGet request
	{
		MultiMyData src;
		src.push_back( MyData("id", "1") );
		src.push_back( MyData("name", "Admin") );
		src.push_back( MyData("pwd", "123") );
		msgpack::pack(stream, src);
	}

	stream.seekg(0);

	// receive MultiGet request
	{
		std::string buffer(stream.str());

		msgpack::unpacked result;
		msgpack::unpack(result, buffer.data(), buffer.size());
		msgpack::object o = result.get();

		MultiMyData dst;
		o.convert(dst);
		std::cout << "received: " << o << std::endl;
	}
}
