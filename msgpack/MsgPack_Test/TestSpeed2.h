#pragma once
#include <msgpack.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
//#include <boost/timer/timer.hpp>

template <typename T, std::size_t level>
struct vecvec
{
	typedef std::vector<typename vecvec<T, level - 1>::type> type;
	static void fill(type& v, std::size_t num_of_elems, T const& val)
	{
		for (std::size_t elem = 0; elem < num_of_elems; ++elem)
		{
			typename vecvec<T, level - 1>::type child;
			vecvec<T, level - 1>::fill(child, num_of_elems, val);
			v.push_back(child);
		}
	}
};

template <typename T>
struct vecvec<T, 0>
{
	typedef std::vector<T> type;
	static void fill(type& v, std::size_t num_of_elems, T const& val)
	{
		for (std::size_t elem = 0; elem < num_of_elems; ++elem)
		{
			v.push_back(val);
		}
	}
};

void TestSpeed2()
{
	std::cout << "[TEST][array_of_array]" << std::endl;
	// setup
	int const depth = 4;
	std::cout << "Setting up array data..." << std::endl;
	vecvec<int, depth>::type v1;
	vecvec<int, depth>::fill(v1, 3, 42);

	std::cout << "Start packing..." << std::endl;
	std::stringstream buffer;
	{
		//boost::timer::cpu_timer timer;
		msgpack::pack(buffer, v1);
		//std::string result = timer.format();
		//std::cout << result << std::endl;
	}
	std::cout << "Pack finished..." << std::endl;

	buffer.seekg(0);
	std::string str(buffer.str());

	msgpack::unpacked unpacked;
	std::cout << "Start unpacking...by void unpack(unpacked& result, const char* data, size_t len)" << std::endl;
	{
		//boost::timer::cpu_timer timer;
		msgpack::unpack(unpacked, str.data(), str.size());
		//std::string result = timer.format();
		//std::cout << result << std::endl;
	}
	std::cout << "Unpack finished..." << std::endl;
	vecvec<int, depth>::type v2;
	std::cout << "Start converting..." << std::endl;
	{
		//boost::timer::cpu_timer timer;
		unpacked.get().convert(&v2);
		//std::string result = timer.format();
		//std::cout << result << std::endl;
	}
	std::cout << "Convert finished..." << std::endl;
}