#pragma once
#include "PxcUtil/Singleton.h"
#include "PxcUtil/StringTools.h"

using namespace PxcUtil;
using namespace Platform;

class CSingleTest : public PxcUtil::Singleton<CSingleTest>
{
DEFINE_SINGLETON_CONSTRUCTOR(CSingleTest) : m_iData(2) {}
public:
	void Do(String^& strOut)
	{
		strOut = strOut + ref new String((L"Singleton!" + StringTools::BasicToWstr(m_iData)).c_str());
		strOut = strOut + " ";
	}

private:
	int m_iData;
};

class CSingleTest2 : public PxcUtil::Singleton<CSingleTest2>
{
DEFINE_SINGLETON_CONSTRUCTOR(CSingleTest2) : m_iData(4) {}
public:
	void Do(String^& strOut)
	{
		strOut = strOut + ref new String((L"Singleton2!" + StringTools::BasicToWstr(m_iData)).c_str());
	}

private:
	int m_iData;
};