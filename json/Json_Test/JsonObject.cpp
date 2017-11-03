#include "JsonObject.h"

CJsonObject::CJsonObject()
{
}

CJsonObject::~CJsonObject()
{

}

string CJsonObject::Serialize()
{
	Json::Value new_item = DoSerialize();
	Json::FastWriter writer;
	std::string out2 = writer.write(new_item);
	return out2;
}

bool CJsonObject::DeSerialize(const char* str)
{
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(str, root))
	{
		return DoDeSerialize(root);
	}
	return false;
}

void CJsonObject::AddProperty(string strName, JsonType eType, void* pAddr, JsonType eArrType /*= asInt*/)
{
	JsonItem item;
	item.strName = strName;
	item.eType = eType;
	item.pAddr = pAddr;
	item.eArrType = eArrType;
	m_vecItems.push_back(item);
}

Json::Value CJsonObject::DoSerialize()
{
	Json::Value new_item;
	int nSize = m_vecItems.size();
	for (int i = 0; i < nSize; ++i)
	{
		string		strName = m_vecItems[i].strName;
		JsonType	eType = m_vecItems[i].eType;
		void*		pAddr = m_vecItems[i].pAddr;
		JsonType	eArrType = m_vecItems[i].eArrType;

		switch (m_vecItems[i].eType)
		{
		case asVectorArray:
		case asListArray:
			new_item[strName] = DoArraySerialize(pAddr, eType, eArrType);
			break;
		case asSpecialArray:
			new_item[strName] = DoSpecialArraySerialize(strName);
			break;
		case asJsonObj:
			{
				CJsonObject* pObj = static_cast<CJsonObject*>(pAddr);
				if (pObj)
				{
					new_item[strName] = pObj->DoSerialize();
				}
			}
			break;
		case asChar:
			{
				new_item[strName] = ToAny<char>(pAddr);
			}
			break;
		case asUChar:
			{
				new_item[strName] = ToAny<unsigned char>(pAddr);
			}
			break;
		case asBool:
			{
				new_item[strName] = ToAny<bool>(pAddr);
			}
			break;
		case asInt:
			{
				new_item[strName] = ToAny<INT>(pAddr);
			}
			break;
		case asUInt:
			{
				new_item[strName] = ToAny<UINT>(pAddr);
			}
			break;
		case asInt64:
			{
				new_item[strName] = ToAny<LONGLONG>(pAddr);
			}
			break;
		case asUInt64:
			{
				new_item[strName] = ToAny<ULONGLONG>(pAddr);
			}
			break;
		case asDouble:
			{
				new_item[strName] = ToAny<double>(pAddr);
			}
			break;
		case asString:
			{
				new_item[strName] = ToAny<string>(pAddr);
			}
		default:
			// 其它类型可以自行添加;  
			break;
		}
	}
	return new_item;
}

bool CJsonObject::DoDeSerialize(Json::Value& root)
{
	int nSize = m_vecItems.size();
	for (int i = 0; i < nSize; ++i)
	{
		string		strName = m_vecItems[i].strName;
		JsonType	eType = m_vecItems[i].eType;
		void*		pAddr = m_vecItems[i].pAddr;
		JsonType	eArrType = m_vecItems[i].eArrType;

		switch (m_vecItems[i].eType)
		{
		case asListArray:
		case asVectorArray:
			{
				if (root.isNull() || root[strName].isNull())
				{
					break;
				}
				DoArrayDeSerialize(strName, pAddr, root[strName], eType, eArrType);
			}
			break;
		case asJsonObj:
			{
				CJsonObject* pObj = ToAny<CJsonObject*>(pAddr);
				if (!root[strName].isNull() && pObj)
				{
					pObj->DoDeSerialize(root[strName]);
				}
			}
			break;
		case asBool:
			{
				bool& val = ToAny<bool>(pAddr);
				val = root.get(strName, 0).asBool();
			}
			break;
		case asChar:
			{
				char& val = ToAny<char>(pAddr);
				val = root.get(strName, 0).asInt();
			}
			break;
		case asUChar:
			{
				unsigned char& val = ToAny<unsigned char>(pAddr);
				val = root.get(strName, 0).asInt();
			}
			break;
		case asInt:
			{
				INT& val = ToAny<INT>(pAddr);
				val = root.get(strName, 0).asInt();
			}
			break;
		case asUInt:
			{
				UINT& val = ToAny<UINT>(pAddr);
				val = root.get(strName, 0).asUInt();
			}
			break;
		case asInt64:
			{
				LONGLONG& val = ToAny<LONGLONG>(pAddr);
				val = root.get(strName, 0).asInt64();
			}
			break;
		case asUInt64:
			{
				ULONGLONG& val = ToAny<ULONGLONG>(pAddr);
				val = root.get(strName, 0).asUInt64();
			}
			break;
		case asDouble:
			{
				double& val = ToAny<double>(pAddr);
				val = root.get(strName, 0).asDouble();
			}
			break;
		case asString:
			{
				string& val = ToAny<string>(pAddr);
				val = root.get(strName, 0).asString();
			}
			break;
		default:
			// 我暂时只支持这几种类型，需要的可以自行添加;
			break;
		}
	}
	return true;
}

