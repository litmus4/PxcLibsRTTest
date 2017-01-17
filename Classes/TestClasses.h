#pragma once
#include "PxcUtil/Thread.h"

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