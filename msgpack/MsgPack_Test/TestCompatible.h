#pragma once
#include <msgpack.hpp>
#include <sstream>
#include <string>
#include <iostream>

class COldClass
{
public:
	COldClass() : m_strValue("old_class"){};

	std::string		m_strValue;

	MSGPACK_DEFINE(m_strValue);
};

class CNewClass
{
public:
	CNewClass() : m_strValue("new_class"), m_iFlag(-1) {}

	std::string		m_strValue;
	int				m_iFlag;

	MSGPACK_DEFINE(m_strValue, m_iFlag);
};

void TestCompatible()
{
	{
		COldClass oc;
		CNewClass nc;

		std::stringstream sbuf;
		msgpack::pack(sbuf, oc);

		msgpack::unpacked result;
		msgpack::unpack(result, sbuf.str().data(), sbuf.str().size());
		msgpack::object obj = result.get();

		obj.convert(&nc);

		std::cout << obj << " value=" << nc.m_strValue << " flag=" << nc.m_iFlag << std::endl;
	}

	{
		CNewClass nc;
		COldClass oc;

		std::stringstream sbuf;
		msgpack::pack(sbuf, nc);

		msgpack::unpacked result;
		msgpack::unpack(result, sbuf.str().data(), sbuf.str().size());
		msgpack::object obj = result.get();

		obj.convert(&oc);

		std::cout << obj << " value=" << oc.m_strValue << std::endl;
	}
}
