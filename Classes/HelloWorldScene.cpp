#include "HelloWorldScene.h"
#include "PxcUtil/CSVTableOperator.h"
#include "PxcUtil/FileManage.h"
#include "PxcUtil/StringTools.h"
#include "PxcUtil/DateTime.h"
#include "PxcUtil/IniFile.h"
#include "PxcUtil/IDPool.h"
#include "PxcUtil/Random.h"
#include "PxcUtil/LogCenter.h"
#include "PxcUtil/md5.h"
#include "SingletonTest.h"
#include "TestClasses.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
	scheduleUpdate();
    
	Platform::String^ strLocalDataPath = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
	PXCU_LOGINST->Init(1, StringTools::WstrToStr((strLocalDataPath + "\\logtest.txt")->Data()).c_str());
	std::string strJie = InitRun1();
    auto label = Label::createWithTTF(strJie, "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
	label->setAnchorPoint(Vec2(0, 1));
    label->setPosition(Vec2(origin.x + 30/*visibleSize.width/2*/,
                            origin.y + visibleSize.height - 10/*label->getContentSize().height*/));
	label->setHorizontalAlignment(TextHAlignment::LEFT);

    // add the label as a child to this layer
    this->addChild(label, 1);

	//-----------------------------------------------
	strJie = InitRun2();
	label = Label::createWithTTF(strJie, "fonts/Marker Felt.ttf", 24);
	label->setAnchorPoint(Vec2(0, 1));
	label->setPosition(Vec2(origin.x + 350, origin.y + visibleSize.height - 10));
	label->setHorizontalAlignment(TextHAlignment::LEFT);
	this->addChild(label, 1);
	//-----------------------------------------------
	strJie = InitThreadMain();
	m_pMainLabel = Label::createWithTTF(strJie, "fonts/Marker Felt.ttf", 24);
	m_pMainLabel->setAnchorPoint(Vec2(0, 1));
	m_pMainLabel->setPosition(Vec2(origin.x + 30, origin.y + 114));
	m_pMainLabel->setHorizontalAlignment(TextHAlignment::LEFT);
	this->addChild(m_pMainLabel, 1);
	m_fMainTime = 0.0f;
	m_iMainCount = 0;
	//-----------------------------------------------
	strJie = InitThreadSub();
	m_pSubLabel = Label::createWithTTF(strJie, "fonts/Marker Felt.ttf", 24);
	m_pSubLabel->setAnchorPoint(Vec2(0, 1));
	m_pSubLabel->setPosition(Vec2(origin.x + 60, origin.y + 114));
	m_pSubLabel->setHorizontalAlignment(TextHAlignment::LEFT);
	this->addChild(m_pSubLabel, 1);
	//-----------------------------------------------
	strJie = InitRun3();
	label = Label::createWithTTF(strJie, "fonts/Marker Felt.ttf", 24);
	label->setAnchorPoint(Vec2(0, 1));
	label->setPosition(Vec2(origin.x + 350, origin.y + 185));
	label->setHorizontalAlignment(TextHAlignment::LEFT);
	this->addChild(label, 1);
	//-----------------------------------------------
	strJie = InitRun4();
	label = Label::createWithTTF(strJie, "fonts/Marker Felt.ttf", 24);
	label->setAnchorPoint(Vec2(0, 1));
	label->setPosition(Vec2(origin.x + visibleSize.width - 350, origin.y + visibleSize.height - 10));
	label->setHorizontalAlignment(TextHAlignment::LEFT);
	this->addChild(label, 1);
	//-----------------------------------------------

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	SAFE_DELETE(m_pSubThread)
	SAFE_DELETE(m_pSubRun)
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

template<typename T>
void OutputArray(std::stringstream& stream, std::vector<T>& vec)
{
	stream << "\t[";
	std::vector<T>::iterator iter = vec.begin();
	for (; iter != vec.end(); iter++)
	{
		if (iter == vec.begin())
			stream << *iter;
		else
			stream << ";" << *iter;
	}
	stream << "]";
}

template<typename T>
void OutputArray(Platform::String^& strOut, std::vector<T>& vec)
{
	strOut = strOut + "\t[";
	std::vector<T>::iterator iter = vec.begin();
	for (; iter != vec.end(); iter++)
	{
		if (iter == vec.begin())
			strOut = strOut + ref new Platform::String(StringTools::BasicToWstr(*iter).c_str());
		else
			strOut = strOut + ref new Platform::String((L";" + StringTools::BasicToWstr(*iter)).c_str());
	}
	strOut = strOut + "]";
}

template<>
void OutputArray(Platform::String^& strOut, std::vector<std::string>& vec)
{
	strOut = strOut + "\t[";
	std::vector<std::string>::iterator iter = vec.begin();
	for (; iter != vec.end(); iter++)
	{
		if (iter == vec.begin())
			strOut = strOut + ref new Platform::String(StringTools::StrToWstr(*iter).c_str());
		else
			strOut = strOut + ref new Platform::String(StringTools::StrToWstr(";" + *iter).c_str());
	}
	strOut = strOut + "]";
}

std::string HelloWorld::InitRun1()
{
	Platform::String^ strOut = "============\n";

	Platform::String^ strInstallPath = Windows::ApplicationModel::Package::Current->InstalledLocation->Path;
	Platform::String^ strLocalDataPath = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
	std::string strFile = StringTools::WstrToStr((strInstallPath + "\\Assets\\Resources\\test2.csv")->Data());
	CCSVTableOperator tabop;
	if (tabop.Load(strFile.c_str()))
	{
		while (tabop.ReadRow())
		{
			int iID;
			if (tabop.GetType("ID") == CCSVTableOperator::ECol_Int && tabop.GetValue("ID", iID))
				strOut = strOut + ref new Platform::String(StringTools::BasicToWstr(iID).c_str());

			std::string strName;
			if (tabop.GetType("Name") == CCSVTableOperator::ECol_String && tabop.GetValue("Name", strName))
				strOut = strOut + ref new Platform::String(StringTools::StrToWstr("\t" + strName).c_str());

			float fHaha;
			if (tabop.GetType("Haha") == CCSVTableOperator::ECol_Float && tabop.GetValue("Haha", fHaha))
				strOut = strOut + ref new Platform::String((L"\t" + StringTools::BasicToWstr(fHaha)).c_str());

			std::vector<int> vecZu1;
			if (tabop.GetType("Zu1") == CCSVTableOperator::ECol_IntArray && tabop.GetArray("Zu1", vecZu1))
				OutputArray(strOut, vecZu1);

			std::vector<std::string> vecZu2;
			if (tabop.GetType("Zu2") == CCSVTableOperator::ECol_StringArray && tabop.GetArray("Zu2", vecZu2))
				OutputArray(strOut, vecZu2);

			std::vector<float> vecZu3;
			if (tabop.GetType("Zu3") == CCSVTableOperator::ECol_FloatArray && tabop.GetArray("Zu3", vecZu3))
			{
				OutputArray(strOut, vecZu3);
				strOut = strOut + "\n";
			}
		}

		tabop.AddColumn("ColEx", CCSVTableOperator::ECol_Int, "-1", "Extend(aaaaaaaaa)");
		tabop.SetValue("ID", 5);
		tabop.SetValue<std::string>("Name", "E,E");
		tabop.SetValue("Haha", 5.5f);
		std::vector<int> vecZu1Save;
		vecZu1Save.push_back(5);
		vecZu1Save.push_back(5);
		tabop.SetArray("Zu1", vecZu1Save);
		tabop.WriteRow();
		strFile = StringTools::WstrToStr((strLocalDataPath + "\\test3.csv")->Data());
		tabop.Save(strFile.c_str());

		strOut = strOut + "\n";
		tabop.Reset();
		if (tabop.Load(strFile.c_str()))
		{
			while (tabop.ReadRow())
			{
				int iID;
				if (tabop.GetType("ID") == CCSVTableOperator::ECol_Int && tabop.GetValue("ID", iID))
					strOut = strOut + ref new Platform::String(StringTools::BasicToWstr(iID).c_str());

				std::string strName;
				if (tabop.GetType("Name") == CCSVTableOperator::ECol_String && tabop.GetValue("Name", strName))
					strOut = strOut + ref new Platform::String(StringTools::StrToWstr("\t" + strName).c_str());

				float fHaha;
				if (tabop.GetType("Haha") == CCSVTableOperator::ECol_Float && tabop.GetValue("Haha", fHaha))
					strOut = strOut + ref new Platform::String((L"\t" + StringTools::BasicToWstr(fHaha)).c_str());

				std::vector<int> vecZu1;
				if (tabop.GetType("Zu1") == CCSVTableOperator::ECol_IntArray && tabop.GetArray("Zu1", vecZu1))
					OutputArray(strOut, vecZu1);

				std::vector<std::string> vecZu2;
				if (tabop.GetType("Zu2") == CCSVTableOperator::ECol_StringArray && tabop.GetArray("Zu2", vecZu2))
					OutputArray(strOut, vecZu2);

				std::vector<float> vecZu3;
				if (tabop.GetType("Zu3") == CCSVTableOperator::ECol_FloatArray && tabop.GetArray("Zu3", vecZu3))
					OutputArray(strOut, vecZu3);

				int iColEx;
				if (tabop.GetType("ColEx") == CCSVTableOperator::ECol_Int && tabop.GetValue("ColEx", iColEx))
				{
					strOut = strOut + ref new Platform::String((L"\t" + StringTools::BasicToWstr(iColEx)).c_str());
					strOut = strOut + "\n";
				}
			}
		}
		else
		{
			strOut = strOut + "CSV3 Load Fail\n";
		}

		FileManage::RemoveFile(StringTools::StrToWstr(strFile).c_str());
		strOut = strOut + "\n";
		tabop.Reset();
		if (!tabop.Load(strFile.c_str()))
		{
			strOut = strOut + "Deleted CSV3 can't be read\n";
		}

	}
	else
	{
		strOut = strOut + "CSV Load Fail\n";
	}

	strOut = strOut + "============\n";
	std::vector<std::wstring> vecFiles;
	FileManage::FindFilesRecursive((strInstallPath + "\\Assets\\Resources\\testdir")->Data(), L"txt", vecFiles);
	std::vector<std::wstring>::iterator itFile = vecFiles.begin();
	for (; itFile != vecFiles.end(); itFile++)
	{
		int ipos = (*itFile).find(L"Assets");
		if (ipos != std::wstring::npos)
			(*itFile) = (*itFile).substr(ipos);
		strOut = strOut + ref new Platform::String((*itFile + L"\n").c_str());
	}
	strFile = StringTools::WstrToStr((strLocalDataPath + "\\Assets\\Resources\\testdir2\\testdir2in\\testinifm.ini")->Data());
	FILE* pfini = FileManage::OpenFileWithCreate(StringTools::StrToWstr(strFile).c_str());
	if (pfini)
	{
		strOut = strOut + "\n";
		char szBuf[128] = "[section1]\nint1=1\n";
		fwrite(szBuf, strlen(szBuf), 1, pfini);
		fclose(pfini);

		IniFile inifm;
		if (inifm.Load(strFile.c_str()))
		{
			int iValue = 0;
			inifm.GetValue("section1", "int1", iValue);
			strOut = strOut + ref new Platform::String((L"testinifm.ini section1 int1 = " + StringTools::BasicToWstr(iValue)).c_str());
			strOut = strOut + "\n";
		}
		else
			strOut = strOut + "testinifm.ini Load Fail\n";

		if (FileManage::RemoveFile(StringTools::StrToWstr(strFile).c_str()))
			strOut = strOut + "testdir2\\testdir2in\\testinifm.ini Deleted\n";
		if (FileManage::RemoveFolder((strLocalDataPath + "\\Assets\\Resources\\testdir2\\testdir2in")->Data()))
			strOut = strOut + "testdir2\\testdir2in Deleted\n";
		if (FileManage::RemoveFolder((strLocalDataPath + "\\Assets\\Resources\\testdir2")->Data()))
			strOut = strOut + "testdir2 Deleted\n";
	}

	strOut = strOut + "============\n";
	CSingleTest::GetInstance()->Do(strOut);
	CSingleTest2::GetInstance()->Do(strOut);
	CSingleTest::DeleteInstance();
	CSingleTest2::DeleteInstance();

	strOut = strOut + "\n============\n";

	return StringTools::WstrToStr(strOut->Data());
}

std::string HelloWorld::InitRun2()
{
	Platform::String^ strOut = "============\n";

	ExactTime::Init();
	strOut = strOut + ref new Platform::String((L"ExactTime: " + StringTools::BasicToWstr(ExactTime::GetSysTick())).c_str());
	strOut = strOut + ref new Platform::String((L" " + StringTools::BasicToWstr(ExactTime::GetPerfTime(ExactTime::ELevel_Second))).c_str());
	strOut = strOut + ref new Platform::String((L"\n" + StringTools::BasicToWstr(ExactTime::GetPerfTime(ExactTime::ELevel_Milli))).c_str());
	strOut = strOut + ref new Platform::String((L" " + StringTools::BasicToWstr(ExactTime::GetPerfTime(ExactTime::ELevel_Micro))).c_str());
	float fTime = ExactTime::GetFloatTime();//TODO 10000 000 000 0
	strOut = strOut + ref new Platform::String((L"\n" + StringTools::BasicToWstr(fTime)).c_str());
	strOut = strOut + "\n";
	DateTimeInfo info;
	long long lDateTime = DateTime::GetDateTime();
	strOut = strOut + ref new Platform::String((L"DateTime: " + StringTools::BasicToWstr(lDateTime)).c_str());
	if (DateTime::InformDateTime(lDateTime, info))
	{
		strOut = strOut + ref new Platform::String((L" " + StringTools::BasicToWstr(info.date.getYear()) +
			L"-" + StringTools::BasicToWstr(info.date.getMonth()) +
			L"-" + StringTools::BasicToWstr(info.date.getDay())).c_str());
		strOut = strOut + ref new Platform::String((L"\n" + StringTools::BasicToWstr(info.iHour) +
			L":" + StringTools::BasicToWstr(info.iMin) +
			L":" + StringTools::BasicToWstr(info.iSec) +
			L" " + StringTools::BasicToWstr(info.date.getWeekday()) +
			L" " + StringTools::BasicToWstr(info.date.getDaysPassedOfYear()) +
			L" " + StringTools::BasicToWstr(DateTime::IntegrateDateTime(info))).c_str());
		strOut = strOut + "\n";
	}

	return StringTools::WstrToStr(strOut->Data());
}

std::string HelloWorld::InitThreadMain()
{
	return "0";
}

std::string HelloWorld::InitThreadSub()
{
	m_pSubRun = new CSubRun(this);
	m_pSubThread = new CThread(m_pSubRun);
	m_pSubThread->Start();

	float fTime = ExactTime::GetFloatTime();
	return StringTools::BasicToStr(fTime);
}

std::string HelloWorld::InitRun3()
{
	Platform::String^ strOut = "============\n";

	CIDPool idpool(0, 10, 3);
	idpool.Declare(3);
	idpool.Declare(5);
	idpool.Declare(9);
	strOut = strOut + "ID Generate : ";//0, 1, 2, 4, 6, 1, 2, 7, 8, 10
	for (int i = 0; i < 5; ++i)
	{
		if (i != 0)
			strOut = strOut + ", ";
		strOut = strOut + ref new Platform::String(StringTools::BasicToWstr(idpool.Generate()).c_str());
	}
	idpool.Free(1);
	idpool.Free(2);
	int iGen = idpool.Generate();
	while (iGen != 3)
	{
		strOut = strOut + ref new Platform::String((L", " + StringTools::BasicToWstr(iGen)).c_str());
		iGen = idpool.Generate();
	}
	strOut = strOut + "\n";

	Random::SetReseedCycle(4);
	strOut = strOut + ref new Platform::String((L"RandomInt : " + StringTools::BasicToWstr(Random::RandInt(-10, 10)) +
		L", " + StringTools::BasicToWstr(Random::RandInt(0, 65536)) +
		L", " + StringTools::BasicToWstr(Random::RandInt(0, 65544))).c_str());
	strOut = strOut + "\n";
	strOut = strOut + ref new Platform::String((L"RandomFloat : " + StringTools::BasicToWstr(Random::RandFloat(0.1f, 0.5f)) +
		L", " + StringTools::BasicToWstr(Random::RandFloat(-10.0f, 10.0f)) +
		L"\n" + StringTools::BasicToWstr(Random::RandFloat(0.1f, 0.5f)) +
		L", " + StringTools::BasicToWstr(Random::RandFloat(-10.0f, 10.0f)) +
		L", " + StringTools::BasicToWstr(Random::RandFloat(0.000001f, 0.0000015f)) +
		L", " + StringTools::BasicToWstr(Random::RandFloat(0.0f, 66666.6f))).c_str());
	strOut = strOut + "\n";
	{
		std::vector<int> vecNormLots;
		for (int i = 0; i < 10; ++i)
			vecNormLots.push_back(i);
		strOut = strOut + "DrawLots : ";
		strOut = strOut + ref new Platform::String(StringTools::BasicToWstr(Random::DrawLots(vecNormLots)).c_str());

		std::vector<std::pair<int, float>> vecProbLots;
		vecProbLots.push_back(std::make_pair(0, -1.0f));
		vecProbLots.push_back(std::make_pair(1, 0.5f));
		vecProbLots.push_back(std::make_pair(2, 0.5f));
		vecProbLots.push_back(std::make_pair(3, 0.1f));
		strOut = strOut + ", ";
		strOut = strOut + ref new Platform::String(StringTools::BasicToWstr(Random::DrawLots(vecProbLots)).c_str());

		std::vector<int> vecResult;
		bool bRet = Random::DrawLots(vecNormLots, 3, vecResult);
		strOut = strOut + ", ";
		for (int i = 0, iSize = vecResult.size(); i < iSize; ++i)
			strOut = strOut + ref new Platform::String((L" " + StringTools::BasicToWstr(vecResult[i])).c_str());

		vecResult.clear();
		bRet = Random::DrawLots(vecProbLots, 2, vecResult);
		strOut = strOut + ", ";
		for (int i = 0, iSize = vecResult.size(); i < iSize; ++i)
			strOut = strOut + ref new Platform::String((L" " + StringTools::BasicToWstr(vecResult[i])).c_str());

		strOut = strOut + "\n";
	}

	return StringTools::WstrToStr(strOut->Data());
}

std::string HelloWorld::InitRun4()
{
	Platform::String^ strOut = "============\n";

	PXCU_LOG_DEBUG(1) << "debug";
	PXCU_LOG(1) << "info";
	PXCU_LOG_WARNING(1, "warning") << "warning";
	PXCU_LOG_ASSERT(1, 1 == 1) << "true";
	PXCU_LOG_ASSERT(1, 1 == 2) << "false";
	PXCU_LOG_ERROR(1, "error") << "error";
	PXCU_LOGINST->Release();

	std::string strStrTest = StringTools::Trim(StringTools::Format("  1%d1%.2f\t", 1, 1.222f));
	float fStrTest = StringTools::StrToBasic<float>(strStrTest);
	strStrTest = StringTools::BasicToStr(fStrTest);
	std::cout << strStrTest << std::endl;
	strOut = strOut + ref new Platform::String((StringTools::StrToWstr(strStrTest) + L" ").c_str());
	std::wstring wstrStrTest = StringTools::Trim(StringTools::Format(L"  1%d1%.2f\t", 1, 1.222f));
	fStrTest = StringTools::WstrToBasic<float>(wstrStrTest);
	wstrStrTest = StringTools::BasicToWstr(fStrTest);
	strOut = strOut + ref new Platform::String((wstrStrTest + L" ").c_str());
	strOut = strOut + ref new Platform::String((StringTools::Format(L"", 1, 2) + L"\n").c_str());

	CMd5 md5;
	md5.TargetStr("sb");
	strOut = strOut + ref new Platform::String((StringTools::StrToWstr(md5.GetDigestKey()) + L"\n").c_str());

	return StringTools::WstrToStr(strOut->Data());
}

void HelloWorld::update(float dt)
{
	if (m_fMainTime >= -0.5f)
	{
		m_fMainTime += dt;
		if (m_fMainTime >= 1.0f)
		{
			if (m_pMainLabel)
			{
				m_pMainLabel->setString(StringTools::BasicToStr(++m_iMainCount));
			}
			if (m_iMainCount >= 5)
				m_fMainTime = -1.0f;
			else
				m_fMainTime -= 1.0f;
		}
	}
}

void HelloWorld::TickSubThread()
{
	float fTime = ExactTime::GetFloatTime();
	m_pSubLabel->setString(StringTools::BasicToStr(fTime));
}
