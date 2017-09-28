#pragma once
#include <msgpack.hpp>
#include <iostream>
#include <sstream>
#include <cassert>
#include <string>
#include <vector>

typedef std::vector<int>	ArrInt;

void TestVector() 
{
	ArrInt arrSrc;
	arrSrc.push_back(1);
	arrSrc.push_back(52);
	arrSrc.push_back(31);
	arrSrc.push_back(42);
	std::string s("ABC");

	std::stringstream ss;
	msgpack::pack(ss, arrSrc);
	msgpack::pack(ss, s);

	msgpack::zone z;
	std::size_t offset = 0;

	// msgpack array is constructed on z.
	msgpack::object obj = msgpack::unpack(z, ss.str().data(), ss.str().size(), offset);
	std::cout << obj << std::endl;

	ArrInt arrDest = obj.as<ArrInt>();
	assert(arrDest == arrSrc);

	// msgpack str is constructed on z.
	std::string const& str = msgpack::unpack(z, ss.str().data(), ss.str().size(), offset).as<std::string>();
	std::cout << str << std::endl;
	assert(str == s);
}
