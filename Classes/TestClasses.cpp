#include "TestClasses.h"
#include "HelloWorldScene.h"

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