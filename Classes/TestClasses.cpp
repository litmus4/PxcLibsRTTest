#include "TestClasses.h"
#include "HelloWorldScene.h"

void CSubRun::Run()
{
	for (int i = 0; i < 4; ++i)
	{
		Sleep(1000);
		if (m_pHelloWorld)
		{
			m_pHelloWorld->TickSubThread();
		}
	}
}