#pragma once
#include <msgpack.hpp>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cassert>

class CPeople 
{
public:
	CPeople() {};

	CPeople(std::string const& strName, int iAge):m_strName(strName), m_iAge(iAge) {};

	friend bool operator==(CPeople const& lhs, CPeople const& rhs)
	{
		return lhs.m_strName == rhs.m_strName && lhs.m_iAge == rhs.m_iAge;
	}

private:
	std::string m_strName;
	int m_iAge;

public:
	MSGPACK_DEFINE_MAP(m_strName, m_iAge);
};

void test3_print(std::string const& buf)
{
	for (std::string::const_iterator it = buf.begin(), end = buf.end(); it != end; ++it) 
	{
		std::cout
				<< std::setw(2)
				<< std::hex
				<< std::setfill('0')
				<< (static_cast<int>(*it) & 0xff)
				<< ' ';
	}
	std::cout << std::dec << std::endl;
}

void TestClass()
{
	{
		// pack, unpack
		CPeople my("John Smith", 42);
		std::stringstream ss;
		msgpack::pack(ss, my);

		test3_print(ss.str());

		msgpack::unpacked unp;
		msgpack::unpack(unp, ss.str().data(), ss.str().size());
		msgpack::object obj = unp.get();
		std::cout << obj << std::endl;
		assert(obj.as<CPeople>() == my);
	}
	{
		// create object with zone
		CPeople my("John Smith", 42);
		msgpack::zone z;
		msgpack::object obj(my, z);
		std::cout << obj << std::endl;
		assert(obj.as<CPeople>() == my);
	}
}