Json::Value CJsonObject::DoSpecialArraySerialize(const string& propertyName)
{
	return "";
}

CJsonObject* CJsonObject::GenerateJsonObjForDeSerialize(const string& propertyName)
{
	return NULL;
}

bool CJsonObject::DoArrayDeSerialize(const string& strName, void* pAddr, Json::Value& jsValue, JsonType eType, JsonType eArrType)
{
	if (eType == asVectorArray)
	{
		switch (eArrType)
		{
		case asJsonObj:
			{
				return DoObjArrayDeSerialize<vector<CJsonObject*>>(strName, pAddr, jsValue);
			}
			break;
		case asBool:
			return DoArrayDeSerialize<vector<bool>, bool>(pAddr, jsValue);
			break;
		case asInt:
			return DoArrayDeSerialize<vector<INT>, INT>(pAddr, jsValue);
		case asUInt:
			return DoArrayDeSerialize<vector<UINT>, UINT>(pAddr, jsValue);
		case asInt64:
			return DoArrayDeSerialize<vector<LONGLONG>, LONGLONG>(pAddr, jsValue);
		case asUInt64:
			return DoArrayDeSerialize<vector<ULONGLONG>, ULONGLONG>(pAddr, jsValue);
		case asString:
			return DoArrayDeSerialize<vector<string>, string>(pAddr, jsValue);
		default:
			break;
		}
	}
	else if (eType == asListArray)
	{
		switch (eArrType)
		{
		case asJsonObj:
		{
			return DoObjArrayDeSerialize<list<CJsonObject*>>(strName, pAddr, jsValue);
		}
		break;
		case asBool:
			return DoArrayDeSerialize<list<bool>, bool>(pAddr, jsValue);
		case asInt:
			return DoArrayDeSerialize<list<INT>, INT>(pAddr, jsValue);
		case asUInt:
			return DoArrayDeSerialize<list<UINT>, UINT>(pAddr, jsValue);
		case asInt64:
			return DoArrayDeSerialize<list<LONGLONG>, LONGLONG>(pAddr, jsValue);
		case asUInt64:
			return DoArrayDeSerialize<list<ULONGLONG>, ULONGLONG>(pAddr, jsValue);
		case asString:
			return DoArrayDeSerialize<list<string>, string>(pAddr, jsValue);
		default:
			break;
		}
	}

	return true;
}

Json::Value CJsonObject::DoArraySerialize(void * addr, JsonType listType, JsonType paramType)
{
	if (listType == asVectorArray)
	{
		switch (paramType)
		{
		case asBool:
			return DoArraySerialize((vector<bool>*)addr);
		case asJsonObj:
			return DoArraySerialize((vector<CJsonObject*>*)addr);
		case asInt:
			return DoArraySerialize((vector<INT>*)addr);
		case asUInt:
			return DoArraySerialize((vector<UINT>*)addr);
		case asInt64:
			return DoArraySerialize((vector<LONGLONG>*)addr);
		case asUInt64:
			return DoArraySerialize((vector<ULONGLONG>*)addr);
		case asString:
			return DoArraySerialize((vector<string>*)addr);
		}
	}
	else
	{
		switch (paramType)
		{
		case asBool:
			return DoArraySerialize((list<bool>*)addr);
		case asJsonObj:
			return DoArraySerialize((list<CJsonObject*>*)addr);
		case asInt:
			return DoArraySerialize((list<INT>*)addr);
		case asUInt:
			return DoArraySerialize((list<UINT>*)addr);
		case asInt64:
			return DoArraySerialize((list<LONGLONG>*)addr);
		case asUInt64:
			return DoArraySerialize((list<ULONGLONG>*)addr);
		case asString:
			return DoArraySerialize((list<string>*)addr);
		}
	}
	return "";
}