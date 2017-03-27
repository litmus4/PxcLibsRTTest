#include "TestClasses.h"
#include "HelloWorldScene.h"
#include "PxcUtil/StringTools.h"

using namespace PxcUtil;

void CSubRun::Run()
{
	for (int i = 0; i < 5; ++i)
	{
		Sleep(1000 + i * 10);
		if (m_pHelloWorld)
		{
			m_pHelloWorld->TickSubThread();
		}
	}
}

Platform::String^* CDali::s_pstrOut = nullptr;

CDali::CDali()
{
	//
}

CDali::~CDali()
{
	//
}

void CDali::SetString(Platform::String^* pstrOut)
{
	s_pstrOut = pstrOut;
}

bool CDali::DynFunc(int i)
{
	if (s_pstrOut != nullptr)
	{
		*s_pstrOut = *s_pstrOut +
			ref new Platform::String((L"CDali::DynFunc arg=" + StringTools::BasicToWstr(i) + L"\n").c_str());
	}
	return true;
}

bool CDali::StaFunc(int i)
{
	if (s_pstrOut != nullptr)
	{
		*s_pstrOut = *s_pstrOut +
			ref new Platform::String((L"CDali::StaFunc arg=" + StringTools::BasicToWstr(i) + L"\n").c_str());
	}
	return false;
}