#ifndef CJSONOBJECTBASE_H  
#define CJSONOBJECTBASE_H  
#include <string>
#include <vector>
#include <list>
#include "json/json.h"
using namespace std;

typedef int					INT;
typedef unsigned int		UINT;
typedef long long			LONGLONG;
typedef unsigned long long	ULONGLONG;

#pragma warning(disable:4267)  

typedef void* (*GenerateJsonObjForDeSerializeFromOutSide)(const string& propertyName);

struct CJsonObject
{
protected:

	enum JsonType
	{
		asBool = 1,
		asChar,
		asUChar,
		asInt,
		asUInt,
		asString,
		asInt64,
		asUInt64,
		asDouble,
		asJsonObj,
		asSpecialArray,
		asVectorArray,
		asListArray,
	};

	struct JsonItem
	{
		string		strName;
		JsonType	eType;
		void*		pAddr;
		JsonType	eArrType;
	};

public:
	CJsonObject();
	virtual ~CJsonObject();

	// 序列化 struct->buff;
	string Serialize();
	// 反序列化 buff->struct;
	bool DeSerialize(const char* str);

protected:

	// 开始构造函数内 初始化属性列表;
	virtual void InitPropertys() = 0;
	void AddProperty(string strName, JsonType eType, void* pAddr, JsonType eArrType = asInt);

	Json::Value DoSerialize();
	bool DoDeSerialize(Json::Value& root);

	// 有特殊对象需要序列化时，请重载此函数;
	virtual Json::Value DoSpecialArraySerialize(const string& propertyName);
	//在反序列化时，如果对象中嵌套了列表，并且列表中容纳的内容是其他特殊对象时，需要重载此函数，new出真正的对象;
	virtual CJsonObject* GenerateJsonObjForDeSerialize(const string& propertyName);

	bool DoArrayDeSerialize(const string& strName, void* pAddr, Json::Value& jsValue, JsonType eType, JsonType eArrType);

	// 特殊对象列表的反序列化;
	template<typename T>
	bool DoObjArrayDeSerialize(const string& strName, void* pAddr, Json::Value& jsValue)
	{
		if (!jsValue.isArray())
		{
			return false;
		}
		T* pList = static_cast<T*>(pAddr);
		int size = jsValue.size();
		for (int i = 0; i < size; ++i)
		{
			CJsonObject* pNode = GenerateJsonObjForDeSerialize(strName);
			pNode->DoDeSerialize(jsValue[i]);
			pList->push_back(pNode);
		}
		return true;
	}

	// 常见类型列表的反序列化;
	template <typename T1, typename T2>
	static bool DoArrayDeSerialize(void* addr, Json::Value& node)
	{
		if (!node.isArray())
		{
			return false;
		}
		T1* pList = (T1*)addr;
		int size = node.size();
		for (int i = 0; i < size; ++i)
			pList->push_back(DeSerialize<T2>(node[i]));
		return true;
	}

	// 特殊对象列表的反序列化;
	template<typename T>
	static bool DoObjArrayDeSerialize(const string& propertyName, void* addr, Json::Value& node, GenerateJsonObjForDeSerializeFromOutSide funGenerate)
	{
		if (!node.isArray())
		{
			return false;
		}
		T* pList = (T*)addr;
		int size = node.size();
		for (int i = 0; i < size; ++i)
		{
			CJsonObject* pNode = (CJsonObject*)funGenerate(propertyName);
			pNode->DoDeSerialize(node[i]);
			pList->push_back(pNode);
		}
		return true;
	}

	Json::Value DoArraySerialize(void* addr, JsonType listType, JsonType paramType);

	template <typename T>
	static Json::Value DoArraySerialize(T* pList)
	{
		Json::Value arrayValue;
		for (auto it = pList->begin(); it != pList->end(); ++it)
		{
			Json::Value temp(*it);
			arrayValue.append(temp);
		}
		return arrayValue;
	}

	static Json::Value DoArraySerialize(vector<CJsonObject*>* pList)
	{
		Json::Value arrayValue;
		for (vector<CJsonObject*>::iterator it = pList->begin(); it != pList->end(); ++it)
		{
			arrayValue.append((*it)->DoSerialize());
		}
		return arrayValue;
	}

	static Json::Value DoArraySerialize(list<CJsonObject*>* pList)
	{
		Json::Value arrayValue;
		for (list<CJsonObject*>::iterator it = pList->begin(); it != pList->end(); ++it)
		{
			arrayValue.append((*it)->DoSerialize());
		}
		return arrayValue;
	}
	static string JsonValueToString(Json::Value& tvalue)
	{
		Json::FastWriter writer;
		return writer.write(tvalue);
	}

private:
	// void* 转任意类型;
	template <typename T>
	T& ToAny(void* pAddr)
	{
		T* pVal = static_cast<T*>(pAddr);
		return *pVal;
	}

	template <typename T>
	static T DeSerialize(Json::Value& root)
	{
		T tVal;
		GetData(tVal, root);
		return tVal;
	}

	static void GetData(bool& bVal, Json::Value& root)
	{
		bVal = root.asBool();
	}

	static void GetData(INT& iVal, Json::Value& root)
	{
		iVal = root.asInt();
	}

	static void GetData(UINT& iVal, Json::Value& root)
	{
		iVal = root.asUInt();
	}

	static void GetData(LONGLONG& lVal, Json::Value& root)
	{
		lVal = root.asInt64();
	}

	static void GetData(ULONGLONG lVal, Json::Value& root)
	{
		lVal = root.asUInt64();
	}

	static void GetData(string& strVal, Json::Value& root)
	{
		strVal = root.asString();
	}

private:
	vector<JsonItem>	m_vecItems;
};
#endif