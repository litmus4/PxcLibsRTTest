#pragma once
#include "PxcUtil/Thread.h"
#include "PxcUtil/Delegate.h"

typedef PxcUtil::CDelegate<bool, int> tDaliGate;

class HelloWorld;
class CSubRun : public PxcUtil::Runnable
{
public:
	CSubRun(HelloWorld* pHello) : m_pHelloWorld(pHello) {}
	virtual ~CSubRun() {}
	virtual void Run();

private:
	HelloWorld* m_pHelloWorld;
};

class CDali
{
public:
	CDali();
	~CDali();
	static void SetString(Platform::String^* pstrOut);
	bool DynFunc(int i);
	static bool StaFunc(int i);

private:
	static Platform::String^* s_pstrOut;
};